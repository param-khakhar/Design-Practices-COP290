.PHONY := execute clean

problemOne:
	@(cd src; $(MAKE))
	@(cd obj; $(MAKE))

execute:
	@(cd bin; $(MAKE))

clean: 
	@rm -f obj/main.o
	@rm -f src/main.c
	@rm -f bin/qSim
	@rm -f bin/plot.png
	


		
