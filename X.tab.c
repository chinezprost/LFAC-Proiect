/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "X.y"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

char buff[100];
int varCount = 0;
int functionsCount = 0;
int fd, fd1;
char errMsg[100];

enum nodetype {
    OPERATOR = 1,
    IDENTIFICATOR = 2,
    NUMAR = 3,
    NUMAR_FLOAT = 4,
    STRING_OR_CHAR = 5
};

struct informatii {
    int int_val;
    char string_val[500];
    float float_val;
    char char_val;
};

struct variabila {
    char nume[100];
    char tip[10];
    struct informatii info;
    int local;
    int isConst;
    int inClass;
    int arrSize;
    int arr[100];
    int elemente;
} symbolTable[100];

struct param {
    char nume[200];
    char tip[20];
} temp[10];

struct func {
    char nume[200];
    char tip[20];
    unsigned int nrArgs;
    int inClass;
    char retId[20];
    struct param val[30];
    char tipuriParam[200];
} symbolTableFunctions[200];

struct AST {
    char nume[50];
    struct AST* st;
    struct AST* dr;
    enum nodetype nodeType;
};

struct AST* buildAST(char* nume, struct AST* st, struct AST* dr, enum nodetype type)
{
    struct AST* nod = (struct AST*)malloc(sizeof(struct AST));
    strcpy(nod->nume, strdup(nume));
    nod->st = st;
    nod->dr = dr;
    nod->nodeType = type;
    return nod;
}

void print_error()
{
    printf("Eroare: %s\n", errMsg);
}

void initialize()
{
    for(int i = 0; i < 100; i++)
    {
        bzero(&symbolTable[i].nume, sizeof(symbolTable[i].nume));
        bzero(&symbolTable[i].tip, sizeof(symbolTable[i].tip));
        symbolTable[i].info.int_val = 0;
        symbolTable[i].info.float_val = 0;
        symbolTable[i].arrSize = 0;
        strcpy(symbolTable[i].info.string_val, "");
        symbolTable[i].info.char_val = '\0';
    }
}

void addInTable(int isc, int arrS, char s[], char tip[], int intv, float floatv, char *c, char *strv, int clasa, int yylineno)
{
    if(!strcmp(tip, "tip"))
    {
        int aux = varCount - 1;
        while(!strcmp(symbolTable[aux].tip, "") && aux >= 0)
        {
            strcpy(symbolTable[aux].tip, s);
            symbolTable[aux].isConst = isc;
            symbolTable[aux].inClass = clasa;
            aux--;
        }
    }
    else
    {
        if(!strcmp(tip, "variabila"))
        {
            int esteDejaDeclarata = 0;
            for(int i = 0; i < varCount; i++)
            {
                if(!strcmp(symbolTable[i].nume, s))
                {
                    esteDejaDeclarata = 1;
                    break;
                }
            }
            if(esteDejaDeclarata)
            {
                sprintf(errMsg, "Linia %d, variabila %s a mai fost declarata!",yylineno, s);
                print_error();
                exit(0);
            }
            else
            {
                strcpy(symbolTable[varCount].nume, s);
                symbolTable[varCount].info.int_val = intv;
                symbolTable[varCount].info.float_val = floatv;
                symbolTable[varCount].info.char_val = c[0];
                symbolTable[varCount].arrSize = arrS;
                strcpy(symbolTable[varCount].info.string_val, strv);
                varCount++;
            }
        }
    }
}

void Verif(char s[], int yylineno, int vec)
{
    int i;
    int existaVariabila = 0;
    for(i = 0; i < varCount; i++)
    {
        if(!strcmp(symbolTable[i].nume, s))
        {
            existaVariabila = 1;
            break;
        }
    }
    if(!existaVariabila)
    {
        sprintf(errMsg, "Linia %d, variabila %s nu este declarata!",yylineno, s);
        print_error();
        exit(0);
    }
    else
    {
        if(vec > 0 && symbolTable[i].arrSize == 0)
        {
            sprintf(errMsg, "Linia %d, variabila %s nu este un array!",yylineno, s);
            print_error();
            exit(0);
        }
        else if(vec == 0 && symbolTable[i].arrSize > 0)
        {
            sprintf(errMsg, "Linia %d, variabila %s este un array!",yylineno, s);
            print_error();
            exit(0);
        }
    }
}

void addInTableFunctions(char tipp[], char s[], char type[], int yylineno, int clasa, char param[])
{
    if(!strcmp(type, "tip"))
    {
        for(int i = 0; i < functionsCount; i++)
            if(!strcmp(symbolTableFunctions[i].nume, s))
            {
                sprintf(errMsg, "Linia %d, functia %s nu este definita!",yylineno, s);
                print_error();
                exit(0);
            }
        strcpy(symbolTableFunctions[functionsCount].nume, s);
        strcpy(symbolTableFunctions[functionsCount].tip, tipp);
        symbolTableFunctions[functionsCount].inClass = clasa;
        symbolTableFunctions[functionsCount].nrArgs = 0;
        bzero(symbolTableFunctions[functionsCount].tipuriParam, sizeof(symbolTableFunctions[functionsCount].tipuriParam));
        if(strcmp(param, ""))
        {
            char *p = strtok(param, ",");
            while(p != NULL)
            {
                char aux[100];
                char p1[100];
                strcpy(p1, strchr(p, ' '));
                strncpy(aux, p, strlen(p) - strlen(p1));
                strcat(symbolTableFunctions[functionsCount].tipuriParam, aux);
                strcat(symbolTableFunctions[functionsCount].tipuriParam, ",");
                strcpy(symbolTableFunctions[functionsCount].val[symbolTableFunctions[functionsCount].nrArgs].tip, aux);
                strcpy(symbolTableFunctions[functionsCount].val[symbolTableFunctions[functionsCount].nrArgs].nume, p + strlen(aux));
                symbolTableFunctions[functionsCount].nrArgs++;
                p = strtok(NULL, ",");
            }
            symbolTableFunctions[functionsCount].tipuriParam[strlen(symbolTableFunctions[functionsCount].tipuriParam) - 1] = '\0';
        }
        functionsCount++;
    }
}

void VerifFct(char s[], char param[], int yylineno)
{
    int i;
    int existaFunctie = 0;
    for(i = 0; i < functionsCount; i++)
    {
        if(!strcmp(symbolTableFunctions[i].nume, s))
        {
            existaFunctie = 1;
            break;
        }
    }
    if(!existaFunctie)
    {
        sprintf(errMsg, "Linia %d, functia %s nu este definita!",yylineno, s);
        print_error();
        exit(0);
    }
    else
    {
        if(strcmp(param, symbolTableFunctions[i].tipuriParam))
        {
            sprintf(errMsg, "Linia %d, functia %s nu este apelata corect!",yylineno, s);
            print_error();
            exit(0);
        }
    }
}

void Clasa(char s[])
{
    int aux = varCount - 1;
    while(symbolTable[aux].inClass && aux >= 0)
    {
        char auxchar[100];
        bzero(&auxchar, sizeof(auxchar));
        strcpy(auxchar, symbolTable[aux].nume);
        strcpy(symbolTable[aux].nume, s);
        strcat(symbolTable[aux].nume, ".");
        strcat(symbolTable[aux].nume, auxchar);
        symbolTable[aux].inClass = 0;
        aux--;
    }
    aux = functionsCount - 1;
    while(symbolTableFunctions[aux].inClass && aux >= 0)
    {
        char auxchar[100];
        bzero(&auxchar, sizeof(auxchar));
        strcpy(auxchar, symbolTableFunctions[aux].nume);
        strcpy(symbolTableFunctions[aux].nume, s);
        strcat(symbolTableFunctions[aux].nume, ".");
        strcat(symbolTableFunctions[aux].nume, auxchar);
        symbolTableFunctions[aux].inClass = 0;
        aux--;   
    }
}

