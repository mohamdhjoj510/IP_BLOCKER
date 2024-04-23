#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char *argv[]){
	char *fileName = argv[1];
	char *ipToBlock = argv[2];
        FILE *myFile;
         //open firewall.txt file for reading each IP_ADDRESS
         myFile=fopen(fileName,"r");
         //cant open the file -> return to the parent process with exit_value = 0  
         if(myFile==NULL){
                     exit(0);
	 }
         char file_lines[100];
         while(fgets(file_lines,sizeof(file_lines),myFile)!=NULL){
          //remove newline character from file_line
          file_lines[strcspn(file_lines, "\n")] = '\0';
          // check if the current ipAddress in the file is the same as the given ipAddress
          if (strcmp(file_lines, ipToBlock) == 0) {
                   fclose(myFile);
                   exit(1); // ipAddress found return to the parent process with exit_value=1
               }
           }
	myFile = fopen(fileName , "a");
	//cant open the file -> return to the parent process with exit_value = 0
	if(myFile==NULL){
		exit(0);
        }
	//write the IP_ADDRESS to block to the firewall.txt file 
	if(myFile!=NULL){
		fprintf(myFile,"%s\n",ipToBlock);
		fclose(myFile);
		exit(2);	
}
}
