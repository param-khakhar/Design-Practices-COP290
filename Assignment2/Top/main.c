#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>   
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_LIMIT 20

extern pwd();
extern cd();
extern process();
extern rmv();
extern make();
extern Read();
extern handle_unpiped();
extern handle_piped();
extern command();

int main() {

	char* characters;
	int n;
	while(1){
		printf("shell> ");

	/* The input string parsing is done in the following lines. The different separators which are used 
	   are \n,\a,\t and white space. The correspoding tokens are stored in tokens. */
		char *buffer;
    		size_t bufsize = 32;
    		size_t characters;
		char ** tokens = malloc(64*sizeof(char*));
    		buffer = (char *)malloc(bufsize * sizeof(char));
    		characters = getline(&buffer,&bufsize,stdin);
		n = process(buffer,tokens);
		
		char* builtIns[5];
		builtIns[0] = "pwd";
		builtIns[1] = "cd";
		builtIns[2] = "exit";
		builtIns[3] = "mkdir";
		builtIns[4] = "rmdir";
		int i = -1;

		/* Built-ins is used to detect the presence of any built-in commands such as cd, mkdir, rmdir pwd, and exit.
		   The corresponding commands are identified and they are executed in the corresponding if-else block. The
		   functions are present in the file builtins.c and they are imported. */

		for(int j=0;j<5;j++){
			if (strcmp(tokens[0], builtIns[j]) == 0) { 
            			i = j; 
            			break; 
        		} 
    		}

		if(i == 0){
			pwd();
		}		
		else if(i == 1)
		{
			cd(tokens[1]);
		}
		else if(i == 2){
			exit(0);
		}
		else if(i == 3){
			for(int i=1;i<n;i++){
				make(tokens[i]);
			}
		}
		else if(i == 4){
			for(int i=1;i<n;i++){
				rmv(tokens[i]);
			}
		}
		else{
	//		Detecting the presence of any input,output and pipes in the input. i.e detecting the symbols <, >, and |. The
	//		variables pi, input and output are indicative of the symbols. Piped and unpiped commands are handled separately.
			int pi = -1;
			int input = -1;
			int output = -1;
			
			for(int i=0;i<n;i++){
				if(strcmp(tokens[i],"<") == 0){
					input = i+1;
				}
				else if(strcmp(tokens[i],">") == 0){
					output = i+1;
				}
				else if(strcmp(tokens[i], "|") == 0){
					pi = 1;
				}
			}

			if(pi == 1){
				
				handle_piped(tokens, n, input,output);
	
			}
			else{
				handle_unpiped(tokens,input,output);	
			}
		}
	}
    return 0;
}
