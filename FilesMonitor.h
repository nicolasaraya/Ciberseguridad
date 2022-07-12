#ifndef FilesMonitor_H
#define FilesMonitor_H
#include <vector>
#include <string>
#include <map> 

using namespace std; 


class FilesMonitor{
    private:
        string path = "./testFiles";
        map<string, int> dataNow;
        map<string, int> dataPrev; 
        vector<string> out;
        void readFiles();
        void createMap();
        void exec();
        void printMap(map<string, int>);
    public:
        FilesMonitor();
        ~FilesMonitor();
        void ScanFiles();
};


#endif