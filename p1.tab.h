/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_P1_TAB_H_INCLUDED
# define YY_YY_P1_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LESS_EQ = 258,                 /* LESS_EQ  */
    GREATER_EQ = 259,              /* GREATER_EQ  */
    NOT_EQ = 260,                  /* NOT_EQ  */
    EQ = 261,                      /* EQ  */
    RETURN = 262,                  /* RETURN  */
    BEGIN_FN = 263,                /* BEGIN_FN  */
    END_FN = 264,                  /* END_FN  */
    AND = 265,                     /* AND  */
    OR = 266,                      /* OR  */
    ID = 267,                      /* ID  */
    STRING = 268,                  /* STRING  */
    TYPE = 269,                    /* TYPE  */
    ASSIGN = 270,                  /* ASSIGN  */
    BEGIN_MAIN = 271,              /* BEGIN_MAIN  */
    END_MAIN = 272,                /* END_MAIN  */
    BEGIN_CLASS = 273,             /* BEGIN_CLASS  */
    END_CLASS = 274,               /* END_CLASS  */
    IF = 275,                      /* IF  */
    END_IF = 276,                  /* END_IF  */
    ELSE = 277,                    /* ELSE  */
    FOR = 278,                     /* FOR  */
    END_FOR = 279,                 /* END_FOR  */
    CONSTANT = 280,                /* CONSTANT  */
    WHILE = 281,                   /* WHILE  */
    END_WHILE = 282,               /* END_WHILE  */
    DO = 283,                      /* DO  */
    EVAL = 284,                    /* EVAL  */
    TYPEOF = 285,                  /* TYPEOF  */
    CHAR = 286,                    /* CHAR  */
    NR = 287,                      /* NR  */
    NR_FLOAT = 288                 /* NR_FLOAT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 508 "p1.y"

    float floatval;
    int intval;
    char* strval;
    struct AST* tree;

#line 104 "p1.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_P1_TAB_H_INCLUDED  */
