%{
#include <stdio.h>
#include <stdlib.h>
#include "p1.tab.h"
%}
%option noyywrap

ID [_a-zA-Z][_a-zA-Z0-9]* 
STRING \"[_a-zA-Z0-9 ]+\"
CHAR \'[_a-zA-Z0-9 ]\'
NR -?[1-9][0-9]*|0
FLOAT -?[1-9][0-9]*\.[0-9]+|-?0\.[0-9]+

%%
"i32" {yylval.string_value = strdup(yytext); return TYPE;}
"f32" {yylval.string_value = strdup(yytext); return TYPE;}
"chr" {yylval.string_value = strdup(yytext); return TYPE;}
"str" {yylval.string_value = strdup(yytext); return TYPE;}
"bool" {yylval.string_value = strdup(yytext); return TYPE;}
"const" {return CONSTANT;}
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
{ID} {yylval.string_value=strdup(yytext); return ID;}
{STRING} {yylval.string_value = strdup(yytext); yylval.string_value++; yylval.string_value[strlen(yylval.string_value)-1] = 0; return STRING;}
{CHAR} {yylval.string_value = strdup(yytext); yylval.string_value++; yylval.string_value[strlen(yylval.string_value)-1] = 0; return CHAR;}
"<-" {yylval.string_value=strdup(yytext);return ASSIGN;}
{NR} {yylval.int_value=atoi(yytext); return NR;}
{FLOAT}  {yylval.float_value=atof(yytext); return NR_FLOAT;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
