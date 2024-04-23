#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    pid=fork();
    //fork failed
    if (pid == -1) {
        perror("error in fork");
        exit(EXIT_FAILURE);
    }
    char *ipAddress_toBlock = argv[1];
    if(pid>0){
	    int status;
            wait(&status);
            int child_exit_status = WEXITSTATUS(status);
	    if(child_exit_status==0){
		     perror("Error opening file");
		     return -1;
	    }
	    //child process exited with 1 value which means the ip is already exist in the firewall file .
	    if(child_exit_status==1){
		    printf("IP Address %s is blocked\n",ipAddress_toBlock);
		    return 0;
	    }
	     //child process exited with 2 value which means the ip is added successfully to the firewall file
	    if(child_exit_status==2){
		    printf("IP Address %s is not blocked\n",ipAddress_toBlock);
		    printf("IP Address %s was successfully added to the blocked list\n",ipAddress_toBlock);
		    return 1;
	    }
    }
    if(pid==0){
	//move child process to writeToFile program to check and write the ipAddress to the firewall.txt file
        char *args[] = {"writeToFile","firewall.txt",ipAddress_toBlock , NULL};
	execv("./writeToFile",args);
	perror("error in execv");
   }
	    
}
