%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

char buff[100];
int var_count = 0;
int func_count = 0;
int fd, fd1;
char error_msg[100];

enum nodetype {
    operator = 1,
    identifier = 2,
    number = 3,
    float_number = 4,
    chr_str = 5
};

struct info {
    int int_val;
    char string_val[500];
    float float_val;
    char char_val;
};

struct var {
    char name[100];
    char type[10];
    struct info info;
    int local;
    int is_const;
    int is_class;
    int arrSize;
    int arr[100];
    int elements;
} symbolTable[100];

struct param {
    char name[200];
    char type[20];
} temp[10];

struct func {
    char name[200];
    char type[20];
    unsigned int arg_number;
    int is_class;
    char retId[20];
    struct param val[30];
    char param_types[200];
} symbolTableFunctions[200];

struct AST {
    char name[50];
    struct AST* st;
    struct AST* dr;
    enum nodetype nodeType;
};

struct AST* buildAST(char* name, struct AST* st, struct AST* dr, enum nodetype type)
{
    struct AST* node = (struct AST*)malloc(sizeof(struct AST));
    strcpy(node->name, strdup(name));
    node->st = st;
    node->dr = dr;
    node->nodeType = type;
    return node;
}

void print_error()
{
    std::cout << "ERROR: " << error_msg << '\n';
}

void initialize()
{
    for(int i = 0; i < 100; i++)
    {
        bzero(&symbolTable[i].name, sizeof(symbolTable[i].name));
        bzero(&symbolTable[i].type, sizeof(symbolTable[i].type));
        symbolTable[i].info.int_val = 0;
        symbolTable[i].info.float_val = 0;
        symbolTable[i].arrSize = 0;
        strcpy(symbolTable[i].info.string_val, "");
        symbolTable[i].info.char_val = '\0';
    }
}

void add_table(int isc, int arrS, char s[], char type[], int intv, float floatv, char *c, char *strv, int clasa, int yylineno)
{
    if(strcmp(type, "type") == 0) 
    {
        int aux = var_count - 1;
        while(strcmp(symbolTable[aux].type, "") == 0 && aux >= 0)
        {
            strcpy(symbolTable[aux].type, s);
            symbolTable[aux].is_const = isc;
            symbolTable[aux].is_class = clasa;
            aux--;
        }
    }
    else
    {
        if(strcmp(type, "var") == 0)
        {
            int esteDejaDeclarata = 0;
            for(int i = 0; i < var_count; i++)
            {
                if(strcmp(symbolTable[i].name, s) == 0)
                {
                    esteDejaDeclarata = 1;
                    break;
                }
            }
            if(esteDejaDeclarata)
            {
                sprintf(error_msg, "Linia %d, var %s a mai fost declarata!",yylineno, s);
                print_error();
                exit(0);
            }
            else
            {
                strcpy(symbolTable[var_count].name, s);
                symbolTable[var_count].info.int_val = intv;
                symbolTable[var_count].info.float_val = floatv;
                symbolTable[var_count].info.char_val = c[0];
                symbolTable[var_count].arrSize = arrS;
                strcpy(symbolTable[var_count].info.string_val, strv);
                var_count++;
            }
        }
    }
}

void Verif(char s[], int yylineno, int vec)
{
    int i;
    int existaVariabila = 0;
    for(i = 0; i < var_count; i++)
    {
        if(!strcmp(symbolTable[i].name, s))
        {
            existaVariabila = 1;
            break;
        }
    }
    if(!existaVariabila)
    {
        sprintf(error_msg, "Linia %d, var %s nu este declarata!",yylineno, s);
        print_error();
        exit(0);
    }
    else
    {
        if(vec > 0 && symbolTable[i].arrSize == 0)
        {
            sprintf(error_msg, "Linia %d, var %s nu este un array!",yylineno, s);
            print_error();
            exit(0);
        }
        else if(vec == 0 && symbolTable[i].arrSize > 0)
        {
            sprintf(error_msg, "Linia %d, var %s este un array!",yylineno, s);
            print_error();
            exit(0);
        }
    }
}

