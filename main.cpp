#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "ResourcesMonitor.h"
#include "FilesMonitor.h"
using namespace std; 

void clear(){system("@cls||clear");}

int main(int argc, char const *argv[]){


    ResourcesMonitor* r = new ResourcesMonitor();
    FilesMonitor* f = new FilesMonitor();
    

    int count = 0;
    while(1){
        clear();
        cout << "Etapa: " << count++ << endl; 
        //if(r->ScanResources()) break;
        f->ScanFiles();
        sleep(1);
        getchar();
    }

	return 0;
}