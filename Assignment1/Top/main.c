#include<stdio.h>

extern adv();
extern Sqrt();
extern basic();
extern Py();	

/* the Lua interpreter */

int main(int argc, char*argv[]){

    printf("Integer Calculator\n");
    printf("Following choices of operations are available:\n");
    printf("1.Addition\n");
    printf("2.Subtraction\n");
    printf("3.Multiplication\n");
    printf("4.Division\n");
    printf("5.Factorial\n");
    printf("6.nCr\n");
    printf("7.nPr\n");
    printf("8.Square\n");
    printf("9.Cube\n");
    printf("10.Display current date and time\n");
    printf("Enter your choice:\n");
    int choice;
    scanf("%d", &choice);
    if(choice<=4){
    	    printf("Enter the two numbers separated by a line:\n");
	    int a,b;
	    scanf("%d", &a);
	    printf("Entered integer is: %d\n", a);
            scanf("%d", &b);
	    printf("Entered integer is: %d\n", b);
   	    printf("The result is:%d\n", basic(choice,a,b));
	}
    else if(choice == 8 || choice == 5 || choice == 9){
            printf("Enter the number:\n");
	    int a;
	    printf("Entered integer is: %d\n", a);
	    scanf("%d", &a);
   	    printf("The result is:%d\n",Sqrt(choice,a));
    }
    else if(choice == 6 || choice == 7){
    	    printf("Enter the two numbers separated by a line:\n");
	    int a,b;
	    scanf("%d", &a);
	    printf("Entered integer is: %d\n", a);
            scanf("%d", &b);
	    printf("Entered integer is: %d\n", b);
   	    printf("The result is:%d\n",adv(choice,a,b));
    }
    else{
        Py(1,argv);
    }
}
