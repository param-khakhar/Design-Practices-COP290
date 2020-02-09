#include <stdio.h>
#include<unistd.h>
#include<sys/stat.h>

/* The functions are used for processing the in-built commands.*/

void pwd(){
	char buffer[1000];
	printf("%s\n", getcwd(buffer, 1000)); 
}

int cd(char* path){

	  return chdir(path);	  
}

int make(char* name){
	return mkdir(name,0700);
}

int rmv(char* path){
	return rmdir(path);
}
