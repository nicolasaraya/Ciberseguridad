#include <iostream>
#include <vector>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std; 

typedef struct{
    float cpu;
    float memory;
}Data;

void clear(){system("@cls||clear");}

void exec(vector<string>* output) {
    if(!output->empty()) output->clear();
    const char* cmd = "ps aux"; 
    char buffer[128];
    FILE* out = fopen("ps_aux_out", "w+");
    FILE* pipe = popen("ps aux", "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            output->push_back(buffer);
            fprintf(out, "%s\n", buffer);
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    fclose(out);
}

void createMap(vector<string>* out, map<int, Data*>* datos){
    string temp = out->at(out->size()-1); 
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



    for(auto i : *out){
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
        datos->insert(make_pair(pid, d));
    }
}


int main(int argc, char const *argv[]){
	//clear();
    vector<string> out;
    map<int, Data*> datos;
    exec(&out);
    createMap(&out, &datos);
    string s = out.at(1); 


    for(auto i : datos){
        cout << "PID: "; 
        cout << fixed << setfill(' ') << setw(5) << i.first;
        cout << " | CPU Usage: " ;
        cout << fixed << setfill(' ')  << setw(4) << setprecision(1) << i.second->cpu ;
        cout << " | Memory Usage: ";
        cout << fixed << setfill(' ')  << setw(4) << setprecision(1) << i.second->memory << endl;
    }

    //cout << out.at(0);
    //cout << out.at(3);

	return 0;
}