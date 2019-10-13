///////////////////////////////////////////////////////////////////////
//////////////// Hagar Usama            ///////////////////////////////
////////////////  4970                  /////////////////////////////// 
////////////////  LAB 1 : Simple Shell  ///////////////////////////////
////////////////  Date : 13/10          ///////////////////////////////
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <fstream>
#include <regex> 
#include <unistd.h>
#include <sys/wait.h>  
#include <vector>

#define LIMIT 50

using namespace std;


void trim(string &str);
void ltrim(string &exp);
void rtrim(string &exp);
string extract(string &exp , string re , string delim="");
int get_matched(string s , regex reg , string &mat);

void write_log(string filename , string str);
void write_dic(string filename , string str);

void handler(int signal){
	
	write_log("log.txt", "Child process was terminated\n");
	//cout<<"Child process was terminated"<<endl;
	
	}	


class Creamy_Shell{
	
	public:
	string command;
	vector<string> args;
	Creamy_Shell();
	void run_shell();
	
	private:
	void split_parameters();
	void trim_command();
	void get_arg_list(char* arr[]);
	void call_fork(bool state);
	
	
	};

Creamy_Shell::Creamy_Shell(){
		write_dic("log.txt" ,"");
	};


void Creamy_Shell::call_fork(bool state){
	pid_t child;
	char *arg[args.size()+1];
	get_arg_list(arg);
		
	
	child =fork();
	if (child == 0) {
		
		execvp(arg[0] ,arg); 
	} else if( child < 0){
		
		perror("Child creation failed\n");
		
	}
	else
	{ 
		 
		//wait my child!! 
		if(state) for(int i=0 ; i< LIMIT ; i++)	wait(NULL);
			
	} 

};	


void Creamy_Shell::run_shell(){
	
	signal(SIGCHLD , handler);
	do{cout<<"$~: ";	
	getline(cin,command);}while(!command.size());
	
		
	split_parameters();
	
	if(!args[0].compare("exit"))
		exit(0);
		
	else if(!args[0].compare("cd"))
		chdir((char*)args[1].c_str()); /* error handling!! and mind the '/' */
	else if(!args[args.size()-1].compare("&")){
		//printf("background");
		args.pop_back();
		call_fork(false);
	}else
		call_fork(true);
	
		
	}
	

	
void Creamy_Shell::trim_command(){
	ltrim(command);
    rtrim(command);
    extract(command , "\\s+" , " ");
	}
		
void Creamy_Shell::split_parameters(){
   
   args.clear();
   //trim_command();
   char *token;
   
   //splitting by space
   token = strtok((char*)command.c_str(), " ");
   while( token != NULL ) {
	   args.push_back(string(token));
	   token = strtok(NULL, " ");
   }
	
	//cout<<"showing args**"<<endl;
	 for(unsigned int i; i< args.size() ; i++){
		 cout<<"---"<<args[i]<<"---"<<endl;
		 }
	}

void Creamy_Shell::get_arg_list(char* arr[]){
	
	unsigned int j=0;
	for(j =0 ; j<args.size() ; j++)
		arr[j] =(char*)args[j].c_str();
				
	arr[j] = NULL;
	
	}
	
	
	
	
	
	
	
int main(){
	
	Creamy_Shell shell;
	while(1){
		shell.run_shell();	
		}
	
	
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

void write_log(string filename , string str){

	  FILE *fp;
	
		fp = fopen(filename.c_str(),"a");
		if(fp == NULL) {
		perror("Error");
		exit(1);
		}
		else{
			
				fprintf (fp, "%s", str.c_str() );
			}
		
  fclose(fp);

	}


void write_dic(string filename , string str){

	  FILE *fp;
	
		fp = fopen(filename.c_str(),"w");
		if(fp == NULL) {
		perror("Error");
		exit(1);
		}
		else{
			
				fprintf (fp, "%s", str.c_str() );
			}
		
  fclose(fp);

	}