int getIdValue(char s[], int yylineno)
{
    for(int i = 0; i < varCount; i++)
    {
        if(!strcmp(symbolTable[i].nume, s))
        {
            if(symbolTable[i].arrSize > 0)
            {
                sprintf(errMsg, "Linia %d, array %s folosit incorect", yylineno, s);
                print_error();
                exit(0);
            }
            return symbolTable[i].info.int_val;
        }
    }
}

char* getIdType(char s[])
{
    for(int i = 0; i < varCount; i++)
        if(!strcmp(symbolTable[i].nume, s))
            return symbolTable[i].tip;
    return (char *)"no type";
}

int evalAST(struct AST* tree, int yylineno)
{
    if(tree->st == NULL && tree->dr == NULL)
    {
        if(tree->nodeType == IDENTIFICATOR)
        {
            char tip[10];
            bzero(&tip, 10);
            strcpy(tip, getIdType(tree->nume));
            if(!strcmp(tip, "chr"))
            {
                sprintf(errMsg, "Linia %d: variabila %s este de tip char!", yylineno, tree->nume);
                print_error();
                exit(0);
            }
            else
            if(!strcmp(tip, "bool"))
            {
                sprintf(errMsg, "Linia %d: variabila %s este de tip bool!", yylineno, tree->nume);
                print_error();
                exit(0);
            }
            else
            if(!strcmp(tip, "str"))
            {
                sprintf(errMsg, "Linia %d: variabila %s este de tip string!", yylineno, tree->nume);
                print_error();
                exit(0);
            }
            else
            {
                if(!strcmp(tip, "i32"))
                {   
                    std::cout << "TIP: " <<  getIdValue(tree->nume, yylineno) << '\n';
                    return getIdValue(tree->nume, yylineno);
                }
            }
        }
        else
        {
            if(tree->nodeType == NUMAR)
            {   
                std::cout << "NUMAR:" << tree->nodeType << '\n';
                return atoi(tree->nume);
            }
            return 0;
        }
    }
    else
    {
        int val_stanga, val_dreapta;

        val_stanga = evalAST(tree->st, yylineno);
        val_dreapta = evalAST(tree->dr, yylineno);

        
        if(!strcmp(tree->nume, "+")) {return val_stanga + val_dreapta;}
        if(!strcmp(tree->nume, "-")) {return val_stanga - val_dreapta;}
        if(!strcmp(tree->nume, "*")) {return val_stanga * val_dreapta;}
        if(!strcmp(tree->nume, "/")) 
        {
            if(val_dreapta) {return val_stanga / val_dreapta;}
            else
            {
                sprintf(errMsg, "Linia %d, impartirea la 0 nu se poate efectua!", yylineno);
                print_error();
                exit(0);
            }
        }
    }
}

char *TypeOf(struct AST* tree, float nrfloat, int boolval, char sir_str[], char chr_sir[], int yylineno)
{
    if(tree == NULL)
    {
        if(nrfloat != 0)
            return (char*)"f32";
        if(boolval != 0)
            return (char*)"bool";
        if(strcmp(sir_str, ""))
            return (char*)"str";
        if(strcmp(chr_sir, ""))
            return (char*)"chr";
    }
    else
    {
        if(tree->st == NULL && tree->dr == NULL)
        {
            if(tree->nodeType == IDENTIFICATOR)
            {
                char tip[10];
                bzero(&tip, 10);
                strcpy(tip, getIdType(tree->nume));
                if(!strcmp(tip, "i32"))
                    return (char*)"i32";
                if(!strcmp(tip, "bool"))
                    return (char*)"bool";
                if(!strcmp(tip, "f32"))
                    return (char*)"f32";
            }
            else
            {
                int x = evalAST(tree, yylineno);
                return "i32";
            }
        }
    }
}

int Eval(struct AST* tree, int yylineno) {
    return evalAST(tree, yylineno);
}

int getArrVal(char nume[], int id, int yylineno)
{
    for(int i = 0; i < varCount; i++)
    {
        if(!strcmp(symbolTable[i].nume, nume))
        {
            if(symbolTable[i].arrSize >= id)
                return symbolTable[i].arr[id];
            else
            {
                sprintf(errMsg, "Linia %d, pozitie depasita!", yylineno);
                print_error();
                exit(0);
            }
        }     
    }
    sprintf(errMsg, "Linia %d, array inexistent!", yylineno);
    print_error();
    exit(0);
}

void actualizareTabel(char nume[], char tip[], int value, int yylineno, float fvalue, char svalue[])
{
    for(int i = 0; i < varCount; i++)
    {
        if(!strcmp(symbolTable[i].nume, nume))
        {
            if(strcmp(symbolTable[i].tip, tip))
            {
                sprintf(errMsg, "Linia %d, tip de date diferit!", yylineno);
                print_error();
                exit(0);
            }
            if(!strcmp(tip, "i32") || !strcmp(tip, "bool"))
                symbolTable[i].info.int_val = value;
            else
                if(!strcmp(tip, "f32"))
                    symbolTable[i].info.float_val = fvalue;
                else
                    if(!strcmp(tip, "str"))
                        strcpy(symbolTable[i].info.string_val, svalue);
                    else
                        if(!strcmp(tip, "chr"))
                            symbolTable[i].info.char_val = svalue[1];
            break;
        }
    }
}

char *ConstruiescRasp(char sir1[], char sir2[], char inter[3])
{
    char *p;
    p = (char*)(malloc(strlen(sir1) + strlen(sir2) + 1));
    strcpy(p, sir1);
    strcat(p, inter);
    strcat(p, sir2);
    return p;
}

char *FctRetType(char fct[])
{
    for(int i = 0; i < functionsCount; i++)
        if(!strcmp(symbolTableFunctions[i].nume, fct))
            return symbolTableFunctions[i].tip;
}

void printVars(int fd)
{
    char sp[2], inf[510];
    strcpy(sp, " ");
    for(int i = 0; i < varCount; i++)
    {
        write(fd, symbolTable[i].nume, strlen(symbolTable[i].nume));
        write(fd, sp, strlen(sp));
        write(fd, symbolTable[i].tip, strlen(symbolTable[i].tip));
        write(fd, sp, strlen(sp));
        if(!strcmp(symbolTable[i].tip, "i32")) {snprintf(inf,100,"%d", symbolTable[i].info.int_val);write(fd, inf, strlen(inf));}
        else if(!strcmp(symbolTable[i].tip, "str")) {snprintf(inf,500,"%s", symbolTable[i].info.string_val);write(fd, inf, strlen(inf));}
        else if(!strcmp(symbolTable[i].tip, "f32")) {snprintf(inf,500,"%f", symbolTable[i].info.float_val);write(fd, inf, strlen(inf));}
        else if(!strcmp(symbolTable[i].tip, "chr")) {snprintf(inf,500,"%c", symbolTable[i].info.char_val);write(fd, inf, strlen(inf));}
        else if(!strcmp(symbolTable[i].tip, "bool")) {snprintf(inf,500,"%d", symbolTable[i].info.int_val);write(fd, inf, strlen(inf));}
        write(fd, "\n", strlen("\n"));
    }
}

