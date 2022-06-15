#include <iostream>
#include <vector>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <cstring>
#include <fstream>

using namespace std; 

struct Data{
    float cpu;
    float memory;
};

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

void createMap(vector<string>* out, map<int, Data>* datos){
    for(auto i : *out){
        if(i[0]=='U') continue;
        string aux = "";
        int pid;
        float cpuUse;
        float memoryUse; 
        aux+=i[11];
        aux+=i[12];
        aux+=i[13]; 
        pid = atoi(aux.c_str());

        aux=""; 
        aux+=i[15];
        aux+=i[16];
        aux+=i[17];
        cpuUse = atof(aux.c_str());

        aux="";
        aux+=i[19];
        aux+=i[20];
        aux+=i[21];
        memoryUse = atof(aux.c_str());
        cout << i;
        cout << pid << " "<< cpuUse <<" " <<memoryUse << endl;

    }
}


int main(int argc, char const *argv[]){
	//clear();
    vector<string> out;
    map<int, Data> datos;
    exec(&out);
    createMap(&out, &datos);
    string s = out.at(1); 
    cout << out.at(2);
    cout << out.at(3);

	return 0;
}