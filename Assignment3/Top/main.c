# include <stdio.h>
#include <stdbool.h>
# include <string.h>

char* reverse(char str[]);
char* add_sub(char op1 [], char op2 [], char op3 []);
char* subiter(char a [],char b [],char c []);
char* multiter(char op1 [], char op2 [],char sum[], int dec);
char* diviter(char op1 [], char op2 [], char quotient []);
char* substring(char destination [], char source [], int begin, int n);

char dot = '.';
char zero = '0';
char one = '1';
char dash = '-';
char* a;
char* b;
char Ten [1000] = "10";


void aheadZero(char s []){
	char t [1000] = "";
	bool trail1 = false;
	char s1[1000] = "";
	if(s[0] == '-'){
		substring(s1,s,1,strlen(s)-1);
	}
	else{
		strcpy(s1,s);
	}
	for(int i = 0;i<strlen(s1);i++){
		if(s1[i] == '0'){
			if((i+1) != strlen(s1)){
				if(s1[i+1] == '.'){
					trail1 = true;
				}
			}
		}
		if(s1[i] != '0'){
			trail1 = true;
		}
		if(trail1){
			char q = s1[i];
			strncat(t,&q,1);
		}
	}
//	printf("Aheadt: %s\n",t);
	if(s[0] == '-'){
		reverse(t);
		strncat(t,&dash,1);
		reverse(t);
	}
	strcpy(s,t);
}

char* removeTrail(char y []){
	char z [1000] = "";
	bool trail = false;
//	printf("Inside trail: %s\n",y);
	for(int i = strlen(y) - 1;i>=0;i--){
		if(y[i] == '.' && (!(trail))){
			trail = true;
			continue;
		}
		if(y[i] != '0'){
			trail = true;
		}
		if(trail){
			char w = y[i];
			strncat(z,&w,1);
		}
	//	printf("Inside trail: %s\n",z);
	}
	if(strlen(z) == 0){
		strncat(z,&zero,1);
	}
//	printf("%s\n",z);
	reverse(z);
	strcpy(y,z);
	return y;
//	printf("%s\n",z);
//	aheadZero(z);
}


int dec(char op1 [], char op2 []){

	//Code to add 2 negative or 2 positive numbers.
	
	//Position after the decimal place for strings op1 and op2.
	int dec1 = 0;
	int dec2 = 0;

	/*If decimal places are present than need a precision of atleast 20 decimal
	 * places. Also taking care of that requirement.*/

	/*Iterate over the strings to identify the number of places after the decimal
	 * point in each of the string. And then equalize the number of digits after the
	 * decimal point for both the strings.*/

	bool found1 = 0;
	int s1 = strlen(op1);
	for(int i=0;i<s1;i++){
		if(found1){
		dec1 += 1;
		}
		if(op1[i] == '.'){
			found1 = 1;
		}
	}

	bool found2 = 0;
	int s2 = strlen(op2);
	for(int i=0;i<s2;i++){
		if(found2){
			dec2 ++;
		}
		if(op2[i] == '.'){
			found2 = 1;
		}
	}
	
	if(found1 || found2){
	
		if(dec1 == 0){
			strncat(op1,&dot,1);
		}
		if(dec2 == 0){
			strncat(op2,&dot,1);
		}
		if(dec2 > dec1){
			while(dec1 != dec2){
				strncat(op1,&zero,1);
				dec1++;
				}
			}
			if(dec1 > dec2){
				while(dec2 != dec1){
					strncat(op2,&zero,1);
					dec2++;
				}
			}
		}
	a = op1;
	b = op2;
	return dec1;
	}

char* setPrecision(char op1 []){

	char op7 [1000] = "";
	bool found = 0;
	int pos = 0;
	int dec = 0;
	int s1 = strlen(op1);
	for(int i=0;i<s1;i++){
		if(found){
			dec += 1;
			if(dec>20){
				break;
			}
		}
		if(op1[i] == '.'){
			found = 1;
			pos = i;
		}
		strncat(op7,&op1[i],1);
	}
	strcpy(op1,op7);
	return op1;
//	printf("%s\n",op7);
}

