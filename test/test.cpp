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
	
    getchar();
    
    long long int x = 25000000;
    if(argc!=2) return 0;
    int n = atoi(argv[1]);

    cout << n << " gb" << endl;
    vector<int> v(x*10*n,0); //n gb

    getchar();
   
	return 0;
}