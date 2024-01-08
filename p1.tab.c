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
#line 1 "p1.y"

    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <string.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <fstream>

    // save buffer
    char internal_buffer[1024];
    int variable_counter = 0;
    int function_counter = 0;

    // char array to output errors
    char error_message[1024];

    // enum that represents the type of the node
    enum n_type
    {
        OPERATOR = 1,
        IDENTIFIER = 2,
        NUMBER = 3,
        FLOAT_NUMBER = 4,
        CHR_STR = 5
    };

    // member class that represents the informations of a symbol table
    class informations
    {
    public:
        char char_value = '\0';
        float float_value = 0;
        std::string string_value = "";
        int integer_value = 0;
    };

    // class that represents the symbol table
    class symbol_table_class
    {
    public:
        std::string name = "";
        std::string type = "";
        informations var_info;
        int local = 0;
        bool is_constant = 0;
        bool is_class = 0;
        int array_size = 0;
        int array[256] = {'\0'};
        int elements = 0;
    };

    // class that represents parameters
    class parameters
    {
    public:
        std::string name;
        std::string type;
    };

    // class of symbol table of functions
    class symbol_table_function_class
    {
    public:
        std::string name;
        std::string type;
        int argument_count;
        bool is_class;
        std::string ret_id;
        parameters value[50];
        std::string parameter_types;
    };

    parameters temp_params[50];
    symbol_table_class symbol_table[500];
    symbol_table_function_class symbol_table_functions[500];

    // the class of the Abstract Syntax Tree
    class AST
    {
    public:
        std::string name;
        AST* left;
        AST* right;
        n_type n_Type;
    };

    AST* AST_Init(std::string _name, AST* _left, AST* _right, n_type _type)
    {
        AST* new_node = new AST;
        new_node->name = _name;
        new_node->left = _left;
        new_node->right = _right;
        new_node->n_Type = _type;

        return new_node;
    }

    void handle_error()
    {
        std::cout << '\n';
    }

    void insert_table(bool _is_constant, int _array_size, std::string _string, std::string _type, int _int_value, float _float_value, char _char_value, std::string _string_value, bool _is_class, int yylineno)
    {
        //std::cout << _string << " " << _type << '\n';
        if(_type == "type")
        {
            int temp = variable_counter - 1;
            while(symbol_table[temp].type == "" && temp >= 0)
            {
                symbol_table[temp].type = _string;
                symbol_table[temp].is_constant = _is_constant;
                symbol_table[temp].is_class = _is_class;
                temp = temp - 1;
            }
        }
        else
        {
            if(_type == "variable")
            {
                for(int i = 0; i < variable_counter; i++)
                {
                    if(symbol_table[i].name == _string)
                    {
                        std::cout << "The line " << yylineno << ": Variable " << _string << " has been already declared!";
                        handle_error();
                         ;
                    }
                }

            symbol_table[variable_counter].name = _string;
            symbol_table[variable_counter].var_info.integer_value = _int_value;
            symbol_table[variable_counter].var_info.float_value = _float_value;
            symbol_table[variable_counter].var_info.char_value = _char_value;
            symbol_table[variable_counter].array_size = _array_size;
            symbol_table[variable_counter].var_info.string_value = _string_value;
            variable_counter += 1;
            }
        }
    }

    void check(std::string _s, int yylineno, int v)
    {
        bool exists = 0;
        int i = 0;
        for(i = 0; i < variable_counter; i++)
        {
            //std::cout << symbol_table[i].name << '\n';
            if(symbol_table[i].name == _s)
            {
                exists = 1;
                break;
            }
        }

        if(!exists)
        {
            {
                std::cout << "The line " << yylineno << ": Variable " << _s << " hasn't been declared!";
                handle_error();
                 ;
            }
        }
    }

    void insert_table_fn(std::string _type_p, std::string _s, std::string _type, int yylineno, bool _is_class, std::string _param)
    {
        if(_type == "type")
        {
            for(int i = 0; i < function_counter; i++)
            {
                if(symbol_table_functions[i].name == _s)
                {
                    std::cout << "The line " << yylineno << ": Function " << _s << " is already defined!";
                    handle_error();
                     ;
                }
            }
            symbol_table_functions[function_counter].name = _s;
            symbol_table_functions[function_counter].type = _type_p;
            symbol_table_functions[function_counter].is_class = _is_class;
            symbol_table_functions[function_counter].argument_count = 0;
            
            if(_param != "")
            {
                char *p = strtok(strdup(_param.c_str()), ",");
                while(p != nullptr)
                {
                    char buffer[1024] = {'\0'};
                    std::string partition;
                    std::string aux;

                    partition = std::string(strchr(p, ' '));
                    strncpy(buffer, p, strlen(p) - partition.size());
                    aux = std::string(buffer);


                    symbol_table_functions[function_counter].parameter_types = symbol_table_functions[function_counter].parameter_types + aux;
                    symbol_table_functions[function_counter].parameter_types = symbol_table_functions[function_counter].parameter_types + ",";
                    symbol_table_functions[function_counter].value[symbol_table_functions[function_counter].argument_count].type = aux;
                    symbol_table_functions[function_counter].value[symbol_table_functions[function_counter].argument_count].name = std::string(p + aux.size());
                    symbol_table_functions[function_counter].argument_count++;

                    p = strtok(NULL, ",");
                }
            }
            function_counter += 1;
        }
    }

    void check_fn(std::string _s, std::string _params, int yylineno)
    {
        //std::cout << "Checking function: " << _s << " --- " << _params;
        bool exists = 0;
        int i;
        for(i = 0; i < function_counter; i++)
        {
            //std::cout << "Currently at: " << symbol_table_functions[i].name << '\n';
            if(symbol_table_functions[i].name == _s)
            {
                exists = 1;
                break;
            }
        }

        if(!exists)
        {
            std::cout << "The line " << yylineno << ": Function " << _s << " is not defined!";
            handle_error();
             ;
        }
        
        if(_params == symbol_table_functions[i].parameter_types)
        {
            std::cout << "The line " << yylineno << ": Function " << _s << " is not called correctly!";
            handle_error();
             ;
        }
    }

    void classs(std::string _s)
    {
        int temp = variable_counter - 1;
        while(symbol_table[temp].is_class && temp >= 0)
        {
            std::string temp_string;
            temp_string = symbol_table[temp].name;
            symbol_table[temp].name = _s;
            symbol_table[temp].name += ".";
            symbol_table[temp].name += temp_string;
            symbol_table[temp].is_class = 0;
            temp -= 1;
        }

        temp = function_counter - 1;
        while(symbol_table_functions[temp].is_class && temp >= 0)
        {
            std::string temp_string;
            temp_string = symbol_table_functions[temp].name;
            symbol_table_functions[temp].name = _s;
            symbol_table_functions[temp].name += ".";
            symbol_table_functions[temp].name += temp_string;
            symbol_table_functions[temp].is_class = 0;
            temp -= 1;
        }
    }

    int get_value(std::string _s, int yylineno)
    {
        for(int i = 0; i < variable_counter; i++)
        {
            if(symbol_table[i].name == _s)
            {
                if(symbol_table[i].array_size > 0)
                {
                    std::cout << "The line " << yylineno << ": Array " << _s << " is not correct!";
                    handle_error();
                     ;
                }
                //std::cout << "VALOARE ESTE: " << symbol_table[i].var_info.integer_value << '\n';
                return symbol_table[i].var_info.integer_value;
            }
        }
    }

    std::string get_type(std::string _s)
    {
        for(int i = 0; i < variable_counter; i++)
        {
            if(symbol_table[i].name == _s)
            {
                //std::cout << symbol_table[i].type << '\n';
                return symbol_table[i].type;
            }
        }
        return std::string("No existent type.");
    }

    int Eval(AST* _ast, int yylineno)
    {
        // If the node is a leaf
        if(_ast->left == nullptr && _ast->right == nullptr)
        {
            if(_ast->n_Type == IDENTIFIER)
            {
                std::string type;
                type = get_type(_ast->name);

                if(type == "chr")
                {
                    std::cout << "Can't assign value with chr.\n";
                }
                else
                if(type == "bool")
                {
                    std::cout << "Can't assign value with bool.\n";

                }
                else
                if(type == "str")
                {
                    std::cout << "Can't assign value with string.\n";

                }
                else 
                if(type == "i32")
                {
                    //std::cout << "TIP: " << get_value(_ast->name, yylineno) << '\n';
                    return get_value(_ast->name, yylineno);
                }
            }
            else
            {
                if(_ast->n_Type == NUMBER)
                {
                    //std::cout << "NUMBER: " << atoi(_ast->name.c_str()) << '\n';
                    return atoi(_ast->name.c_str());
                }
                return 0;
            }
        }
        else
        {
            int left_value, right_value;
            left_value = Eval(_ast->left, yylineno);
            right_value = Eval(_ast->right, yylineno);


            if(_ast->name == "+")
            {
                return left_value + right_value;
            }
            if(_ast->name == "-")
            {
                return left_value - right_value;

            }
            if(_ast->name == "*")
            {
                return left_value * right_value;

            }
            if(_ast->name == "/")
            {
                if(right_value != 0)
                {
                    return left_value / right_value;
                }
                else
                {
                    //eroare
                }
            }

        }
    }

    int get_array_value(std::string _name, int _id, int yylineno)
    {
        for(int i = 0; i < variable_counter; i++)
        {
            if(symbol_table[i].name == _name)
            {
                if(symbol_table[i].array_size >= _id)
                {
                    return symbol_table[i].array[_id];
                }
                else
                {
                    //eroare
                }
            }
        }
        //eroare
    }

    void update_table(std::string _name, std::string _type, int _int_value, int yylineno, int _float_value, std::string _string_value)
    {
        for(int i = 0; i < variable_counter; i++)
        {
            if(symbol_table[i].name == _name)
            {
                if(symbol_table[i].type != _type)
                {
                    std::cout << "Undefined error!" << '\n';
                }
                if(_type == "i32" || _type == "bool")
                {
                    symbol_table[i].var_info.integer_value = _int_value;
                }
                else if(_type == "f32")
                {
                    symbol_table[i].var_info.float_value = _float_value;
                }
                else if(_type == "str")
                {
                    symbol_table[i].var_info.string_value = _string_value;
                }
                else if(_type == "chr")
                {
                    symbol_table[i].var_info.char_value = _string_value[1];
                }
                break;
            }
        }
    }

    std::string final(std::string first, std::string second, std::string in)
    {
        first += in;
        first += second;
        return first;
    }

    std::string fn_get_type(std::string _fn)
    {
        for(int i = 0; i < function_counter; i++)
        {
            if(symbol_table_functions[i].name == _fn)
            {
                return symbol_table_functions[i].type;
            }
        }
    }

    void print_values_to_text_file(std::ofstream& _file)
    {
        for(int i = 0; i < variable_counter; i++)
        {
            _file << symbol_table[i].name << " ";
            _file << symbol_table[i].type << " ";
            if(symbol_table[i].type == "i32")
            {
                _file << symbol_table[i].var_info.integer_value;
            }
            else if(symbol_table[i].type == "str")
            {
                _file << symbol_table[i].var_info.string_value;
            }
            else if(symbol_table[i].type == "f32")
            {
                _file << symbol_table[i].var_info.float_value;
            }
            else if(symbol_table[i].type == "chr")
            {
                _file << symbol_table[i].var_info.char_value;
            }
            else if(symbol_table[i].type == "bool")
            {
                _file << symbol_table[i].var_info.integer_value;
            }
            _file << std::endl;
        }
    }

    void print_functions_to_text_file(std::ofstream& _fout)
    {
        for(int i = 0; i < function_counter; i++)
        {
            _fout << symbol_table_functions[i].type << " " << symbol_table_functions[i].name << "(";
            for(int j = 0; j < symbol_table_functions[i].argument_count - 1; j++)
            {
                _fout << symbol_table_functions[i].value[j].type << symbol_table_functions[i].value[j].name << "," << " ";
            }
            if(symbol_table_functions[i].argument_count != 0)
            {
                _fout << symbol_table_functions[i].value[symbol_table_functions[i].argument_count-1].type << symbol_table_functions[i].value[symbol_table_functions[i].argument_count-1].name;
            }
            _fout << ")" << std::endl;
        }
    }