char* reverse(char str[]){
	int s = strlen(str);
	for(int i = 0;i < s/2;i++){
		char temp = str[i];
		str[i] = str[s-i-1];
		str[s-i-1] = temp;
	}
	return str;
}

char* substring(char destination [], char source [], int begin, int n){
	/*Function extracts n characters from the string starting from begin index
	 * and copy them into the destination string*/
	for(int i=0;i<n;i++){
		destination[i] = source[i+begin];
	}
	return destination;
}

char* add(char op1[],char op2 []){
	char c [10000] = "";
	add_sub(op1,op2,c);
	printf("%s\n",c);
	return c;
}

char* add_sub(char op1 [], char op2 [], char c []){
	dec(op1,op2);
//	printf("Inside add");
	if((op1[0] != '-' && op2[0] != '-')||(op1[0] == '-' && op2[0] == '-')){

	//	Adding two positive or 2 negative numbers
		
		int s1 = strlen(op1);
		int s2 = strlen(op2);

		if(s1>s2){
			a = op1;
			b = op2;
		}
		else{
			a = op2;
			b = op1;
		}
	

		reverse(a);
		reverse(b);
//		printf(a);
//		printf("\n");
//		printf(b);
//		printf("\n");	
		int car = 0;
		int m = strlen(a);
		int n = strlen(b);
		int curr1 = 0;
		int curr2 = 0;
		int res = 0;
		for(int i=0;i<m;i++){
			if(a[i] == '-'){
				if(car == 1){
					strncat(c,&one,1);
					car = 0;
					}
				strncat(c,&dash,1);
				
			}
			else if(a[i] == '.'){
				strncat(c,&dot,1);
			}

			else{
				if(i<n){
					curr1 = a[i] - '0';
					curr2 = b[i] - '0';
					res = curr1 + curr2 + car;
					if(res>=10){
						car = 1;
						res = res-10;
					}
					else{
						car = 0;
					}
					char temp = res + '0';
					strncat(c,&temp,1);
				}
				else{
					curr1 = a[i] - '0';
					res = curr1+car;
					if(res>=10){
						car = 1;
						res = res - 10;
					}
					else{
						car = 0;
					}
					char temp = res + '0';
				//	cout<<temp<<endl;
					strncat(c,&temp,1); 	
				}
			}
		}
		if(car == 1){
			strncat(c,&one,1);
		}
//	printf(c);
//	printf("\n");
//	printf(reverse(c));
//	printf("\n");
//	return reverse(c);
	reverse(c);
	return c;
	}
	else{
	//Code to add a positive and a negative number;
		char temp [1000] = "";
		int res;
		int s1 = strlen(op1);
		int s2 = strlen(op2);
		if(op1[0] == '-'){
			substring(temp,op1,1,s1-1);
			res = compare(temp,op2);
			if(res == 0){
				subiter(temp,op2,c);
				strncat(c,&dash,1);
			}
			else{
				subiter(op2,temp,c);
			}
		}
		else{
			substring(temp,op2,1,s2-1);
	//		printf(temp);
			res = compare(op1,temp);
			if(res == 0){
				subiter(op1,temp,c);
			}
			else{
				subiter(temp,op1,c);
				strncat(c,&dash,1);
				}
			}
//		printf("%s\n",c1);
		return reverse(c);
		}
//	printf(c);
//	printf("\n");
}

