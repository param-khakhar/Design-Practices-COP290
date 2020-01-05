objects := obj/main.o obj/basic.o obj/Py.o obj/adv.o obj/Sqrt.o
.PHONY := cleanall clean1 clean2 clean3 clean4 build
headers :=  1/basic.h 2/Py.h 3/adv.h 4/Sqrt.h

build: 
	@echo "Integer-Calculator-File-Manager"
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
	@echo "make clean1:"
	@echo "clean header and object files associated with component1"
	@echo "================================="
	@echo "make clean2:"
	@echo "clean header and object files associated with component2"
	@echo "================================="
	@echo "make clean3:"
	@echo "clean header and object files associated with component3"
	@echo "================================="
	@echo "make clean4:"
	@echo "clean header and object files associated with component4"
	@echo "================================="

link:  $(objects) 
	@cc $(objects) -w -o link -I/usr/include/python3.6m -lpython3.6m  
	@rm -f exe/link
	@mv link exe	

obj/main.o: $(headers) $(objects) main.c

	@echo "****** Compiling Main"
	@cc -c main.c -w
	@mv main.o obj

obj/basic.o 1/basic.h: 1/basic.c 
	@echo "****** Invoking  1/makefile"
	@(cd 1; $(MAKE))
	@(cd 1; make)	

obj/Py.o 2/Py.h: 2/Py.c
	@echo "****** Invoking  2/makefile"
	@(cd 2; $(MAKE))

obj/adv.o obj/adv.h: 3/adv.c
	@echo "****** Invoking  3/makefile"
	@(cd 3; $(MAKE))

obj/Sqrt.o obj/Sqrt.h: 4/Sqrt.c
	@echo "****** Invoking  4/makefile"
	@(cd 4; $(MAKE))
  
run:
	@echo "Executing the program!";\
	exe/./link

clean1: 
	@echo "Cleaning object and header files for component1"
	-rm -f header/basic.h
	-rm -f obj/basic.o

clean2: 
	@echo "Cleaning object and header files for component2"
	-rm -f header/Py.h
	-rm -f obj/Py.o         

clean3: 
	@echo "Cleaning object and header files for component3"
	-rm -f header/adv.h
	-rm -f obj/adv.o 

clean4: 
	@echo "Cleaning object and header files for component4"
	-rm -f header/Sqrt.h
	-rm -f obj/Sqrt.o

cleanall:
	@echo "Cleaning all the header,object and executable files"
	-rm -f exe/link 
	-rm -f header/basic.h
	-rm -f obj/basic.o
	-rm -f header/Py.h
	-rm -f obj/Py.o
	-rm -f header/adv.h
	-rm -f obj/adv.o
	-rm -f header/Sqrt.h
	-rm -f obj/Sqrt.o