extern FILE* yyin;
extern int yylex();
void yyerror(char* s);
extern char* yytext;
extern int yylineno;

#line 573 "p1.tab.c"

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

#include "p1.tab.h"
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
  YYSYMBOL_program_structure = 48,         /* program_structure  */
  YYSYMBOL_variable_partition = 49,        /* variable_partition  */
  YYSYMBOL_function_partition = 50,        /* function_partition  */
  YYSYMBOL_class_partition = 51,           /* class_partition  */
  YYSYMBOL_variable_declaration = 52,      /* variable_declaration  */
  YYSYMBOL_class_variable_declaration = 53, /* class_variable_declaration  */
  YYSYMBOL_function_declaration = 54,      /* function_declaration  */
  YYSYMBOL_class_fn_declaration = 55,      /* class_fn_declaration  */
  YYSYMBOL_PARAMETER_LIST = 56,            /* PARAMETER_LIST  */
  YYSYMBOL_PARAMETER = 57,                 /* PARAMETER  */
  YYSYMBOL_class = 58,                     /* class  */
  YYSYMBOL_class_first_partition = 59,     /* class_first_partition  */
  YYSYMBOL_class_second_partition = 60,    /* class_second_partition  */
  YYSYMBOL_inside_of_class = 61,           /* inside_of_class  */
  YYSYMBOL_id_list = 62,                   /* id_list  */
  YYSYMBOL_main_partition = 63,            /* main_partition  */
  YYSYMBOL_list = 64,                      /* list  */
  YYSYMBOL_statement = 65,                 /* statement  */
  YYSYMBOL_CONDITION = 66,                 /* CONDITION  */
  YYSYMBOL_OPERATOR = 67,                  /* OPERATOR  */
  YYSYMBOL_do = 68,                        /* do  */
  YYSYMBOL_while = 69,                     /* while  */
  YYSYMBOL_if = 70,                        /* if  */
  YYSYMBOL_for = 71,                       /* for  */
  YYSYMBOL_E = 72,                         /* E  */
  YYSYMBOL_AUX_E = 73,                     /* AUX_E  */
  YYSYMBOL_CALLABLE_LIST = 74              /* CALLABLE_LIST  */
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
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  253

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
       0,   542,   542,   545,   546,   549,   550,   553,   554,   557,
     558,   561,   562,   565,   566,   567,   568,   571,   572,   575,
     576,   579,   584,   587,   588,   591,   592,   595,   596,   597,
     600,   601,   602,   603,   604,   605,   606,   607,   608,   609,
     610,   611,   614,   617,   618,   619,   620,   621,   622,   625,
     636,   637,   638,   639,   651,   661,   666,   669,   670,   673,
     676,   687,   688,   689,   690,   691,   692,   695,   698,   701,
     702,   705,   706,   709,   710,   711,   712,   713,   714,   715,
     716,   717,   718,   719,   722,   731,   740,   749,   758,   759,
     760,   761,   762,   763,   764,   765,   768,   780,   798,   799,
     800,   801,   802,   803
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
  "')'", "','", "'['", "']'", "'.'", "$accept", "program_structure",
  "variable_partition", "function_partition", "class_partition",
  "variable_declaration", "class_variable_declaration",
  "function_declaration", "class_fn_declaration", "PARAMETER_LIST",
  "PARAMETER", "class", "class_first_partition", "class_second_partition",
  "inside_of_class", "id_list", "main_partition", "list", "statement",
  "CONDITION", "OPERATOR", "do", "while", "if", "for", "E", "AUX_E",
  "CALLABLE_LIST", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-142)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      62,    -8,    -4,    29,   149,   -18,    70,  -142,    -8,  -142,
      13,     5,    -6,  -142,  -142,   112,    -8,    39,  -142,   140,
      68,    72,    -7,  -142,  -142,  -142,   118,    31,    65,  -142,
      73,   168,   288,  -142,    51,    58,    98,   189,    53,  -142,
    -142,   115,   143,   160,    -8,    -8,    -8,   296,   168,   168,
     168,   168,    -8,   155,   205,   218,   187,   198,   223,   229,
     207,   230,   189,   245,   249,    66,   233,   236,   243,   240,
    -142,  -142,  -142,    93,   124,   237,   253,  -142,  -142,  -142,
    -142,   199,   199,  -142,  -142,  -142,    -8,  -142,    53,   278,
     297,   150,  -142,    -8,  -142,  -142,   272,   245,   295,   274,
    -142,    85,   115,   283,   305,   168,   145,  -142,   277,   279,
     287,    53,   289,  -142,  -142,  -142,  -142,  -142,  -142,   156,
    -142,   115,  -142,   192,    53,  -142,    64,  -142,  -142,   302,
    -142,  -142,    93,   210,   285,    48,   303,   161,  -142,  -142,
     145,   310,   178,    63,   178,   293,  -142,  -142,  -142,  -142,
      93,   219,   168,  -142,   216,  -142,   294,  -142,   322,   168,
     115,  -142,   115,   312,   338,   317,   145,   145,   145,   145,
    -142,   178,     7,    99,   336,   345,    16,   340,  -142,   324,
     168,  -142,  -142,   168,    93,   222,   246,   313,   341,  -142,
     260,   260,  -142,  -142,    22,     9,   178,   178,    53,  -142,
    -142,  -142,  -142,  -142,  -142,   168,   168,   365,    53,   178,
     374,   329,    93,  -142,  -142,  -142,   115,  -142,  -142,   375,
     228,    93,   334,   168,   204,    25,  -142,   377,   259,  -142,
      53,   178,   339,  -142,   111,  -142,  -142,   255,    -3,   178,
    -142,  -142,    53,    59,   342,    53,    53,   346,   267,    53,
    -142,   280,  -142
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,    30,     9,     0,     1,
       0,     0,     0,     5,     3,     0,     0,     0,    10,    30,
       0,     0,     0,     6,     7,     4,    78,    38,    40,    79,
      36,     0,    34,    32,     0,     0,     0,     0,     0,     8,
       2,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,    19,     0,     0,
       0,     0,    28,    29,     0,     0,     0,     0,     0,     0,
     102,   100,    98,    96,     0,     0,    82,    39,    41,    37,
      77,    74,    73,    76,    75,    35,     0,    21,     0,     0,
       0,    30,    11,     0,    23,    25,     0,    27,     0,     0,
      22,     0,     0,     0,     0,     0,     0,    42,     0,     0,
       0,     0,     0,    47,    48,    45,    46,    43,    81,     0,
      80,     0,    33,     0,     0,    20,     0,    12,    24,     0,
      26,    54,    49,     0,     0,     0,     0,    89,    90,    91,
       0,     0,     0,     0,     0,     0,    44,   103,   101,    99,
      97,     0,     0,    14,     0,    18,     0,    50,     0,     0,
       0,    52,     0,     0,     0,     0,     0,     0,     0,     0,
      51,     0,     0,     0,     0,     0,     0,     0,    83,     0,
       0,    13,    17,     0,    53,     0,     0,     0,    94,    88,
      85,    84,    86,    87,     0,     0,     0,     0,     0,    61,
      62,    63,    64,    66,    65,     0,     0,     0,     0,     0,
       0,     0,    56,    55,    93,    92,     0,    57,    58,    59,
       0,    60,     0,     0,     0,     0,    16,     0,     0,    69,
       0,     0,     0,    68,     0,    15,    95,     0,     0,     0,
      67,    70,     0,     0,     0,     0,     0,     0,     0,     0,
      72,     0,    71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,  -142,  -142,   383,   327,   379,   -35,   -84,
    -142,   369,  -142,   330,  -142,     8,  -142,   -38,   -66,  -141,
    -142,  -142,  -142,  -142,  -142,   -10,   -47,  -101
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,    11,    22,     5,    60,    13,    61,    56,
      57,    24,    62,    63,    64,     7,    40,   224,    69,   172,
     205,   113,   114,   115,   116,   173,   141,    74
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      68,   133,   112,   176,     6,    32,   125,   196,   197,    38,
       8,    21,   199,   200,   201,   202,    18,   196,   197,    20,
     151,    47,    14,    21,    33,    19,   196,   197,    99,     9,
     194,    73,   196,   197,    25,   196,   197,   242,    81,    82,
      83,    84,   156,   203,   204,    48,    49,    50,    51,   198,
     123,    80,    77,    78,    79,   218,   219,   112,   208,   185,
      85,   186,    99,   159,   217,    65,    92,   234,   225,   196,
     197,    34,    54,   145,    44,   174,     1,   175,    54,   112,
      36,   101,    66,    67,    37,    15,   154,     2,   112,   160,
     238,   132,    73,   165,   122,   136,    53,    26,   243,   245,
      55,   127,   199,   200,   201,   202,   155,   102,    45,   150,
     103,    73,   104,    16,    17,   228,    46,    29,   131,   190,
     191,   192,   193,    65,    26,    27,    31,    26,    70,    48,
      49,    50,    51,   203,   204,    48,    49,    50,    51,    35,
      66,    67,   179,    28,    29,    30,    71,    29,    72,   184,
      73,   240,    73,    31,   112,    15,    31,   137,   112,    41,
     220,   195,    42,    10,    43,    15,   118,   119,    26,   147,
     211,   112,    76,   212,     2,    75,   244,   138,   139,   247,
      26,    35,   112,    16,    17,   112,   140,   148,    29,   149,
      26,   126,   237,    16,    17,   221,   222,    31,    86,   152,
      29,   153,   162,    58,    65,   163,    73,   164,   248,    31,
      29,   251,   108,   232,    59,   109,    65,    87,   110,   171,
     111,    66,    67,   180,   108,   181,    88,   109,    65,    89,
     110,   233,   111,    66,    67,    91,   108,    50,    51,   109,
      65,    90,   110,    93,   111,    66,    67,    94,   108,   229,
     230,   109,   157,   119,   110,    65,   111,    66,    67,    98,
     107,   178,   119,   108,   213,   119,   109,    65,   100,   110,
      95,   111,    66,    67,   105,   108,   241,   106,   109,    65,
     117,   110,   120,   111,    66,    67,   124,   108,   214,   119,
     109,   250,    65,   110,   121,   111,    66,    67,   168,   169,
     108,   236,   119,   109,   252,    65,   110,   129,   111,    66,
      67,    54,   128,   108,   130,   134,   109,   135,   142,   177,
     143,   111,    66,    67,    48,    49,    50,    51,   144,   146,
     158,    52,    48,    49,    50,    51,   182,   183,    80,    48,
      49,    50,    51,   126,   187,   161,   166,   167,   168,   169,
     188,   206,   170,   166,   167,   168,   169,   207,   215,   189,
      48,    49,    50,    51,   210,    48,    49,    50,    51,   227,
      48,    49,    50,    51,   231,    48,    49,    50,    51,   239,
     223,   209,   216,   226,   246,   196,   235,    12,   249,    96,
      23,    39,    97
};

