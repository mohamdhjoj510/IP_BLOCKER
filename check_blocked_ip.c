#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
	       pid_t pid;
	       pid = fork();
	       char *ipAddress = argv[1];
	       //fork failed
	       if (pid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
	       } 
	       //parent process
	       if(pid>0){
		       int status;
		       wait(&status);
		       int child_exit_status = WEXITSTATUS(status);
		       //exit status value = 1 -> the child process couldnt open the firewall.txt file
		       if(child_exit_status==1){
			       perror("Error opening file");
			       return -1;
		       }
		       //exit status value = 2 -> the child process found ipAddress in the firewall.txt file
		       if(child_exit_status==2){
			       printf("IP Address %s is blocked\n",ipAddress);
			       return 0;
		       }
		       //exit status value = 3 -> the child process not found ipAddress in the firewall.txt file
		       if(child_exit_status==3){
			       printf("IP Address %s is not blocked\n",ipAddress);
			       return 1;
	       }
             }
	       //child process
	       if(pid==0){
		       FILE *myFile;
		       char blocked_ip_fileName[] = "firewall.txt";
		       //open firewall.txt file for reading each IP_ADDRESS
		       myFile=fopen(blocked_ip_fileName,"r");
		       //cant open the file -> return to the parent process with exit_value = 1
		       if(myFile==NULL){
			      exit(1);
		       } 
		       char file_lines[100];
		       //check each line (ip) in the firewall.txt file 
		       while(fgets(file_lines,sizeof(file_lines),myFile)!=NULL){
	           	//remove newline character from file_lines
                       file_lines[strcspn(file_lines, "\n")] = '\0';
                       // check if the current ipAddress in the file is the same as the given ipAddress
                       if (strcmp(file_lines, ipAddress) == 0) {
                                fclose(myFile);
				exit(2); // ipAddress found return to the parent process with exit_value=2
			}
                    }
		      
		       exit(3); // the given ipAddress not found in the firewall.txt file
			       // return to the parent process with exit_value=3    
	       }
	    }


