// C program to demonstrate working of wait()
#include <sys/wait.h> 
#include <unistd.h> 
#include <string>
#include <iostream>
#include <fstream>
#include <ctype.h>

using namespace std;

int main() 
{ 
	
//char *cmd[] = { "ls", "-A", (char *)0 };

    string command = "ls";
	char *arg[2];
	arg[0] =(char*)command.c_str();
	arg[1] = NULL;
	
	
	int i = 5;
	while(i){
		
		
		
    if (fork()== 0) {
		printf("HC: hello from child\n");
		execvp(arg[0] ,arg); 
	} else
	{ 
		printf("HP: hello from parent\n"); 
		wait(NULL); 
		printf("CT: child has terminated\n"); 
	} 

		
	i--;	
		
		}
	
	printf("Bye\n"); 
	return 0; 
} 
