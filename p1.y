%{
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

    int get_i32_value(std::string _s, int yylineno)
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
                    //std::cout << "TIP: " << get_i32_value(_ast->name, yylineno) << '\n';
                    return get_i32_value(_ast->name, yylineno);
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
                    std::cout << "Division by 0";
                    exit(0);
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
                    std::cout << "Invalid position in array!\n";
                }
            }
        }
        std::cout << "Invalid array!\n";
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
%}
%union {
    float float_value;
    int int_value;
    char* string_value;
    struct AST* tree;
}

%token <string_value> LESS_EQ GREATER_EQ NOT_EQ EQ RETURN BEGIN_FN END_FN 
%token <string_value> AND OR
%token <string_value> ID
%token <string_value> STRING
%token <string_value> TYPE ASSIGN BEGIN_MAIN END_MAIN BEGIN_CLASS END_CLASS IF END_IF ELSE
%token <string_value> FOR END_FOR CONSTANT WHILE END_WHILE DO EVAL TYPEOF
%token <string_value> CHAR
%token <int_value> NR
%token <float_value> NR_FLOAT
%type  <string_value> CALLABLE_LIST
%type  <string_value> OPERATOR
%type  <int_value> CONDITION  
%type  <string_value> PARAMETER
%type  <string_value> PARAMETER_LIST
%type  <string_value> AUX_E
%type <tree> E
%start program_structure
%left OR 
%left AND
%left NOT_EQ EQ
%left LESS_EQ GREATER_EQ '<' '>'
%left '-' '+'
%left '/' '*'
%%

// program_structure: variable_partition main_partition                                      {std::cout << "The program is syntactically correct!" << std::endl;} | 
//                    function_partition main_partition                                      {std::cout << "The program is syntactically correct!" << std::endl;} | 
//                    class_partition main_partition                                         {std::cout << "The program is syntactically correct!" << std::endl;} |
//                    variable_partition program_structure                         | 
//                    function_partition program_structure                         | 
//                    class_partition program_structure                            |
//       ;

program_structure: variable_partition function_partition class_partition main_partition {std::cout << "The program is syntactically correct!" << std::endl;}
      ;

variable_partition : variable_declaration ';'
           | variable_partition variable_declaration ';'
           ;

function_partition : function_declaration 
           | function_partition function_declaration 
           ;

class_partition : class
           | class_partition class
           ;

variable_declaration : TYPE id_list { insert_table(0, 0, $1, std::string("type"), 0, 0, '\0', std::string(""), 0, yylineno); }
                    | CONSTANT TYPE id_list {insert_table(1, 0, $1, std::string("type"), 0, 0, '\0', std::string(""), 0, yylineno);}
                    ;

class_variable_declaration : TYPE id_list { insert_table(0, 0, $1, std::string("type"), 0, 0, '\0', std::string(""), 1, yylineno); }
                         | CONSTANT TYPE id_list {insert_table(1, 0, $1, std::string("type"), 0, 0, '\0', std::string(""), 1, yylineno);}
                         ;

function_declaration : TYPE ID '(' PARAMETER_LIST ')' BEGIN_FN list END_FN { insert_table_fn($1, $2, std::string("type"), yylineno, 0, $4);}
                  | TYPE ID '(' ')' BEGIN_FN list END_FN { insert_table_fn($1, $2, std::string("type"), yylineno, 0, "");}
                  | TYPE ID '(' PARAMETER_LIST ')' BEGIN_FN list RETURN E ';' END_FN { int val = Eval($9, yylineno); insert_table_fn($1, $2, std::string("type"), yylineno, 0, $4);}
                  | TYPE ID '(' ')' BEGIN_FN list RETURN E ';' END_FN { int val = Eval($8, yylineno); insert_table_fn($1, $2, std::string("type"), yylineno, 0, std::string(""));}
                  ;

class_fn_declaration : TYPE ID '(' PARAMETER_LIST ')' { insert_table_fn($1, $2, std::string("type"), yylineno, 1, $4);}
                       | TYPE ID '(' ')' { insert_table_fn($1, $2, std::string("type"), yylineno, 1, std::string(""));}
                       ;

PARAMETER_LIST : PARAMETER {$$ = $1;} 
            | PARAMETER ',' PARAMETER_LIST { $$ = strdup(final($1, $3, std::string(",")).c_str()); }
            ;
            
PARAMETER : TYPE ID {
                $$ = strdup(final($1, $2, std::string(" ")).c_str());
               }
      ; 

class : BEGIN_CLASS ID inside_of_class END_CLASS {classs($2);}
      ;

class_first_partition : class_variable_declaration ';'
                | class_first_partition class_variable_declaration ';'
                ;

class_second_partition : class_fn_declaration ';'
                | class_second_partition class_fn_declaration ';'
                ;

inside_of_class : class_first_partition class_second_partition
               | class_first_partition
               | class_second_partition
               ;

