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


char* aheadZero(char s []){
	char zer [10] = "0";
	char* w = zer;
	if(strcmp(zer,s) == 0){
		return w;
	}
	char mzer [10] = "-0";
	if(strcmp(mzer,s) == 0){
		return w;
	}	
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
	if(s[0] == '-'){
		reverse(t);
		strncat(t,&dash,1);
		reverse(t);
	}
	char* T = t;
	return T;
}

char* removeTrail(char y []){
	bool decimal = true;
	char z [1000] = "";
	bool trail = false;
	for(int i = strlen(y) - 1;i>=0;i--){
		if(y[i] == '.')
			decimal = false;
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
	}
	if(strlen(z) == 0){
		strncat(z,&zero,1);
	}
	reverse(z);
	if(decimal){
		char* R1 = y;
		return R1;
	}
	char* R = z;
//	strcpy(y,R);
	return R;
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
	if((op1[0] != '-' && op2[0] != '-')||(op1[0] == '-' && op2[0] == '-')){

	//	Adding two positive or 2 negative numbers
		char op1m [1000] = "";
		char op2m [1000] = "";
		if(op1[0] == '-'){
			substring(op1m,op1,1,strlen(op1)-1);
			substring(op2m,op2,1,strlen(op2)-1);

			int s1 = strlen(op1m);
			int s2 = strlen(op2m);

			if(s1>s2){
				a = op1m;
				b = op2m;
			}
			else{
				a = op2m;
				b = op1m;
			}
		}
		else{
		
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
		}

		reverse(a);
		reverse(b);
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
		if(op1[0] == '-'){
			strncat(c,&dash,1);
		}
	reverse(c);
	char* c1 = aheadZero(c);
	char c1A [1000] = "";
	strcpy(c1A,c1);
	char* c2 = removeTrail(c1A);
	char c2A [1000] = "";
	strcpy(c2A,c2);
	return c2;
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
			res = compare(op1,temp);
			if(res == 0){
				subiter(op1,temp,c);
			}
			else{
				subiter(temp,op1,c);
				strncat(c,&dash,1);
				}
			}
		
		reverse(c);
		char* c1 = aheadZero(c);
		char c1A [1000] = "";
		strcpy(c1A,c1);
		char* c2 = removeTrail(c1A);
		char c2A [1000] = "";
		strcpy(c2A,c2);
		return c2;
	}
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
	strcpy(c,r);
	reverse(c);
	return c;
}

int compare(char op1 [], char op2 []){
//	int s1 = strlen(op1);
//	int s2 = strlen(op2);
//	printf("Op1: %s\n",op1);
//	printf("Op2: %s\n",op2);
	char o1 [1000];
	char o2 [1000];
	strcpy(o1,op1);
	strcpy(o2,op2);
	dec(o1,o2);
//	printf("Op1: %s\n",o1);
//	printf("Op2: %s\n",o2);
	reverse(o1);
	reverse(o2);
	int s1 = strlen(o1);
	int s2 = strlen(o2);
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
//	printf("O1: %s\n",o1);
//	printf("O2: %s\n",o2);
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

char* sub(char op1 [], char op2 [],int status){
	
	if(op2[0] == '-'){
		char temp [1000] = "";
		char temp2 [1000] = "";
		int s2 = strlen(op2);
		substring(temp,op2,1,s2-1);
		add_sub(op1,temp,temp2);
		if(status == 0)
			printf("%s\n",temp2);
		char* temp4 = temp2;
		return temp4;
	}
	else{
		char* temp;
		reverse(op2);
		strncat(op2,&dash,1);
		reverse(op2);
		char temp2 [1000] = "";
//		printf("Op1: %s\n",op1);
//		printf("Op2: %s\n",op2);
		add_sub(op1,op2,temp2);
		if(status == 0)
			printf("%s\n",temp2);
		temp = temp2;
		return temp;
	}
}


char* mul(char op1 [], char op2 [],int status){

	char* res;
	int i = dec(op1,op2);
//	printf("Op1: %s\n",op1);
//	printf("Op2: %s\n",op2);
	char temp [10000] = "";
	int s1 = strlen(op1);
	int s2 = strlen(op2);
	char sum [10000] = "0";

	if((op1[0] != '-') && (op2[0] != '-')){
		res = multiter(op1,op2,sum,i);
	//	printf("res: %s\n",res);
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
		char temp1 [10000] = "";
		char temp2 [10000] = "";
		substring(temp1,op1,1,s1-1);
		substring(temp2,op2,1,s2-1);
		res = multiter(temp1,temp2,sum,i);
	}
	//printf("Res: %s\n",res);

	char resA [1000] = "";
	strcpy(resA,res);
	char* r1 = aheadZero(resA);
	char r1A [1000] = "";
	strcpy(r1A,r1);
//	printf("%s\n",r1A);
	char* r2 = removeTrail(r1A);
	char r2A [1000] = "";
	strcpy(r2A,r2);
	if(status == 0){
		printf("%s\n",r2A);
	}
	return r2;	
}

char* multiter(char op1 [], char op2 [], char sum [], int dec){
	
//	printf("Op1 iter: %s\n",op1);
//	printf("Op2 iter: %s\n",op2);
	
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
	int res = 0;
	int m = strlen(a1);
	int n = strlen(b1);
	int carry = 0;
	int times = -1;
	int quo;
	char* sumt;
	for(int i=0;i<n;i++){
		char result [10000] = "";
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
				carry = 0;
			}
			for(int z = 0;z<times;z++){
				strncat(result,&zero,1);
			}
		//	printf("result: %s\n",result);
			char y [10000] = "";
			sumt = add_sub(sum,result,y);
			strcpy(sum,sumt);
		//	printf("Sum: %s\n");
		}
	}
