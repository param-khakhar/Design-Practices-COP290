#include <stdio.h>

float fact(int n){
    if(n == 0){
        return 1;
    }
    else{
        return n*fact(n-1);
    }
}

float Sqrt(int choice,int n){
    
    if(choice == 5){
       return factorial(n);
    }
    else if(choice == 8){
        return n*n;
    }
    else{
        return n*n*n;
    }
}
