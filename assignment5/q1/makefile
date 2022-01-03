CC:= gcc
.PHONY:= Re

command: myscanner.l 
	@lex myscanner.l	
	@gcc -w lex.yy.c -o decomment  