//	printf("Sum: %s\n",sum);
	char sumA [1000] = "";
	if(strlen(sum) > 2*dec){
		for(int j = 0;j<strlen(sum);j++){
			if(j == strlen(sum) - 2*dec){
			       strncat(sumA,&dot,1);
			}
			strncat(sumA,&sum[j],1);	
		}
	}
	else if(strlen(sum) == 2*dec){
		strncat(sumA,&zero,1);
		strncat(sumA,&dot,1);
		strcat(sumA,sum);
	//	reverse(sum);
	//	strncat(sum,&dot,1);
	//	strncat(sum,&zero,1);
	//	reverse(sum);
	}
	else{
		strncat(sumA,&zero,1);
		strncat(sumA,&dot,1);
		int j = 2*dec - strlen(sum);
		while(j>0){
			strncat(sumA,&zero,1);
			j--;
		}
		strcat(sumA,sum);
	}
	char* sumAF = removeTrail(sumA);
	return sumAF;
}

char* abs(char a [], int status){
	char* R;
	if(a[0] != '-'){
		if(status == 0)
			printf("%s\n",a);
		R = a;
	}
	else{
		int s1 = strlen(a);
		char temp[1000] = "";
		substring(temp,a,1,s1-1);
		if(status == 0)
			printf("%s\n",temp);
		R = temp;
	}
	return R;
}


char* div(char op1 [], char op2 [], int precision, int status){


	char O [10] = "0";
	//printf("Op1 just inside divide: %s\n",op1);	
	//printf("Op2 just inside divide: %s\n",op2);
	if(strcmp(op2,O) == 0){
		printf("Sorry. Out of the computational capabilities of this calculator\n");
		return;
	}
	if(strcmp(op1,O) == 0){
		if(status == 0)
			printf("%s\n",O);
		char* sO = O;	
		return sO;
	}
	int index1 = 0;
	int index2 = 0;
	char res [10000] = "";
	char result [10000] = "";
	char a2 [10000] = "";
	char b2 [10000] = "";
	char temp [10000] = "";

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

	char a3[10000] = "";
	char b3[10000] = "";
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
		char temp1 [10000];
		char temp2 [10000];
		substring(temp1,a3,1,s1-1);
		substring(temp2,b3,1,s2-1);
		diviter(temp1,temp2,res);
	}
	
	//printf("Inside div: %s\n",res);
	char* R;
	char factor [10000] = "1";
	int index4 = index1-index2;
	//printf("index1: %d\n",index1);
	//printf("Index2: %d\n",index2);
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
		multiter(factor,res,result,0);
		R = mul(factor,res,1);
		strcpy(result,R);
	//	printf("res: %s\n",res);
		//printf("result: %s\n",result);
	}
	else{
		strcpy(result,res);
	}
	char zero [10000];
	strcpy(zero,result);
	//printf("Zero: %s\n",zero);
	char* z1 = aheadZero(zero);
	char z1A [10000] = "";
	strcpy(z1A,z1);
//	printf("z1A: %s\n",z1A);
	char* z = removeTrail(z1A);
	char zA [10000];
	strcpy(zA,z);
//	printf("%s\n",zA);
	if(precision == 0)
		setPrecision(zA);
	if(status == 0)
		printf("%s\n",zA);
	char* zF = zA;
	return zF;
}