char* subiter(char op1 [], char op2 [], char c []){
	
	/*Code for performing subtraction where |a| > |b|*/
	char a [1000];
	char b [1000];
	strcpy(a,op1);
	strcpy(b,op2);
	int curr1;
	int curr2;
	int carry = 0;
	int res;
	int m = strlen(a);
	int n = strlen(b);
	reverse(a);
	reverse(b);
//	printf(a);
//	printf("\n");
//	printf(b);
//	printf("\n");
	for(int i=0;i<m;i++){
		if(a[i] == '.'){
			strncat(c,&dot,1);
		}
		else{
			if(i<n){ 
				curr1 = a[i]-'0';
				curr2 = b[i]-'0';
				res = curr1-curr2-carry;
				if(res>=0){
					carry = 0;
					char temp = res + '0';
					strncat(c,&temp,1);
				}
				else{
					carry = 1;
					res = res + 10;
					char temp = res + '0';
					strncat(c,&temp,1);
				}
			}
			else{
				curr1 = a[i]-'0';
				res = curr1 - carry;
				if(res>=0){
					carry = 0;
					char temp = res + '0';
					strncat(c,&temp,1);
				}
				else{
					carry = 1;
					res += 10;
					char temp = res + '0';
					strncat(c,&temp,1);
				}
			}
		}

	}
	reverse(c);
	char r [1000] = "";
	bool lead = false;
	for(int i = 0;i < strlen(c);i++){
		if(c[i] == '0'){
			if(i+1 != strlen(c)){
				if(c[i+1] == '.'){
					lead = true;
				}
			}
			else{
				lead = true;
			}
		}

		if(c[i] != '0'){
			lead = true;
		}

		if(lead){
			char t = c[i];
			strncat(r,&t,1);
		}
	}
	//printf("R is:%s\n",r);
	strcpy(c,r);
	reverse(c);
	return c;
}

int compare(char op1 [], char op2 []){
	int s1 = strlen(op1);
	int s2 = strlen(op2);
	char o1 [1000];
	char o2 [1000];
	strcpy(o1,op1);
	strcpy(o2,op2);
	reverse(o1);
	reverse(o2);
	if(s1>s2){
		while(strlen(o2)!=strlen(o1)){
			strncat(o2,&zero,1);
		}
	}
	else{
		while(strlen(o1)!=strlen(o2)){
			strncat(o1,&zero,1);
		}
	}
	reverse(o1);
	reverse(o2);
	int i = 0;
	int curr1 = 0;
	int curr2 = 0;
	curr1 = o1[0] - '0';
	curr2 = o2[0] - '0';
	while(curr1 == curr2 && i < strlen(o1)){
		i++;
		if(o1[i] != '.'){
			curr1 = o1[i] - '0';
			curr2 = o2[i] - '0';
		}
	}
	if(curr1>=curr2){
		return 0;
	}
	else{
		return 1;
	}
}

char* sub(char op1 [], char op2 []){
	
	if(op2[0] == '-'){
		char temp [1000];
		char temp2 [1000];
		int s2 = strlen(op2);
		substring(temp,op2,1,s2-1);
		add_sub(op1,temp,temp2);
		printf("%s\n",temp2);
		return temp2;
	}
	else{
		char* temp;
		reverse(op2);
		strncat(op2,&dash,1);
		reverse(op2);
		char temp2 [1000] = "";
		add_sub(op1,op2,temp2);
		printf("%s\n",temp2);
		return temp2;
	}
}


char* mul(char op1 [], char op2 [],int status){

	char* res;
	int i = dec(op1,op2);
	char temp [1000];
	int s1 = strlen(op1);
	int s2 = strlen(op2);
	char sum [1000] = "0";

	if((op1[0] != '-') && (op2[0] != '-')){
		res = multiter(op1,op2,sum,i);
	}
	else if((op1[0] == '-') && (op2[0] != '-')){
		substring(temp,op1,1,s1-1);
		res = multiter(temp,op2,sum,i);
		reverse(res);
		strncat(res,&dash,1);
		reverse(res);
	}
	else if((op1[0] != '-') && (op2[0] == '-')){
		substring(temp,op2,1,s2-1);
		res = multiter(op1,temp,sum,i);
		reverse(res);
		strncat(res,&dash,1);
		reverse(res);
	}
	else{
		char temp1 [1000];
		char temp2 [1000];
		substring(temp1,op1,1,s1-1);
		substring(temp2,op2,1,s2-1);
		res = multiter(temp1,temp2,sum,i);
	}
	if(status == 0){
		printf("%s\n",res);
	}
	return res;	
}

