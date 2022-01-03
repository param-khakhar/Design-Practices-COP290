#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
	char *commands[8];
	commands[0] = "set term png";
	commands[1] = "set output \" plot.png \" ";
	commands[2] = "set xlabel 'Number of Tellers'";
	commands[3] = "set ylabel 'Average Time Spent by Customers (single queue)'";
    commands[4]="plot \"data.dat\" using 2:1 title \"\" with line";
	
	for(int i = 0;i<5;i++){
		fprintf(gnuplotPipe,"%s \n", commands[i]);
	}
    fflush(gnuplotPipe);
    fclose(gnuplotPipe);    
    return 0;  
}