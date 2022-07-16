#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "ResourcesMonitor.h"
#include "FilesMonitor.h"
using namespace std; 

void clear(){
    system("@cls||clear");
}


int analyzer(){
    ResourcesMonitor* r = new ResourcesMonitor();
    FilesMonitor* f = new FilesMonitor();

    int count = 0;
    while(1){
        sleep(3);
        //clear();
        cout << "Etapa: " << count++ << endl; 
        if (count == 7) return 1; 
        if(r->ScanResources() && f->ScanFiles()){
            return 1;
        }
        else {
            cout << "Normal" << endl;
        }
    }
}



int main(int argc, char const *argv[]){
    ResourcesMonitor* r = new ResourcesMonitor();
    FilesMonitor* f = new FilesMonitor();
    int damage = analyzer();
    while(damage){
        cout << "Ataque detectado" << endl; 
        sleep(10); 
        //clear();
    }
	return 0;
}