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
	
	char * token;
	int j = 0;
	token = strtok(input, DE_LIM);
	while(token != NULL){
		tokens[j] = token;
		j++;
		token = strtok(NULL, DE_LIM);
	}
	tokens[j] = NULL;
	return j-1;
}

void handle_unpiped(char** tokens,int input,int output){

		pid_t child_pid;
    		int stat_loc;
		child_pid = fork();
        	if (child_pid == 0) {

			int in,out;
			if(input!=-1){
				in = open(tokens[input], O_RDONLY);
				dup2(in,0);
				close(in);
			}

			if(output!=-1){
			
				out = open(tokens[output],O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				printf("%d",out);
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