void printFunctions(int fd)
{
    char sp[2], inf[510];
    strcpy(sp, " ");
    for(int i = 0; i < functionsCount; i++)
    {
        write(fd, symbolTableFunctions[i].tip, strlen(symbolTableFunctions[i].tip));
        write(fd, sp, strlen(sp));
        write(fd, symbolTableFunctions[i].nume, strlen(symbolTableFunctions[i].nume));
        write(fd, sp, strlen(sp));
        write(fd, "(", strlen("("));
        int j = 0;
        for(j=0; j<symbolTableFunctions[i].nrArgs - 1; j++)
        {
            write(fd, symbolTableFunctions[i].val[j].tip, strlen(symbolTableFunctions[i].val[j].tip));
            write(fd, symbolTableFunctions[i].val[j].nume, strlen(symbolTableFunctions[i].val[j].nume));
            write(fd, ",", strlen(","));
            write(fd, sp, strlen(sp));
        }
        if(symbolTableFunctions[i].nrArgs!=0)
        {
            write(fd, symbolTableFunctions[i].val[symbolTableFunctions[i].nrArgs-1].tip, strlen(symbolTableFunctions[i].val[symbolTableFunctions[i].nrArgs-1].tip));
            write(fd, symbolTableFunctions[i].val[symbolTableFunctions[i].nrArgs-1].nume, strlen(symbolTableFunctions[i].val[symbolTableFunctions[i].nrArgs-1].nume));
        }
        write(fd, ")", strlen(")"));
        write(fd, "\n", strlen("\n"));
    }
}

extern FILE* yyin;
extern int yylex();
extern char* yytext;
void yyerror(char* s);
extern int yylineno;