void addInTableFunctions(char tipp[], char s[], char type[], int yylineno, int clasa, char param[])
{
    if(!strcmp(type, "type"))
    {
        for(int i = 0; i < func_count; i++)
            if(!strcmp(symbolTableFunctions[i].name, s))
            {
                sprintf(error_msg, "Linia %d, functia %s nu este definita!",yylineno, s);
                print_error();
                exit(0);
            }
        strcpy(symbolTableFunctions[func_count].name, s);
        strcpy(symbolTableFunctions[func_count].type, tipp);
        symbolTableFunctions[func_count].is_class = clasa;
        symbolTableFunctions[func_count].arg_number = 0;
        bzero(symbolTableFunctions[func_count].param_types, sizeof(symbolTableFunctions[func_count].param_types));
        if(strcmp(param, ""))
        {
            char *p = strtok(param, ",");
            while(p != NULL)
            {
                char aux[100];
                char p1[100];
                strcpy(p1, strchr(p, ' '));
                strncpy(aux, p, strlen(p) - strlen(p1));
                strcat(symbolTableFunctions[func_count].param_types, aux);
                strcat(symbolTableFunctions[func_count].param_types, ",");
                strcpy(symbolTableFunctions[func_count].val[symbolTableFunctions[func_count].arg_number].type, aux);
                strcpy(symbolTableFunctions[func_count].val[symbolTableFunctions[func_count].arg_number].name, p + strlen(aux));
                symbolTableFunctions[func_count].arg_number++;
                p = strtok(NULL, ",");
            }
            symbolTableFunctions[func_count].param_types[strlen(symbolTableFunctions[func_count].param_types) - 1] = '\0';
        }
        func_count++;
    }
}

void VerifFct(char s[], char param[], int yylineno)
{
    int i;
    int existaFunctie = 0;
    for(i = 0; i < func_count; i++)
    {
        if(!strcmp(symbolTableFunctions[i].name, s))
        {
            existaFunctie = 1;
            break;
        }
    }
    if(!existaFunctie)
    {
        sprintf(error_msg, "Linia %d, functia %s nu este definita!",yylineno, s);
        print_error();
        exit(0);
    }
    else
    {
        if(strcmp(param, symbolTableFunctions[i].param_types))
        {
            sprintf(error_msg, "Linia %d, functia %s nu este apelata corect!",yylineno, s);
            print_error();
            exit(0);
        }
    }
}

void Clasa(char s[])
{
    int aux = var_count - 1;
    while(symbolTable[aux].is_class && aux >= 0)
    {
        char auxchar[100];
        bzero(&auxchar, sizeof(auxchar));
        strcpy(auxchar, symbolTable[aux].name);
        strcpy(symbolTable[aux].name, s);
        strcat(symbolTable[aux].name, ".");
        strcat(symbolTable[aux].name, auxchar);
        symbolTable[aux].is_class = 0;
        aux--;
    }
    aux = func_count - 1;
    while(symbolTableFunctions[aux].is_class && aux >= 0)
    {
        char auxchar[100];
        bzero(&auxchar, sizeof(auxchar));
        strcpy(auxchar, symbolTableFunctions[aux].name);
        strcpy(symbolTableFunctions[aux].name, s);
        strcat(symbolTableFunctions[aux].name, ".");
        strcat(symbolTableFunctions[aux].name, auxchar);
        symbolTableFunctions[aux].is_class = 0;
        aux--;   
    }
}

int getIdValue(char s[], int yylineno)
{
    for(int i = 0; i < var_count; i++)
    {
        if(!strcmp(symbolTable[i].name, s))
        {
            if(symbolTable[i].arrSize > 0)
            {
                sprintf(error_msg, "Linia %d, array %s folosit incorect", yylineno, s);
                print_error();
                exit(0);
            }
            return symbolTable[i].info.int_val;
        }
    }
}

char* getIdType(char s[])
{
    for(int i = 0; i < var_count; i++)
        if(!strcmp(symbolTable[i].name, s))
            return symbolTable[i].type;
    return (char *)"no type";
}

