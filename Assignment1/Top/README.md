#Working with Makefiles 

##### An integer calculator is implemented and different functions are implemented in the subdirectories 1,2,3 and 4. The description of the sub-directories are as follows:

 **/Top**
  1. **1**
     ------------
     1. **basic.c**: The function basic() computes the result of **addition**, **subtraction**, **multiplication**, **division** and returns the answer.
     2. **basic.h** : The header file corresponding to the function basic().
     3. **makefile**: There is one PHONY target Re, which copies the header file to the header directory present in the Top directory. Also the object file(basic.o is 			      generated and moved to the obj directory of the Top directory. The prerequisites are basic.h and basic.c.
     ------------
  2. **2**
     ------------
     1. **Py.c** : The function Py() is used to display the **current date and time**. It uses **python embedded code** to achieve the purpose.
     2. **Py.h** : The header file corresponding to the function Py().
     3. **makefile** : There is one PHONY target Re, which copies the header file to the header directory present in the Top directory. Also the object file(Py.o) is 			       generated and moved to the obj directory of the Top directory. The prerequisites are basic.h and basic.c.
     ------------
  3. **3**
     ------------
     1. **adv.c**: The function adv() computes the result of **nCr**, **nPr** and returns the answer.
     2. **adv.h** : The header file corresponding to the function adv().
     3. **makefile**: There is one PHONY target Re, which copies the header file to the header directory present in the Top directory. Also the object file(adv.o) is 			      generated and moved to the obj directory of the Top directory. The prerequisites are adv.h and adv.c.
     ------------
  4. **4**
     ------------
     1. **Sqrt.c**: The function adv() computes the result of **square**, **cube**, **factorial** and returns the answer.
     2. **Sqrt.h** : The header file corresponding to the function Sqrt().
     3. **makefile**: There is one PHONY target Re, which copies the header file to the header directory present in the Top directory. Also the object file(Sqrt.o) is 			      generated and moved to the obj directory of the Top directory. The prerequisites are Sqrt.h and Sqrt.c.
     ------------ 
  5. **main.c** : This is the master file which displays the menu of the calculator and accepts input from the user to perform operations. It calls functions whose source    	                files are present in the different subdirectories.

  6. **header**: Contains the header files **basic.h**, **Py.h**, **adv.h** and **Sqrt.h**.

  7. **obj** : Contains the object files **basic.o**, **Py.o**, **adv.o** and **Sqrt.o**.

  8. **exe** : Contains the final executable link after linking all the object files.

  9. **makefile**: The main makefile for the entire file system. Following targets are used.
        
     1.**build**: Contains the description of the various targets which need to be used and is the default target.
     
     2.**link**: Links all object(.o) files present in the obj directory and returns an executable link.
     
     3.**obj/basic.o obj/basic.h**: Recursive call to the make present in the directory 1.
     
     4.**obj/Py.o obj/Py.h**: Recursive call to the make present in the directory 2.
     
     5.**obj/adv.o obj/adv.h**: Recursive call to the make present in the directory 3.
     
     6.**obj/Sqrt.o obj/Sqrt.h**: Recursive call to the make present in the directory 4.
     
     7.**run**: Run the program by executing the link file.
     
     8.**clean1**: Clean the contents of the sub directory 1 which is basic.o and basic.h from the respective subdirectories.
     
     9.**clean2**: Clean the contents of the sub directory 1 which is basic.o and basic.h from the respective subdirectories.
     
     10.**clean3**: Clean the contents of the sub directory 1 which is basic.o and basic.h from the respective sub directories.
    
     11.**clean4**: Clean the contents of the sub directory 1 which is basic.o and basic.h from the respective sub directories.
    
     12.**cleanall**: Clean the contents of all the subdirectories 1,2,3 and 4 i.e empty the header and obj directories.

Upon testing, the changes made to different source are reflected when the make is used again. Thus, the design of the file system achieves its purpose. 