#line 601 "X.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "X.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LESS_EQ = 3,                    /* LESS_EQ  */
  YYSYMBOL_GREATER_EQ = 4,                 /* GREATER_EQ  */
  YYSYMBOL_NOT_EQ = 5,                     /* NOT_EQ  */
  YYSYMBOL_EQ = 6,                         /* EQ  */
  YYSYMBOL_RETURN = 7,                     /* RETURN  */
  YYSYMBOL_BEGIN_FN = 8,                   /* BEGIN_FN  */
  YYSYMBOL_END_FN = 9,                     /* END_FN  */
  YYSYMBOL_AND = 10,                       /* AND  */
  YYSYMBOL_OR = 11,                        /* OR  */
  YYSYMBOL_ID = 12,                        /* ID  */
  YYSYMBOL_STRING = 13,                    /* STRING  */
  YYSYMBOL_TYPE = 14,                      /* TYPE  */
  YYSYMBOL_ASSIGN = 15,                    /* ASSIGN  */
  YYSYMBOL_BEGIN_MAIN = 16,                /* BEGIN_MAIN  */
  YYSYMBOL_END_MAIN = 17,                  /* END_MAIN  */
  YYSYMBOL_BEGIN_CLASS = 18,               /* BEGIN_CLASS  */
  YYSYMBOL_END_CLASS = 19,                 /* END_CLASS  */
  YYSYMBOL_IF = 20,                        /* IF  */
  YYSYMBOL_END_IF = 21,                    /* END_IF  */
  YYSYMBOL_ELSE = 22,                      /* ELSE  */
  YYSYMBOL_FOR = 23,                       /* FOR  */
  YYSYMBOL_END_FOR = 24,                   /* END_FOR  */
  YYSYMBOL_CONSTANT = 25,                  /* CONSTANT  */
  YYSYMBOL_WHILE = 26,                     /* WHILE  */
  YYSYMBOL_END_WHILE = 27,                 /* END_WHILE  */
  YYSYMBOL_DO = 28,                        /* DO  */
  YYSYMBOL_EVAL = 29,                      /* EVAL  */
  YYSYMBOL_TYPEOF = 30,                    /* TYPEOF  */
  YYSYMBOL_CHAR = 31,                      /* CHAR  */
  YYSYMBOL_NR = 32,                        /* NR  */
  YYSYMBOL_NR_FLOAT = 33,                  /* NR_FLOAT  */
  YYSYMBOL_34_ = 34,                       /* '<'  */
  YYSYMBOL_35_ = 35,                       /* '>'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '+'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_39_ = 39,                       /* '*'  */
  YYSYMBOL_40_ = 40,                       /* ';'  */
  YYSYMBOL_41_ = 41,                       /* '('  */
  YYSYMBOL_42_ = 42,                       /* ')'  */
  YYSYMBOL_43_ = 43,                       /* ','  */
  YYSYMBOL_44_ = 44,                       /* '['  */
  YYSYMBOL_45_ = 45,                       /* ']'  */
  YYSYMBOL_46_ = 46,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_progr = 48,                     /* progr  */
  YYSYMBOL_rest1 = 49,                     /* rest1  */
  YYSYMBOL_rest2 = 50,                     /* rest2  */
  YYSYMBOL_sectiunea1 = 51,                /* sectiunea1  */
  YYSYMBOL_sectiunea2 = 52,                /* sectiunea2  */
  YYSYMBOL_sectiunea3 = 53,                /* sectiunea3  */
  YYSYMBOL_declaratieVariabila = 54,       /* declaratieVariabila  */
  YYSYMBOL_declaratieVariabilaClasa = 55,  /* declaratieVariabilaClasa  */
  YYSYMBOL_declaratieFunctie = 56,         /* declaratieFunctie  */
  YYSYMBOL_declaratieFunctieClasa = 57,    /* declaratieFunctieClasa  */
  YYSYMBOL_lista_param = 58,               /* lista_param  */
  YYSYMBOL_param = 59,                     /* param  */
  YYSYMBOL_clasa = 60,                     /* clasa  */
  YYSYMBOL_sectiuneaclasa1 = 61,           /* sectiuneaclasa1  */
  YYSYMBOL_sectiuneaclasa2 = 62,           /* sectiuneaclasa2  */
  YYSYMBOL_interior_clasa = 63,            /* interior_clasa  */
  YYSYMBOL_lista_id = 64,                  /* lista_id  */
  YYSYMBOL_bloc = 65,                      /* bloc  */
  YYSYMBOL_list = 66,                      /* list  */
  YYSYMBOL_statement = 67,                 /* statement  */
  YYSYMBOL_cond = 68,                      /* cond  */
  YYSYMBOL_opr = 69,                       /* opr  */
  YYSYMBOL_if = 70,                        /* if  */
  YYSYMBOL_for = 71,                       /* for  */
  YYSYMBOL_do = 72,                        /* do  */
  YYSYMBOL_while = 73,                     /* while  */
  YYSYMBOL_e = 74,                         /* e  */
  YYSYMBOL_pseudo_e = 75,                  /* pseudo_e  */
  YYSYMBOL_lista_apel = 76                 /* lista_apel  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   392

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  255

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    42,    39,    37,    43,    36,    46,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
      34,     2,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   562,   562,   565,   568,   571,   572,   575,   576,   579,
     580,   583,   584,   587,   588,   591,   592,   593,   594,   597,
     598,   601,   602,   605,   610,   613,   614,   617,   618,   621,
     622,   623,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   635,   636,   637,   641,   645,   646,   647,   648,   649,
     650,   654,   665,   666,   667,   668,   680,   690,   695,   698,
     699,   702,   705,   716,   717,   718,   719,   720,   721,   724,
     725,   728,   729,   732,   735,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   749,   750,   753,   762,   771,   780,
     789,   790,   791,   792,   793,   794,   795,   796,   799,   811,
     829,   830,   831,   832,   833,   834
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LESS_EQ",
  "GREATER_EQ", "NOT_EQ", "EQ", "RETURN", "BEGIN_FN", "END_FN", "AND",
  "OR", "ID", "STRING", "TYPE", "ASSIGN", "BEGIN_MAIN", "END_MAIN",
  "BEGIN_CLASS", "END_CLASS", "IF", "END_IF", "ELSE", "FOR", "END_FOR",
  "CONSTANT", "WHILE", "END_WHILE", "DO", "EVAL", "TYPEOF", "CHAR", "NR",
  "NR_FLOAT", "'<'", "'>'", "'-'", "'+'", "'/'", "'*'", "';'", "'('",
  "')'", "','", "'['", "']'", "'.'", "$accept", "progr", "rest1", "rest2",
  "sectiunea1", "sectiunea2", "sectiunea3", "declaratieVariabila",
  "declaratieVariabilaClasa", "declaratieFunctie",
  "declaratieFunctieClasa", "lista_param", "param", "clasa",
  "sectiuneaclasa1", "sectiuneaclasa2", "interior_clasa", "lista_id",
  "bloc", "list", "statement", "cond", "opr", "if", "for", "do", "while",
  "e", "pseudo_e", "lista_apel", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-144)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      10,    -7,    -4,    22,    56,   -15,    78,  -144,    -7,  -144,
      20,  -144,   176,    24,  -144,  -144,    87,    -7,    14,  -144,
      69,    57,    77,  -144,   139,  -144,  -144,  -144,   118,   105,
     122,  -144,   173,    85,   150,  -144,   185,    64,    73,    71,
      -1,  -144,  -144,   112,   187,   209,    -7,    -7,    -7,   301,
      85,    85,    85,    85,    -7,   196,   230,   240,   214,   211,
     248,   258,   234,   235,    71,   263,   259,    21,   242,   246,
     256,   250,  -144,  -144,  -144,    93,    40,   236,   252,  -144,
    -144,  -144,  -144,   101,   101,  -144,  -144,  -144,    -7,  -144,
      -1,   287,   285,   131,  -144,    -7,  -144,  -144,   261,   263,
     290,   267,  -144,    39,   112,   279,   300,    85,    75,  -144,
     273,   274,   283,    -1,   288,  -144,  -144,  -144,  -144,  -144,
    -144,   191,  -144,   112,  -144,   205,    -1,  -144,   109,  -144,
    -144,   284,  -144,  -144,    93,   135,   275,     4,   308,   174,
    -144,  -144,    75,   315,   115,   193,   115,   306,  -144,  -144,
    -144,  -144,    93,   141,    85,  -144,   229,  -144,   289,  -144,
     312,    85,   112,  -144,   112,   298,   321,   322,    75,    75,
      75,    75,  -144,   115,     2,   163,   326,   330,     5,   307,
    -144,   329,    85,  -144,  -144,    85,    93,   167,   184,   304,
     314,  -144,   212,   212,  -144,  -144,     7,    99,   115,   115,
      -1,  -144,  -144,  -144,  -144,  -144,  -144,    85,    85,   341,
      -1,   115,   353,   334,    93,  -144,  -144,  -144,   112,  -144,
    -144,   375,   241,    93,   339,    85,   217,    16,  -144,   354,
     223,  -144,    -1,   115,   344,  -144,   151,  -144,  -144,   268,
      -3,   115,  -144,  -144,    -1,    23,   345,    -1,    -1,   346,
     280,    -1,  -144,   293,  -144
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,    32,    11,     0,     1,
       0,     2,     0,     0,     7,     5,     0,     0,     0,    12,
      32,     0,     0,     3,     0,     8,     9,     6,    80,    40,
      42,    81,    38,     0,    36,    34,     0,     0,     0,     0,
       0,    10,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,    21,
       0,     0,     0,     0,    30,    31,     0,     0,     0,     0,
       0,     0,   104,   102,   100,    98,     0,     0,    84,    41,
      43,    39,    79,    76,    75,    78,    77,    37,     0,    23,
       0,     0,     0,    32,    13,     0,    25,    27,     0,    29,
       0,     0,    24,     0,     0,     0,     0,     0,     0,    44,
       0,     0,     0,     0,     0,    47,    48,    49,    50,    45,
      83,     0,    82,     0,    35,     0,     0,    22,     0,    14,
      26,     0,    28,    56,    51,     0,     0,     0,     0,    91,
      92,    93,     0,     0,     0,     0,     0,     0,    46,   105,
     103,   101,    99,     0,     0,    16,     0,    20,     0,    52,
       0,     0,     0,    54,     0,     0,     0,     0,     0,     0,
       0,     0,    53,     0,     0,     0,     0,     0,     0,     0,
      85,     0,     0,    15,    19,     0,    55,     0,     0,     0,
      96,    90,    87,    86,    88,    89,     0,     0,     0,     0,
       0,    63,    64,    65,    66,    68,    67,     0,     0,     0,
       0,     0,     0,     0,    58,    57,    95,    94,     0,    59,
      60,    61,     0,    62,     0,     0,     0,     0,    18,     0,
       0,    69,     0,     0,     0,    74,     0,    17,    97,     0,
       0,     0,    73,    70,     0,     0,     0,     0,     0,     0,
       0,     0,    72,     0,    71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -144,  -144,  -144,  -144,  -144,   382,   325,   378,
     -56,   -86,  -144,   367,  -144,   328,  -144,     6,  -144,   -40,
     -68,  -143,  -144,  -144,  -144,  -144,  -144,   -12,   -94,  -103
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,    11,    23,     4,    12,    24,     5,    62,    14,
      63,    58,    59,    26,    64,    65,    66,     7,    42,   226,
      71,   174,   207,   115,   116,   117,   118,   175,   143,    76
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      70,   135,   114,   178,    34,     6,   127,   198,   199,   101,
       8,    67,   198,   199,    19,   198,   199,   198,   199,   161,
     153,    49,     9,    35,     1,    15,   198,   199,    68,    69,
     196,    75,    20,   198,   199,     2,   103,   244,    83,    84,
      85,    86,   158,   101,   200,   162,    36,   210,   167,   219,
     125,    28,    79,    80,    81,   220,   221,   114,   236,   187,
      87,   188,   104,   247,    27,   105,    94,   106,   227,    38,
      10,    31,   133,   147,   192,   193,   194,   195,    56,   114,
      33,     2,   120,   121,    16,    60,   156,   139,   114,    39,
     240,   134,    75,    16,   124,   138,    61,    28,   245,    28,
      29,   129,   201,   202,   203,   204,    57,   140,   141,   152,
      37,    75,    17,    18,    37,   230,   142,    31,    30,    31,
      32,    17,    18,    56,    28,    72,    33,    28,    33,    50,
      51,    52,    53,   205,   206,    50,    51,    52,    53,    52,
      53,    82,   181,    73,    31,    74,    16,    31,    46,   186,
      75,   157,    75,    33,   114,    40,   173,    22,   114,    43,
     222,   197,    44,    67,    45,    47,   201,   202,   203,   204,
     213,   114,   128,   214,    17,    18,   246,   159,   121,   249,
      68,    69,   114,   180,   121,   114,    50,    51,    52,    53,
      21,   242,   239,    54,    22,   223,   224,   205,   206,    50,
      51,    52,    53,    28,   149,   176,    75,   177,   250,   215,
     121,   253,   154,   234,   155,   164,    48,    67,   165,    77,
     166,    78,   150,    31,   151,   110,   216,   121,   111,    67,
      55,   112,    33,   113,    68,    69,   182,   110,   183,    88,
     111,    67,    89,   112,   235,   113,    68,    69,    90,   110,
     170,   171,   111,    67,    92,   112,    91,   113,    68,    69,
      93,   110,   231,   232,   111,   238,   121,   112,    67,   113,
      68,    69,    95,   109,    96,    97,   110,   100,   102,   111,
      67,   122,   112,   107,   113,    68,    69,   108,   110,   243,
     119,   111,    67,   123,   112,   126,   113,    68,    69,    56,
     110,   130,   131,   111,   252,    67,   112,   132,   113,    68,
      69,   136,   137,   110,   144,   145,   111,   254,    67,   112,
     160,   113,    68,    69,   146,   128,   110,   185,   148,   111,
     189,   184,   179,   190,   113,    68,    69,    50,    51,    52,
      53,   208,   209,    82,    50,    51,    52,    53,   211,   217,
     163,   168,   169,   170,   171,   218,   225,   172,   168,   169,
     170,   171,   228,   237,   191,    50,    51,    52,    53,   212,
      50,    51,    52,    53,   229,    50,    51,    52,    53,   233,
      50,    51,    52,    53,   241,   198,    13,   248,   251,    98,
      25,    41,    99
};

static const yytype_uint8 yycheck[] =
{
      40,   104,    70,   146,    16,    12,    92,    10,    11,    65,
      14,    12,    10,    11,     8,    10,    11,    10,    11,    15,
     123,    33,     0,    17,    14,    40,    10,    11,    29,    30,
     173,    43,    12,    10,    11,    25,    15,    40,    50,    51,
      52,    53,   128,    99,    42,    41,    32,    42,   142,    42,
      90,    12,    46,    47,    48,   198,   199,   125,    42,   162,
      54,   164,    41,    40,    40,    44,    60,    46,   211,    12,
      14,    32,    33,   113,   168,   169,   170,   171,    14,   147,
      41,    25,    42,    43,    15,    14,   126,    12,   156,    12,
     233,   103,   104,    15,    88,   107,    25,    12,   241,    12,
      13,    95,     3,     4,     5,     6,    42,    32,    33,   121,
      41,   123,    43,    44,    41,   218,    41,    32,    31,    32,
      33,    43,    44,    14,    12,    13,    41,    12,    41,    36,
      37,    38,    39,    34,    35,    36,    37,    38,    39,    38,
      39,    42,   154,    31,    32,    33,    15,    32,    43,   161,
     162,    42,   164,    41,   222,    16,    41,    18,   226,    41,
     200,   173,    44,    12,    46,    43,     3,     4,     5,     6,
     182,   239,    41,   185,    43,    44,   244,    42,    43,   247,
      29,    30,   250,    42,    43,   253,    36,    37,    38,    39,
      14,    40,   232,    43,    18,   207,   208,    34,    35,    36,
      37,    38,    39,    12,    13,    12,   218,    14,   248,    42,
      43,   251,     7,   225,     9,    41,    43,    12,    44,    32,
      46,    12,    31,    32,    33,    20,    42,    43,    23,    12,
      45,    26,    41,    28,    29,    30,     7,    20,     9,    43,
      23,    12,    12,    26,    27,    28,    29,    30,     8,    20,
      38,    39,    23,    12,    43,    26,    42,    28,    29,    30,
      12,    20,    21,    22,    23,    42,    43,    26,    12,    28,
      29,    30,    14,    17,    40,    40,    20,    14,    19,    23,
      12,    45,    26,    41,    28,    29,    30,    41,    20,    21,
      40,    23,    12,    41,    26,     8,    28,    29,    30,    14,
      20,    40,    12,    23,    24,    12,    26,    40,    28,    29,
      30,    32,    12,    20,    41,    41,    23,    24,    12,    26,
      45,    28,    29,    30,    41,    41,    20,    15,    40,    23,
      32,    42,    26,    12,    28,    29,    30,    36,    37,    38,
      39,    15,    12,    42,    36,    37,    38,    39,    41,    45,
      42,    36,    37,    38,    39,    41,    15,    42,    36,    37,
      38,    39,     9,     9,    42,    36,    37,    38,    39,    40,
      36,    37,    38,    39,    40,    36,    37,    38,    39,    40,
      36,    37,    38,    39,    40,    10,     4,    42,    42,    64,
      12,    24,    64
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    25,    48,    51,    54,    12,    64,    14,     0,
      14,    49,    52,    54,    56,    40,    15,    43,    44,    64,
      12,    14,    18,    50,    53,    56,    60,    40,    12,    13,
      31,    32,    33,    41,    74,    64,    32,    41,    12,    12,
      16,    60,    65,    41,    44,    46,    43,    43,    43,    74,
      36,    37,    38,    39,    43,    45,    14,    42,    58,    59,
      14,    25,    55,    57,    61,    62,    63,    12,    29,    30,
      66,    67,    13,    31,    33,    74,    76,    32,    12,    64,
      64,    64,    42,    74,    74,    74,    74,    64,    43,    12,
       8,    42,    43,    12,    64,    14,    40,    40,    55,    62,
      14,    57,    19,    15,    41,    44,    46,    41,    41,    17,
      20,    23,    26,    28,    67,    70,    71,    72,    73,    40,
      42,    43,    45,    41,    64,    66,     8,    58,    41,    64,
      40,    12,    40,    33,    74,    76,    32,    12,    74,    12,
      32,    33,    41,    75,    41,    41,    41,    66,    40,    13,
      31,    33,    74,    76,     7,     9,    66,    42,    58,    42,
      45,    15,    41,    42,    41,    44,    46,    75,    36,    37,
      38,    39,    42,    41,    68,    74,    12,    14,    68,    26,
      42,    74,     7,     9,    42,    15,    74,    76,    76,    32,
      12,    42,    75,    75,    75,    75,    68,    74,    10,    11,
      42,     3,     4,     5,     6,    34,    35,    69,    15,    12,
      42,    41,    40,    74,    74,    42,    42,    45,    41,    42,
      68,    68,    66,    74,    74,    15,    66,    68,     9,    40,
      76,    21,    22,    40,    74,    27,    42,     9,    42,    66,
      68,    40,    40,    21,    40,    68,    67,    40,    42,    67,
      66,    42,    24,    66,    24
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    50,    51,    51,    52,    52,    53,
      53,    54,    54,    55,    55,    56,    56,    56,    56,    57,
      57,    58,    58,    59,    60,    61,    61,    62,    62,    63,
      63,    63,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    65,    66,    66,    66,    66,    66,
      66,    67,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    68,    68,    69,    69,    69,    69,    69,    69,    70,
      70,    71,    71,    72,    73,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    76,    76,
      76,    76,    76,    76,    76,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     3,     1,     2,     1,
       2,     2,     3,     2,     3,     8,     7,    11,    10,     5,
       4,     1,     3,     2,     4,     2,     3,     2,     3,     2,
       1,     1,     1,     4,     3,     6,     3,     5,     3,     5,
       3,     5,     3,     5,     3,     2,     3,     2,     2,     2,
       2,     3,     4,     4,     4,     5,     3,     6,     6,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     6,
       8,    13,    12,     7,     6,     3,     3,     3,     3,     3,
       1,     1,     4,     4,     3,     6,     3,     3,     3,     3,
       3,     1,     1,     1,     4,     4,     3,     6,     1,     3,
       1,     3,     1,     3,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* progr: sectiunea1 rest1  */