int evalAST(struct AST* tree, int yylineno)
{
    if(tree->st == NULL && tree->dr == NULL)
    {
        if(tree->nodeType == identifier)
        {
            char type[10];
            bzero(&type, 10);
            strcpy(type, getIdType(tree->name));
            if(!strcmp(type, "chr"))
            {
                sprintf(error_msg, "Linia %d: var %s este de type char!", yylineno, tree->name);
                print_error();
                exit(0);
            }
            else
            if(!strcmp(type, "bool"))
            {
                sprintf(error_msg, "Linia %d: var %s este de type bool!", yylineno, tree->name);
                print_error();
                exit(0);
            }
            else
            if(!strcmp(type, "str"))
            {
                sprintf(error_msg, "Linia %d: var %s este de type string!", yylineno, tree->name);
                print_error();
                exit(0);
            }
            else
            {
                if(!strcmp(type, "i32"))
                    return getIdValue(tree->name, yylineno);
            }
        }
        else
        {
            if(tree->nodeType == number)
                return atoi(tree->name);
            return 0;
        }
    }
    else
    {
        int val_stanga, val_dreapta;
        val_stanga = evalAST(tree->st, yylineno);
        val_dreapta = evalAST(tree->dr, yylineno);
        if(!strcmp(tree->name, "+")) {return val_stanga + val_dreapta;}
        if(!strcmp(tree->name, "-")) {return val_stanga - val_dreapta;}
        if(!strcmp(tree->name, "*")) {return val_stanga * val_dreapta;}
        if(!strcmp(tree->name, "/")) 
        {
            if(val_dreapta) {return val_stanga / val_dreapta;}
            else
            {
                sprintf(error_msg, "Linia %d, impartirea la 0 nu se poate efectua!", yylineno);
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
            return (char*)"f64";
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
            if(tree->nodeType == identifier)
            {
                char type[10];
                bzero(&type, 10);
                strcpy(type, getIdType(tree->name));
                if(!strcmp(type, "i32"))
                    return (char*)"i32";
                if(!strcmp(type, "bool"))
                    return (char*)"bool";
                if(!strcmp(type, "f64"))
                    return (char*)"f64";
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

int getArrVal(char name[], int id, int yylineno)
{
    for(int i = 0; i < var_count; i++)
    {
        if(!strcmp(symbolTable[i].name, name))
        {
            if(symbolTable[i].arrSize >= id)
                return symbolTable[i].arr[id];
            else
            {
                sprintf(error_msg, "Linia %d, pozitie depasita!", yylineno);
                print_error();
                exit(0);
            }
        }     
    }
    sprintf(error_msg, "Linia %d, array inexistent!", yylineno);
    print_error();
    exit(0);
}

void actualizareTabel(char name[], char type[], int value, int yylineno, float fvalue, char svalue[])
{
    for(int i = 0; i < var_count; i++)
    {
        if(!strcmp(symbolTable[i].name, name))
        {
            if(strcmp(symbolTable[i].type, type))
            {
                sprintf(error_msg, "Linia %d, type de date diferit!", yylineno);
                print_error();
                exit(0);
            }
            if(!strcmp(type, "i32") || !strcmp(type, "bool"))
                symbolTable[i].info.int_val = value;
            else
                if(!strcmp(type, "f64"))
                    symbolTable[i].info.float_val = fvalue;
                else
                    if(!strcmp(type, "str"))
                        strcpy(symbolTable[i].info.string_val, svalue);
                    else
                        if(!strcmp(type, "chr"))
                            symbolTable[i].info.char_val = svalue[1];
            break;
        }
    }
}

char* ConstruiescRasp(char sir1[], char sir2[], char inter[3])
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
    for(int i = 0; i < func_count; i++)
        if(!strcmp(symbolTableFunctions[i].name, fct))
            return symbolTableFunctions[i].type;
}

void printVars(int fd)
{
    char sp[2], inf[510];
    strcpy(sp, " ");
    for(int i = 0; i < var_count; i++)
    {
        write(fd, symbolTable[i].name, strlen(symbolTable[i].name));
        write(fd, sp, strlen(sp));
        write(fd, symbolTable[i].type, strlen(symbolTable[i].type));
        write(fd, sp, strlen(sp));
        if(!strcmp(symbolTable[i].type, "i32")) {snprintf(inf,100,"%d", symbolTable[i].info.int_val);write(fd, inf, strlen(inf));}
        else if(!strcmp(symbolTable[i].type, "str")) {snprintf(inf,500,"%s", symbolTable[i].info.string_val);write(fd, inf, strlen(inf));}
        else if(!strcmp(symbolTable[i].type, "f64")) {snprintf(inf,500,"%f", symbolTable[i].info.float_val);write(fd, inf, strlen(inf));}
        else if(!strcmp(symbolTable[i].type, "chr")) {snprintf(inf,500,"%c", symbolTable[i].info.char_val);write(fd, inf, strlen(inf));}
        else if(!strcmp(symbolTable[i].type, "bool")) {snprintf(inf,500,"%d", symbolTable[i].info.int_val);write(fd, inf, strlen(inf));}
        write(fd, "\n", strlen("\n"));
    }
}

void printFunctions(int fd)
{
    char sp[2], inf[510];
    strcpy(sp, " ");
    for(int i = 0; i < func_count; i++)
    {
        write(fd, symbolTableFunctions[i].type, strlen(symbolTableFunctions[i].type));
        write(fd, sp, strlen(sp));
        write(fd, symbolTableFunctions[i].name, strlen(symbolTableFunctions[i].name));
        write(fd, sp, strlen(sp));
        write(fd, "(", strlen("("));
        int j = 0;
        for(j=0; j<symbolTableFunctions[i].arg_number - 1; j++)
        {
            write(fd, symbolTableFunctions[i].val[j].type, strlen(symbolTableFunctions[i].val[j].type));
            write(fd, symbolTableFunctions[i].val[j].name, strlen(symbolTableFunctions[i].val[j].name));
            write(fd, ",", strlen(","));
            write(fd, sp, strlen(sp));
        }
        if(symbolTableFunctions[i].arg_number!=0)
        {
            write(fd, symbolTableFunctions[i].val[symbolTableFunctions[i].arg_number-1].type, strlen(symbolTableFunctions[i].val[symbolTableFunctions[i].arg_number-1].type));
            write(fd, symbolTableFunctions[i].val[symbolTableFunctions[i].arg_number-1].name, strlen(symbolTableFunctions[i].val[symbolTableFunctions[i].arg_number-1].name));
        }
        write(fd, ")", strlen(")"));
        write(fd, "\n", strlen("\n"));
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

%start program

%left OR 
%left AND
%left NOT_EQ EQ
%left LESS_EQ GREATER_EQ '<' '>'
%left '-' '+'
%left '/' '*'
%%

program: sectiunea1 rest1 {printf("program corect sintactic\n");}
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

declaratieVariabila : TYPE lista_id { add_table(0, 0, $1, "type", 0, 0, "", "", 0, yylineno); }
                    | CONSTANT TYPE lista_id {add_table(1, 0, $1, "type", 0, 0, "", "", 0, yylineno);}
                    ;

declaratieVariabilaClasa : TYPE lista_id { add_table(0, 0, $1, "type", 0, 0, "", "", 1, yylineno); }
                         | CONSTANT TYPE lista_id {add_table(1, 0, $1, "type", 0, 0, "", "", 1, yylineno);}
                         ;

declaratieFunctie : TYPE ID '(' lista_param ')' BEGIN_FN list END_FN { addInTableFunctions($1, $2, "type", yylineno, 0, $4);}
                  | TYPE ID '(' ')' BEGIN_FN list END_FN { addInTableFunctions($1, $2, "type", yylineno, 0, "");}
                  | TYPE ID '(' lista_param ')' BEGIN_FN list RETURN e ';' END_FN { int val = evalAST($9, yylineno); addInTableFunctions($1, $2, "type", yylineno, 0, $4);}
                  | TYPE ID '(' ')' BEGIN_FN list RETURN e ';' END_FN { int val = evalAST($8, yylineno); addInTableFunctions($1, $2, "type", yylineno, 0, "");}
                  ;

declaratieFunctieClasa : TYPE ID '(' lista_param ')' { addInTableFunctions($1, $2, "type", yylineno, 1, $4);}
                       | TYPE ID '(' ')' { addInTableFunctions($1, $2, "type", yylineno, 1, "");}
                       ;

lista_param : param {$$ = $1;} 
            | param ',' lista_param { $$ = ConstruiescRasp($1, $3, ",");}
            ;
            
param : TYPE ID {
                $$ = ConstruiescRasp($1, $2, " ");
               }
      ; 

clasa : BEGIN_CLASS ID interior_clasa END_CLASS {Clasa($2);}
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

lista_id : ID {add_table(0, 0, $1, "var", 0, 0, "", "", 0, yylineno);}
         | ID '[' NR ']' { add_table(0, $3, $1, "var", 0, 0, "", "", 0, yylineno);}
         | ID ',' lista_id { add_table(0, 0, $1, "var", 0, 0, "", "", 0, yylineno);}
         | ID '[' NR ']' ',' lista_id { add_table(0, $3, $1, "var", 0, 0, "", "", 0, yylineno);}
         | ID ASSIGN e { int val = Eval($3, yylineno); add_table(0, 0, $1, "var", val, 0, "", "", 0, yylineno);}
         | ID ASSIGN e ',' lista_id { int val = Eval($3, yylineno); add_table(0, 0, $1, "var", 0, 0, "", "", 0, yylineno);}
         | ID ASSIGN NR_FLOAT { add_table(0, 0, $1, "var", 0, $3, "", "", 0, yylineno);}
         | ID ASSIGN NR_FLOAT ',' lista_id { add_table(0, 0, $1, "var", 0, $3, "", "", 0, yylineno);}
         | ID ASSIGN STRING { add_table(0, 0, $1, "var", 0, 0, "", $3, 0, yylineno);}
         | ID ASSIGN STRING ',' lista_id { add_table(0, 0, $1, "var", 0, 0, "", $3, 0, yylineno);}
         | ID ASSIGN CHAR { add_table(0, 0, $1, "var", 0, 0, $3, "", 0, yylineno);}
         | ID ASSIGN CHAR ',' lista_id { add_table(0, 0, $1, "var", 0, 0, $3, "", 0, yylineno);}
         ;
      
/* bloc */
bloc : BEGIN_MAIN list BEGIN_MAIN
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
                            Verif($1, yylineno, 0);
                            if(strcmp(getIdType($1), "i32"))
                            {
                                sprintf(error_msg, "Linia %d, type de date diferit", yylineno);
                                print_error();
                                exit(0);
                            }
                            int val = Eval($3, yylineno);
                            actualizareTabel($1, "i32", val, yylineno, 0, "");
                        }
         | ID '(' lista_apel ')' {VerifFct($1, $3, yylineno);}
         | TYPEOF '(' pseudo_e ')' {printf("%s\n", $3);}
         | EVAL '(' e ')' {printf("%d\n", Eval($3, yylineno));}
         | ID '.' ID ASSIGN e { 
                                snprintf(buff,100,"%s.%s", $1, $3);
                                Verif(buff, yylineno, 0);
                                if(strcmp(getIdType($1), "i32"))
                                {
                                    sprintf(error_msg, "Linia %d, type de date diferit", yylineno);
                                    print_error();
                                    exit(0);
                                }
                                int val = Eval($5, yylineno);
                                actualizareTabel(buff, "i32", val, yylineno, 0, "");
                              }
         | ID ASSIGN NR_FLOAT {
                                Verif($1, yylineno, 0);
                                if(strcmp(getIdType($1), "f64"))
                                {
                                    sprintf(error_msg, "Linia %d, type de date diferit", yylineno);
                                    print_error();
                                    exit(0);
                                }
                                actualizareTabel($1, "f64", 0, yylineno, $3, "");
                              }
         | ID '.' ID '(' lista_apel ')' {
                                            snprintf(buff,100,"%s.%s", $1, $3);
                                            VerifFct(buff, $5, yylineno);

                                        }
         | ID '[' NR ']' ASSIGN e { Verif($1, yylineno, $3);}
         ;

cond : '(' cond ')' {$$ = $2;}
     | cond AND cond { int rez1=$1; int rez2=$3; 
                       $$=(rez1 && rez2);
                     }
     | cond OR cond { int rez1=$1; int rez2=$3;
                      $$=(rez1 || rez2);
                    }
     | e opr e { 
                int rez1=evalAST($1, yylineno); int rez2=evalAST($3, yylineno);
                if (strcmp($2, "<=")) $$=(rez1 <= rez2);
                if (strcmp($2, ">=")) $$=(rez1 >= rez2);
                if (strcmp($2, "!=")) $$=(rez1 != rez2);
                if (strcmp($2, "==")) $$=(rez1 == rez2);
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

e : e '+' e { $$ = buildAST("+", $1, $3, operator); }
  | e '-' e { $$ = buildAST("-", $1, $3, operator); }
  | e '*' e { $$ = buildAST("*", $1, $3, operator); }
  | e '/' e { $$ = buildAST("/", $1, $3, operator); }
  | '(' e ')' { $$ = $2; }
  | ID { Verif($1, yylineno, 0); $$ = buildAST($1, NULL, NULL, identifier);}
  | NR { char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", $1); $$ = buildAST(nr, NULL, NULL, number); }
  | ID '[' NR ']' {Verif($1, yylineno, 1); int val = getArrVal($1, $3, yylineno); char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", val); $$ = buildAST(nr, NULL, NULL, number); }
  | ID '(' lista_apel ')' { VerifFct($1, $3, yylineno);
                            $$ = buildAST("0", NULL, NULL, number);
                          }
  | ID '.' ID { snprintf(buff,100,"%s.%s", $1, $3); Verif(buff, yylineno, 0);  $$ = buildAST($1, NULL, NULL, identifier);}
  | ID '.' ID '(' lista_apel ')' { snprintf(buff,100,"%s.%s", $1, $3); VerifFct(buff, $3, yylineno); $$ = buildAST("0", NULL, NULL, number);}
  ;

pseudo_e : pseudo_e '+' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_msg, "Linia %d, type de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '-' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_msg, "Linia %d, type de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '/' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_msg, "Linia %d, type de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '*' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(error_msg, "Linia %d, type de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | '(' pseudo_e ')' { $$ = $2; }
         | ID {Verif($1, yylineno, 0); $$ = getIdType($1);}
         | NR {$$ = "i32";}
         | NR_FLOAT {$$ = "f64";}
         | ID '[' NR ']' {Verif($1, yylineno, 1); $$ = getIdType($1);}
         | ID '(' lista_apel ')' { VerifFct($1, $3, yylineno); $$ = FctRetType($1);}
         | ID '.' ID {snprintf(buff,100,"%s.%s", $1, $3); Verif($1, yylineno, 1); $$ = getIdType(buff);}
         | ID '.' ID '(' lista_apel ')' { snprintf(buff,100,"%s.%s", $1, $3); VerifFct(buff, $5, yylineno); $$ = FctRetType(buff);}
         ;

lista_apel : e {
                struct AST* tree = $1;
                if(tree->st == NULL && tree->dr == NULL)
                {
                    if(tree->nodeType == identifier)
                        $$ = getIdType(tree->name);
                    else
                        $$ = "i32";
                }
                else
                    $$ = "i32";
            }
           | lista_apel ',' e {
                    struct AST* tree = $3;
                    char type[20];
                        if(tree->st == NULL && tree->dr == NULL)
                        {
                            if(tree->nodeType == identifier)
                                strcpy(type, getIdType(tree->name));
                            else
                                strcpy(type, "i32");
                        }
                        else
                            strcpy(type, "i32");
                        strcpy(buff, $1);
                        strcat(buff, ",");
                        strcat(buff, type);
                        $$ = buff;
                        // printf("%s.\n", type);
                }
           | NR_FLOAT {$$ = "f64";}
           | lista_apel ',' NR_FLOAT { snprintf(buff,100,"%s,float",$1); $$ = buff;}
           | CHAR {$$ = "chr";}
           | lista_apel ',' CHAR {snprintf(buff,100,"%s,char",$1); $$ = buff;}
           | STRING {$$ = "str";}
           | lista_apel ',' STRING {snprintf(buff,100,"%s,string",$1); $$ = buff;}
           ;

%%

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