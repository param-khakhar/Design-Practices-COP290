#include <stdio.h>

int factorial(int n){
    if(n == 0){
        return 1;
	}
    else{
	return n*factorial(n-1);
	}
    }

int nCr(int n,int r){
    return factorial(n)/(factorial(r)*factorial(n-r));
}

int nPr(int n,int r){
    return factorial(n)/factorial(n-r);
}

int adv(int choice, int n, int r){
    
    if(choice == 6){
        return nCr(n,r);
        }
    else{
        return nPr(n,r);
        }
}
