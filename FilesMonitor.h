#ifndef FilesMonitor_H
#define FilesMonitor_H
#include <vector>
#include <string>
#include <map> 

using namespace std; 


class FilesMonitor{
    private:
        void exec();
        vector<string> out;
    public:
        FilesMonitor();
        ~FilesMonitor();
};


#endif