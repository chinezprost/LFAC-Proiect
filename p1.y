%{
    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <string.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <fstream>

    char internal_buffer[1024];
    int variable_counter = 0;
    int function_counter = 0;
    int symbol_table_descriptor, symbol_table_function_descriptor;
    char error_message[1024];

    std::string error_string;

    enum n_type
    {
        OPERATOR = 1,
        IDENTIFIER = 2,
        NUMBER = 3,
        FLOAT_NUMBER = 4,
        CHR_STR = 5
    };

    class informations
    {
    public:
        char char_value = '\0';
        float float_value = 0;
        std::string string_value = "";
        int integer_value = 0;
    };

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
        int array[100] = {'\0'};
        int elements = 0;
    };

    class parameters
    {
    public:
        std::string name;
        std::string type;
    };

    class symbol_table_function_class
    {
    public:
        std::string name;
        std::string type;
        int argument_count;
        bool is_class;
        std::string ret_id;
        parameters value[30];
        std::string parameter_types;
    };

    parameters temp_params[10];
    symbol_table_class symbol_table[100];
    symbol_table_function_class symbol_table_functions[100];

    struct AST
    {
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
                        //std::cout << "The line " << yylineno << ": Variable " << _string << " has been already declared!";
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

    int get_id(std::string _s, int yylineno)
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
                    //std::cout << "TIP: " << get_id(_ast->name, yylineno) << '\n';
                    return get_id(_ast->name, yylineno);
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

    std::string TypeOf(AST* _ast, float n_float, bool n_bool, std::string string_string, std::string string_char, int yylineno)
    {
        if(_ast == nullptr)
        {
            if(n_float != 0)
            {
                return std::string("f64");
            }
            if(n_bool != 0)
            {
                return std::string("bool");
            }
            if(string_string != "")
            {
                return std::string("str");
            }
            if(string_char != "")
            {
                return std::string("chr");
            }
        }
        else
        {
            if(_ast->left == nullptr && _ast->right == nullptr)
            {
                if(_ast->n_Type == IDENTIFIER)
                {
                    std::string type = get_type(_ast->name);
                    if(type == "i32")
                    {
                        return std::string("i32");
                    }
                    if(type == "bool")
                    {
                        return std::string("bool");
                    }if(type == "f64")
                    {
                        return std::string("f64");
                    }
                }
                else
                {
                    Eval(_ast, yylineno);
                    return "i32";
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
                    std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << '\n';
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

    std::string FnRetType(std::string _fn)
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
    AST* tree;
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
%type  <string_value> callable_list
%type  <string_value> operator
%type  <int_value> condition  
%type  <string_value> parameter
%type  <string_value> parameter_list
%type  <string_value> pseudo_e
%type <tree> e
%start program_structure
%left OR 
%left AND
%left NOT_EQ EQ
%left LESS_EQ GREATER_EQ '<' '>'
%left '-' '+'
%left '/' '*'
%%

program_structure: variable_partition bloc                                      {std::cout << "The program is syntactically correct!" << std::endl;} | 
                   function_partition bloc                                      {std::cout << "The program is syntactically correct!" << std::endl;} | 
                   class_partition bloc                                         {std::cout << "The program is syntactically correct!" << std::endl;} | 
                   variable_partition function_partition bloc                   {std::cout << "The program is syntactically correct!" << std::endl;} |
                   function_partition variable_partition bloc                   {std::cout << "The program is syntactically correct!" << std::endl;} | 
                   variable_partition class_partition bloc                      {std::cout << "The program is syntactically correct!" << std::endl;} |
                   function_partition class_partition bloc                      {std::cout << "The program is syntactically correct!" << std::endl;} |
                   class_partition function_partition bloc                      {std::cout << "The program is syntactically correct!" << std::endl;} |
                   variable_partition function_partition class_partition bloc   {std::cout << "The program is syntactically correct!" << std::endl;} |
                   variable_partition class_partition function_partition bloc   {std::cout << "The program is syntactically correct!" << std::endl;} |
                   function_partition variable_partition class_partition bloc   {std::cout << "The program is syntactically correct!" << std::endl;} |
                   function_partition class_partition variable_partition bloc   {std::cout << "The program is syntactically correct!" << std::endl;} |
                   class_partition variable_partition function_partition bloc   {std::cout << "The program is syntactically correct!" << std::endl;} |
                   class_partition function_partition variable_partition bloc   {std::cout << "The program is syntactically correct!" << std::endl;}
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

function_declaration : TYPE ID '(' parameter_list ')' BEGIN_FN list END_FN { insert_table_fn($1, $2, std::string("type"), yylineno, 0, $4);}
                  | TYPE ID '(' ')' BEGIN_FN list END_FN { insert_table_fn($1, $2, std::string("type"), yylineno, 0, "");}
                  | TYPE ID '(' parameter_list ')' BEGIN_FN list RETURN e ';' END_FN { int val = Eval($9, yylineno); insert_table_fn($1, $2, std::string("type"), yylineno, 0, $4);}
                  | TYPE ID '(' ')' BEGIN_FN list RETURN e ';' END_FN { int val = Eval($8, yylineno); insert_table_fn($1, $2, std::string("type"), yylineno, 0, std::string(""));}
                  ;

class_fn_declaration : TYPE ID '(' parameter_list ')' { insert_table_fn($1, $2, std::string("type"), yylineno, 1, $4);}
                       | TYPE ID '(' ')' { insert_table_fn($1, $2, std::string("type"), yylineno, 1, std::string(""));}
                       ;

parameter_list : parameter {$$ = $1;} 
            | parameter ',' parameter_list { $$ = strdup(final($1, $3, std::string(",")).c_str()); }
            ;
            
parameter : TYPE ID {
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
         | ID ASSIGN e                       { int val = Eval($3, yylineno); insert_table(0, 0, $1, std::string("variable"), val, 0, '\0', "", 0, yylineno);}
         | ID ASSIGN e ',' id_list           { int val = Eval($3, yylineno); insert_table(0, 0, $1, std::string("variable"), 0, 0, '\0', "", 0, yylineno);}
         | ID ASSIGN NR_FLOAT                { insert_table(0, 0, $1, std::string("variable"), 0, $3, '\0', "", 0, yylineno);}
         | ID ASSIGN NR_FLOAT ',' id_list    { insert_table(0, 0, $1, std::string("variable"), 0, $3, '\0', "", 0, yylineno);}
         | ID ASSIGN STRING                  { insert_table(0, 0, $1, std::string("variable"), 0, 0, '\0', $3, 0, yylineno);}
         | ID ASSIGN STRING ',' id_list      { insert_table(0, 0, $1, std::string("variable"), 0, 0, '\0', $3, 0, yylineno);}
         | ID ASSIGN CHAR                    { insert_table(0, 0, $1, std::string("variable"), 0, 0, $3[0], std::string(""), 0, yylineno);}
         | ID ASSIGN CHAR ',' id_list        { insert_table(0, 0, $1, std::string("variable"), 0, 0, $3[0], std::string(""), 0, yylineno);}
         ;
      
bloc : BEGIN_MAIN list END_MAIN
     ;
     
list : statement ';' 
     | list statement ';'
     | list if 
     | list for
     | list do
     | list while
     ;

statement: ID ASSIGN e  { 
                            check($1, yylineno, 0);
                            if(strcmp(get_type(std::string($1)).c_str(), "i32"))
                            {
                                sprintf(error_message, "Linia %d, type de date diferit", yylineno);
                                handle_error();
                                exit(0);
                            }
                            int val = Eval($3, yylineno);
                            update_table($1, "i32", val, yylineno, 0, "");
                        }
         | ID '(' callable_list ')' {check_fn($1, $3, yylineno);}
         | TYPEOF '(' pseudo_e ')' {printf("%s\n", $3);}
         | EVAL '(' e ')' {printf("%d\n", Eval($3, yylineno));}
         | ID '.' ID ASSIGN e { 
                                snprintf(internal_buffer,100,"%s.%s", $1, $3);
                                check(std::string(internal_buffer), yylineno, 0);
                                if(strcmp(strdup(get_type($1).c_str()), "i32"))
                                {
                                    sprintf(error_message, "Linia %d, type de date diferit", yylineno);
                                    handle_error();
                                    exit(0);
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
                                    exit(0);
                                }
                                update_table($1, "f32", 0, yylineno, $3, "");
                              }
         | ID '.' ID '(' callable_list ')' {
                                            snprintf(internal_buffer,100,"%s.%s", $1, $3);
                                            check_fn(internal_buffer, $5, yylineno);

                                        }
         | ID '[' NR ']' ASSIGN e { check($1, yylineno, $3);}
         ;

condition : '(' condition ')' {$$ = $2;}
     | condition AND condition { int rez1=$1; int rez2=$3; 
                       $$=(rez1 && rez2);
                     }
     | condition OR condition { int rez1=$1; int rez2=$3;
                      $$=(rez1 || rez2);
                    }
     | e operator e { 
                int rez1=Eval($1, yylineno); int rez2=Eval($3, yylineno);
                if (strcmp($2, "less_equal")) $$=(rez1 <= rez2);
                if (strcmp($2, "greater_equal")) $$=(rez1 >= rez2);
                if (strcmp($2, "not_equal")) $$=(rez1 != rez2);
                if (strcmp($2, "equal")) $$=(rez1 == rez2);
                if (strcmp($2, ">")) $$=(rez1 > rez2);
                if (strcmp($2, "<")) $$=(rez1 < rez2);
                }
     ; 

operator : LESS_EQ {$$ = $1;}
    | GREATER_EQ {$$ = $1;}
    | NOT_EQ {$$ = $1;}
    | EQ  {$$ = $1;}
    | '>' {$$ = ">";}
    | '<' {$$ = "<";}
    ;

do : DO list WHILE '(' condition ')' ';'
   ;

while : WHILE '(' condition ')' list END_WHILE
      ;

if : IF '(' condition ')' list END_IF
   | IF '(' condition ')' list ELSE list END_IF
   ;

for : FOR '(' TYPE ID ASSIGN e ';' condition ';' statement ')' list END_FOR
    | FOR '(' ID ASSIGN e ';' condition ';' statement ')' list END_FOR
    ;

e : e '+' e                         { $$ = AST_Init("+", $1, $3, OPERATOR); }
  | e '-' e                         { $$ = AST_Init("-", $1, $3, OPERATOR); }
  | e '*' e                         { $$ = AST_Init("*", $1, $3, OPERATOR); }
  | e '/' e                         { $$ = AST_Init("/", $1, $3, OPERATOR); }
  | '(' e ')'                       { $$ = $2; }
  | ID                              { check($1, yylineno, 0); $$ = AST_Init($1, NULL, NULL, IDENTIFIER);}
  | NR                              { char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", $1); $$ = AST_Init(nr, NULL, NULL, NUMBER); }
  | ID '[' NR ']'                   { check($1, yylineno, 1); int val = get_array_value($1, $3, yylineno); char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", val); $$ = AST_Init(nr, NULL, NULL, NUMBER); }
  | ID '(' callable_list ')'           { check_fn($1, $3, yylineno); $$ = AST_Init("0", NULL, NULL, NUMBER); }
  | ID '.' ID                       { snprintf(internal_buffer,100,"%s.%s", $1, $3); check(std::string(internal_buffer), yylineno, 0);  $$ = AST_Init($1, NULL, NULL, IDENTIFIER);}
  | ID '.' ID '(' callable_list ')'    { snprintf(internal_buffer,100,"%s.%s", $1, $3); check_fn(std::string(internal_buffer), $3, yylineno); $$ = AST_Init("0", NULL, NULL, NUMBER);}
  ;

pseudo_e : pseudo_e '+' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '-' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '/' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '*' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "At line: %d, data types are different!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | '(' pseudo_e ')' { $$ = $2; }
         | ID                                    { check($1, yylineno, 0); $$ = strdup(get_type($1).c_str());}
         | NR                                    { $$ = "i32";}
         | NR_FLOAT                              { $$ = "f32";}
         | ID '[' NR ']'                         { check($1, yylineno, 1); $$ = strdup(get_type($1).c_str());}
         | ID '(' callable_list ')'                 { check_fn($1, $3, yylineno); $$ = strdup(FnRetType($1).c_str());}
         | ID '.' ID                             { snprintf(internal_buffer,100,"%s.%s", $1, $3); check($1, yylineno, 1); $$ = strdup(get_type(internal_buffer).c_str());}
         | ID '.' ID '(' callable_list ')'          { snprintf(internal_buffer,100,"%s.%s", $1, $3); check_fn(internal_buffer, $5, yylineno); $$ = strdup(FnRetType(internal_buffer).c_str());}
         ;

callable_list : e {
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
           | callable_list ',' e {
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
           | callable_list ',' NR_FLOAT { snprintf(internal_buffer,100,"%s,float",$1); $$ = internal_buffer;}
           | CHAR {$$ = "chr";}
           | callable_list ',' CHAR {snprintf(internal_buffer,100,"%s,char",$1); $$ = internal_buffer;}
           | STRING {$$ = "str";}
           | callable_list ',' STRING {snprintf(internal_buffer,100,"%s,string",$1); $$ = internal_buffer;}
           ;

%%

void yyerror(char * s)
{
    printf("eroare: %s la linia:%d\n",s,yylineno);
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
}
