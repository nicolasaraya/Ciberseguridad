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
#include <math.h>

using namespace std; 


int main(int argc, char const *argv[]){
    if(argc<1) return 0; 
    int n = atoi(argv[1]);
	if(argc == 3) cout << "Pulse una tecla para reservar "<< n <<" gb de memoria " << endl; 
    if(argc == 3) getchar();
    long long int x = 25000000;
    if(argc!=2) return 0;
    cout << "Se reservaron " << n << " gb" << endl;
    vector<int> v(x*10*n,0); //n gb

    if(argc == 3) cout << "Pulse una tecla para salir " << endl;
    getchar();
   
	return 0;
}