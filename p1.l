%{
#include <stdio.h>
#include <stdlib.h>
#include "p1.tab.h"
%}
%option noyywrap
%%
"i32" {yylval.strval = strdup(yytext); return TYPE;}
"f32" {yylval.strval = strdup(yytext); return TYPE;}
"chr" {yylval.strval = strdup(yytext); return TYPE;}
"str" {yylval.strval = strdup(yytext); return TYPE;}
"bool" {yylval.strval = strdup(yytext); return TYPE;}
"less_equal" {return LESS_EQ;}
"greater_equal" {return GREATER_EQ;}
"not_equal" {return NOT_EQ;}
"equal" {return EQ;}
"and" {return AND;}
"or" {return OR;}
"if" {return IF;}
"else" {return ELSE;}
"if_end" {return END_IF;}
"for" {return FOR;}
"fn" {return BEGIN_FN;}
"fn_end" {return END_FN;}
"for_end" {return END_FOR;}
"do" {return DO;}
"while" {return WHILE;}
"while_end" {return END_WHILE;}
"begin_class" {return BEGIN_CLASS;}
"end_class" {return END_CLASS;}
"begin_main" {return BEGIN_MAIN;}
"end_main" {return END_MAIN;}
"return" {return RETURN;}
"Eval" {return EVAL;}
"TypeOf" {return TYPEOF;}
[_a-zA-Z][_a-zA-Z0-9]* {yylval.strval=strdup(yytext); return ID;}
\"[_a-zA-Z0-9 ]+\" {yylval.strval = strdup(yytext); yylval.strval++; yylval.strval[strlen(yylval.strval)-1] = 0; return STRING;}
\'[_a-zA-Z0-9 ]\' {yylval.strval = strdup(yytext); yylval.strval++; yylval.strval[strlen(yylval.strval)-1] = 0; return CHAR;}
"=" {yylval.strval=strdup(yytext);return ASSIGN;}
-?[1-9][0-9]*|0 {yylval.intval=atoi(yytext); return NR;}
-?[1-9][0-9]*\.[0-9]+|-?0\.[0-9]+  {yylval.floatval=atof(yytext); return NR_FLOAT;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
