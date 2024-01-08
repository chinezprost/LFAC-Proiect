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
        std::cout << "An error has occured: " << error_message << '\n';
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
                        exit(0);
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
                exit(0);
            }
        }
        else
        {
            if(v > 0 && symbol_table[i].array_size == 0)
            {
                std::cout << "The line " << yylineno << ": Variable " << _s << " is not an array!";
                handle_error();
                exit(0);
            }
            else if(v == 0 && symbol_table[i].array_size > 0)
            {
                std::cout << "The line " << yylineno << ": Variable " << _s << " is a array!";
                handle_error();
                exit(0);
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
                    exit(0);
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
            exit(0);
        }
        
        if(_params == symbol_table_functions[i].parameter_types)
        {
            std::cout << "The line " << yylineno << ": Function " << _s << " is not called correctly!";
            handle_error();
            exit(0);
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
                    exit(0);
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
                    std::cout << "eroare\n";
                }
                else
                if(type == "bool")
                {
                    std::cout << "eroare\n";

                }
                else
                if(type == "str")
                {
                    std::cout << "eroare\n";

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

#line 588 "p1.tab.c"

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
  YYSYMBOL_bloc = 63,                      /* bloc  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   447

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  278

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
       0,   549,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   566,   567,   570,   571,
     574,   575,   578,   579,   582,   583,   586,   587,   588,   589,
     592,   593,   596,   597,   600,   605,   608,   609,   612,   613,
     616,   617,   618,   621,   622,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,   635,   638,   639,   640,   641,
     642,   643,   646,   657,   658,   659,   660,   672,   682,   687,
     690,   691,   694,   697,   708,   709,   710,   711,   712,   713,
     716,   719,   722,   723,   726,   727,   730,   731,   732,   733,
     734,   735,   736,   737,   738,   739,   740,   743,   752,   761,
     770,   779,   780,   781,   782,   783,   784,   785,   786,   789,
     801,   819,   820,   821,   822,   823,   824
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
  "inside_of_class", "id_list", "bloc", "list", "statement", "CONDITION",
  "OPERATOR", "do", "while", "if", "for", "E", "AUX_E", "CALLABLE_LIST", YY_NULLPTR
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
     364,    11,    45,    14,    32,   358,   358,   358,    31,  -142,
    -142,   128,  -142,    21,    65,  -142,   191,   255,   255,    49,
    -142,   359,   359,  -142,  -142,    98,   210,  -142,  -142,  -142,
     104,    -2,    65,    48,    97,    89,    75,    80,    21,   110,
     115,    95,  -142,    40,   109,   114,   279,   125,   158,   103,
    -142,   182,  -142,  -142,    65,   103,  -142,   254,  -142,   182,
     254,  -142,   207,   180,   184,  -142,   187,    73,   349,   224,
     239,   208,   219,  -142,   229,   170,  -142,    65,  -142,  -142,
     243,   110,   265,   276,  -142,    41,   147,   263,   288,    73,
      66,  -142,   269,   281,   284,   191,   290,  -142,  -142,  -142,
    -142,  -142,   287,  -142,  -142,  -142,  -142,  -142,  -142,   147,
     302,   330,    65,    65,    65,   357,    73,    73,    73,    73,
      65,  -142,   191,   347,   345,   317,    30,  -142,  -142,   321,
    -142,  -142,   406,  -142,  -142,  -142,   406,   -24,   318,    -7,
     365,   260,  -142,  -142,    66,   372,    99,   152,    99,   341,
    -142,   133,   320,   325,  -142,  -142,  -142,  -142,   250,   250,
    -142,  -142,  -142,   237,   191,  -142,    65,  -142,   326,  -142,
     150,   366,    73,   147,  -142,   147,   348,   367,   379,    66,
      66,    66,    66,  -142,    99,     0,   204,   375,   385,    20,
     350,  -142,  -142,   147,    73,  -142,   252,  -142,  -142,  -142,
    -142,  -142,   406,    73,   406,   270,   294,   353,   371,  -142,
     259,   259,  -142,  -142,    26,    91,    99,    99,   191,  -142,
    -142,  -142,  -142,  -142,  -142,    73,    73,   390,   191,    99,
     304,   386,    73,  -142,   406,  -142,  -142,  -142,   147,  -142,
    -142,   403,   264,   406,   391,    73,   291,    28,  -142,   397,
     396,   307,  -142,   191,    99,   401,  -142,   175,  -142,   410,
    -142,   303,     5,    99,  -142,  -142,  -142,   191,    16,   378,
     191,   191,   404,   315,   191,  -142,   328,  -142
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
      20,    43,    22,     0,     0,     1,     0,     0,     0,     0,
       2,     0,     0,    19,     3,     0,     0,    21,     4,    16,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    42,
       0,    43,    23,     0,     0,     0,     0,     0,     0,     0,
       5,     0,     7,    17,     0,     0,     6,     0,     8,     0,
       0,     9,    91,    51,    53,    92,    49,     0,    47,     0,
       0,     0,    32,    45,     0,    43,    24,     0,    36,    38,
       0,    40,     0,     0,    35,     0,     0,     0,     0,     0,
       0,    55,     0,     0,     0,     0,     0,    60,    61,    58,
      59,    56,     0,    10,    11,    12,    13,    14,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,     0,    44,     0,    25,    37,     0,
      39,    67,    62,   115,   113,   111,   109,     0,     0,     0,
       0,   102,   103,   104,     0,     0,     0,     0,     0,     0,
      57,     0,     0,    95,    52,    54,    50,    90,    87,    86,
      89,    88,    48,     0,     0,    33,     0,    31,     0,    63,
       0,     0,     0,     0,    65,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,     0,     0,
       0,    94,    93,     0,     0,    27,     0,    46,    30,   116,
     114,   112,   110,     0,    66,     0,     0,     0,   107,   101,
      98,    97,    99,   100,     0,     0,     0,     0,     0,    74,
      75,    76,    77,    79,    78,     0,     0,     0,     0,     0,
       0,     0,     0,    26,    69,    68,   106,   105,     0,    70,
      71,    72,     0,    73,     0,     0,     0,     0,    96,     0,
       0,     0,    82,     0,     0,     0,    81,     0,    29,     0,
     108,     0,     0,     0,    80,    28,    83,     0,     0,     0,
       0,     0,     0,     0,     0,    85,     0,    84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,   167,   227,   212,     4,   362,     7,   -34,   130,
    -142,    -1,  -142,   409,  -142,   -12,   135,   -16,   -45,  -141,
    -142,  -142,  -142,  -142,  -142,   -26,  -130,  -106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,    36,     9,    37,    71,
      72,    10,    38,    39,    40,    12,    20,   246,    47,   185,
     225,    97,    98,    99,   100,   186,   145,   137
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,    96,    42,   151,    68,    83,    27,   189,   172,    19,
     216,   217,    69,    23,   178,   216,   217,    27,   169,   170,
      73,    27,    76,    11,    23,    19,   216,   217,    14,    19,
     216,   217,    15,    23,   173,    34,   216,   217,   216,   217,
      70,   115,   218,   214,    69,   267,    35,    83,    27,   210,
     211,   212,   213,    62,    27,    85,   270,    13,    23,   132,
     136,    19,   228,   140,    19,   127,    23,   205,   239,   206,
     257,    29,   167,    65,   131,   240,   241,    41,   141,   149,
      74,    86,    67,   136,    87,    62,    88,   230,   247,    53,
     158,   159,   160,   161,   219,   220,   221,   222,   142,   143,
     154,   155,   156,    77,    96,    65,   163,   144,   162,    75,
      30,    62,     1,   262,    67,    78,    62,    63,    96,    16,
      79,     2,   268,     3,    82,   223,   224,   116,   117,   118,
     119,    65,   251,   157,    84,    64,    65,    66,    32,    33,
     184,    24,    28,    30,   202,    67,   204,   136,   196,   136,
      89,    96,    50,    52,   197,    90,    56,    58,   215,    62,
     133,    61,    62,   199,   187,   101,   188,   136,   231,    31,
     102,    32,    33,    21,    25,   191,   170,   234,   134,    65,
     135,   200,    65,   201,   103,    30,   104,    43,    67,    57,
     105,    67,   106,    60,   107,   108,    48,    96,    16,   243,
     244,    96,   242,    43,    44,    45,   250,   219,   220,   221,
     222,   126,   136,    32,    33,   264,    96,    18,    22,   255,
      44,    45,   269,   112,     1,   272,    16,   113,    96,    49,
     114,    96,    17,    55,    26,     3,   121,   261,   223,   224,
     116,   117,   118,   119,   194,    51,   195,   122,   109,    43,
     123,   110,    59,   111,   165,   273,   168,    92,   276,   232,
      93,   233,   124,    94,    43,    95,    44,    45,    54,    48,
      16,    16,    92,     2,   125,    93,    43,   129,    94,     3,
      95,    44,    45,   128,    92,   252,   253,    93,   118,   119,
      94,    43,    95,    44,    45,   138,    91,   181,   182,    92,
     139,   175,    93,    43,   176,    94,   177,    95,    44,    45,
     146,    92,   235,   170,    93,    43,   130,    94,   256,    95,
      44,    45,   147,    92,   266,   148,    93,    43,    31,    94,
     150,    95,    44,    45,   152,    92,   236,   170,    93,   275,
      43,    94,   153,    95,    44,    45,   248,   170,    92,   260,
     170,    93,   277,    43,    94,   164,    95,    44,    45,    69,
     166,    92,   126,   171,    93,   192,   193,   190,   198,    95,
      44,    45,     1,    54,    16,    16,     2,     2,     1,   208,
     207,   203,     2,     3,     3,   116,   117,   118,   119,     3,
     226,   229,   120,   116,   117,   118,   119,   227,   237,   157,
      80,   116,   117,   118,   119,   245,   258,   174,   179,   180,
     181,   182,   238,   216,   183,   179,   180,   181,   182,   265,
     271,   209,   116,   117,   118,   119,   249,   116,   117,   118,
     119,   254,   116,   117,   118,   119,   259,   116,   117,   118,
     119,   263,   116,   117,   118,   119,   274,    81
};

static const yytype_int16 yycheck[] =
{
      16,    46,    14,   109,    30,    39,     7,   148,    15,     5,
      10,    11,    14,     6,   144,    10,    11,    18,    42,    43,
      32,    22,    34,    12,    17,    21,    10,    11,    14,    25,
      10,    11,     0,    26,    41,    14,    10,    11,    10,    11,
      42,    67,    42,   184,    14,    40,    25,    81,    49,   179,
     180,   181,   182,    12,    55,    15,    40,    12,    51,    85,
      86,    57,    42,    89,    60,    77,    59,   173,    42,   175,
      42,    40,    42,    32,    33,   216,   217,    12,    12,    95,
      32,    41,    41,   109,    44,    12,    46,   193,   229,    40,
     116,   117,   118,   119,     3,     4,     5,     6,    32,    33,
     112,   113,   114,    14,   149,    32,   122,    41,   120,    12,
      15,    12,    14,   254,    41,    40,    12,    13,   163,    16,
      40,    18,   263,    25,    14,    34,    35,    36,    37,    38,
      39,    32,   238,    42,    19,    31,    32,    33,    43,    44,
      41,     6,     7,    15,   170,    41,   172,   173,   164,   175,
      41,   196,    17,    18,   166,    41,    21,    22,   184,    12,
      13,    26,    12,    13,    12,    40,    14,   193,   194,    41,
      12,    43,    44,     6,     7,    42,    43,   203,    31,    32,
      33,    31,    32,    33,    49,    15,    51,    12,    41,    22,
      55,    41,    57,    26,    59,    60,    14,   242,    16,   225,
     226,   246,   218,    12,    29,    30,   232,     3,     4,     5,
       6,    41,   238,    43,    44,    40,   261,     5,     6,   245,
      29,    30,   267,    43,    14,   270,    16,    43,   273,    17,
      43,   276,     5,    21,     7,    25,    12,   253,    34,    35,
      36,    37,    38,    39,     7,    18,     9,     8,    41,    12,
      42,    44,    25,    46,   124,   271,   126,    20,   274,     7,
      23,     9,    43,    26,    12,    28,    29,    30,    14,    14,
      16,    16,    20,    18,    45,    23,    12,    12,    26,    25,
      28,    29,    30,    40,    20,    21,    22,    23,    38,    39,
      26,    12,    28,    29,    30,    32,    17,    38,    39,    20,
      12,    41,    23,    12,    44,    26,    46,    28,    29,    30,
      41,    20,    42,    43,    23,    12,    40,    26,    27,    28,
      29,    30,    41,    20,    21,    41,    23,    12,    41,    26,
      40,    28,    29,    30,    32,    20,    42,    43,    23,    24,
      12,    26,    12,    28,    29,    30,    42,    43,    20,    42,
      43,    23,    24,    12,    26,     8,    28,    29,    30,    14,
      43,    20,    41,    45,    23,    45,    41,    26,    42,    28,
      29,    30,    14,    14,    16,    16,    18,    18,    14,    12,
      32,    15,    18,    25,    25,    36,    37,    38,    39,    25,
      15,    41,    43,    36,    37,    38,    39,    12,    45,    42,
      38,    36,    37,    38,    39,    15,     9,    42,    36,    37,
      38,    39,    41,    10,    42,    36,    37,    38,    39,     9,
      42,    42,    36,    37,    38,    39,    40,    36,    37,    38,
      39,    40,    36,    37,    38,    39,    40,    36,    37,    38,
      39,    40,    36,    37,    38,    39,    42,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    18,    25,    48,    49,    50,    51,    52,    54,
      58,    12,    62,    12,    14,     0,    16,    50,    51,    52,
      63,    49,    51,    54,    63,    49,    50,    58,    63,    40,
      15,    41,    43,    44,    14,    25,    53,    55,    59,    60,
      61,    12,    62,    12,    29,    30,    64,    65,    14,    51,
      63,    50,    63,    40,    14,    51,    63,    49,    63,    50,
      49,    63,    12,    13,    31,    32,    33,    41,    72,    14,
      42,    56,    57,    62,    32,    12,    62,    14,    40,    40,
      53,    60,    14,    55,    19,    15,    41,    44,    46,    41,
      41,    17,    20,    23,    26,    28,    65,    68,    69,    70,
      71,    40,    12,    63,    63,    63,    63,    63,    63,    41,
      44,    46,    43,    43,    43,    72,    36,    37,    38,    39,
      43,    12,     8,    42,    43,    45,    41,    62,    40,    12,
      40,    33,    72,    13,    31,    33,    72,    74,    32,    12,
      72,    12,    32,    33,    41,    73,    41,    41,    41,    64,
      40,    74,    32,    12,    62,    62,    62,    42,    72,    72,
      72,    72,    62,    64,     8,    56,    43,    42,    56,    42,
      43,    45,    15,    41,    42,    41,    44,    46,    73,    36,
      37,    38,    39,    42,    41,    66,    72,    12,    14,    66,
      26,    42,    45,    41,     7,     9,    64,    62,    42,    13,
      31,    33,    72,    15,    72,    74,    74,    32,    12,    42,
      73,    73,    73,    73,    66,    72,    10,    11,    42,     3,
       4,     5,     6,    34,    35,    67,    15,    12,    42,    41,
      74,    72,     7,     9,    72,    42,    42,    45,    41,    42,
      66,    66,    64,    72,    72,    15,    64,    66,    42,    40,
      72,    74,    21,    22,    40,    72,    27,    42,     9,    40,
      42,    64,    66,    40,    40,     9,    21,    40,    66,    65,
      40,    42,    65,    64,    42,    24,    64,    24
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    54,    54,
      55,    55,    56,    56,    57,    58,    59,    59,    60,    60,
      61,    61,    61,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    63,    64,    64,    64,    64,
      64,    64,    65,    65,    65,    65,    65,    65,    65,    65,
      66,    66,    66,    66,    67,    67,    67,    67,    67,    67,
      68,    69,    70,    70,    71,    71,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    74,
      74,    74,    74,    74,    74,    74,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     3,     3,     3,     3,     3,
       4,     4,     4,     4,     4,     4,     2,     3,     1,     2,
       1,     2,     2,     3,     2,     3,     8,     7,    11,    10,
       5,     4,     1,     3,     2,     4,     2,     3,     2,     3,
       2,     1,     1,     1,     4,     3,     6,     3,     5,     3,
       5,     3,     5,     3,     5,     3,     2,     3,     2,     2,
       2,     2,     3,     4,     4,     4,     5,     3,     6,     6,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       7,     6,     6,     8,    13,    12,     3,     3,     3,     3,
       3,     1,     1,     4,     4,     3,     6,     3,     3,     3,
       3,     3,     1,     1,     1,     4,     4,     3,     6,     1,
       3,     1,     3,     1,     3,     1,     3
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
  case 2: /* program_structure: variable_partition bloc  */
#line 549 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1855 "p1.tab.c"
    break;

  case 3: /* program_structure: function_partition bloc  */
#line 550 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1861 "p1.tab.c"
    break;

  case 4: /* program_structure: class_partition bloc  */
#line 551 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1867 "p1.tab.c"
    break;

  case 5: /* program_structure: variable_partition function_partition bloc  */
#line 552 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1873 "p1.tab.c"
    break;

  case 6: /* program_structure: function_partition variable_partition bloc  */
#line 553 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1879 "p1.tab.c"
    break;

  case 7: /* program_structure: variable_partition class_partition bloc  */
#line 554 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1885 "p1.tab.c"
    break;

  case 8: /* program_structure: function_partition class_partition bloc  */
#line 555 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1891 "p1.tab.c"
    break;

  case 9: /* program_structure: class_partition function_partition bloc  */
#line 556 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1897 "p1.tab.c"
    break;

  case 10: /* program_structure: variable_partition function_partition class_partition bloc  */
#line 557 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1903 "p1.tab.c"
    break;

  case 11: /* program_structure: variable_partition class_partition function_partition bloc  */
#line 558 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1909 "p1.tab.c"
    break;

  case 12: /* program_structure: function_partition variable_partition class_partition bloc  */
#line 559 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1915 "p1.tab.c"
    break;

  case 13: /* program_structure: function_partition class_partition variable_partition bloc  */
#line 560 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1921 "p1.tab.c"
    break;

  case 14: /* program_structure: class_partition variable_partition function_partition bloc  */
#line 561 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1927 "p1.tab.c"
    break;

  case 15: /* program_structure: class_partition function_partition variable_partition bloc  */
#line 562 "p1.y"
                                                                                {std::cout << "The program is syntactically correct!" << std::endl;}
#line 1933 "p1.tab.c"
    break;

  case 22: /* variable_declaration: TYPE id_list  */
#line 578 "p1.y"
                                    { insert_table(0, 0, (yyvsp[-1].string_value), std::string("type"), 0, 0, '\0', std::string(""), 0, yylineno); }
#line 1939 "p1.tab.c"
    break;

  case 23: /* variable_declaration: CONSTANT TYPE id_list  */
#line 579 "p1.y"
                                            {insert_table(1, 0, (yyvsp[-2].string_value), std::string("type"), 0, 0, '\0', std::string(""), 0, yylineno);}
#line 1945 "p1.tab.c"
    break;

  case 24: /* class_variable_declaration: TYPE id_list  */
#line 582 "p1.y"
                                          { insert_table(0, 0, (yyvsp[-1].string_value), std::string("type"), 0, 0, '\0', std::string(""), 1, yylineno); }
#line 1951 "p1.tab.c"
    break;

  case 25: /* class_variable_declaration: CONSTANT TYPE id_list  */
#line 583 "p1.y"
                                                 {insert_table(1, 0, (yyvsp[-2].string_value), std::string("type"), 0, 0, '\0', std::string(""), 1, yylineno);}
#line 1957 "p1.tab.c"
    break;

  case 26: /* function_declaration: TYPE ID '(' PARAMETER_LIST ')' BEGIN_FN list END_FN  */
#line 586 "p1.y"
                                                                           { insert_table_fn((yyvsp[-7].string_value), (yyvsp[-6].string_value), std::string("type"), yylineno, 0, (yyvsp[-4].string_value));}
#line 1963 "p1.tab.c"
    break;

  case 27: /* function_declaration: TYPE ID '(' ')' BEGIN_FN list END_FN  */
#line 587 "p1.y"
                                                         { insert_table_fn((yyvsp[-6].string_value), (yyvsp[-5].string_value), std::string("type"), yylineno, 0, "");}
#line 1969 "p1.tab.c"
    break;

  case 28: /* function_declaration: TYPE ID '(' PARAMETER_LIST ')' BEGIN_FN list RETURN E ';' END_FN  */
#line 588 "p1.y"
                                                                                     { int val = Eval((yyvsp[-2].tree), yylineno); insert_table_fn((yyvsp[-10].string_value), (yyvsp[-9].string_value), std::string("type"), yylineno, 0, (yyvsp[-7].string_value));}
#line 1975 "p1.tab.c"
    break;

  case 29: /* function_declaration: TYPE ID '(' ')' BEGIN_FN list RETURN E ';' END_FN  */
#line 589 "p1.y"
                                                                      { int val = Eval((yyvsp[-2].tree), yylineno); insert_table_fn((yyvsp[-9].string_value), (yyvsp[-8].string_value), std::string("type"), yylineno, 0, std::string(""));}
#line 1981 "p1.tab.c"
    break;

  case 30: /* class_fn_declaration: TYPE ID '(' PARAMETER_LIST ')'  */
#line 592 "p1.y"
                                                      { insert_table_fn((yyvsp[-4].string_value), (yyvsp[-3].string_value), std::string("type"), yylineno, 1, (yyvsp[-1].string_value));}
#line 1987 "p1.tab.c"
    break;

  case 31: /* class_fn_declaration: TYPE ID '(' ')'  */
#line 593 "p1.y"
                                         { insert_table_fn((yyvsp[-3].string_value), (yyvsp[-2].string_value), std::string("type"), yylineno, 1, std::string(""));}
#line 1993 "p1.tab.c"
    break;

  case 32: /* PARAMETER_LIST: PARAMETER  */
#line 596 "p1.y"
                           {(yyval.string_value) = (yyvsp[0].string_value);}
#line 1999 "p1.tab.c"
    break;

  case 33: /* PARAMETER_LIST: PARAMETER ',' PARAMETER_LIST  */
#line 597 "p1.y"
                                           { (yyval.string_value) = strdup(final((yyvsp[-2].string_value), (yyvsp[0].string_value), std::string(",")).c_str()); }
#line 2005 "p1.tab.c"
    break;

  case 34: /* PARAMETER: TYPE ID  */
#line 600 "p1.y"
                    {
                (yyval.string_value) = strdup(final((yyvsp[-1].string_value), (yyvsp[0].string_value), std::string(" ")).c_str());
               }
#line 2013 "p1.tab.c"
    break;

  case 35: /* class: BEGIN_CLASS ID inside_of_class END_CLASS  */
#line 605 "p1.y"
                                                 {classs((yyvsp[-2].string_value));}
#line 2019 "p1.tab.c"
    break;

  case 43: /* id_list: ID  */
#line 621 "p1.y"
                                             { insert_table(0, 0, (yyvsp[0].string_value), std::string("variable"), 0, 0, '\0', std::string(""), 0, yylineno);}
#line 2025 "p1.tab.c"
    break;

  case 44: /* id_list: ID '[' NR ']'  */
#line 622 "p1.y"
                                             { insert_table(0, (yyvsp[-1].int_value), (yyvsp[-3].string_value), std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
#line 2031 "p1.tab.c"
    break;

  case 45: /* id_list: ID ',' id_list  */
#line 623 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-2].string_value), std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
#line 2037 "p1.tab.c"
    break;

  case 46: /* id_list: ID '[' NR ']' ',' id_list  */
#line 624 "p1.y"
                                             { insert_table(0, (yyvsp[-3].int_value), (yyvsp[-5].string_value), std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
#line 2043 "p1.tab.c"
    break;

  case 47: /* id_list: ID ASSIGN E  */
#line 625 "p1.y"
                                             { int val = Eval((yyvsp[0].tree), yylineno); insert_table(0, 0, (yyvsp[-2].string_value), std::string("variable"), val, 0, '\0', "", 0, yylineno);}
#line 2049 "p1.tab.c"
    break;

  case 48: /* id_list: ID ASSIGN E ',' id_list  */
#line 626 "p1.y"
                                             { int val = Eval((yyvsp[-2].tree), yylineno); insert_table(0, 0, (yyvsp[-4].string_value), std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
#line 2055 "p1.tab.c"
    break;

  case 49: /* id_list: ID ASSIGN NR_FLOAT  */
#line 627 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-2].string_value), std::string("variable"), 0, (yyvsp[0].float_value), '\0', "", 0, yylineno);}
#line 2061 "p1.tab.c"
    break;

  case 50: /* id_list: ID ASSIGN NR_FLOAT ',' id_list  */
#line 628 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-4].string_value), std::string("variable"), 0, (yyvsp[-2].float_value), '\0', "", 0, yylineno);}
#line 2067 "p1.tab.c"
    break;

  case 51: /* id_list: ID ASSIGN STRING  */
#line 629 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-2].string_value), std::string("variable"), 0, 0, '\0', (yyvsp[0].string_value), 0, yylineno);}
#line 2073 "p1.tab.c"
    break;

  case 52: /* id_list: ID ASSIGN STRING ',' id_list  */
#line 630 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-4].string_value), std::string("variable"), 0, 0, '\0', (yyvsp[-2].string_value), 0, yylineno);}
#line 2079 "p1.tab.c"
    break;

  case 53: /* id_list: ID ASSIGN CHAR  */
#line 631 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-2].string_value), std::string("variable"), 0, 0, (yyvsp[0].string_value)[0], std::string(""), 0, yylineno);}
#line 2085 "p1.tab.c"
    break;

  case 54: /* id_list: ID ASSIGN CHAR ',' id_list  */
#line 632 "p1.y"
                                             { insert_table(0, 0, (yyvsp[-4].string_value), std::string("variable"), 0, 0, (yyvsp[-2].string_value)[0], std::string(""), 0, yylineno);}
#line 2091 "p1.tab.c"
    break;

  case 62: /* statement: ID ASSIGN E  */
#line 646 "p1.y"
                        { 
                            check((yyvsp[-2].string_value), yylineno, 0);
                            if(strcmp(get_type(std::string((yyvsp[-2].string_value))).c_str(), "i32"))
                            {
                                sprintf(error_message, "Linia %d, type de date diferit", yylineno);
                                handle_error();
                                exit(0);
                            }
                            int val = Eval((yyvsp[0].tree), yylineno);
                            update_table((yyvsp[-2].string_value), "i32", val, yylineno, 0, "");
                        }
#line 2107 "p1.tab.c"
    break;

  case 63: /* statement: ID '(' CALLABLE_LIST ')'  */
#line 657 "p1.y"
                                    {check_fn((yyvsp[-3].string_value), (yyvsp[-1].string_value), yylineno);}
#line 2113 "p1.tab.c"
    break;

  case 64: /* statement: TYPEOF '(' AUX_E ')'  */
#line 658 "p1.y"
                                { std::cout << (yyvsp[-1].string_value) << std::endl; }
#line 2119 "p1.tab.c"
    break;

  case 65: /* statement: EVAL '(' E ')'  */
#line 659 "p1.y"
                          { std::cout << Eval((yyvsp[-1].tree), yylineno) << std::endl;}
#line 2125 "p1.tab.c"
    break;

  case 66: /* statement: ID '.' ID ASSIGN E  */
#line 660 "p1.y"
                              { 
                                snprintf(internal_buffer,100,"%s.%s", (yyvsp[-4].string_value), (yyvsp[-2].string_value));
                                check(std::string(internal_buffer), yylineno, 0);
                                if(strcmp(strdup(get_type((yyvsp[-4].string_value)).c_str()), "i32"))
                                {
                                    sprintf(error_message, "Linia %d, type de date diferit", yylineno);
                                    handle_error();
                                    exit(0);
                                }
                                int val = Eval((yyvsp[0].tree), yylineno);
                                update_table(std::string(internal_buffer), "i32", val, yylineno, 0, "");
                              }
#line 2142 "p1.tab.c"
    break;

  case 67: /* statement: ID ASSIGN NR_FLOAT  */
#line 672 "p1.y"
                              {
                                check((yyvsp[-2].string_value), yylineno, 0);
                                if(strcmp(strdup(get_type((yyvsp[-2].string_value)).c_str()), "f32"))
                                {
                                    sprintf(error_message, "Linia %d, type de date diferit", yylineno);
                                    handle_error();
                                    exit(0);
                                }
                                update_table((yyvsp[-2].string_value), "f32", 0, yylineno, (yyvsp[0].float_value), "");
                              }
#line 2157 "p1.tab.c"
    break;

  case 68: /* statement: ID '.' ID '(' CALLABLE_LIST ')'  */
#line 682 "p1.y"
                                           {
                                            snprintf(internal_buffer,100,"%s.%s", (yyvsp[-5].string_value), (yyvsp[-3].string_value));
                                            check_fn(internal_buffer, (yyvsp[-1].string_value), yylineno);

                                        }
#line 2167 "p1.tab.c"
    break;

  case 69: /* statement: ID '[' NR ']' ASSIGN E  */
#line 687 "p1.y"
                                  { check((yyvsp[-5].string_value), yylineno, (yyvsp[-3].int_value));}
#line 2173 "p1.tab.c"
    break;

  case 70: /* CONDITION: '(' CONDITION ')'  */
#line 690 "p1.y"
                              {(yyval.int_value) = (yyvsp[-1].int_value);}
#line 2179 "p1.tab.c"
    break;

  case 71: /* CONDITION: CONDITION AND CONDITION  */
#line 691 "p1.y"
                               { int rez1=(yyvsp[-2].int_value); int rez2=(yyvsp[0].int_value); 
                       (yyval.int_value)=(rez1 && rez2);
                     }
#line 2187 "p1.tab.c"
    break;

  case 72: /* CONDITION: CONDITION OR CONDITION  */
#line 694 "p1.y"
                              { int rez1=(yyvsp[-2].int_value); int rez2=(yyvsp[0].int_value);
                      (yyval.int_value)=(rez1 || rez2);
                    }
#line 2195 "p1.tab.c"
    break;

  case 73: /* CONDITION: E OPERATOR E  */
#line 697 "p1.y"
                    { 
                int rez1=Eval((yyvsp[-2].tree), yylineno); int rez2=Eval((yyvsp[0].tree), yylineno);
                if (strcmp((yyvsp[-1].string_value), "less_equal")) (yyval.int_value)=(rez1 <= rez2);
                if (strcmp((yyvsp[-1].string_value), "greater_equal")) (yyval.int_value)=(rez1 >= rez2);
                if (strcmp((yyvsp[-1].string_value), "not_equal")) (yyval.int_value)=(rez1 != rez2);
                if (strcmp((yyvsp[-1].string_value), "equal")) (yyval.int_value)=(rez1 == rez2);
                if (strcmp((yyvsp[-1].string_value), ">")) (yyval.int_value)=(rez1 > rez2);
                if (strcmp((yyvsp[-1].string_value), "<")) (yyval.int_value)=(rez1 < rez2);
                }
#line 2209 "p1.tab.c"
    break;

  case 74: /* OPERATOR: LESS_EQ  */
#line 708 "p1.y"
                   {(yyval.string_value) = (yyvsp[0].string_value);}
#line 2215 "p1.tab.c"
    break;

  case 75: /* OPERATOR: GREATER_EQ  */
#line 709 "p1.y"
                 {(yyval.string_value) = (yyvsp[0].string_value);}
#line 2221 "p1.tab.c"
    break;

  case 76: /* OPERATOR: NOT_EQ  */
#line 710 "p1.y"
             {(yyval.string_value) = (yyvsp[0].string_value);}
#line 2227 "p1.tab.c"
    break;

  case 77: /* OPERATOR: EQ  */
#line 711 "p1.y"
          {(yyval.string_value) = (yyvsp[0].string_value);}
#line 2233 "p1.tab.c"
    break;

  case 78: /* OPERATOR: '>'  */
#line 712 "p1.y"
          {(yyval.string_value) = ">";}
#line 2239 "p1.tab.c"
    break;

  case 79: /* OPERATOR: '<'  */
#line 713 "p1.y"
          {(yyval.string_value) = "<";}
#line 2245 "p1.tab.c"
    break;

  case 86: /* E: E '+' E  */
#line 730 "p1.y"
                                    { (yyval.tree) = AST_Init("+", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2251 "p1.tab.c"
    break;

  case 87: /* E: E '-' E  */
#line 731 "p1.y"
                                    { (yyval.tree) = AST_Init("-", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2257 "p1.tab.c"
    break;

  case 88: /* E: E '*' E  */
#line 732 "p1.y"
                                    { (yyval.tree) = AST_Init("*", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2263 "p1.tab.c"
    break;

  case 89: /* E: E '/' E  */
#line 733 "p1.y"
                                    { (yyval.tree) = AST_Init("/", (yyvsp[-2].tree), (yyvsp[0].tree), OPERATOR); }
#line 2269 "p1.tab.c"
    break;

  case 90: /* E: '(' E ')'  */
#line 734 "p1.y"
                                    { (yyval.tree) = (yyvsp[-1].tree); }
#line 2275 "p1.tab.c"
    break;

  case 91: /* E: ID  */
#line 735 "p1.y"
                                    { check((yyvsp[0].string_value), yylineno, 0); (yyval.tree) = AST_Init((yyvsp[0].string_value), NULL, NULL, IDENTIFIER);}
#line 2281 "p1.tab.c"
    break;

  case 92: /* E: NR  */
#line 736 "p1.y"
                                    { char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", (yyvsp[0].int_value)); (yyval.tree) = AST_Init(nr, NULL, NULL, NUMBER); }
#line 2287 "p1.tab.c"
    break;

  case 93: /* E: ID '[' NR ']'  */
#line 737 "p1.y"
                                    { check((yyvsp[-3].string_value), yylineno, 1); int val = get_array_value((yyvsp[-3].string_value), (yyvsp[-1].int_value), yylineno); char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", val); (yyval.tree) = AST_Init(nr, NULL, NULL, NUMBER); }
#line 2293 "p1.tab.c"
    break;

  case 94: /* E: ID '(' CALLABLE_LIST ')'  */
#line 738 "p1.y"
                                       { check_fn((yyvsp[-3].string_value), (yyvsp[-1].string_value), yylineno); (yyval.tree) = AST_Init("0", NULL, NULL, NUMBER); }
#line 2299 "p1.tab.c"
    break;

  case 95: /* E: ID '.' ID  */
#line 739 "p1.y"
                                    { snprintf(internal_buffer,100,"%s.%s", (yyvsp[-2].string_value), (yyvsp[0].string_value)); check(std::string(internal_buffer), yylineno, 0);  (yyval.tree) = AST_Init((yyvsp[-2].string_value), NULL, NULL, IDENTIFIER);}
#line 2305 "p1.tab.c"
    break;

  case 96: /* E: ID '.' ID '(' CALLABLE_LIST ')'  */
#line 740 "p1.y"
                                       { snprintf(internal_buffer,100,"%s.%s", (yyvsp[-5].string_value), (yyvsp[-3].string_value)); check_fn(std::string(internal_buffer), (yyvsp[-3].string_value), yylineno); (yyval.tree) = AST_Init("0", NULL, NULL, NUMBER);}
#line 2311 "p1.tab.c"
    break;

  case 97: /* AUX_E: AUX_E '+' AUX_E  */
#line 743 "p1.y"
                        {
                                    if(strcmp((yyvsp[-2].string_value), (yyvsp[0].string_value)))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    (yyval.string_value) = (yyvsp[-2].string_value);
                                 }
#line 2325 "p1.tab.c"
    break;

  case 98: /* AUX_E: AUX_E '-' AUX_E  */
#line 752 "p1.y"
                           {
                                    if(strcmp((yyvsp[-2].string_value), (yyvsp[0].string_value)))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    (yyval.string_value) = (yyvsp[-2].string_value);
                                 }
#line 2339 "p1.tab.c"
    break;

  case 99: /* AUX_E: AUX_E '/' AUX_E  */
#line 761 "p1.y"
                           {
                                    if(strcmp((yyvsp[-2].string_value), (yyvsp[0].string_value)))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    (yyval.string_value) = (yyvsp[-2].string_value);
                                 }
#line 2353 "p1.tab.c"
    break;

  case 100: /* AUX_E: AUX_E '*' AUX_E  */
#line 770 "p1.y"
                           {
                                    if(strcmp((yyvsp[-2].string_value), (yyvsp[0].string_value)))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    (yyval.string_value) = (yyvsp[-2].string_value);
                                 }
#line 2367 "p1.tab.c"
    break;

  case 101: /* AUX_E: '(' AUX_E ')'  */
#line 779 "p1.y"
                         { (yyval.string_value) = (yyvsp[-1].string_value); }
#line 2373 "p1.tab.c"
    break;

  case 102: /* AUX_E: ID  */
#line 780 "p1.y"
                                                 { check((yyvsp[0].string_value), yylineno, 0); (yyval.string_value) = strdup(get_type((yyvsp[0].string_value)).c_str());}
#line 2379 "p1.tab.c"
    break;

  case 103: /* AUX_E: NR  */
#line 781 "p1.y"
                                                 { (yyval.string_value) = "i32";}
#line 2385 "p1.tab.c"
    break;

  case 104: /* AUX_E: NR_FLOAT  */
#line 782 "p1.y"
                                                 { (yyval.string_value) = "f32";}
#line 2391 "p1.tab.c"
    break;

  case 105: /* AUX_E: ID '[' NR ']'  */
#line 783 "p1.y"
                                                 { check((yyvsp[-3].string_value), yylineno, 1); (yyval.string_value) = strdup(get_type((yyvsp[-3].string_value)).c_str());}
#line 2397 "p1.tab.c"
    break;

  case 106: /* AUX_E: ID '(' CALLABLE_LIST ')'  */
#line 784 "p1.y"
                                                 { check_fn((yyvsp[-3].string_value), (yyvsp[-1].string_value), yylineno); (yyval.string_value) = strdup(fn_get_type((yyvsp[-3].string_value)).c_str());}
#line 2403 "p1.tab.c"
    break;

  case 107: /* AUX_E: ID '.' ID  */
#line 785 "p1.y"
                                                 { snprintf(internal_buffer,100,"%s.%s", (yyvsp[-2].string_value), (yyvsp[0].string_value)); check((yyvsp[-2].string_value), yylineno, 1); (yyval.string_value) = strdup(get_type(internal_buffer).c_str());}
#line 2409 "p1.tab.c"
    break;

  case 108: /* AUX_E: ID '.' ID '(' CALLABLE_LIST ')'  */
#line 786 "p1.y"
                                                 { snprintf(internal_buffer,100,"%s.%s", (yyvsp[-5].string_value), (yyvsp[-3].string_value)); check_fn(internal_buffer, (yyvsp[-1].string_value), yylineno); (yyval.string_value) = strdup(fn_get_type(internal_buffer).c_str());}
#line 2415 "p1.tab.c"
    break;

  case 109: /* CALLABLE_LIST: E  */
#line 789 "p1.y"
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
#line 2432 "p1.tab.c"
    break;

  case 110: /* CALLABLE_LIST: CALLABLE_LIST ',' E  */
#line 801 "p1.y"
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
#line 2455 "p1.tab.c"
    break;

  case 111: /* CALLABLE_LIST: NR_FLOAT  */
#line 819 "p1.y"
                      {(yyval.string_value) = "f32";}
#line 2461 "p1.tab.c"
    break;

  case 112: /* CALLABLE_LIST: CALLABLE_LIST ',' NR_FLOAT  */
#line 820 "p1.y"
                                        { snprintf(internal_buffer,100,"%s,float",(yyvsp[-2].string_value)); (yyval.string_value) = internal_buffer;}
#line 2467 "p1.tab.c"
    break;

  case 113: /* CALLABLE_LIST: CHAR  */
#line 821 "p1.y"
                  {(yyval.string_value) = "chr";}
#line 2473 "p1.tab.c"
    break;

  case 114: /* CALLABLE_LIST: CALLABLE_LIST ',' CHAR  */
#line 822 "p1.y"
                                    {snprintf(internal_buffer,100,"%s,char",(yyvsp[-2].string_value)); (yyval.string_value) = internal_buffer;}
#line 2479 "p1.tab.c"
    break;

  case 115: /* CALLABLE_LIST: STRING  */
#line 823 "p1.y"
                    {(yyval.string_value) = "str";}
#line 2485 "p1.tab.c"
    break;

  case 116: /* CALLABLE_LIST: CALLABLE_LIST ',' STRING  */
#line 824 "p1.y"
                                      {snprintf(internal_buffer,100,"%s,string",(yyvsp[-2].string_value)); (yyval.string_value) = internal_buffer;}
#line 2491 "p1.tab.c"
    break;


#line 2495 "p1.tab.c"

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

#line 827 "p1.y"


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