char* multiter(char op1 [], char op2 [], char sum [], int dec){

	int s1 = strlen(op1);
	int s2 = strlen(op2);
	char* a1;
	char* b1;
	if(s1>s2){
		a1 = op1;
		b1 = op2;
	}
	else{
		a1 = op2;
		b1 = op1;
	}
	
	int rem = 0;
	int curr1 = 0;
	int curr2 = 0;
	int res;
	int m = strlen(a1);
	int n = strlen(b1);
	int carry = 0;
	int times = -1;
	int quo;
	char* sumt;
	for(int i=0;i<n;i++){
		char result [1000] = "";
		if(b1[n-i-1] != '.'){
			times++;
			for(int j=0;j<m;j++){
				if(a1[m-j-1] != '.'){
					curr1 = a1[m-j-1] - '0';
					curr2 = b1[n-i-1] - '0';
					res = curr1*curr2 + carry;
					carry = 0;
					if(res>=10){
						quo = (int)res/10;
						rem = res%10;
						carry = carry + quo;
					}
					else{
						rem = res%10;
					}
					char temp = rem + '0';
					reverse(result);
					strncat(result,&temp,1);
					reverse(result);
					}
				}
			if(carry != 0){
				char temp = carry + '0';
				reverse(result);
				strncat(result,&temp,1);
				reverse(result);
			}
			for(int z = 0;z<times;z++){
				strncat(result,&zero,1);
		
			}
			char y [1000] = "";
			sumt = add_sub(sum,result,y);
			strcpy(sum,sumt);
		}
	}
	if(dec>0){
		char resultf [1000] = "";
		reverse(sum);
		int s3 = strlen(sum);
		for(int i = 0;i< s3;i++){
			if(i == 2*dec){
				strncat(resultf,&dot,1);
			}
			char t = sum[i];
			strncat(resultf,&t,1);
		}
	reverse(resultf);
	strcpy(sum,resultf);
	}
	return sum;
}

void abs(char a []){
	if(a[0] != '-'){
		printf("%s\n",a);
	}
	else{
		int s1 = strlen(a);
		char temp[1000] = "";
		substring(temp,a,1,s1-1);
		printf("%s\n",temp);
	}
}


