%Start comment0 comment1 string backslashs char0 backslashc 
%{
#include "myscanner.h"
int countbn = 0;
int linecount = 0;
int starts = 0;
int startc = 0;
int startco = 0;
int even = 0;
%}

whitespace 	[ \t]
newline		"\n"
digit 		[0-9]
start_comment	"/*"
WORRY   	"*"
FINAL   	*/
END		"/"
SIMPLE		[^*]
NEWLINE 	\n
START_STRING	"\""
END_STRING	"\""
NOT_END_STRING	[^("\"")]
end_comment	"*/"
NOTWORRY	[^(*/)]
START_CHAR	"\'"
END_CHAR	"\'"
BSCHAR		"\\\'"
BSSTRING	"\\\""
ENDC		<<EOF>>
FS		"\/"
BS		"\\"

%%

<INITIAL>{start_comment}				{BEGIN comment0; startco = linecount;}
<INITIAL>{START_CHAR}					{BEGIN char0; startc = linecount; return yytext;}
<INITIAL>{START_STRING}					{BEGIN string; starts = linecount;return yytext;}

<char0>{BS}						{even += 1; if(even%2 != 0){BEGIN backslashs;}else{BEGIN char0;}return yytext;}
<char0>{newline}					{linecount++; BEGIN char0; return yytext;}
<char0>{END_CHAR}					{BEGIN INITIAL;return yytext;}
<char0>[^{END_CHAR}]					{BEGIN char0;return yytext;}

<string>{BS}						{even += 1; if(even%2 != 0){BEGIN backslashs;}else{BEGIN string;}return yytext;}
<string>{newline}					{BEGIN string; linecount++;return yytext;}
<string>{END_STRING}					{BEGIN INITIAL; return yytext;}
<string>{NOT_END_STRING}				{BEGIN string; return yytext;}

<backslashs>{END_STRING}|[^{END_STRING}]		{BEGIN string;return yytext;}
<backslashs>{END_CHAR}|[^{END_CHAR}]			{BEGIN char0;return yytext;}

<comment0>{NEWLINE}					{linecount++;countbn++;BEGIN comment0;}
<comment0>{SIMPLE}					{BEGIN comment0;} 
<comment0>{WORRY}					{BEGIN comment1;}
<comment1>{WORRY}					{BEGIN comment1;}
<comment1>{END}						{fprintf(yyout,"%s"," ");while(countbn>0){countbn--;fprintf(yyout,"%s","\n");}countbn = 0; BEGIN INITIAL;}
<comment1>{SIMPLE}					{BEGIN comment0;}
<comment1><<EOF>>					{fprintf(yyout,"%s"," \n");while(countbn>0){countbn--;fprintf(yyout,"%s","\n");}countbn = 0;fprintf(stderr,"Error: line %d: unterminated comment\n",startco+1);exit(0);}

<comment0><<EOF>>					{fprintf(yyout,"%s"," \n");while(countbn>0){countbn--;fprintf(yyout,"%s","\n");}countbn = 0;fprintf(stderr,"Error: line %d: unterminated comment\n",startco+1);exit(0);}

{newline}						linecount++;return yytext;	
{whitespace}						return yytext;
.							return yytext;
%%

int yywrap(void){
	return 1;
}

int main(int argc, char* argv[]){
	
	extern FILE *yyin, *yyout;
        int ntoken, vtoken;
	
        ntoken = yylex();
        while(ntoken){ 
                fprintf(yyout,"%s",yytext);
                ntoken = yylex();
        }
        return 0;
}
