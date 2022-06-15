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

void clear(){system("@cls||clear");}

void exec() {
    const char* cmd = "ps aux"; 
    char buffer[128];
    FILE* out = fopen("ps_aux_out", "w+");
    FILE* pipe = popen("ps aux", "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            fprintf(out, "%s\n", buffer);
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    fclose(out);
}


int main(int argc, char const *argv[]){
	clear();
    exec();
	return 0;
}