char* div(char op1 [], char op2 []){

//	printf("Op1 just inside divide: %s\n",op1);	
//	printf("Op2 just inside divide: %s\n",op2);
	if(strcmp(op2,"0") == 0){
		printf("Sorry. Out of the computational capabilities of this calculator\n");
		return;
	}
	int index1 = 0;
	int index2 = 0;
	char res [1000] = "";
	char result [1000] = "";
	char a2 [1000] = "";
	char b2 [1000] = "";
	char temp [1000] = "";

	for(int j=0;j<strlen(op1);j++){
		char x = op1[j];
		if(x == '.'){
			index1 = strlen(op1)-j-1;
			continue;
		}
		strncat(a2,&x,1);
	}

	for(int k=0 ;k<strlen(op2);k++){
		char w = op2[k];
		if(w == '.'){
			index2 = strlen(op2)-k-1;
			continue;
		}
		strncat(b2,&w,1);
	}

	char a3[1000] = "";
	char b3[1000] = "";
	bool lead1 = false;
	bool lead2 = false;

	for(int i = 0;i<strlen(a2);i++){
		if(a2[i] == '0'){
			if(i+1 == strlen(a2)){
				lead1 = true;
			}
		}
		
		if(a2[i] != '0'){
			lead1 = true;
		}
		if(lead1){
			char f = a2[i];
			strncat(a3,&f,1);
		}
	}

	for(int i = 0;i<strlen(b2);i++){
		if(b3[i] == '0'){
			if(i+1 == strlen(b2)){
				lead2 = true;
			}
		}
		
		if(b2[i] != '0'){
			lead2 = true;
		}
		if(lead2){
			char f = b2[i];
			strncat(b3,&f,1);
		}
	}

	int s1 = strlen(a3);
	int s2 = strlen(b3);

	if((op1[0] != '-') && (op2[0] != '-')){
		diviter(a2,b2,res);
//		printf("If1: %s\n",res);
	}
	else if((op1[0] == '-') && (op2[0] != '-')){
		substring(temp,a3,1,s1-1);
		diviter(temp,b3,res);
		reverse(res);
		strncat(res,&dash,1);
		reverse(res);
	}
	else if((op1[0] != '-') && (op2[0] == '-')){
		substring(temp,b3,1,s2-1);
		diviter(a3,temp,res);
		reverse(res);
		strncat(res,&dash,1);
		reverse(res);
	}
	else{
		char temp1 [1000];
		char temp2 [1000];
		substring(temp1,a3,1,s1-1);
		substring(temp2,b3,1,s2-1);
		diviter(temp1,temp2,res);
	}
	
//	printf("%Inside div: %s\n",res);
	char* R;
	char factor [1000] = "1";
	int index4 = index1-index2;
//	printf("index1: %d\n",index1);
//	printf("Index2: %d\n",index2);
	if(index4 < 0){
		while(index4<0){
			index4++;
			strncat(factor,&zero,1);
		}
	//	multiter(factor,res,result,0);
		R = mul(factor,res,1);
		strcpy(result,R);
	}
	else if(index4 > 0){
		while(index4>1){
			index4--;
			strncat(factor,&zero,1);
		}
		strncat(factor,&dot,1);
		strncat(factor,&zero,1);
		reverse(factor);
	//	printf("factor: %s\n",factor);
	//	printf("res: %s\n",res);
	//	multiter(factor,res,result,0);
		R = mul(factor,res,1);
		strcpy(result,R);
	//	printf("res: %s\n",res);
	//		printf("result: %s\n",result);
	}
	else{
		strcpy(result,res);
	}
	char zero [1000];
	strcpy(zero,result);
	aheadZero(zero);
	removeTrail(zero);
	setPrecision(zero);
	printf("%s\n",zero);
	return zero;
}

