#include <stdio.h>

#define BUFFERSIZE 100

int main(){
		int ch;
	/* read character by character from stdin */
	do {
		ch = fgetc(stdin);
		putchar(ch);
	} while (ch != EOF); 
	printf("Param Khakhar!\n");
}
