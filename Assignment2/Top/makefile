objects := obj/main.o obj/builtin.o obj/process.o
.PHONY := cleanall clean1 clean2 build
headers :=  1/builtin.h 2/process.h

build: 
	@echo "File manager for mini Shell implemented in C"
	@echo "================================"
	@echo "make link:"
	@echo "Compilation and linking of all the sourc and object files and generate a final executable file"
	@echo "================================="
	@echo "make run:"
	@echo "execution of the program"
	@echo "================================="
	@echo "make cleanall:"
	@echo "clean all the header and object files"
	@echo "================================="
	@echo "make clean-builtin:"
	@echo "clean header and object files associated with builtin"
	@echo "================================="
	@echo "make clean-process:"
	@echo "clean header and object files associated with process"
	@echo "================================="

link:  $(objects) 
	@cc $(objects) -w -o link 
	@rm -f exe/link
	@mv link exe	

obj/main.o: $(headers) $(objects) main.c

	@echo "****** Compiling Main"
	@gcc -c main.c -w
	@mv main.o obj

obj/builtin.o 1/builtin.h: 1/builtin.c 
	@echo "****** Invoking  1/makefile"
	@(cd 1; $(MAKE))
	@(cd 1; make)	

obj/process.o 2/process.h: 2/process.c
	@echo "****** Invoking  2/makefile"
	@(cd 2; $(MAKE))

  
run:
	@echo "Executing the program!"
	exe/./link

clean1: 
	@echo "Cleaning object and header files for component1"
	-rm -f header/builtin.h
	-rm -f obj/builtin.o

clean2: 
	@echo "Cleaning object and header files for component2"
	-rm -f header/process.h
	-rm -f obj/process.o         

cleanall:
	@echo "Cleaning all the header,object and executable files"
	-rm -f exe/link 
	-rm -f header/builtin.h
	-rm -f obj/builtin.o
	-rm -f header/process.h
	-rm -f obj/process.o
