%{

#include <stdio.h>
#include <stdlib.h>		
#include <string.h>
#include <assert.h>

void push(char* a);
char* top();
void compute(char* a);
void pushn(char* a);
int topn();

extern FILE *yyout, *yyin;
extern int yylex();

int yyerror(const char *p) { fprintf(yyout,"%s\n","invalid_input"); return 0; }

char *concat( const char* s1, const char* s2, const char*s3)
{
    int len = strlen(s1) + strlen(s2) + strlen(s3) + 1;
    char *s = malloc(sizeof(char)*len);

    int i=0;
    for(int j=0; s1[j]!='\0'; j++)
        s[i++] = s1[j];
    for(int j=0; s2[j]!='\0'; j++)
        s[i++] = s2[j];
    for(int j=0; s3[j]!='\0'; j++)
        s[i++] = s3[j];

    s[i] = '\0';

    return s;
}


%}

%union
{
    char *expr;
    int val;
};
				
%token INTEGER OPR1 OPR2 NEWLINE EXIT 
%left	OPR1 
%left	OPR2 

%%

lines: 
     | lines expr NEWLINE {fprintf(yyout,"%s ",top());fprintf(yyout,"%d\n",topn());}
     | lines NEWLINE
	;

expr:	expr expr OPR1		{compute($<expr>3);} 
	| expr expr OPR2	{compute($<expr>3);}
	| INTEGER		{push($<expr>1); pushn($<expr>1);}
	| EXIT			{ exit(0);}		
;

%%

int toString(char a[]) {
  int c, sign, offset, n;

  if (a[0] == '-') {  // Handle negative integers
    sign = -1;
  }

  if (sign == -1) {  // Set starting position to convert
    offset = 1;
  }
  else {
    offset = 0;
  }

  n = 0;

  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }

  if (sign == -1) {
    n = -n;
  }

  return n;
}

int yywrap(){
	return 1;
}
int pointern = 0;
int pointer = 0;
int capn = 8;
int cap = 8;
char** stack;
int* number;

char* my_strcat(char* destination, char* source){
	int z =(int)strlen(destination) + (int)(strlen(source)) + 20;
	char* result = malloc(((int)strlen(destination) + (int)(strlen(source)) + 20)*sizeof(char));
	int idx = 0;
	int i = 0;
	while(destination[i] != '\0'){
		result[idx] = destination[i];
		++i;
		++idx;
	}
	int j = 0;
	while(source[j] != '\0'){
		result[idx] = source[j];
		++idx;
		++j;
	}
	result[idx] = '\0';
	return result;
}

char* my_strcpy(char* s1){
	char* result = malloc(((int)strlen(s1)+10)*sizeof(char));
	int i = 0;
	int j = 0;
	while(s1[i] != '\0'){
		result[j] = s1[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return result;
}

int main(int argc, char* argv []){
	yyin = fopen(argv[1],"r");
	yyout = fopen(argv[2],"w");
	pointer = 0;
	pointern = 0;
	stack = malloc(8*sizeof(char *));
	number = malloc(8*sizeof(int));
	yyparse();
}

void pushn(char* a){
	if(pointern == capn){
		capn = capn*2;
		number = realloc(number, capn*sizeof(int));
	}
	if(a[0] == '-'){
		number[pointern++] = a[1] - '0';
		number[pointern-1] *= -1;
	}
	else{
		number[pointern++] = toString(a);
	}
}

void push(char* a){
	
	if(pointer == cap){
		cap = cap*2;
		stack = realloc(stack, cap*sizeof(char *));
	}
	stack[pointer] = my_strcpy(a);
	++pointer;
	
}

int popn(){
	assert(pointern>=0);
	return number[--pointern];
}

char* pop(){
	assert(pointer>=0);
	return stack[--pointer];
}

int topn(){
	return number[pointern-1];
}

char* top(){
	return stack[pointer-1];
}

void compute(char* op){
	
	int o1 = popn();
	int o2 = popn();
	int res;
	if(strcmp(op,"+") == 0){	
		res = o1 + o2;
	}
	else if(strcmp(op,"-") == 0){
		res = o1 - o2;
	}
	else if(strcmp(op,"*") == 0){
		res = o1 * o2;
	}
	else if(strcmp(op,"/") == 0){
		if(o2 == 0){
			exit(1);
		}
		res = o1 / o2;
	} 		
	if(pointern == capn){
		capn = capn*2;
		number = realloc(number, capn*sizeof(int));
	}
	number[pointern++] = res;
	char *exp = my_strcpy(op); 
	
	char* op2 = pop();
	char* op1 = pop();
	char* opr4 = my_strcat(exp," ");
	char* opr2 = my_strcat(opr4,op1);
	char* opr3 = my_strcat(opr2," ");
	//printf("%s\n" , opr3);
	//printf("%s\n" , op2);
	char* opr1 = my_strcat(opr3,op2);
	//printf("%s\n" , opr1);
	//fflush(stdout);
	int a = 0;
	if(pointer == cap){
		cap = cap*2;
		stack = realloc(stack, cap*sizeof(char *));
	}
	stack[pointer++] = my_strcpy(opr1);
}