#line 562 "X.y"
                        {printf("program corect sintactic\n");}
#line 1851 "X.tab.c"
    break;

  case 11: /* declaratieVariabila: TYPE lista_id  */
#line 583 "X.y"
                                    { addInTable(0, 0, (yyvsp[-1].strval), "tip", 0, 0, "", "", 0, yylineno); }
#line 1857 "X.tab.c"
    break;

  case 12: /* declaratieVariabila: CONSTANT TYPE lista_id  */
#line 584 "X.y"
                                             {addInTable(1, 0, (yyvsp[-2].strval), "tip", 0, 0, "", "", 0, yylineno);}
#line 1863 "X.tab.c"
    break;

  case 13: /* declaratieVariabilaClasa: TYPE lista_id  */
#line 587 "X.y"
                                         { addInTable(0, 0, (yyvsp[-1].strval), "tip", 0, 0, "", "", 1, yylineno); }
#line 1869 "X.tab.c"
    break;

  case 14: /* declaratieVariabilaClasa: CONSTANT TYPE lista_id  */
#line 588 "X.y"
                                                  {addInTable(1, 0, (yyvsp[-2].strval), "tip", 0, 0, "", "", 1, yylineno);}
#line 1875 "X.tab.c"
    break;

  case 15: /* declaratieFunctie: TYPE ID '(' lista_param ')' BEGIN_FN list END_FN  */
