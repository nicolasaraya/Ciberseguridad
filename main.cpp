#include <iostream>
#include <vector>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include <cstring>
#include <fstream>

using namespace std; 

string now; 
//int c = 0;			

void clear();
vector<const char*> parsing(string);
void exec(vector<const char*>);

void clear(){system("@cls||clear");}


vector<const char*> parsing(string s){
	vector<const char*> args; 
	vector<string> commands;
	string aux = ""; 
	for(auto i : s){
		if(i != ' ' ) aux+=i;
		else{
			commands.push_back(aux);
			aux = "";
		}
	}
	commands.push_back(aux);
	for(int i = 0; i < commands.size(); i++) args.push_back(commands[i].c_str());
	return args;
}

void exec(string com){
	now = "";
	vector<const char*> arg = parsing(com);
	char *args[arg.size()+1];
	for(int i = 0; i < arg.size(); i++) args[i] = (char*)arg[i];
	args[arg.size()]=NULL;
	
	int pid = fork();
	if(pid<0) cout << "error" << endl;
	else if (pid == 0) {
		execvp(args[0], args);
		perror("comando no existente");
		exit(EXIT_FAILURE);	
	}
	else wait(NULL);
	return;
}

int main(int argc, char const *argv[]){
	clear();
    if(argc!=2) return 0; 
	exec(argv[1]);
	return 0;
}