char* diviter(char dividend [], char divisor [], char quotient []){

//	printf("Just inside diviter dividend: %s\n",dividend);
//	printf("Just inside diviter divisor: %s\n",divisor);
	int res;
	int digitsr = 0;
	int digitsl = 0;
	bool initial = true;
	bool decimal = true;
	char tempDvd [10000] = "";
	char tempDvr1 [10000] = "";
	char tempDvd1 [10000] = "";

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
//			printf("res just outside the loop: %d\n",res);
//			break;
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
		//	break;
		//	printf("Divisor just after the loop: %s\n",divisor);
			int quod = 0;	
			res = compare(dividend,divisor);
			while(res == 0){
				quod++;
				char tempDvd2 [10000] = "";
				subiter(dividend,divisor,tempDvd2);
				reverse(tempDvd2);
				res = compare(tempDvd2,divisor);
				strcpy(dividend,tempDvd2);
			}
			char tempc = quod + '0';
			strncat(quotient,&tempc,1);
	//		printf("Quotient case1: %s\n",quotient);
			
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
			char tempDvd3 [10000] = "";
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
				char tempDvd4 [10000] = "";
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
//	printf("Quotient before tangled: %s\n",quotient);

	char* quo = "";
	char factor [10000] = "1";
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

char* Sqrt(char op1 []){
	int l = strlen(op1);
	char x [100] = "1";
	int dec = 0;
	for(int j = 0;j < l;j++){
		if(op1[j] == '.')
			break;
		dec++;
	}
	int append = dec/2;
	if(append == 0){
		dec = 0;
		for(int i = 2;i<l;i++){
			if(op1[i] != '0')
				break;
			dec++;
		}
		append = dec/2;
		if(append == 0)
			append = 1;
	}
	while(append > 0){
		append--;
		strncat(x,&zero,1);
	}
	//printf("Op1: %s\n",op1);
	//printf("Seed: %s\n",x);
	int i = 0;
	while(true){
		i++;
		if(i == 70){
			char* r = setPrecision(x);
			printf("%s\n",x);
			printf("%d\n",i);
			return r;  
			break;
		}
		printf("X2: %s\n",x);
		char* temp = div(op1,x,0,1);
		char tempA [1000] = "";
		strcpy(tempA,temp);
		printf("tempA: %s\n",tempA);
		char result [10000] = "";
		add_sub(x,tempA,result);
		printf("Result: %s\n",result);
		char half [1000] = "0.5";
		char* Fresult = mul(half,result,1);
		strcpy(x,Fresult);
		printf("Xbefore: %s\n",x);
		char* x1 = aheadZero(x);
		char x1A [1000] = "";
		strcpy(x1A,x1);
		char* x2 = removeTrail(x1A);
		strcpy(x,x2);
	}
}

//(-0.02) + (-1234)
//

//Adding statuses to mult div.
//Changes made to multiter.
// Format multiplication reduce by decimal places.
// Change s1 and s2 lengths in compare.
// Add dec in compare
//Compare 0.14 and 0.000001
//Compare 2.56000000 and 0.0000001
//Modify sub as well for removeTail and aheadZero.
//Modify removeTail for nondecimal values. Zeros not to be removed in that case.
//aheadZero and removeTrail in mul
//Modifying arguments in removeTrail and hence changes in Division as well as aheadZero.
//Modifying add_sub by adding removeTail and aheaZero on the arguments. Need to make changes in the sub() as well and other places where add_sub was used.

int main(){
	char s [1000] = "12345678908765434567765456789098765456789098726523512379812351278351825387126781296129678327018273817293618531785478361498673197849823719";
	char t [1000] = "1625367127512635267125367125671527512635126531672567125671256125376571";
//	printf("%s","Div:");
	char g [1000] = "0";
	char h [1000] = "10";
//	div(g,h);
	char a [10000] = "12345678908765434567765456789098765456789098726523512379812351278351825387126781296129678327018273817293618531785478361498673197849823719";
	char b [10000] = "1625367127512635267125367125671527512635126531672567125671256125376571";
	char c [1000] = "12345678908765434567765456789098765456789098726523512379812351278351825387126781296129678327018273817293618531785478361498673197849823719";
	char d [1000] = "1625367127512635267125367125671527512635126531672567125671256125376571";
	char e [1000] = "12345678908765434567765456789098765456789098726523512379812351278351825387126781296129678327018273817293618531785478361498673197849823719";
	char f [1000] = "1625367127512635267125367125671527512635126531672567125671256125376571";

//	mul(g,h,0);
	//printf("%s","Add:");
//	sub(g,h,0);
	//printf("%s","Sub:");
//	sub(s,t,0);
//	printf("%s","SQRT:");
//	char i [1000] = "0.000000000001417301038062283736846366782006920415225";
//	char j [1000] = "0.00000001";
//	int res = compare(i,j);
//	printf("%d\n",res);
	div(g,h,0,0);
	Sqrt(g);
//	char* R = abs("1",0);
//	char R1 [1000];
//	strcpy(R1,R);
//	printf("R1: %s\n",R1);
//	char* P = removeTrail(i);
//	char PA [1000] = "";
//	strcpy(PA,P);
//	printf("%s\n",PA);
	return 0;
}

