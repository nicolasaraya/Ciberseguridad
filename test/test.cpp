#include <iostream>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <time.h>

using namespace std;

string path = "./test/files/";

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
    
    if(argc != 3) {
        cout << " ./a.out porcentaje gb"<< endl;
        return 0;
    } 
    
    int n = atoi(argv[2]);
    int porc = atoi(argv[1]);
    cout << "Pulse una tecla para reservar "<< n <<" gb de memoria y modificar el " << porc << "%" << " de archivos" << endl; 
    getchar();

    vector<string> out; 
    readFiles(&out); 
    long long int x = 25000000;
    vector<int> v(x*10*n,0); //n gb
    cout << "Reservando y renombrando" << endl;
    
    double aux = double(porc) / 100;

    double range =out.size() * aux;

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
    cout << "Pulse una tecla para salir" << endl;
    getchar();
    
    return 0;
}
