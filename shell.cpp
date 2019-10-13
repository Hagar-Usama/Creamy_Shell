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
	void run_shell();
	void split_parameters();
	
	
	};

void Creamy_Shell::run_shell(){
	
	
	
	
	}

int main(){
	
	string buffer;
	getline(cin,buffer);
	
	vector <string> args;
	
	//cout<<buffer;
 
    ltrim(buffer);
    rtrim(buffer);
    
    //arguments are separated by just one space
    extract(buffer , "\\s+" , ";");
    cout<<buffer;
	
	string command = "firefox";
	char *arg[2];
	arg[0] =(char*)command.c_str();
	arg[1] = NULL;
	
	/*
	string matched;
	while(buffer.size() > 0){
		matched = extract(buffer, "");
		args.push_back(matched);
		
		}
		
	cout<<endl;
	for (int i=0 ; i<args.size() ; i++)
	{
		cout<<args[i]<<endl;
		
		}
	*/
	
   char *token;
   token = strtok((char*)buffer.c_str(), ";");
   
   cout<<endl;
   while( token != NULL ) {
	   cout<<token<<endl;
	   args.push_back(string(token));
	   token = strtok(NULL, ";");
	   
   }
	
	cout<<endl;
	
	for (unsigned int i=0 ; i<args.size() ; i++)
	{
		cout<<args[i]<<endl;
		
		}
	
		
	int i = 5;
	while(0){
		
		
		
    if (fork()== 0) {
		//get into child process >> execute here
		printf("HC: hello from child\n");
		execvp(arg[0] ,arg); 
	} else
	{ 
		printf("HP: hello from parent\n"); 
		//wait my child
		wait(NULL); 
		printf("CT: child has terminated\n"); 
	} 

		
	i--;	
		
		}
	
	printf("Bye\n"); 
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
		//cout<<"<"<<exp<<"<"<<endl;
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
