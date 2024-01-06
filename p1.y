%{
    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <string.h>
    #include <fcntl.h>
    #include <unistd.h>

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
        std::string name;
        std::string type;
        informations var_info;
        int local;
        bool is_constant;
        bool is_class;
        int array_size = 0;
        int array[100];
        int elements;
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
        if(_type == "type")
        {
            int temp = variable_counter - 1;
            while(symbol_table[temp].type == "" && temp >= 0)
            {
                symbol_table[temp].type = _type;
                symbol_table[temp].is_constant = _is_constant;
                symbol_table[temp].is_class = _is_class;
                temp = temp - 1;
            }
        }
        else
        {
            if(_type == "var")
            {
                for(int i = 0; i < variable_counter; i++)
                {
                    if(symbol_table[i].name == _string)
                    {
                        std::cout << "The line " << yylineno << ": Variable " << _string << " has been already declared!";
                        handle_error();
                        exit(0);
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
    }

    void check(std::string _s, int yylineno, int v)
    {
        bool exists = 0;
        int i = 0;
        for(i = 0; i < variable_counter; i++)
        {
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
                    std::cout << "The line " << yylineno << ": Function " << _s << " is not defined!";
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
                    char buffer[1024];
                    std::string partition;
                    std::string aux;

                    partition = strchr(p, ' ');
                    strncpy(buffer, p, strlen(p) - partition.size());
                    aux = std::string(buffer);

                    symbol_table_functions[function_counter].parameter_types = symbol_table_functions[function_counter].parameter_types + aux;
                    symbol_table_functions[function_counter].parameter_types = symbol_table_functions[function_counter].parameter_types + ",";
                    symbol_table_functions[function_counter].value[symbol_table_functions[function_counter].argument_count].type = aux;
                    symbol_table_functions[function_counter].value[symbol_table_functions[function_counter].argument_count].name = p + strlen(aux.c_str());

                    symbol_table_functions[function_counter].argument_count++;

                    p = strtok(NULL, ",");
                }
            }
        }
    }

    void check_fn(std::string _s, std::string _params, int yylineno)
    {
        bool exists = 0;
        int i;
        for(i = 0; i < function_counter; i++)
        {
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

                }
                else
                if(type == "bool")
                {

                }
                else
                if(type == "str")
                {

                }
                else 
                if(type == "i32")
                {
                    return get_id(_ast->name, yylineno);
                }
            }
            else
            {
                if(_ast->n_Type == NUMBER)
                {
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
            if(symbol_table[i].name == _type)
            {
                if(symbol_table[i].type == _type)
                {
                    //eroare
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

    void print_values_to_text_file(int _file_descriptor)
    {
        for(int i = 0; i < function_counter; i++)
        {
            
        }
    }

extern FILE* yyin;
extern int yylex();
void yyerror(char* s);
extern char* yytext;
extern int yylineno;
%}
%union {
    float floatval;
    int intval;
    char* strval;
    struct AST* tree;
}

%token <strval> LESS_EQ GREATER_EQ NOT_EQ EQ RETURN BEGIN_FN END_FN
%token <strval> AND OR
%token <strval> ID
%token <strval> STRING
%token <strval> TYPE ASSIGN BEGIN_MAIN END_MAIN BEGIN_CLASS END_CLASS IF END_IF ELSE
%token <strval> FOR END_FOR CONSTANT WHILE END_WHILE DO EVAL TYPEOF
%token <strval> CHAR
%token <intval> NR
%token <floatval> NR_FLOAT
%type  <strval> lista_apel
%type  <strval> opr
%type  <intval> cond  
%type  <strval> param
%type  <strval> lista_param
%type  <strval> pseudo_e
%type <tree> e
%start progr
%left OR 
%left AND
%left NOT_EQ EQ
%left LESS_EQ GREATER_EQ '<' '>'
%left '-' '+'
%left '/' '*'
%%

progr: sectiunea1 rest1 {printf("program corect sintactic\n");}
     ;

rest1 : sectiunea2 rest2
      ;

rest2 : sectiunea3 bloc
      ;

sectiunea1 : declaratieVariabila ';'
           | sectiunea1 declaratieVariabila ';'
           ;

sectiunea2 : declaratieFunctie 
           | sectiunea2 declaratieFunctie 
           ;

sectiunea3 : clasa
           | sectiunea3 clasa
           ;

declaratieVariabila : TYPE lista_id { insert_table(0, 0, $1, std::string(std::string("tip")), 0, 0, '\0', std::string(""), 0, yylineno); }
                    | CONSTANT TYPE lista_id {insert_table(1, 0, $1, std::string("tip"), 0, 0, '\0', std::string(""), 0, yylineno);}
                    ;

declaratieVariabilaClasa : TYPE lista_id { insert_table(0, 0, $1, std::string("tip"), 0, 0, '\0', std::string(""), 1, yylineno); }
                         | CONSTANT TYPE lista_id {insert_table(1, 0, $1, std::string("tip"), 0, 0, '\0', std::string(""), 1, yylineno);}
                         ;

declaratieFunctie : TYPE ID '(' lista_param ')' BEGIN_FN list END_FN { insert_table_fn($1, $2, std::string("tip"), yylineno, 0, $4);}
                  | TYPE ID '(' ')' BEGIN_FN list END_FN { insert_table_fn($1, $2, std::string("tip"), yylineno, 0, "");}
                  | TYPE ID '(' lista_param ')' BEGIN_FN list RETURN e ';' END_FN { int val = Eval($9, yylineno); insert_table_fn($1, $2, std::string("tip"), yylineno, 0, $4);}
                  | TYPE ID '(' ')' BEGIN_FN list RETURN e ';' END_FN { int val = Eval($8, yylineno); insert_table_fn($1, $2, std::string("tip"), yylineno, 0, std::string(""));}
                  ;

declaratieFunctieClasa : TYPE ID '(' lista_param ')' { insert_table_fn($1, $2, std::string("tip"), yylineno, 1, $4);}
                       | TYPE ID '(' ')' { insert_table_fn($1, $2, std::string("tip"), yylineno, 1, std::string(""));}
                       ;

lista_param : param {$$ = $1;} 
            | param ',' lista_param { $$ = strdup(final($1, $3, std::string(",")).c_str()); }
            ;
            
param : TYPE ID {
                $$ = strdup(final($1, $2, std::string(" ")).c_str());
               }
      ; 

clasa : BEGIN_CLASS ID interior_clasa END_CLASS {classs($2);}
      ;

sectiuneaclasa1 : declaratieVariabilaClasa ';'
                | sectiuneaclasa1 declaratieVariabilaClasa ';'
                ;

sectiuneaclasa2 : declaratieFunctieClasa ';'
                | sectiuneaclasa2 declaratieFunctieClasa ';'
                ;

interior_clasa : sectiuneaclasa1 sectiuneaclasa2
               | sectiuneaclasa1
               | sectiuneaclasa2
               ;

lista_id : ID {insert_table(0, 0, $1, std::string("variabila"), 0, 0, '\0', std::string(""), 0, yylineno);}
         | ID '[' NR ']' { insert_table(0, $3, $1, std::string("variabila"), 0, 0, '\0', "", 0, yylineno);}
         | ID ',' lista_id { insert_table(0, 0, $1, std::string("variabila"), 0, 0, '\0', "", 0, yylineno);}
         | ID '[' NR ']' ',' lista_id { insert_table(0, $3, $1, std::string("variabila"), 0, 0, '\0', "", 0, yylineno);}
         | ID ASSIGN e { int val = Eval($3, yylineno); insert_table(0, 0, $1, std::string("variabila"), val, 0, '\0', "", 0, yylineno);}
         | ID ASSIGN e ',' lista_id { int val = Eval($3, yylineno); insert_table(0, 0, $1, std::string("variabila"), 0, 0, '\0', "", 0, yylineno);}
         | ID ASSIGN NR_FLOAT { insert_table(0, 0, $1, std::string("variabila"), 0, $3, '\0', "", 0, yylineno);}
         | ID ASSIGN NR_FLOAT ',' lista_id { insert_table(0, 0, $1, std::string("variabila"), 0, $3, '\0', "", 0, yylineno);}
         | ID ASSIGN STRING { insert_table(0, 0, $1, std::string("variabila"), 0, 0, '\0', $3, 0, yylineno);}
         | ID ASSIGN STRING ',' lista_id { insert_table(0, 0, $1, std::string("variabila"), 0, 0, '\0', $3, 0, yylineno);}
         | ID ASSIGN CHAR { insert_table(0, 0, $1, std::string("variabila"), 0, 0, $3[0], std::string(""), 0, yylineno);}
         | ID ASSIGN CHAR ',' lista_id { insert_table(0, 0, $1, std::string("variabila"), 0, 0, $3[0], std::string(""), 0, yylineno);}
         ;
      
/* bloc */
bloc : BEGIN_MAIN list END_MAIN
     ;
     
/* lista instructiuni */
list : statement ';' 
     | list statement ';'
     | list if 
     | list for
     | list do
     | list while
     ;

/* instructiune */
statement: ID ASSIGN e  { 
                            check($1, yylineno, 0);
                            if(strcmp(get_type(std::string($1)).c_str(), "i32"))
                            {
                                sprintf(error_message, "Linia %d, tip de date diferit", yylineno);
                                handle_error();
                                exit(0);
                            }
                            int val = Eval($3, yylineno);
                            update_table($1, "i32", val, yylineno, 0, "");
                        }
         | ID '(' lista_apel ')' {check_fn($1, $3, yylineno);}
         | TYPEOF '(' pseudo_e ')' {printf("%s\n", $3);}
         | EVAL '(' e ')' {printf("%d\n", Eval($3, yylineno));}
         | ID '.' ID ASSIGN e { 
                                snprintf(internal_buffer,100,"%s.%s", $1, $3);
                                check(std::string(internal_buffer), yylineno, 0);
                                if(strcmp(strdup(get_type($1).c_str()), "i32"))
                                {
                                    sprintf(error_message, "Linia %d, tip de date diferit", yylineno);
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
                                    sprintf(error_message, "Linia %d, tip de date diferit", yylineno);
                                    handle_error();
                                    exit(0);
                                }
                                update_table($1, "f32", 0, yylineno, $3, "");
                              }
         | ID '.' ID '(' lista_apel ')' {
                                            snprintf(internal_buffer,100,"%s.%s", $1, $3);
                                            check_fn(internal_buffer, $5, yylineno);

                                        }
         | ID '[' NR ']' ASSIGN e { check($1, yylineno, $3);}
         ;

cond : '(' cond ')' {$$ = $2;}
     | cond AND cond { int rez1=$1; int rez2=$3; 
                       $$=(rez1 && rez2);
                     }
     | cond OR cond { int rez1=$1; int rez2=$3;
                      $$=(rez1 || rez2);
                    }
     | e opr e { 
                int rez1=Eval($1, yylineno); int rez2=Eval($3, yylineno);
                if (strcmp($2, "less_equal")) $$=(rez1 <= rez2);
                if (strcmp($2, "greater_equal")) $$=(rez1 >= rez2);
                if (strcmp($2, "not_equal")) $$=(rez1 != rez2);
                if (strcmp($2, "equal")) $$=(rez1 == rez2);
                if (strcmp($2, ">")) $$=(rez1 > rez2);
                if (strcmp($2, "<")) $$=(rez1 < rez2);
                }
     ; 

opr : LESS_EQ {$$ = $1;}
    | GREATER_EQ {$$ = $1;}
    | NOT_EQ {$$ = $1;}
    | EQ  {$$ = $1;}
    | '>' {$$ = ">";}
    | '<' {$$ = "<";}
    ;

if : IF '(' cond ')' list END_IF
   | IF '(' cond ')' list ELSE list END_IF
   ;

for : FOR '(' TYPE ID ASSIGN e ';' cond ';' statement ')' list END_FOR
    | FOR '(' ID ASSIGN e ';' cond ';' statement ')' list END_FOR
    ;

do : DO list WHILE '(' cond ')' ';'
   ;

while : WHILE '(' cond ')' list END_WHILE
      ;

e : e '+' e { $$ = AST_Init("+", $1, $3, OPERATOR); }
  | e '-' e { $$ = AST_Init("-", $1, $3, OPERATOR); }
  | e '*' e { $$ = AST_Init("*", $1, $3, OPERATOR); }
  | e '/' e { $$ = AST_Init("/", $1, $3, OPERATOR); }
  | '(' e ')' { $$ = $2; }
  | ID { check($1, yylineno, 0); $$ = AST_Init($1, NULL, NULL, IDENTIFIER);}
  | NR { char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", $1); $$ = AST_Init(nr, NULL, NULL, NUMBER); }
  | ID '[' NR ']' {check($1, yylineno, 1); int val = get_array_value($1, $3, yylineno); char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", val); $$ = AST_Init(nr, NULL, NULL, NUMBER); }
  | ID '(' lista_apel ')' { check_fn($1, $3, yylineno);
                            $$ = AST_Init("0", NULL, NULL, NUMBER);
                          }
  | ID '.' ID { snprintf(internal_buffer,100,"%s.%s", $1, $3); check(std::string(internal_buffer), yylineno, 0);  $$ = AST_Init($1, NULL, NULL, IDENTIFIER);}
  | ID '.' ID '(' lista_apel ')' { snprintf(internal_buffer,100,"%s.%s", $1, $3); check_fn(std::string(internal_buffer), $3, yylineno); $$ = AST_Init("0", NULL, NULL, NUMBER);}
  ;

pseudo_e : pseudo_e '+' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "Linia %d, tip de date diferit!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '-' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "Linia %d, tip de date diferit!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '/' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "Linia %d, tip de date diferit!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '*' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_message, "Linia %d, tip de date diferit!", yylineno);
                                        handle_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | '(' pseudo_e ')' { $$ = $2; }
         | ID {check($1, yylineno, 0); $$ = strdup(get_type($1).c_str());}
         | NR {$$ = "i32";}
         | NR_FLOAT {$$ = "f32";}
         | ID '[' NR ']' {check($1, yylineno, 1); $$ = strdup(get_type($1).c_str());}
         | ID '(' lista_apel ')' { check_fn($1, $3, yylineno); $$ = strdup(FnRetType($1).c_str());}
         | ID '.' ID {snprintf(internal_buffer,100,"%s.%s", $1, $3); check($1, yylineno, 1); $$ = strdup(get_type(internal_buffer).c_str());}
         | ID '.' ID '(' lista_apel ')' { snprintf(internal_buffer,100,"%s.%s", $1, $3); check_fn(internal_buffer, $5, yylineno); $$ = strdup(FnRetType(internal_buffer).c_str());}
         ;

lista_apel : e {
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
           | lista_apel ',' e {
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
                        // printf("%s.\n", tip);
                }
           | NR_FLOAT {$$ = "f32";}
           | lista_apel ',' NR_FLOAT { snprintf(internal_buffer,100,"%s,float",$1); $$ = internal_buffer;}
           | CHAR {$$ = "chr";}
           | lista_apel ',' CHAR {snprintf(internal_buffer,100,"%s,char",$1); $$ = internal_buffer;}
           | STRING {$$ = "str";}
           | lista_apel ',' STRING {snprintf(internal_buffer,100,"%s,string",$1); $$ = internal_buffer;}
           ;

%%

void yyerror(char * s)
{
    printf("eroare: %s la linia:%d\n",s,yylineno);
}

int main(int argc, char** argv)
{
    symbol_table_descriptor = open("symbol_table.txt", O_RDWR|O_TRUNC);
    symbol_table_function_descriptor = open("symbol_table_functions.txt", O_RDWR|O_TRUNC);
    yyin = fopen(argv[1],"r");
    yyparse();
    print_values_to_text_file(symbol_table_descriptor);
    print_values_to_text_file(symbol_table_function_descriptor);
}
