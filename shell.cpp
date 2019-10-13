#include <iostream>
#include <fstream>
#include <ctype.h>
#include <regex>
#include <cstdio>
#include <cstdlib> // exit(), EXIT_SUCCESS, EXIT_FAILURE , system()
#include <unistd.h> // fork() , execvp()

#include <sys/wait.h> 
#include <unistd.h> 
#include <string>
#include <iostream>
#include <vector> // vector
#include <ctype.h>
//#include <regex.h>

using namespace std;


void trim(string &str);
void ltrim(string &exp);
void rtrim(string &exp);
string extract(string &exp , string re , string delim="");
int get_matched(string s , regex reg , string &mat);

class Creamy_Shell{
	
	public:
	string command;
	vector<string> args;
	Creamy_Shell();
	void run_shell();
	void split_parameters();
	void trim_command();
	void get_arg_list(char* arr[]);
	void call_fork();
	
	};

Creamy_Shell::Creamy_Shell(){
	//args.push_back("ls");
	//args.push_back("-l");
	
	};
	
void Creamy_Shell::call_fork(){
	
	char *arg[args.size()+1];
	get_arg_list(arg);
	
	if (fork()== 0) {
		//get into child process >> execute here
		//printf("HC: hello from child\n");	
		// call is generic for both commands with/without args
		execvp(arg[0] ,arg); 
	} else
	{ 
		//printf("HP: hello from parent\n"); 
		//wait my child
		wait(NULL); 
		printf("CT: child has terminated\n"); 
	} 

}	

void Creamy_Shell::run_shell(){
	
	
	string buffer;
	while(1){
		
	cout<<"$ ";	
	getline(cin,buffer);
	trim(buffer);
	if(buffer.size()){
		command = buffer;
		split_parameters();
		call_fork();
	
		}
	
		
		
		}
	
	
	}
	
void Creamy_Shell::trim_command(){
	ltrim(command);
    rtrim(command);
    extract(command , "\\s+" , " ");
	}
		
void Creamy_Shell::split_parameters(){
   
   args.empty();
   trim_command();
   char *token;
   
   //splitting by space
   token = strtok((char*)command.c_str(), " ");
   while( token != NULL ) {
	   
	   args.push_back(string(token));
	   token = strtok(NULL, " ");
	   
   }
	
	}

void Creamy_Shell::get_arg_list(char* arr[]){
	
	unsigned int j=0;
	for(j =0 ; j<args.size() ; j++){
		//char* strcpy(char* dest, const char* src);
		arr[j] =(char*)args[j].c_str();
				
		}
	arr[j] = NULL;
	
	}
	
	
	
	
	
	
	
int main(){
	
	Creamy_Shell shell;
	
	shell.run_shell();
	
	return 0; 
}



void trim(string &str){
		 
		 if(str.size()){
			regex ret(".[^\\s]+");
		    get_matched(str,ret,str);
			}

		 
		 }


int get_matched(string s , regex reg , string &mat){
	smatch match;
	if(regex_search(s,match,reg) == true){
		mat = match.str(0);
		return 1;
		}
	return 0;
	
		 }
		 
string extract(string &exp , string re , string delim){
		 
		regex reg(re);
		string matched;
		get_matched(exp, reg , matched);
		trim(matched);
		exp = regex_replace(exp,reg, delim);
		return matched;
		 }




void ltrim(string &exp){
		regex reg("^\\s*");
		string mat;
		get_matched(exp , reg,mat);
		exp = regex_replace(exp,reg,"");
	 }

 
 void rtrim(string &exp){
	regex reg("(\\s*)$");
	string mat;
	get_matched(exp ,reg,mat);
	exp = regex_replace(exp,reg,"");
		 
		 }
