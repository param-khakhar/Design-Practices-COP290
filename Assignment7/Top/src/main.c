#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h> 
# define CHUNK 10
# define CHARACTERS 128

// Tries would be used in order to store the words of a particular document.
struct Node{
	struct Node *children[CHARACTERS];
	bool EndOfWord;
};

// The function initializes an empty node.
struct Node* init(void){
	struct Node *c = NULL;
	c = (struct Node*)malloc(sizeof(struct Node));
	if(c){
		int i;
		c->EndOfWord = false;
		for(int i = 0;i<CHARACTERS;i++){
			c->children[i] = NULL;
		}
	}
	return c;
}

//Insert a word in the Trie. Inserts the word if not present or marking EndOfWord, in case of prefix. As we proceed to move
// down, we would initialize the nodes correponding to the ASCII value of the letters which haven't been initialized.

void insert(struct Node* root, char* word){
	int level = 0;
	int length = strlen(word);
	int index;
	struct Node* curr = root;
	while(level < length){
		int index = (int)word[level];
		// printf("%c %d\n",word[level],index);
		if(index  < 0){
			printf("%c\n",word[level]);
			printf("%d\n",index);
		}
		if(!curr->children[index]){
			curr->children[index] = init();
		}
		curr = curr->children[index];
		level++;
	}
	curr->EndOfWord = true;
}

//Search: The function searches the word in the Trie. Returns true if present and false if absent.

bool search(struct Node* root,char* word){
	int level = 0;
	int length = strlen(word);
	int index;
	struct Node* curr = root;
	while(level < length){
		index = ((int)word[level]);
		//printf(curr->children[index]);
		if(!curr->children[index]){
			return false;
		}
		curr = curr->children[index];
		level++;
	}
	return (curr != NULL && curr->EndOfWord);
}

// Match: The function matches the sentence with those present in the trie and returns the number of characters matched. 

int match(struct Node* root, char* sentence){
	int level = 0;
	int length = strlen(sentence);
	int index;
	struct Node* curr = root;
	while(level < length){
		index = ((int)sentence[level]);
		if(!curr->children[index]){
			return level;
		}
		fflush(stdout);
		curr = curr->children[index];
		level++;
	}
	return level;
}

void compute(char* argv[2]){
	struct Node* docs [2];
	char** tables[2];
	int counts[2];		//Contains the number of sentences in each of the documents.

	for(int a = 0;a<2;a++){

		char * filename = argv[a]; 
		FILE * fp = fopen(filename, "r"); 
		if (fp == NULL) return 1; 
		char c; 
		int count = 0;			//Count of the number of words 
		int width = 8;			//Width of the Table
		int height = 1;			//Height of the Table

		char* word = malloc(width*sizeof(char));
		char** table = calloc(height, sizeof(char*));

		int i = 0;
		int j = 0;
		struct Node* doc = init();

		while((c = fgetc(fp)) != EOF) 
		{ 	
			if(c == ' ' || (int)c < 0)
				continue;
			// printf("%c\n",c);
			if(c == '.') 
			{ 
				word[j] = '\0';
				bool res = search(doc,word);
				if(!res){
					if(i >= height){
						height = height + CHUNK;
						//printf("Increasing the Height: %d\n",height);
						table = realloc(table,height*(width/8 + 1)*sizeof(char*));
					}
					table[i] = malloc((width/8 + 1)*sizeof(char*));
					strcpy(table[i],word);
					insert(doc,word);
					free(word);
					word = malloc((width+1)*sizeof(char));
					j = 0; 
					i++;
					count++;
//					fgetc(fp);
					continue;
				//}
				}
				else{
					free(word);
					word = malloc((width+1)*sizeof(char));
					j = 0;
					continue;
				}
			} 
			else 
			{ 
				if(width<=j){
					width = width + CHUNK;
					word = realloc(word,(width+1)*sizeof(char));
					if(!word){
						free(word);
						word = NULL;
						break;
					}
				}
				word[j] = c;
			//	printf("%d %c\n", j, c); 
				j++;
			} 
		} 
		fclose(fp);
		docs[a] = doc;
		tables[a] = table; 
		counts[a] = count;
	}
	//Test File present in 0th index. (Table as well as Doc). Document from the corpus present at the 1st index.
	//We'd iterate over the sentences of the corpus document in the test file.

	// The variable matches stores the number of words of the corpus doc which are matched in the test file.s
	float matches = 0.0;
	float total = 0.0;
	struct Node* root = docs[0];
	for(int i = 0;i<counts[1];i++){
	 	char* s = tables[1][i];
	 	//printf("%s\n",s);
	 	int a = match(root,s);
		matches = matches + a;
		total = total + strlen(s);
	 	//printf("Number of characters matched between the two sentences: %d\n",a);
	 	//printf("Length of the sentence in the corpus doc: %d\n",strlen(s));
	}
	//printf("matches: %.2f\n",matches);
	//printf("total length checked: %.2f\n",total);
	float res = (matches / total)*100;
	printf("%.2f\n",res);
}

bool has_txt_extension(char const *name)
{
    size_t len = strlen(name);
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;
}

int main(int argc, char * argv[]) 
{ 
	// This program reads a file from its arguments and prints a word by word. Additionally, it counts the words in the file. 
	if (argc < 2) return 1;

	struct dirent *de;
	DIR *dr = opendir(argv[2]);
	if(dr == NULL){
		printf("Couldn't open the current directory.");
		return 0;
	}
	char* path = argv[2];
	char ch = '/';
	strncat(path,&ch,1);
	while((de = readdir(dr)) != NULL){
		char* temp = malloc(100*sizeof(char));
		strcpy(temp,path);
		strcat(temp,de->d_name);
		if(has_txt_extension(temp)){
			//printf("%s\n",temp);
			char* args [2];
			args[0] = argv[1];
			args[1] = temp;
			printf("%s ",de->d_name);
			compute(args);
		}
		free(temp);
	}
	closedir(dr);
	return 0; 
} 