#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>   
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define DE_LIM " \t\a\n"

int process(char* input, char** tokens){

/* This function is used for separating the input into tokens. The various separator values are \n,\t,\a and white space.
   The return value of the function is the number of tokens.*/ 
	
	char * token;
	int j = 0;
	token = strtok(input, DE_LIM);
	while(token != NULL){
		tokens[j] = token;
		j++;
		token = strtok(NULL, DE_LIM);
	}
	tokens[j] = NULL;
	return j;
}

void handle_unpiped(char** tokens,int input,int output){

	/* This function is called when there aren't any pipes and input/output redirections are involved.
	   The presence of the input and output files are indicated by the values of the variables input and 
    	   output. File opening and closing is involved and execvp() is used to execute the files. 

	   All the above stuff is done in a child process which is created by using fork(). The parent process waits
	   until the child process finishes its execution.*/
		
		pid_t child_pid;
    		int stat_loc;
		child_pid = fork();
        	if (child_pid == 0) {

			int in,out;
			if(input!=-1){
				in = open(tokens[input], O_RDONLY);
				/*Duplicating in to 0*/
				dup2(in,0);
				close(in);
			}

			if(output!=-1){
			
				out = open(tokens[output],O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				
				if(out<0){
					out = creat(output , 0644) ;
				}
				dup2(out,1);
				close(out);
			}

            		execvp(tokens[0], tokens);

			} 
			else {
            			waitpid(child_pid, &stat_loc, WUNTRACED);
        		}
	return;	
}

int command(int input, int output, int cmd, int fd, int first, int last, char** tokens){

	/* This is called as a supplementary function for the case when pipelining is involved. It executes a particular file
	   and stores the input and output in the array pipeline with the help of function dup2(). There are three cases 

	   	1. The command is the first command, has to read input from the file.
		2. The command is last command has to output to the console or another file.
		3. The command is a middle command, i.e the input has to be read from the previous file and the output
		is to be provided as an input to the next file. 
	*/	
	
		int pipeline[2];
		pipe(pipeline);
		pid_t child_pid;
    		int stat_loc;
		child_pid = fork();
        	if (child_pid == 0) {

			int in,out;
			if(first == 1){
				if(input!=-1){
					in = open(tokens[input], O_RDONLY);
					dup2(in,STDIN_FILENO);
					close(in);
				}
				dup2(pipeline[1], STDOUT_FILENO);				
			}

			else if(last == 1){
				if(output!=-1){
			
					out = open(tokens[output],O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
					if(out<0){
						out = creat(output , 0644) ;
					}
					dup2(out,STDOUT_FILENO);
					close(out);
				}
				dup2(fd,STDIN_FILENO);
			}
			
			else{
				dup2(fd,STDIN_FILENO);
				dup2(pipeline[1],STDOUT_FILENO);
			}
		execvp(tokens[cmd], tokens);
		} 
		else {
            			waitpid(child_pid, &stat_loc, WUNTRACED);
        	}
	if(fd != 0){
		close(fd);
	}
	close(pipeline[1]);
	if(last == 1){
		close(pipeline[0]);
	}
	return pipeline[0];
}

int handle_piped(char ** array, int n, int input, int output){

	/* This is the function which is called for executing the piped commands. An iteration is performed over all the pipes and the command()
	function is used to execute the individual file.*/
	
	int cmd = 0;
	int first = 1;
	int last = 0;
	int res = 0;
	for(int i = 0;i<n;i++){
		if(strcmp(array[i], "|") == 0){
			res = command(input,output,cmd,res,first,last,array);
			cmd = i+1;
			first = 0;
		}
	}
	last = 1;
	res = command(input,output,cmd,res,first,last,array);

	return 0;
}



