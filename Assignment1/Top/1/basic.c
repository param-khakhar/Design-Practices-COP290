#include <stdio.h>

int basic(int choice, int x1, int x2){

    if(choice == 1){
        return x1+x2;
        }
    else if(choice == 2){
        return x1-x2;
        }
    else if(choice == 3){
        return x1*x2;
        }
    else{
        if(x2 == 0){
            printf("ZeroDivision Error,Cannot perform division");
	}
	else{
	    return x1/x2;
	}
    }
}  
