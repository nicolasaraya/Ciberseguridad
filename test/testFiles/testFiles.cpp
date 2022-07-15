#include <iostream>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <time.h>

using namespace std;

string path = "./testFiles/files/";

void readFiles(vector<string>* out){
    out->clear();
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            string aux = ent->d_name; 
            //aux.pop_back(); 
            //cout << aux << endl; 
            out->push_back(aux);
            //printf ("%s\n", ent->d_name);
        }
        closedir (dir);
        delete (ent);
    } else {
        perror ("");
        return;
    }
}

string generador(){
    string s; 

    for(int i = 0; i < rand()%10 + 5; i++){
        char c = rand()%10 + 65;
        s+=c;
    }
    return s; 
}





int main(int argc, char const *argv[]){
    srand(time(NULL));
    if(argc != 2) {
        cout << " ./a.out porcentaje "<< endl;
        return 0;
    } 

    vector<string> out; 
    readFiles(&out); 

    //for(auto i : out) cout << i << endl;


    int porc = atoi(argv[1]);

    double x = double(porc) / 100;

    double range =out.size() * x;

    cout << "Archivos a modificar:" << int(range) << endl;

    for(int i = 0; i < int(range); i++){
        if(out.at(i).c_str() == "testFiles.cpp") continue;
        if(out.at(i).c_str() == "a.out") continue;
        
        FILE* f; 
        string s = path + generador();
        string s2 = path + out.at(i);
        remove(s2.c_str());
        f = fopen(s.c_str(), "w+b");
        fprintf(f, "%s\n", "hola");
        fclose(f);

    }

    
    return 0;
}
