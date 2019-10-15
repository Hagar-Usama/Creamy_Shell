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


#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


#define LIMIT 50

using namespace std;


void trim(string &str);
// left trim
void ltrim(string &exp);
// right trim
void rtrim(string &exp);
// extract a certain expersion & replaces it by a delimiter
string extract(string &exp , string re , string delim="");
//get matched expersion from a string using regex
int get_matched(string s , regex reg , string &mat);

//write in log file (append)
void write_log(string filename , string str);
//write in a file (w)
void write_dic(string filename , string str);


//signal handler for terminated processes
void handler(int signal){
	
	pid_t pid;
    pid = wait(NULL);
    
	//cout<<"Child process was terminated"<<endl;
	if(pid == -1)write_log("log.txt", "Child process was terminated [foreground]\n");
	else write_log("log.txt", "Child process was terminated [Background]\n");
	
	}	


class Creamy_Shell{
	
	public:
	string command;
	vector<string> args;
	int status;
	
	Creamy_Shell();
	void run_shell();
	
	private:
	//splits parameters of command string
	void split_parameters();
	//trims spaces from command string
	void trim_command();
	//converts the vector of args into array of char**
	void get_arg_list(char* arr[]);
	//calling fork to create a new process
	void call_fork(bool state);
	//call cd command since no need for forking here
	void call_cd();
	
	};

Creamy_Shell::Creamy_Shell(){
		//log file is cleared (initially)
		write_dic("log.txt" ,"");
		//command = "Hello";
	};

void Creamy_Shell::call_cd(){
	
if(args[1][0] == '/'){
			args[1][0] = ' ';
			ltrim(args[1]);			
			}
		chdir((char*)args[1].c_str());
			
	
}

void Creamy_Shell::call_fork(bool state){
	
  
    pid_t   pid;
    int     status;
	
	char *arg[args.size()+1];
	get_arg_list(arg);
		
    
	pid =fork();
	//if we are in the child process >> execute the command
	if (pid == 0) {
	
		
		execvp(arg[0] ,arg); 
	
	//if there is an error >> print it	
	} else if( pid < 0){
		
		perror("Child creation failed\n");
		
	}
	//else, we are in the parent process
	else
	{ 
		 
		//wait my child!! 
		if(state) wait(&status);
		//if(state) for(int i=0 ; i< LIMIT ; i++)	wait(NULL);
			
	} 

};	



void Creamy_Shell::run_shell(){
	
	do{
		
		cout<<BOLDGREEN<<"$~: "<<RESET;	
		getline(cin,command);}while(!command.size());
	
	
	split_parameters();
	
	/*
	for( unsigned int i =0 ; i< args.size() ; i++){
		
		cout<<"** "<< args[i]<<"**" <<endl;
		}
	*/
	
	
	if(!args[0].compare("exit"))
		exit(0);
		
	else if(!args[0].compare("cd")){
		call_cd();
		
	}else if(!args[args.size()-1].compare("&")){
		
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
	
	
	}

void Creamy_Shell::get_arg_list(char* arr[]){
	
	unsigned int j=0;
	for(j =0 ; j<args.size() ; j++)
		arr[j] =(char*)args[j].c_str();
				
	arr[j] = NULL;
	
	}
	
	
	
	
	
	
	
int main(){
		
	Creamy_Shell shell;
	signal(SIGCHLD , handler);
	
	//shell.run_shell();	
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
