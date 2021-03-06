#include <iostream>
#include <unistd.h>
#include "ResourcesMonitor.h"

using namespace std; 

ResourcesMonitor::ResourcesMonitor(){
    exec();
    createMap();
    datosPrev = datos; 
}

void ResourcesMonitor::exec() { //escribe cada linea en el vector
    if(!out.empty()) out.clear();
    const char* cmd = "ps aux"; 
    char buffer[128];
    FILE* outp = fopen("./out/ps_aux_out", "w+");
    FILE* pipe = popen("ps aux", "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            out.push_back(buffer);
            fprintf(outp, "%s\n", buffer);
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    fclose(outp);
}

void ResourcesMonitor::createMap(){
    datos.clear();
    string temp = out.at(out.size()-1); 
    //cout << temp << endl; 
    bool a=false;
    bool b=false;
    int pos=0;
    while(!b){
        pos++;
        if(temp[pos] >= 48 && temp[pos] <= 57) a = true;
        if(a == true && temp[pos] == ' ') b = true; 
    }
    //cout << pos << " " << temp[pos-1] << temp[pos-2]  << endl; 

    for(auto i : out){
        if(i[0]=='U') continue;
        string aux = "";
        int pid;
        float cpuUse;
        float memoryUse;

        int x = 1; 
        while(i[pos-x]>= 48 && i[pos-x] <= 57) {
            aux+=i[pos-x];
            x++;
        }
        for(int i = 0; i < aux.size()/2; i++) swap(aux[i], aux[aux.size()-i-1]);

        pid = atoi(aux.c_str());
        if(pid==0) continue;
        int posPoint = pos;
        while(i[posPoint]!='.') posPoint++;

        aux=""; 
        aux+=i[posPoint-1];
        aux+=i[posPoint];
        aux+=i[posPoint+1];
        cpuUse = atof(aux.c_str());


        posPoint++;
        while(i[posPoint]!='.') posPoint++;
        aux="";
        aux+=i[posPoint-1];
        aux+=i[posPoint];
        aux+=i[posPoint+1];
        memoryUse = atof(aux.c_str());

        //cout << i;
        //cout << pid << " "<< cpuUse <<" " <<aux << endl;

        Data* d = new Data();
        d->cpu = cpuUse; 
        d->memory = memoryUse;
        datos.insert(make_pair(pid, d));
    }
}

bool ResourcesMonitor::ScanResources(){
    bool flag = false;
    exec();
    createMap();

    int count = 0; 
    for(auto i : datos){
        int pid = i.first;
        Data* infoAct = i.second; 
        Data* infoPrev = datosPrev[{pid}]; 
            
        if(infoAct==NULL) continue; 
        
        if(infoPrev == NULL) continue; 
        
        if(infoAct->memory - infoPrev->memory > 3 ) {
            pidDang.push_back(pid);
            flag=true;
        }

        
    }
    datosPrev = datos; 

    if(flag) {
        cout << "Resources anomaly" << endl; 
        cout << "Uso alto de memoria\n PID: " << endl; 
        for(auto i : getPid()){
            cout << i << endl;                 
        }
        sleep(3);
        return true;
    }
    
    return false;
}


void ResourcesMonitor::printCommand(){
    for(auto i : out) cout << i << endl;
}

vector<int> ResourcesMonitor::getPid(){
    return pidDang;
}