static const yytype_uint8 yycheck[] =
{
      38,   102,    68,   144,    12,    15,    90,    10,    11,    16,
      14,    18,     3,     4,     5,     6,     8,    10,    11,    14,
     121,    31,    40,    18,    16,    12,    10,    11,    63,     0,
     171,    41,    10,    11,    40,    10,    11,    40,    48,    49,
      50,    51,   126,    34,    35,    36,    37,    38,    39,    42,
      88,    42,    44,    45,    46,   196,   197,   123,    42,   160,
      52,   162,    97,    15,    42,    12,    58,    42,   209,    10,
      11,    32,    14,   111,    43,    12,    14,    14,    14,   145,
      12,    15,    29,    30,    12,    15,   124,    25,   154,    41,
     231,   101,   102,   140,    86,   105,    45,    12,   239,    40,
      42,    93,     3,     4,     5,     6,    42,    41,    43,   119,
      44,   121,    46,    43,    44,   216,    43,    32,    33,   166,
     167,   168,   169,    12,    12,    13,    41,    12,    13,    36,
      37,    38,    39,    34,    35,    36,    37,    38,    39,    41,
      29,    30,   152,    31,    32,    33,    31,    32,    33,   159,
     160,    40,   162,    41,   220,    15,    41,    12,   224,    41,
     198,   171,    44,    14,    46,    15,    42,    43,    12,    13,
     180,   237,    12,   183,    25,    32,   242,    32,    33,   245,
      12,    41,   248,    43,    44,   251,    41,    31,    32,    33,
      12,    41,   230,    43,    44,   205,   206,    41,    43,     7,
      32,     9,    41,    14,    12,    44,   216,    46,   246,    41,
      32,   249,    20,   223,    25,    23,    12,    12,    26,    41,
      28,    29,    30,     7,    20,     9,     8,    23,    12,    42,
      26,    27,    28,    29,    30,    12,    20,    38,    39,    23,
      12,    43,    26,    14,    28,    29,    30,    40,    20,    21,
      22,    23,    42,    43,    26,    12,    28,    29,    30,    14,
      17,    42,    43,    20,    42,    43,    23,    12,    19,    26,
      40,    28,    29,    30,    41,    20,    21,    41,    23,    12,
      40,    26,    45,    28,    29,    30,     8,    20,    42,    43,
      23,    24,    12,    26,    41,    28,    29,    30,    38,    39,
      20,    42,    43,    23,    24,    12,    26,    12,    28,    29,
      30,    14,    40,    20,    40,    32,    23,    12,    41,    26,
      41,    28,    29,    30,    36,    37,    38,    39,    41,    40,
      45,    43,    36,    37,    38,    39,    42,    15,    42,    36,
      37,    38,    39,    41,    32,    42,    36,    37,    38,    39,
      12,    15,    42,    36,    37,    38,    39,    12,    45,    42,
      36,    37,    38,    39,    40,    36,    37,    38,    39,    40,
      36,    37,    38,    39,    40,    36,    37,    38,    39,    40,
      15,    41,    41,     9,    42,    10,     9,     4,    42,    62,
      11,    22,    62
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    25,    48,    49,    52,    12,    62,    14,     0,
      14,    50,    52,    54,    40,    15,    43,    44,    62,    12,
      14,    18,    51,    54,    58,    40,    12,    13,    31,    32,
      33,    41,    72,    62,    32,    41,    12,    12,    16,    58,
      63,    41,    44,    46,    43,    43,    43,    72,    36,    37,
      38,    39,    43,    45,    14,    42,    56,    57,    14,    25,
      53,    55,    59,    60,    61,    12,    29,    30,    64,    65,
      13,    31,    33,    72,    74,    32,    12,    62,    62,    62,
      42,    72,    72,    72,    72,    62,    43,    12,     8,    42,
      43,    12,    62,    14,    40,    40,    53,    60,    14,    55,
      19,    15,    41,    44,    46,    41,    41,    17,    20,    23,
      26,    28,    65,    68,    69,    70,    71,    40,    42,    43,
      45,    41,    62,    64,     8,    56,    41,    62,    40,    12,
      40,    33,    72,    74,    32,    12,    72,    12,    32,    33,
      41,    73,    41,    41,    41,    64,    40,    13,    31,    33,
      72,    74,     7,     9,    64,    42,    56,    42,    45,    15,
      41,    42,    41,    44,    46,    73,    36,    37,    38,    39,
      42,    41,    66,    72,    12,    14,    66,    26,    42,    72,
       7,     9,    42,    15,    72,    74,    74,    32,    12,    42,
      73,    73,    73,    73,    66,    72,    10,    11,    42,     3,
       4,     5,     6,    34,    35,    67,    15,    12,    42,    41,
      40,    72,    72,    42,    42,    45,    41,    42,    66,    66,
      64,    72,    72,    15,    64,    66,     9,    40,    74,    21,
      22,    40,    72,    27,    42,     9,    42,    64,    66,    40,
      40,    21,    40,    66,    65,    40,    42,    65,    64,    42,
      24,    64,    24
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    53,    53,    54,    54,    54,    54,    55,    55,    56,
      56,    57,    58,    59,    59,    60,    60,    61,    61,    61,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    63,    64,    64,    64,    64,    64,    64,    65,
      65,    65,    65,    65,    65,    65,    65,    66,    66,    66,
      66,    67,    67,    67,    67,    67,    67,    68,    69,    70,
      70,    71,    71,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    74,    74,    74,    74,
      74,    74,    74,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     2,     3,     1,     2,     1,     2,     2,
       3,     2,     3,     8,     7,    11,    10,     5,     4,     1,
       3,     2,     4,     2,     3,     2,     3,     2,     1,     1,
       1,     4,     3,     6,     3,     5,     3,     5,     3,     5,
       3,     5,     3,     2,     3,     2,     2,     2,     2,     3,
       4,     4,     4,     5,     3,     6,     6,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     7,     6,     6,
       8,    13,    12,     3,     3,     3,     3,     3,     1,     1,
       4,     4,     3,     6,     3,     3,     3,     3,     3,     1,
       1,     1,     4,     4,     3,     6,     1,     3,     1,     3,
       1,     3,     1,     3
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
  case 2: /* program_structure: variable_partition function_partition class_partition main_partition  */
#line 542 "p1.y"
                                                                                        {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1822 "p1.tab.c"
    break;

  case 9: /* variable_declaration: TYPE id_list  */
#line 557 "p1.y"
                                    { insert_table(0, 0, (yyvsp[-1].string_value), std::string("type"), 0, 0, '\0', std::string(""), 0, yylineno); }
#line 1828 "p1.tab.c"
    break;

  case 10: /* variable_declaration: CONSTANT TYPE id_list  */
#line 558 "p1.y"
                                            {insert_table(1, 0, (yyvsp[-2].string_value), std::string("type"), 0, 0, '\0', std::string(""), 0, yylineno);}
#line 1834 "p1.tab.c"
    break;

  case 11: /* class_variable_declaration: TYPE id_list  */
#line 561 "p1.y"
                                          { insert_table(0, 0, (yyvsp[-1].string_value), std::string("type"), 0, 0, '\0', std::string(""), 1, yylineno); }
#line 1840 "p1.tab.c"
    break;

  case 12: /* class_variable_declaration: CONSTANT TYPE id_list  */
#line 562 "p1.y"
                                                 {insert_table(1, 0, (yyvsp[-2].string_value), std::string("type"), 0, 0, '\0', std::string(""), 1, yylineno);}
#line 1846 "p1.tab.c"
    break;

  case 13: /* function_declaration: TYPE ID '(' PARAMETER_LIST ')' BEGIN_FN list END_FN  */
#line 565 "p1.y"
                                                                           { insert_table_fn((yyvsp[-7].string_value), (yyvsp[-6].string_value), std::string("type"), yylineno, 0, (yyvsp[-4].string_value));}
#line 1852 "p1.tab.c"
    break;

  case 14: /* function_declaration: TYPE ID '(' ')' BEGIN_FN list END_FN  */
#line 566 "p1.y"
                                                         { insert_table_fn((yyvsp[-6].string_value), (yyvsp[-5].string_value), std::string("type"), yylineno, 0, "");}
#line 1858 "p1.tab.c"
    break;

  case 15: /* function_declaration: TYPE ID '(' PARAMETER_LIST ')' BEGIN_FN list RETURN E ';' END_FN  */
#line 567 "p1.y"
                                                                                     { int val = Eval((yyvsp[-2].tree), yylineno); insert_table_fn((yyvsp[-10].string_value), (yyvsp[-9].string_value), std::string("type"), yylineno, 0, (yyvsp[-7].string_value));}
#line 1864 "p1.tab.c"
    break;

  case 16: /* function_declaration: TYPE ID '(' ')' BEGIN_FN list RETURN E ';' END_FN  */
#line 568 "p1.y"
                                                                      { int val = Eval((yyvsp[-2].tree), yylineno); insert_table_fn((yyvsp[-9].string_value), (yyvsp[-8].string_value), std::string("type"), yylineno, 0, std::string(""));}
#line 1870 "p1.tab.c"
    break;

  case 17: /* class_fn_declaration: TYPE ID '(' PARAMETER_LIST ')'  */
#line 571 "p1.y"
                                                      { insert_table_fn((yyvsp[-4].string_value), (yyvsp[-3].string_value), std::string("type"), yylineno, 1, (yyvsp[-1].string_value));}
#line 1876 "p1.tab.c"
    break;

  case 18: /* class_fn_declaration: TYPE ID '(' ')'  */
#line 572 "p1.y"
                                         { insert_table_fn((yyvsp[-3].string_value), (yyvsp[-2].string_value), std::string("type"), yylineno, 1, std::string(""));}
#line 1882 "p1.tab.c"
    break;

  case 19: /* PARAMETER_LIST: PARAMETER  */
#line 575 "p1.y"
                           {(yyval.string_value) = (yyvsp[0].string_value);}
#line 1888 "p1.tab.c"
    break;

  case 20: /* PARAMETER_LIST: PARAMETER ',' PARAMETER_LIST  */
#line 576 "p1.y"
                                           { (yyval.string_value) = strdup(final((yyvsp[-2].string_value), (yyvsp[0].string_value), std::string(",")).c_str()); }
#line 1894 "p1.tab.c"
    break;

  case 21: /* PARAMETER: TYPE ID  */
#line 579 "p1.y"
                    {
                (yyval.string_value) = strdup(final((yyvsp[-1].string_value), (yyvsp[0].string_value), std::string(" ")).c_str());
               }
#line 1902 "p1.tab.c"
    break;

  case 22: /* class: BEGIN_CLASS ID inside_of_class END_CLASS  */
#line 584 "p1.y"
                                                 {classs((yyvsp[-2].string_value));}
#line 1908 "p1.tab.c"
    break;

  case 30: /* id_list: ID  */
#line 600 "p1.y"
                                             { insert_table(0, 0, (yyvsp[0].string_value), std::string("variable"), 0, 0, '\0', std::string(""), 0, yylineno);}
#line 1914 "p1.tab.c"
    break;

  case 31: /* id_list: ID '[' NR ']'  */
#line 601 "p1.y"
                                             { insert_table(0, (yyvsp[-1].int_value), (yyvsp[-3].string_value), std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
#line 1920 "p1.tab.c"
    break;

  case 32: /* id_list: ID ',' id_list  */
#line 602 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-2].string_value), std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
#line 1926 "p1.tab.c"
    break;

  case 33: /* id_list: ID '[' NR ']' ',' id_list  */
#line 603 "p1.y"
                                             { insert_table(0, (yyvsp[-3].int_value), (yyvsp[-5].string_value), std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
#line 1932 "p1.tab.c"
    break;

  case 34: /* id_list: ID ASSIGN E  */
#line 604 "p1.y"
                                             { int val = Eval((yyvsp[0].tree), yylineno); insert_table(0, 0, (yyvsp[-2].string_value), std::string("variable"), val, 0, '\0', "", 0, yylineno);}
#line 1938 "p1.tab.c"
    break;

  case 35: /* id_list: ID ASSIGN E ',' id_list  */
#line 605 "p1.y"
                                             { int val = Eval((yyvsp[-2].tree), yylineno); insert_table(0, 0, (yyvsp[-4].string_value), std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
#line 1944 "p1.tab.c"
    break;

  case 36: /* id_list: ID ASSIGN NR_FLOAT  */
#line 606 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-2].string_value), std::string("variable"), 0, (yyvsp[0].float_value), '\0', "", 0, yylineno);}
#line 1950 "p1.tab.c"
    break;

  case 37: /* id_list: ID ASSIGN NR_FLOAT ',' id_list  */
#line 607 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-4].string_value), std::string("variable"), 0, (yyvsp[-2].float_value), '\0', "", 0, yylineno);}
#line 1956 "p1.tab.c"
    break;

  case 38: /* id_list: ID ASSIGN STRING  */
#line 608 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-2].string_value), std::string("variable"), 0, 0, '\0', (yyvsp[0].string_value), 0, yylineno);}
#line 1962 "p1.tab.c"
    break;

  case 39: /* id_list: ID ASSIGN STRING ',' id_list  */
#line 609 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-4].string_value), std::string("variable"), 0, 0, '\0', (yyvsp[-2].string_value), 0, yylineno);}
#line 1968 "p1.tab.c"
    break;

  case 40: /* id_list: ID ASSIGN CHAR  */
#line 610 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-2].string_value), std::string("variable"), 0, 0, (yyvsp[0].string_value)[0], std::string(""), 0, yylineno);}
#line 1974 "p1.tab.c"
    break;

  case 41: /* id_list: ID ASSIGN CHAR ',' id_list  */
#line 611 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-4].string_value), std::string("variable"), 0, 0, (yyvsp[-2].string_value)[0], std::string(""), 0, yylineno);}
#line 1980 "p1.tab.c"
    break;

  case 49: /* statement: ID ASSIGN E  */
#line 625 "p1.y"
                        { 
                            check((yyvsp[-2].string_value), yylineno, 0);
                            if(strcmp(get_type(std::string((yyvsp[-2].string_value))).c_str(), "i32"))
                            {
                                sprintf(error_message, "Linia %d, type de date diferit", yylineno);
                                handle_error();
                                 ;
                            }
                            int val = Eval((yyvsp[0].tree), yylineno);
                            update_table((yyvsp[-2].string_value), "i32", val, yylineno, 0, "");
                        }
#line 1996 "p1.tab.c"
    break;

  case 50: /* statement: ID '(' CALLABLE_LIST ')'  */
#line 636 "p1.y"
                                    {check_fn((yyvsp[-3].string_value), (yyvsp[-1].string_value), yylineno);}
#line 2002 "p1.tab.c"
    break;

  case 51: /* statement: TYPEOF '(' AUX_E ')'  */
#line 637 "p1.y"
                                { std::cout << (yyvsp[-1].string_value) << std::endl; }
#line 2008 "p1.tab.c"
    break;

  case 52: /* statement: EVAL '(' E ')'  */
#line 638 "p1.y"
                          { std::cout << Eval((yyvsp[-1].tree), yylineno) << std::endl;}
#line 2014 "p1.tab.c"
    break;

  case 53: /* statement: ID '.' ID ASSIGN E  */
#line 639 "p1.y"
                              { 
                                snprintf(internal_buffer,100,"%s.%s", (yyvsp[-4].string_value), (yyvsp[-2].string_value));
                                check(std::string(internal_buffer), yylineno, 0);
                                if(strcmp(strdup(get_type((yyvsp[-4].string_value)).c_str()), "i32"))
                                {
                                    sprintf(error_message, "Linia %d, type de date diferit", yylineno);
                                    handle_error();
                                     ;
                                }
                                int val = Eval((yyvsp[0].tree), yylineno);
                                update_table(std::string(internal_buffer), "i32", val, yylineno, 0, "");
                              }
#line 2031 "p1.tab.c"
    break;

  case 54: /* statement: ID ASSIGN NR_FLOAT  */
#line 651 "p1.y"
                              {
                                check((yyvsp[-2].string_value), yylineno, 0);
                                if(strcmp(strdup(get_type((yyvsp[-2].string_value)).c_str()), "f32"))
                                {
                                    sprintf(error_message, "Linia %d, type de date diferit", yylineno);
                                    handle_error();
                                     ;
                                }
                                update_table((yyvsp[-2].string_value), "f32", 0, yylineno, (yyvsp[0].float_value), "");
                              }
#line 2046 "p1.tab.c"
    break;

  case 55: /* statement: ID '.' ID '(' CALLABLE_LIST ')'  */
#line 661 "p1.y"
                                           {
                                            snprintf(internal_buffer,100,"%s.%s", (yyvsp[-5].string_value), (yyvsp[-3].string_value));
                                            check_fn(internal_buffer, (yyvsp[-1].string_value), yylineno);

                                        }
#line 2056 "p1.tab.c"
    break;

  case 56: /* statement: ID '[' NR ']' ASSIGN E  */
#line 666 "p1.y"
                                  { check((yyvsp[-5].string_value), yylineno, (yyvsp[-3].int_value));}
#line 2062 "p1.tab.c"
    break;

  case 57: /* CONDITION: '(' CONDITION ')'  */
#line 669 "p1.y"
                              {(yyval.int_value) = (yyvsp[-1].int_value);}
#line 2068 "p1.tab.c"
    break;

  case 58: /* CONDITION: CONDITION AND CONDITION  */
#line 670 "p1.y"
                               { int rez1=(yyvsp[-2].int_value); int rez2=(yyvsp[0].int_value); 
                       (yyval.int_value)=(rez1 && rez2);
                     }
#line 2076 "p1.tab.c"
    break;

  case 59: /* CONDITION: CONDITION OR CONDITION  */
#line 673 "p1.y"
                              { int rez1=(yyvsp[-2].int_value); int rez2=(yyvsp[0].int_value);
                      (yyval.int_value)=(rez1 || rez2);
                    }
#line 2084 "p1.tab.c"
    break;

  case 60: /* CONDITION: E OPERATOR E  */
#line 676 "p1.y"
                    { 
                int rez1=Eval((yyvsp[-2].tree), yylineno); int rez2=Eval((yyvsp[0].tree), yylineno);
                if (strcmp((yyvsp[-1].string_value), "less_equal")) (yyval.int_value)=(rez1 <= rez2);
                if (strcmp((yyvsp[-1].string_value), "greater_equal")) (yyval.int_value)=(rez1 >= rez2);
                if (strcmp((yyvsp[-1].string_value), "not_equal")) (yyval.int_value)=(rez1 != rez2);
                if (strcmp((yyvsp[-1].string_value), "equal")) (yyval.int_value)=(rez1 == rez2);
                if (strcmp((yyvsp[-1].string_value), ">")) (yyval.int_value)=(rez1 > rez2);
                if (strcmp((yyvsp[-1].string_value), "<")) (yyval.int_value)=(rez1 < rez2);
                }
#line 2098 "p1.tab.c"
    break;

  case 61: /* OPERATOR: LESS_EQ  */
#line 687 "p1.y"
                   {(yyval.string_value) = (yyvsp[0].string_value);}
#line 2104 "p1.tab.c"
    break;

  case 62: /* OPERATOR: GREATER_EQ  */
#line 688 "p1.y"
                 {(yyval.string_value) = (yyvsp[0].string_value);}
#line 2110 "p1.tab.c"
    break;

  case 63: /* OPERATOR: NOT_EQ  */
#line 689 "p1.y"
             {(yyval.string_value) = (yyvsp[0].string_value);}
#line 2116 "p1.tab.c"
    break;

  case 64: /* OPERATOR: EQ  */
#line 690 "p1.y"
          {(yyval.string_value) = (yyvsp[0].string_value);}
#line 2122 "p1.tab.c"
    break;

  case 65: /* OPERATOR: '>'  */
#line 691 "p1.y"
          {(yyval.string_value) = ">";}
#line 2128 "p1.tab.c"
    break;

  case 66: /* OPERATOR: '<'  */
#line 692 "p1.y"
          {(yyval.string_value) = "<";}
#line 2134 "p1.tab.c"
    break;

  case 73: /* E: E '+' E  */
#line 709 "p1.y"
                                    { (yyval.tree) = AST_Init("+", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2140 "p1.tab.c"
    break;

  case 74: /* E: E '-' E  */
#line 710 "p1.y"
                                    { (yyval.tree) = AST_Init("-", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2146 "p1.tab.c"
    break;

  case 75: /* E: E '*' E  */
#line 711 "p1.y"
                                    { (yyval.tree) = AST_Init("*", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2152 "p1.tab.c"
    break;

  case 76: /* E: E '/' E  */
#line 712 "p1.y"
                                    { (yyval.tree) = AST_Init("/", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2158 "p1.tab.c"
    break;

  case 77: /* E: '(' E ')'  */
#line 713 "p1.y"
                                    { (yyval.tree) = (yyvsp[-1].tree); }
#line 2164 "p1.tab.c"
    break;

  case 78: /* E: ID  */
#line 714 "p1.y"
                                    { check((yyvsp[0].string_value), yylineno, 0); (yyval.tree) = AST_Init((yyvsp[0].string_value), NULL, NULL, IDENTIFIER);}
#line 2170 "p1.tab.c"
    break;

  case 79: /* E: NR  */
#line 715 "p1.y"
                                    { char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", (yyvsp[0].int_value)); (yyval.tree) = AST_Init(nr, NULL, NULL, NUMBER); }
#line 2176 "p1.tab.c"
    break;

  case 80: /* E: ID '[' NR ']'  */
#line 716 "p1.y"
                                    { check((yyvsp[-3].string_value), yylineno, 1); int val = get_array_value((yyvsp[-3].string_value), (yyvsp[-1].int_value), yylineno); char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", val); (yyval.tree) = AST_Init(nr, NULL, NULL, NUMBER); }
#line 2182 "p1.tab.c"
    break;

  case 81: /* E: ID '(' CALLABLE_LIST ')'  */
#line 717 "p1.y"
                                       { check_fn((yyvsp[-3].string_value), (yyvsp[-1].string_value), yylineno); (yyval.tree) = AST_Init("0", NULL, NULL, NUMBER); }
#line 2188 "p1.tab.c"
    break;

  case 82: /* E: ID '.' ID  */
#line 718 "p1.y"
                                    { snprintf(internal_buffer,100,"%s.%s", (yyvsp[-2].string_value), (yyvsp[0].string_value)); check(std::string(internal_buffer), yylineno, 0);  (yyval.tree) = AST_Init((yyvsp[-2].string_value), NULL, NULL, IDENTIFIER);}
#line 2194 "p1.tab.c"
    break;

  case 83: /* E: ID '.' ID '(' CALLABLE_LIST ')'  */
#line 719 "p1.y"
                                       { snprintf(internal_buffer,100,"%s.%s", (yyvsp[-5].string_value), (yyvsp[-3].string_value)); check_fn(std::string(internal_buffer), (yyvsp[-3].string_value), yylineno); (yyval.tree) = AST_Init("0", NULL, NULL, NUMBER);}
#line 2200 "p1.tab.c"
    break;

  case 84: /* AUX_E: AUX_E '+' AUX_E  */
#line 722 "p1.y"
                        {
                                    if(strcmp((yyvsp[-2].string_value), (yyvsp[0].string_value)))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                         ;
                                    }
                                    (yyval.string_value) = (yyvsp[-2].string_value);
                                 }
#line 2214 "p1.tab.c"
    break;

  case 85: /* AUX_E: AUX_E '-' AUX_E  */
#line 731 "p1.y"
                           {
                                    if(strcmp((yyvsp[-2].string_value), (yyvsp[0].string_value)))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                         ;
                                    }
                                    (yyval.string_value) = (yyvsp[-2].string_value);
                                 }
#line 2228 "p1.tab.c"
    break;

  case 86: /* AUX_E: AUX_E '/' AUX_E  */
#line 740 "p1.y"
                           {
                                    if(strcmp((yyvsp[-2].string_value), (yyvsp[0].string_value)))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                         ;
                                    }
                                    (yyval.string_value) = (yyvsp[-2].string_value);
                                 }
#line 2242 "p1.tab.c"
    break;

  case 87: /* AUX_E: AUX_E '*' AUX_E  */
#line 749 "p1.y"
                           {
                                    if(strcmp((yyvsp[-2].string_value), (yyvsp[0].string_value)))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                         ;
                                    }
                                    (yyval.string_value) = (yyvsp[-2].string_value);
                                 }
#line 2256 "p1.tab.c"
    break;

  case 88: /* AUX_E: '(' AUX_E ')'  */
#line 758 "p1.y"
                         { (yyval.string_value) = (yyvsp[-1].string_value); }
#line 2262 "p1.tab.c"
    break;

  case 89: /* AUX_E: ID  */
#line 759 "p1.y"
                                                 { check((yyvsp[0].string_value), yylineno, 0); (yyval.string_value) = strdup(get_type((yyvsp[0].string_value)).c_str());}
#line 2268 "p1.tab.c"
    break;

  case 90: /* AUX_E: NR  */
#line 760 "p1.y"
                                                 { (yyval.string_value) = "i32";}
#line 2274 "p1.tab.c"
    break;

  case 91: /* AUX_E: NR_FLOAT  */
#line 761 "p1.y"
                                                 { (yyval.string_value) = "f32";}
#line 2280 "p1.tab.c"
    break;

  case 92: /* AUX_E: ID '[' NR ']'  */
#line 762 "p1.y"
                                                 { check((yyvsp[-3].string_value), yylineno, 1); (yyval.string_value) = strdup(get_type((yyvsp[-3].string_value)).c_str());}
#line 2286 "p1.tab.c"
    break;

  case 93: /* AUX_E: ID '(' CALLABLE_LIST ')'  */
#line 763 "p1.y"
                                                 { check_fn((yyvsp[-3].string_value), (yyvsp[-1].string_value), yylineno); (yyval.string_value) = strdup(fn_get_type((yyvsp[-3].string_value)).c_str());}
#line 2292 "p1.tab.c"
    break;

  case 94: /* AUX_E: ID '.' ID  */
#line 764 "p1.y"
                                                 { snprintf(internal_buffer,100,"%s.%s", (yyvsp[-2].string_value), (yyvsp[0].string_value)); check((yyvsp[-2].string_value), yylineno, 1); (yyval.string_value) = strdup(get_type(internal_buffer).c_str());}
#line 2298 "p1.tab.c"
    break;

  case 95: /* AUX_E: ID '.' ID '(' CALLABLE_LIST ')'  */
#line 765 "p1.y"
                                                 { snprintf(internal_buffer,100,"%s.%s", (yyvsp[-5].string_value), (yyvsp[-3].string_value)); check_fn(internal_buffer, (yyvsp[-1].string_value), yylineno); (yyval.string_value) = strdup(fn_get_type(internal_buffer).c_str());}
#line 2304 "p1.tab.c"
    break;

  case 96: /* CALLABLE_LIST: E  */
#line 768 "p1.y"
                  {
                struct AST* tree = (yyvsp[0].tree);
                if(tree->left == NULL && tree->right == NULL)
                {
                    if(tree->n_Type == IDENTIFIER)
                        (yyval.string_value) = strdup(get_type(tree->name).c_str());
                    else
                        (yyval.string_value) = "i32";
                }
                else
                    (yyval.string_value) = "i32";
            }
#line 2321 "p1.tab.c"
    break;

  case 97: /* CALLABLE_LIST: CALLABLE_LIST ',' E  */
#line 780 "p1.y"
                                 {
                    struct AST* tree = (yyvsp[0].tree);
                    char type[20];
                        if(tree->left == NULL && tree->right == NULL)
                        {
                            if(tree->n_Type == IDENTIFIER)
                                strcpy(type, strdup(get_type(tree->name).c_str()));
                            else
                                strcpy(type, "i32");
                        }
                        else
                            strcpy(type, "i32");
                        strcpy(internal_buffer, (yyvsp[-2].string_value));
                        strcat(internal_buffer, ",");
                        strcat(internal_buffer, type);
                        (yyval.string_value) = internal_buffer;
                        // printf("%s.\n", type);
                }
#line 2344 "p1.tab.c"
    break;

  case 98: /* CALLABLE_LIST: NR_FLOAT  */
#line 798 "p1.y"
                      {(yyval.string_value) = "f32";}
#line 2350 "p1.tab.c"
    break;

  case 99: /* CALLABLE_LIST: CALLABLE_LIST ',' NR_FLOAT  */
#line 799 "p1.y"
                                        { snprintf(internal_buffer,100,"%s,float",(yyvsp[-2].string_value)); (yyval.string_value) = internal_buffer;}
#line 2356 "p1.tab.c"
    break;

  case 100: /* CALLABLE_LIST: CHAR  */
#line 800 "p1.y"
                  {(yyval.string_value) = "chr";}
#line 2362 "p1.tab.c"
    break;

  case 101: /* CALLABLE_LIST: CALLABLE_LIST ',' CHAR  */
#line 801 "p1.y"
                                    {snprintf(internal_buffer,100,"%s,char",(yyvsp[-2].string_value)); (yyval.string_value) = internal_buffer;}
#line 2368 "p1.tab.c"
    break;

  case 102: /* CALLABLE_LIST: STRING  */
#line 802 "p1.y"
                    {(yyval.string_value) = "str";}
#line 2374 "p1.tab.c"
    break;

  case 103: /* CALLABLE_LIST: CALLABLE_LIST ',' STRING  */
#line 803 "p1.y"
                                      {snprintf(internal_buffer,100,"%s,string",(yyvsp[-2].string_value)); (yyval.string_value) = internal_buffer;}
#line 2380 "p1.tab.c"
    break;


#line 2384 "p1.tab.c"

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

#line 806 "p1.y"


void yyerror(char * s)
{
    std::cout << "An error occured:" << s <<" At line:" << yylineno << std::endl;
}

int main(int argc, char** argv)
{
    std::ofstream fout;
    std::ofstream fout2;
    fout.open("symbol_table.txt");
    fout2.open("symbol_table_functions.txt");
    
    yyin = fopen(argv[1],"r");

    yyparse();
    
    print_values_to_text_file(fout);
    print_functions_to_text_file(fout2);

    return 0;
}
