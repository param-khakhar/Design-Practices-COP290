%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
%}

INTEGER    [0-9]+
SIGN	"-"

%%

exit.*			{ return EXIT; }
{SIGN}?{INTEGER}   	{ yylval.expr = strdup(yytext);  return INTEGER;}
[+-]        		{ yylval.expr = strdup(yytext);  return OPR1;  }
[/*]        		{ yylval.expr = strdup(yytext);  return OPR2;  }
\n          		{ return NEWLINE; }
.           		;

%%
