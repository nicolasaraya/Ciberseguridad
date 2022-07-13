#include "FilesMonitor.h"
#include <iostream>
#include <dirent.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

FilesMonitor::FilesMonitor(){
    readFiles();
    createMap();
    dataPrev = dataNow; 
    //printMap(dataPrev);
}

FilesMonitor::~FilesMonitor(){}

void FilesMonitor::readFiles(){
    out.clear();
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            out.push_back(ent->d_name);
            //printf ("%s\n", ent->d_name);
        }
        closedir (dir);
        delete (ent);
    } else {
        perror ("");
        return;
    }
}


void FilesMonitor::createMap(){
    dataNow.clear();

    for(auto i : out){
        dataNow.insert(make_pair(i, 1));
    }
}

void FilesMonitor::printMap(map<string, int> mp){
    for(auto i : mp){
        cout << i.first << "  " << i.second << endl;
    }
}

void FilesMonitor::ScanFiles(){
    readFiles();
    //exec();
    createMap();

    for(auto i : out) cout << i << endl;

    int newFiles = 0;
    int deletedFiles = 0;
    int filesPrev = dataPrev.size();
    int filesNow = dataNow.size();

    for(auto i : dataNow) {
        if(dataPrev.count({i.first}) == 0) newFiles++;
    }

    for(auto j : dataPrev){
        if(dataNow.count({j.first}) == 0) deletedFiles++;
    }

    cout << "New: " << newFiles << " Deleted: " << deletedFiles << endl;
    cout << "Num of files: " << filesNow << ", Num of files before: " << filesPrev << endl;
    cout << "Damage: " << damage(newFiles, deletedFiles) << "% "<< endl;
    dataPrev = dataNow; 
}

double FilesMonitor::damage(int newF, int deletedF){
    int filesPrev = dataPrev.size();
    int filesNow = dataNow.size();


    if(deletedF > double(filesPrev)*0.5 ){
        cout << "se han modificado la mitad de archivos" << endl; 
        sleep(10);
        return 100; 
    }
    return 0;




}