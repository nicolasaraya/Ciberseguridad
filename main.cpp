#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "ResourcesMonitor.h"
#include "FilesMonitor.h"
using namespace std; 

void clear(){system("@cls||clear");}


int analyzer(){
    ResourcesMonitor* r = new ResourcesMonitor();
    FilesMonitor* f = new FilesMonitor();

    int count = 0;
    while(1){
        clear();
        cout << "Etapa: " << count++ << endl; 
        if(r->ScanResources()){
            cout << "Uso alto de memoria\n PID: " << endl; 
            for(auto i : r->getPid()){
                cout << i << endl;                 
            }
        }
        

        f->ScanFiles();


        sleep(3);
        //getchar();
    }






}



int main(int argc, char const *argv[]){
<<<<<<< HEAD
<<<<<<< HEAD
	//clear();
    ResourcesMonitor* r = new ResourcesMonitor();
    FilesMonitor* f = new FilesMonitor();
=======
=======
>>>>>>> 6caeac0ff0c829072d0fabc76f05475d6a39dc52



    int damage = analyzer();
<<<<<<< HEAD
>>>>>>> 6caeac0ff0c829072d0fabc76f05475d6a39dc52
=======
>>>>>>> 6caeac0ff0c829072d0fabc76f05475d6a39dc52
    
	return 0;
}