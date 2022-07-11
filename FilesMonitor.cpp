#include "FilesMonitor.h"
#include <iostream>

using namespace std;

FilesMonitor::FilesMonitor(){
    exec();
    for(int i = 0 ; i < out.size(); i++) cout << i << ": " << out.at(i) << endl;
}

FilesMonitor::~FilesMonitor(){}

void FilesMonitor::exec(){
    if(!out.empty()) out.clear();
    const char* cmd = "ls -a"; 
    char buffer[128];
    FILE* outp = fopen("ls_out", "w+");
    FILE* pipe = popen("ls ", "r");
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