#line 591 "X.y"
                                                                     { addInTableFunctions((yyvsp[-7].strval), (yyvsp[-6].strval), "tip", yylineno, 0, (yyvsp[-4].strval));}
#line 1881 "X.tab.c"
    break;

  case 16: /* declaratieFunctie: TYPE ID '(' ')' BEGIN_FN list END_FN  */
#line 592 "X.y"
                                                         { addInTableFunctions((yyvsp[-6].strval), (yyvsp[-5].strval), "tip", yylineno, 0, "");}
#line 1887 "X.tab.c"
    break;

  case 17: /* declaratieFunctie: TYPE ID '(' lista_param ')' BEGIN_FN list RETURN e ';' END_FN  */
#line 593 "X.y"
                                                                                  { int val = evalAST((yyvsp[-2].tree), yylineno); addInTableFunctions((yyvsp[-10].strval), (yyvsp[-9].strval), "tip", yylineno, 0, (yyvsp[-7].strval));}
#line 1893 "X.tab.c"
    break;

  case 18: /* declaratieFunctie: TYPE ID '(' ')' BEGIN_FN list RETURN e ';' END_FN  */
#line 594 "X.y"
                                                                      { int val = evalAST((yyvsp[-2].tree), yylineno); addInTableFunctions((yyvsp[-9].strval), (yyvsp[-8].strval), "tip", yylineno, 0, "");}
#line 1899 "X.tab.c"
    break;

  case 19: /* declaratieFunctieClasa: TYPE ID '(' lista_param ')'  */
#line 597 "X.y"
                                                     { addInTableFunctions((yyvsp[-4].strval), (yyvsp[-3].strval), "tip", yylineno, 1, (yyvsp[-1].strval));}
#line 1905 "X.tab.c"
    break;

  case 20: /* declaratieFunctieClasa: TYPE ID '(' ')'  */
#line 598 "X.y"
                                         { addInTableFunctions((yyvsp[-3].strval), (yyvsp[-2].strval), "tip", yylineno, 1, "");}
#line 1911 "X.tab.c"
    break;

  case 21: /* lista_param: param  */
#line 601 "X.y"
                    {(yyval.strval) = (yyvsp[0].strval);}
#line 1917 "X.tab.c"
    break;

  case 22: /* lista_param: param ',' lista_param  */
#line 602 "X.y"
                                    { (yyval.strval) = ConstruiescRasp((yyvsp[-2].strval), (yyvsp[0].strval), ",");}
#line 1923 "X.tab.c"
    break;

  case 23: /* param: TYPE ID  */
#line 605 "X.y"
                {
                (yyval.strval) = ConstruiescRasp((yyvsp[-1].strval), (yyvsp[0].strval), " ");
               }
#line 1931 "X.tab.c"
    break;

  case 24: /* clasa: BEGIN_CLASS ID interior_clasa END_CLASS  */
#line 610 "X.y"
                                                {Clasa((yyvsp[-2].strval));}
#line 1937 "X.tab.c"
    break;

  case 32: /* lista_id: ID  */
#line 626 "X.y"
              {addInTable(0, 0, (yyvsp[0].strval), "variabila", 0, 0, "", "", 0, yylineno);}
#line 1943 "X.tab.c"
    break;

  case 33: /* lista_id: ID '[' NR ']'  */
#line 627 "X.y"
                         { addInTable(0, (yyvsp[-1].intval), (yyvsp[-3].strval), "variabila", 0, 0, "", "", 0, yylineno);}
#line 1949 "X.tab.c"
    break;

  case 34: /* lista_id: ID ',' lista_id  */
#line 628 "X.y"
                           { addInTable(0, 0, (yyvsp[-2].strval), "variabila", 0, 0, "", "", 0, yylineno);}
#line 1955 "X.tab.c"
    break;

  case 35: /* lista_id: ID '[' NR ']' ',' lista_id  */
#line 629 "X.y"
                                      { addInTable(0, (yyvsp[-3].intval), (yyvsp[-5].strval), "variabila", 0, 0, "", "", 0, yylineno);}
#line 1961 "X.tab.c"
    break;

  case 36: /* lista_id: ID ASSIGN e  */
#line 630 "X.y"
                       { int val = Eval((yyvsp[0].tree), yylineno); addInTable(0, 0, (yyvsp[-2].strval), "variabila", val, 0, "", "", 0, yylineno);}
#line 1967 "X.tab.c"
    break;

  case 37: /* lista_id: ID ASSIGN e ',' lista_id  */
#line 631 "X.y"
                                    { int val = Eval((yyvsp[-2].tree), yylineno); addInTable(0, 0, (yyvsp[-4].strval), "variabila", 0, 0, "", "", 0, yylineno);}
#line 1973 "X.tab.c"
    break;

  case 38: /* lista_id: ID ASSIGN NR_FLOAT  */
#line 632 "X.y"
                              { addInTable(0, 0, (yyvsp[-2].strval), "variabila", 0, (yyvsp[0].floatval), "", "", 0, yylineno);}
#line 1979 "X.tab.c"
    break;

  case 39: /* lista_id: ID ASSIGN NR_FLOAT ',' lista_id  */
#line 633 "X.y"
                                           { addInTable(0, 0, (yyvsp[-4].strval), "variabila", 0, (yyvsp[-2].floatval), "", "", 0, yylineno);}
#line 1985 "X.tab.c"
    break;

  case 40: /* lista_id: ID ASSIGN STRING  */
#line 634 "X.y"
                            { addInTable(0, 0, (yyvsp[-2].strval), "variabila", 0, 0, "", (yyvsp[0].strval), 0, yylineno);}
#line 1991 "X.tab.c"
    break;

  case 41: /* lista_id: ID ASSIGN STRING ',' lista_id  */
#line 635 "X.y"
                                         { addInTable(0, 0, (yyvsp[-4].strval), "variabila", 0, 0, "", (yyvsp[-2].strval), 0, yylineno);}
#line 1997 "X.tab.c"
    break;

  case 42: /* lista_id: ID ASSIGN CHAR  */
#line 636 "X.y"
                          { addInTable(0, 0, (yyvsp[-2].strval), "variabila", 0, 0, (yyvsp[0].strval), "", 0, yylineno);}
#line 2003 "X.tab.c"
    break;

  case 43: /* lista_id: ID ASSIGN CHAR ',' lista_id  */
#line 637 "X.y"
                                       { addInTable(0, 0, (yyvsp[-4].strval), "variabila", 0, 0, (yyvsp[-2].strval), "", 0, yylineno);}
#line 2009 "X.tab.c"
    break;

  case 51: /* statement: ID ASSIGN e  */
#line 654 "X.y"
                        { 
                            Verif((yyvsp[-2].strval), yylineno, 0);
                            if(strcmp(getIdType((yyvsp[-2].strval)), "i32"))
                            {
                                sprintf(errMsg, "Linia %d, tip de date diferit", yylineno);
                                print_error();
                                exit(0);
                            }
                            int val = Eval((yyvsp[0].tree), yylineno);
                            actualizareTabel((yyvsp[-2].strval), "i32", val, yylineno, 0, "");
                        }
