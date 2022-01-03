command: fix.y fix.l
	@yacc fix.y -d
	@lex fix.l
	@cc -w y.tab.c lex.yy.c -o precision

clean:
	echo "This will clean all the files except these: "
	echo "Makefile"
	echo "yacc.y"
	echo "lex.l"
	rm `ls -1 | grep -v "\(lex.l\)\|\(yacc.y\)\|\(Makefile\)"` 