id_list :  ID                                { insert_table(0, 0, $1, std::string("variable"), 0, 0, '\0', std::string(""), 0, yylineno);}
         | ID '[' NR ']'                     { insert_table(0, $3, $1, std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
         | ID ',' id_list                    { insert_table(0, 0, $1, std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
         | ID '[' NR ']' ',' id_list         { insert_table(0, $3, $1, std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
         | ID ASSIGN E                       { int val = Eval($3, yylineno); insert_table(0, 0, $1, std::string("variable"), val, 0, '\0', "", 0, yylineno);}
         | ID ASSIGN E ',' id_list           { int val = Eval($3, yylineno); insert_table(0, 0, $1, std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
         | ID ASSIGN NR_FLOAT                { insert_table(0, 0, $1, std::string("variable"), 0, $3, '\0', "", 0, yylineno);}
         | ID ASSIGN NR_FLOAT ',' id_list    { insert_table(0, 0, $1, std::string("variable"), 0, $3, '\0', "", 0, yylineno);}
         | ID ASSIGN STRING                  { insert_table(0, 0, $1, std::string("variable"), 0, 0, '\0', $3, 0, yylineno);}
         | ID ASSIGN STRING ',' id_list      { insert_table(0, 0, $1, std::string("variable"), 0, 0, '\0', $3, 0, yylineno);}
         | ID ASSIGN CHAR                    { insert_table(0, 0, $1, std::string("variable"), 0, 0, $3[0], std::string(""), 0, yylineno);}
         | ID ASSIGN CHAR ',' id_list        { insert_table(0, 0, $1, std::string("variable"), 0, 0, $3[0], std::string(""), 0, yylineno);}
         ;
      
main_partition : BEGIN_MAIN list END_MAIN
     ;
     
list : statement ';' 
     | list statement ';'
     | list if 
     | list for
     | list do
     | list while
     ;

statement: ID ASSIGN E  { 
                            check($1, yylineno, 0);
                            if(strcmp(get_type(std::string($1)).c_str(), "i32"))
                            {
                                sprintf(error_message, "Linia %d, type de date diferit", yylineno);
                                handle_error();
                                 ;
                            }
                            int val = Eval($3, yylineno);
                            update_table($1, "i32", val, yylineno, 0, "");
                        }
         | ID '(' CALLABLE_LIST ')' {check_fn($1, $3, yylineno);}
         | TYPEOF '(' AUX_E ')' { std::cout << $3 << std::endl; }
         | EVAL '(' E ')' { std::cout << Eval($3, yylineno) << std::endl;}
         | ID '.' ID ASSIGN E { 
                                snprintf(internal_buffer,100,"%s.%s", $1, $3);
                                check(std::string(internal_buffer), yylineno, 0);
                                if(strcmp(strdup(get_type($1).c_str()), "i32"))
                                {
                                    sprintf(error_message, "Linia %d, type de date diferit", yylineno);
                                    handle_error();
                                     ;
                                }
                                int val = Eval($5, yylineno);
                                update_table(std::string(internal_buffer), "i32", val, yylineno, 0, "");
                              }
         | ID ASSIGN NR_FLOAT {
                                check($1, yylineno, 0);
                                if(strcmp(strdup(get_type($1).c_str()), "f32"))
                                {
                                    sprintf(error_message, "Linia %d, type de date diferit", yylineno);
                                    handle_error();
                                     ;
                                }
                                update_table($1, "f32", 0, yylineno, $3, "");
                              }
         | ID '.' ID '(' CALLABLE_LIST ')' {
                                            snprintf(internal_buffer,100,"%s.%s", $1, $3);
                                            check_fn(internal_buffer, $5, yylineno);

                                        }
         | ID '[' NR ']' ASSIGN E { check($1, yylineno, $3);}
         ;

CONDITION : '(' CONDITION ')' {$$ = $2;}
     | CONDITION AND CONDITION { int rez1=$1; int rez2=$3; 
                       $$=(rez1 && rez2);
                     }
     | CONDITION OR CONDITION { int rez1=$1; int rez2=$3;
                      $$=(rez1 || rez2);
                    }
     | E OPERATOR E { 
                int rez1=Eval($1, yylineno); int rez2=Eval($3, yylineno);
                if (strcmp($2, "less_equal")) $$=(rez1 <= rez2);
                if (strcmp($2, "greater_equal")) $$=(rez1 >= rez2);
                if (strcmp($2, "not_equal")) $$=(rez1 != rez2);
                if (strcmp($2, "equal")) $$=(rez1 == rez2);
                if (strcmp($2, ">")) $$=(rez1 > rez2);
                if (strcmp($2, "<")) $$=(rez1 < rez2);
                }
     ; 

OPERATOR : LESS_EQ {$$ = $1;}
    | GREATER_EQ {$$ = $1;}
    | NOT_EQ {$$ = $1;}
    | EQ  {$$ = $1;}
    | '>' {$$ = ">";}
    | '<' {$$ = "<";}
    ;

do : DO list WHILE '(' CONDITION ')' ';'
   ;

while : WHILE '(' CONDITION ')' list END_WHILE
      ;

if : IF '(' CONDITION ')' list END_IF
   | IF '(' CONDITION ')' list ELSE list END_IF
   ;

for : FOR '(' TYPE ID ASSIGN E ';' CONDITION ';' statement ')' list END_FOR
    | FOR '(' ID ASSIGN E ';' CONDITION ';' statement ')' list END_FOR
    ;

E : E '+' E                         { $$ = AST_Init("+", $1, $3, OPERATOR); }
  | E '-' E                         { $$ = AST_Init("-", $1, $3, OPERATOR); }
  | E '*' E                         { $$ = AST_Init("*", $1, $3, OPERATOR); }
  | E '/' E                         { $$ = AST_Init("/", $1, $3, OPERATOR); }
  | '(' E ')'                       { $$ = $2; }
  | ID                              { check($1, yylineno, 0); $$ = AST_Init($1, NULL, NULL, IDENTIFIER);}
  | NR                              { char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", $1); $$ = AST_Init(nr, NULL, NULL, NUMBER); }
  | ID '[' NR ']'                   { check($1, yylineno, 1); int val = get_array_value($1, $3, yylineno); char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", val); $$ = AST_Init(nr, NULL, NULL, NUMBER); }
  | ID '(' CALLABLE_LIST ')'           { check_fn($1, $3, yylineno); $$ = AST_Init("0", NULL, NULL, NUMBER); }
  | ID '.' ID                       { snprintf(internal_buffer,100,"%s.%s", $1, $3); check(std::string(internal_buffer), yylineno, 0);  $$ = AST_Init($1, NULL, NULL, IDENTIFIER);}
  | ID '.' ID '(' CALLABLE_LIST ')'    { snprintf(internal_buffer,100,"%s.%s", $1, $3); check_fn(std::string(internal_buffer), $3, yylineno); $$ = AST_Init("0", NULL, NULL, NUMBER);}
  ;

AUX_E : AUX_E '+' AUX_E {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                         ;
                                    }
                                    $$ = $1;
                                 }
         | AUX_E '-' AUX_E {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                         ;
                                    }
                                    $$ = $1;
                                 }
         | AUX_E '/' AUX_E {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                         ;
                                    }
                                    $$ = $1;
                                 }
         | AUX_E '*' AUX_E {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                         ;
                                    }
                                    $$ = $1;
                                 }
         | '(' AUX_E ')' { $$ = $2; }
         | ID                                    { check($1, yylineno, 0); $$ = strdup(get_type($1).c_str());}
         | NR                                    { $$ = "i32";}
         | NR_FLOAT                              { $$ = "f32";}
         | ID '[' NR ']'                         { check($1, yylineno, 1); $$ = strdup(get_type($1).c_str());}
         | ID '(' CALLABLE_LIST ')'              { check_fn($1, $3, yylineno); $$ = strdup(fn_get_type($1).c_str());}
         | ID '.' ID                             { snprintf(internal_buffer,100,"%s.%s", $1, $3); check($1, yylineno, 1); $$ = strdup(get_type(internal_buffer).c_str());}
         | ID '.' ID '(' CALLABLE_LIST ')'       { snprintf(internal_buffer,100,"%s.%s", $1, $3); check_fn(internal_buffer, $5, yylineno); $$ = strdup(fn_get_type(internal_buffer).c_str());}
         ;

CALLABLE_LIST : E {
                struct AST* tree = $1;
                if(tree->left == NULL && tree->right == NULL)
                {
                    if(tree->n_Type == IDENTIFIER)
                        $$ = strdup(get_type(tree->name).c_str());
                    else
                        $$ = "i32";
                }
                else
                    $$ = "i32";
            }
           | CALLABLE_LIST ',' E {
                    struct AST* tree = $3;
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
                        strcpy(internal_buffer, $1);
                        strcat(internal_buffer, ",");
                        strcat(internal_buffer, type);
                        $$ = internal_buffer;
                        // printf("%s.\n", type);
                }
           | NR_FLOAT {$$ = "f32";}
           | CALLABLE_LIST ',' NR_FLOAT { snprintf(internal_buffer,100,"%s,float",$1); $$ = internal_buffer;}
           | CHAR {$$ = "chr";}
           | CALLABLE_LIST ',' CHAR {snprintf(internal_buffer,100,"%s,char",$1); $$ = internal_buffer;}
           | STRING {$$ = "str";}
           | CALLABLE_LIST ',' STRING {snprintf(internal_buffer,100,"%s,string",$1); $$ = internal_buffer;}
           ;

%%

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