char* diviter(char dividend [], char divisor [], char quotient []){

//	printf("Just inside diviter dividend: %s\n",dividend);
//	printf("Just inside diviter divisor: %s\n",divisor);
	int res;
	int digitsr = 0;
	int digitsl = 0;
	bool initial = true;
	bool decimal = true;
	char tempDvd [1000] = "";
	char tempDvr1 [1000] = "";
	char tempDvd1 [1000] = "";

	int iter = 0;
	int control = compare("0",dividend);
	while((control != 0) && (strlen(quotient)<=100)){
		res = compare(dividend,divisor);
		if (res == 0){
			initial = false;
			char tempDvr [1000] = "";
			multiter(divisor,Ten,tempDvr,0);
		//	printf("tempDvr before comparison outside loop case1: %s\n",tempDvr);
		//	printf("dividend before comparison outside loop case1: %s\n",dividend);
			res = compare(dividend,tempDvr);
		//	printf("res just outside the loop: %d\n",res);
			while(res==0){
				strcpy(divisor,tempDvr);
				digitsr++;
				char tempDvr1 [1000] = "";
			//	multiter(divisor,Ten,tempDvr,0);
				multiter(divisor,Ten,tempDvr1,0);
				strcpy(tempDvr,tempDvr1);
		//		printf("tempDvr case1 first loop: %s\n",tempDvr);
				res = compare(dividend,tempDvr);
			}
		//	printf("Divisor just after the loop: %s\n",divisor);
			int quod = 0;	
			res = compare(dividend,divisor);
			while(res == 0){
				quod++;
				char tempDvd2 [1000] = "";
				subiter(dividend,divisor,tempDvd2);
				reverse(tempDvd2);
				res = compare(tempDvd2,divisor);
				strcpy(dividend,tempDvd2);
			}
			char tempc = quod + '0';
			strncat(quotient,&tempc,1);
		//	printf("Quotient case1: %s\n",quotient);
			
		}

		else{
			if(initial){
				strncat(quotient,&zero,1);
				strncat(quotient,&dot,1);
				decimal = false;
				initial = false;
			}
			if(decimal){
				strncat(quotient,&dot,1);
				decimal = false;
			}
			
		//	printf("Dividend before the loop case2: %s\n",dividend);
		//	printf("Divisor before the loop case2; %s\n",divisor);
			char tempDvd3 [1000] = "";
			multiter(dividend,Ten,tempDvd3,0);
			res = compare(divisor,tempDvd3);
			int i = 0;
			if(res == 1){
				strcpy(dividend,tempDvd3);
			}
			while(res == 0 && (strcmp(dividend,divisor) != 0)){
				i++;
			//	digitsl++;
				strcpy(dividend,tempDvd3);
				char tempDvd4 [1000] = "";
				multiter(dividend,Ten,tempDvd4,0);
				res = compare(divisor,tempDvd4);
				strcpy(tempDvd3,tempDvd4);
//				printf("Inside the loop dividend: %s\n",dividend);
//				printf("Inside the lood divisor: %s\n",divisor);
				
			}
		//	printf("Outside the loop dividend: %s\n",dividend);
		//	printf("Outside the loop divisor: %s\n",divisor);
			while(i>0){
				i--;
				strncat(quotient,&zero,1);
			}
		//	printf("Quotient: case2 end: %s\n",quotient);

		}
		control = compare("0",dividend);
	}
	
	char* quo = "";
	char factor [1000] = "1";
	int i = digitsr-digitsl;
//	printf("Index diviter: %d\n",i);
	if(i>=0){
		while(i>0){
			i--;
			strncat(factor,&zero,1);
		}
	}
	else{
		while(i<-1){
			i++;
			strncat(factor,&zero,1);
		}
		strncat(factor,&dot,1);
		strncat(factor,&zero,1);
		reverse(factor);
	}
//	printf("FactorDiviter: %s\n",factor);
//	printf("quotient before factor: %s\n",quotient);
	quo = mul(quotient,factor,1);
	strcpy(quotient,quo);
//	printf("Return diviter: %s\n",quotient);
	return quotient;
}

int main(){
	char s [1000] = "12345678908765434567765456789098765456789098726523512379812351278351825387126781296129678327018273817293618531785478361498673197849823719";
	char t [1000] = "1625367127512635267125367125671527512635126531672567125671256125376571";
	printf("%s","Div:");
	char g [1000] = "10";
	char h [1000] = "0";
	div(g,h);
	char a [10000] = "12345678908765434567765456789098765456789098726523512379812351278351825387126781296129678327018273817293618531785478361498673197849823719";
	char b [10000] = "1625367127512635267125367125671527512635126531672567125671256125376571";
	char c [1000] = "12345678908765434567765456789098765456789098726523512379812351278351825387126781296129678327018273817293618531785478361498673197849823719";
	char d [1000] = "1625367127512635267125367125671527512635126531672567125671256125376571";
	char e [1000] = "12345678908765434567765456789098765456789098726523512379812351278351825387126781296129678327018273817293618531785478361498673197849823719";
	char f [1000] = "1625367127512635267125367125671527512635126531672567125671256125376571";

	//printf("%s","Add:");
	//add(a,b);
	//printf("%s","Sub:");
	//sub(c,d);
	//printf("%s","Mul:");
	//mul(e,f);
	return 0;
}

