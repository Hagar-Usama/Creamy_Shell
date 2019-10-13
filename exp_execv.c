#include <stdio.h>  // perror()
#include <stdlib.h> // exit(), EXIT_SUCCESS, EXIT_FAILURE , system()
#include <unistd.h> // fork() , execvp()


int main(){

	
	/*
	 * The  execv(),  execvp(),  and  execvpe()  functions provide an array of pointers to null-terminated strings that represent the argument list
       available to the new program.  The first argument, by convention, should point to the filename associated with the file being executed.  The
       array of pointers must be terminated by a null pointer.
      
      * The execle()  and  execvpe() functions allow the caller to specify the environment of the executed program via the argument envp.  The envp
       argument is an array of pointers to null-terminated strings and must be terminated by a null pointer.  The other functions take the environ‐
       ment for the new process image from the external variable environ in the calling process.
       
       *Special semantics for execlp() and execvp()
       The  execlp(),  execvp(),  and  execvpe()  functions duplicate the actions of the shell in searching for an executable file if the specified
       filename does not contain a slash (/) character.  The file is sought in the colon-separated list of directory  pathnames  specified  in  the
       PATH environment variable.  If this variable isn't defined, the path list defaults to the current directory followed by the list of directo‐
       ries returned by confstr(_CS_PATH).  (This confstr(3) call typically returns the value "/bin:/usr/bin".)

       If the specified filename includes a slash character, then PATH is ignored, and the file at the specified pathname is executed.

       In addition, certain errors are treated specially.

       
       
      
	*/
	
	/* int execvp(const char *file, char *const argv[]); */
	char *arg[2];
	arg[0] = "ls";
	arg[1] = NULL;
	
	execvp(arg[0] ,arg);
	wait();
	execvp(arg[0] ,arg);
	printf("*.*.*.*.*.*");
	system("ls");
	



return 0;
}
