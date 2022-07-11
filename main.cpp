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
#include <chrono>
#include <thread>
#include "ResourcesMonitor.h"
#include "FilesMonitor.h"

using namespace std; 

void clear(){system("@cls||clear");}

int main(int argc, char const *argv[]){
	//clear();

    ResourcesMonitor* r = new ResourcesMonitor();
    FilesMonitor* f = new FilesMonitor();
    bool flag = true;
    while(!flag){
        //if(r->ScanResources()) flag = true;


    }

	return 0;
}