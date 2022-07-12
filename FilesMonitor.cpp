#include "FilesMonitor.h"
#include <iostream>
#include <dirent.h>

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

    cout << "***" << endl;
    //printMap(dataNow); 
    cout << "***" << endl; 
    //printMap(dataPrev);

    dataPrev = dataNow; 
}