#line 2025 "X.tab.c"
    break;

  case 52: /* statement: ID '(' lista_apel ')'  */
#line 665 "X.y"
                                 {VerifFct((yyvsp[-3].strval), (yyvsp[-1].strval), yylineno);}
#line 2031 "X.tab.c"
    break;

  case 53: /* statement: TYPEOF '(' pseudo_e ')'  */
#line 666 "X.y"
                                   {printf("%s\n", (yyvsp[-1].strval));}
#line 2037 "X.tab.c"
    break;

  case 54: /* statement: EVAL '(' e ')'  */
#line 667 "X.y"
                          {printf("%d\n", Eval((yyvsp[-1].tree), yylineno));}
#line 2043 "X.tab.c"
    break;

  case 55: /* statement: ID '.' ID ASSIGN e  */
#line 668 "X.y"
                              { 
                                snprintf(buff,100,"%s.%s", (yyvsp[-4].strval), (yyvsp[-2].strval));
                                Verif(buff, yylineno, 0);
                                if(strcmp(getIdType((yyvsp[-4].strval)), "i32"))
                                {
                                    sprintf(errMsg, "Linia %d, tip de date diferit", yylineno);
                                    print_error();
                                    exit(0);
                                }
                                int val = Eval((yyvsp[0].tree), yylineno);
                                actualizareTabel(buff, "i32", val, yylineno, 0, "");
                              }
#line 2060 "X.tab.c"
    break;

  case 56: /* statement: ID ASSIGN NR_FLOAT  */
#line 680 "X.y"
                              {
                                Verif((yyvsp[-2].strval), yylineno, 0);
                                if(strcmp(getIdType((yyvsp[-2].strval)), "f32"))
                                {
                                    sprintf(errMsg, "Linia %d, tip de date diferit", yylineno);
                                    print_error();
                                    exit(0);
                                }
                                actualizareTabel((yyvsp[-2].strval), "f32", 0, yylineno, (yyvsp[0].floatval), "");
                              }
#line 2075 "X.tab.c"
    break;

  case 57: /* statement: ID '.' ID '(' lista_apel ')'  */
#line 690 "X.y"
                                        {
                                            snprintf(buff,100,"%s.%s", (yyvsp[-5].strval), (yyvsp[-3].strval));
                                            VerifFct(buff, (yyvsp[-1].strval), yylineno);

                                        }
#line 2085 "X.tab.c"
    break;

  case 58: /* statement: ID '[' NR ']' ASSIGN e  */
#line 695 "X.y"
                                  { Verif((yyvsp[-5].strval), yylineno, (yyvsp[-3].intval));}
#line 2091 "X.tab.c"
    break;

  case 59: /* cond: '(' cond ')'  */
#line 698 "X.y"
                    {(yyval.intval) = (yyvsp[-1].intval);}
#line 2097 "X.tab.c"
    break;

  case 60: /* cond: cond AND cond  */
#line 699 "X.y"
                     { int rez1=(yyvsp[-2].intval); int rez2=(yyvsp[0].intval); 
                       (yyval.intval)=(rez1 && rez2);
                     }
#line 2105 "X.tab.c"
    break;

  case 61: /* cond: cond OR cond  */
#line 702 "X.y"
                    { int rez1=(yyvsp[-2].intval); int rez2=(yyvsp[0].intval);
                      (yyval.intval)=(rez1 || rez2);
                    }
#line 2113 "X.tab.c"
    break;

  case 62: /* cond: e opr e  */
#line 705 "X.y"
               { 
                int rez1=evalAST((yyvsp[-2].tree), yylineno); int rez2=evalAST((yyvsp[0].tree), yylineno);
                if (strcmp((yyvsp[-1].strval), "less_equal")) (yyval.intval)=(rez1 <= rez2);
                if (strcmp((yyvsp[-1].strval), "greater_equal")) (yyval.intval)=(rez1 >= rez2);
                if (strcmp((yyvsp[-1].strval), "not_equal")) (yyval.intval)=(rez1 != rez2);
                if (strcmp((yyvsp[-1].strval), "equal")) (yyval.intval)=(rez1 == rez2);
                if (strcmp((yyvsp[-1].strval), ">")) (yyval.intval)=(rez1 > rez2);
                if (strcmp((yyvsp[-1].strval), "<")) (yyval.intval)=(rez1 < rez2);
                }
#line 2127 "X.tab.c"
    break;

  case 63: /* opr: LESS_EQ  */
#line 716 "X.y"
              {(yyval.strval) = (yyvsp[0].strval);}
#line 2133 "X.tab.c"
    break;

  case 64: /* opr: GREATER_EQ  */
#line 717 "X.y"
                 {(yyval.strval) = (yyvsp[0].strval);}
#line 2139 "X.tab.c"
    break;

  case 65: /* opr: NOT_EQ  */
#line 718 "X.y"
             {(yyval.strval) = (yyvsp[0].strval);}
#line 2145 "X.tab.c"
    break;

  case 66: /* opr: EQ  */
#line 719 "X.y"
          {(yyval.strval) = (yyvsp[0].strval);}
#line 2151 "X.tab.c"
    break;

  case 67: /* opr: '>'  */
#line 720 "X.y"
          {(yyval.strval) = ">";}
#line 2157 "X.tab.c"
    break;

  case 68: /* opr: '<'  */
#line 721 "X.y"
          {(yyval.strval) = "<";}
#line 2163 "X.tab.c"
    break;

  case 75: /* e: e '+' e  */
#line 738 "X.y"
            { (yyval.tree) = buildAST("+", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2169 "X.tab.c"
    break;

  case 76: /* e: e '-' e  */
#line 739 "X.y"
            { (yyval.tree) = buildAST("-", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2175 "X.tab.c"
    break;

  case 77: /* e: e '*' e  */
#line 740 "X.y"
            { (yyval.tree) = buildAST("*", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2181 "X.tab.c"
    break;

  case 78: /* e: e '/' e  */
#line 741 "X.y"
            { (yyval.tree) = buildAST("/", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2187 "X.tab.c"
    break;

  case 79: /* e: '(' e ')'  */
#line 742 "X.y"
              { (yyval.tree) = (yyvsp[-1].tree); }
#line 2193 "X.tab.c"
    break;

  case 80: /* e: ID  */
#line 743 "X.y"
       { Verif((yyvsp[0].strval), yylineno, 0); (yyval.tree) = buildAST((yyvsp[0].strval), NULL, NULL, IDENTIFICATOR);}
#line 2199 "X.tab.c"
    break;

  case 81: /* e: NR  */
#line 744 "X.y"
       { char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", (yyvsp[0].intval)); (yyval.tree) = buildAST(nr, NULL, NULL, NUMAR); }
#line 2205 "X.tab.c"
    break;

  case 82: /* e: ID '[' NR ']'  */
#line 745 "X.y"
                  {Verif((yyvsp[-3].strval), yylineno, 1); int val = getArrVal((yyvsp[-3].strval), (yyvsp[-1].intval), yylineno); char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", val); (yyval.tree) = buildAST(nr, NULL, NULL, NUMAR); }
#line 2211 "X.tab.c"
    break;

  case 83: /* e: ID '(' lista_apel ')'  */
#line 746 "X.y"
                          { VerifFct((yyvsp[-3].strval), (yyvsp[-1].strval), yylineno);
                            (yyval.tree) = buildAST("0", NULL, NULL, NUMAR);
                          }
#line 2219 "X.tab.c"
    break;

  case 84: /* e: ID '.' ID  */
#line 749 "X.y"
              { snprintf(buff,100,"%s.%s", (yyvsp[-2].strval), (yyvsp[0].strval)); Verif(buff, yylineno, 0);  (yyval.tree) = buildAST((yyvsp[-2].strval), NULL, NULL, IDENTIFICATOR);}
#line 2225 "X.tab.c"
    break;

  case 85: /* e: ID '.' ID '(' lista_apel ')'  */
#line 750 "X.y"
                                 { snprintf(buff,100,"%s.%s", (yyvsp[-5].strval), (yyvsp[-3].strval)); VerifFct(buff, (yyvsp[-3].strval), yylineno); (yyval.tree) = buildAST("0", NULL, NULL, NUMAR);}
#line 2231 "X.tab.c"
    break;

  case 86: /* pseudo_e: pseudo_e '+' pseudo_e  */
#line 753 "X.y"
                                 {
                                    if(strcmp((yyvsp[-2].strval), (yyvsp[0].strval)))
                                    {
                                        sprintf(errMsg, "Linia %d, tip de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    (yyval.strval) = (yyvsp[-2].strval);
                                 }
#line 2245 "X.tab.c"
    break;

  case 87: /* pseudo_e: pseudo_e '-' pseudo_e  */
#line 762 "X.y"
                                 {
                                    if(strcmp((yyvsp[-2].strval), (yyvsp[0].strval)))
                                    {
                                        sprintf(errMsg, "Linia %d, tip de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    (yyval.strval) = (yyvsp[-2].strval);
                                 }
#line 2259 "X.tab.c"
    break;

  case 88: /* pseudo_e: pseudo_e '/' pseudo_e  */
#line 771 "X.y"
                                 {
                                    if(strcmp((yyvsp[-2].strval), (yyvsp[0].strval)))
                                    {
                                        sprintf(errMsg, "Linia %d, tip de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    (yyval.strval) = (yyvsp[-2].strval);
                                 }
#line 2273 "X.tab.c"
    break;

  case 89: /* pseudo_e: pseudo_e '*' pseudo_e  */
#line 780 "X.y"
                                 {
                                    if(strcmp((yyvsp[-2].strval), (yyvsp[0].strval)))
                                    {
                                        sprintf(errMsg, "Linia %d, tip de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    (yyval.strval) = (yyvsp[-2].strval);
                                 }
#line 2287 "X.tab.c"
    break;

  case 90: /* pseudo_e: '(' pseudo_e ')'  */
#line 789 "X.y"
                            { (yyval.strval) = (yyvsp[-1].strval); }
#line 2293 "X.tab.c"
    break;

  case 91: /* pseudo_e: ID  */
#line 790 "X.y"
              {Verif((yyvsp[0].strval), yylineno, 0); (yyval.strval) = getIdType((yyvsp[0].strval));}
#line 2299 "X.tab.c"
    break;

  case 92: /* pseudo_e: NR  */
#line 791 "X.y"
              {(yyval.strval) = "i32";}
#line 2305 "X.tab.c"
    break;

  case 93: /* pseudo_e: NR_FLOAT  */
#line 792 "X.y"
                    {(yyval.strval) = "f32";}
#line 2311 "X.tab.c"
    break;

  case 94: /* pseudo_e: ID '[' NR ']'  */
#line 793 "X.y"
                         {Verif((yyvsp[-3].strval), yylineno, 1); (yyval.strval) = getIdType((yyvsp[-3].strval));}
#line 2317 "X.tab.c"
    break;

  case 95: /* pseudo_e: ID '(' lista_apel ')'  */
#line 794 "X.y"
                                 { VerifFct((yyvsp[-3].strval), (yyvsp[-1].strval), yylineno); (yyval.strval) = FctRetType((yyvsp[-3].strval));}
#line 2323 "X.tab.c"
    break;

  case 96: /* pseudo_e: ID '.' ID  */
#line 795 "X.y"
                     {snprintf(buff,100,"%s.%s", (yyvsp[-2].strval), (yyvsp[0].strval)); Verif((yyvsp[-2].strval), yylineno, 1); (yyval.strval) = getIdType(buff);}
#line 2329 "X.tab.c"
    break;

  case 97: /* pseudo_e: ID '.' ID '(' lista_apel ')'  */
#line 796 "X.y"
                                        { snprintf(buff,100,"%s.%s", (yyvsp[-5].strval), (yyvsp[-3].strval)); VerifFct(buff, (yyvsp[-1].strval), yylineno); (yyval.strval) = FctRetType(buff);}
#line 2335 "X.tab.c"
    break;

  case 98: /* lista_apel: e  */
#line 799 "X.y"
               {
                struct AST* tree = (yyvsp[0].tree);
                if(tree->st == NULL && tree->dr == NULL)
                {
                    if(tree->nodeType == IDENTIFICATOR)
                        (yyval.strval) = getIdType(tree->nume);
                    else
                        (yyval.strval) = "i32";
                }
                else
                    (yyval.strval) = "i32";
            }
#line 2352 "X.tab.c"
    break;

  case 99: /* lista_apel: lista_apel ',' e  */
#line 811 "X.y"
                              {
                    struct AST* tree = (yyvsp[0].tree);
                    char tip[20];
                        if(tree->st == NULL && tree->dr == NULL)
                        {
                            if(tree->nodeType == IDENTIFICATOR)
                                strcpy(tip, getIdType(tree->nume));
                            else
                                strcpy(tip, "i32");
                        }
                        else
                            strcpy(tip, "i32");
                        strcpy(buff, (yyvsp[-2].strval));
                        strcat(buff, ",");
                        strcat(buff, tip);
                        (yyval.strval) = buff;
                        // printf("%s.\n", tip);
                }
#line 2375 "X.tab.c"
    break;

  case 100: /* lista_apel: NR_FLOAT  */
#line 829 "X.y"
                      {(yyval.strval) = "f32";}
#line 2381 "X.tab.c"
    break;

  case 101: /* lista_apel: lista_apel ',' NR_FLOAT  */
#line 830 "X.y"
                                     { snprintf(buff,100,"%s,float",(yyvsp[-2].strval)); (yyval.strval) = buff;}
#line 2387 "X.tab.c"
    break;

  case 102: /* lista_apel: CHAR  */
#line 831 "X.y"
                  {(yyval.strval) = "chr";}
#line 2393 "X.tab.c"
    break;

  case 103: /* lista_apel: lista_apel ',' CHAR  */
#line 832 "X.y"
                                 {snprintf(buff,100,"%s,char",(yyvsp[-2].strval)); (yyval.strval) = buff;}
#line 2399 "X.tab.c"
    break;

  case 104: /* lista_apel: STRING  */
#line 833 "X.y"
                    {(yyval.strval) = "str";}
#line 2405 "X.tab.c"
    break;

  case 105: /* lista_apel: lista_apel ',' STRING  */
#line 834 "X.y"
                                   {snprintf(buff,100,"%s,string",(yyvsp[-2].strval)); (yyval.strval) = buff;}
#line 2411 "X.tab.c"
    break;


#line 2415 "X.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 837 "X.y"


void yyerror(char * s)
{
    printf("eroare: %s la linia:%d\n",s,yylineno);
}

int main(int argc, char** argv)
{
    fd = open("symbol_table.txt", O_RDWR|O_TRUNC);
    fd1 = open("symbol_table_functions.txt", O_RDWR|O_TRUNC);
    initialize();
    yyin = fopen(argv[1],"r");
    yyparse();
    printVars(fd);
    printFunctions(fd1);
}
