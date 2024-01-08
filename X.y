%{
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

declaratieVariabila : TYPE lista_id { addInTable(0, 0, $1, "tip", 0, 0, "", "", 0, yylineno); }
                    | CONSTANT TYPE lista_id {addInTable(1, 0, $1, "tip", 0, 0, "", "", 0, yylineno);}
                    ;

declaratieVariabilaClasa : TYPE lista_id { addInTable(0, 0, $1, "tip", 0, 0, "", "", 1, yylineno); }
                         | CONSTANT TYPE lista_id {addInTable(1, 0, $1, "tip", 0, 0, "", "", 1, yylineno);}
                         ;

declaratieFunctie : TYPE ID '(' lista_param ')' BEGIN_FN list END_FN { addInTableFunctions($1, $2, "tip", yylineno, 0, $4);}
                  | TYPE ID '(' ')' BEGIN_FN list END_FN { addInTableFunctions($1, $2, "tip", yylineno, 0, "");}
                  | TYPE ID '(' lista_param ')' BEGIN_FN list RETURN e ';' END_FN { int val = evalAST($9, yylineno); addInTableFunctions($1, $2, "tip", yylineno, 0, $4);}
                  | TYPE ID '(' ')' BEGIN_FN list RETURN e ';' END_FN { int val = evalAST($8, yylineno); addInTableFunctions($1, $2, "tip", yylineno, 0, "");}
                  ;

declaratieFunctieClasa : TYPE ID '(' lista_param ')' { addInTableFunctions($1, $2, "tip", yylineno, 1, $4);}
                       | TYPE ID '(' ')' { addInTableFunctions($1, $2, "tip", yylineno, 1, "");}
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

lista_id : ID {addInTable(0, 0, $1, "variabila", 0, 0, "", "", 0, yylineno);}
         | ID '[' NR ']' { addInTable(0, $3, $1, "variabila", 0, 0, "", "", 0, yylineno);}
         | ID ',' lista_id { addInTable(0, 0, $1, "variabila", 0, 0, "", "", 0, yylineno);}
         | ID '[' NR ']' ',' lista_id { addInTable(0, $3, $1, "variabila", 0, 0, "", "", 0, yylineno);}
         | ID ASSIGN e { int val = Eval($3, yylineno); addInTable(0, 0, $1, "variabila", val, 0, "", "", 0, yylineno);}
         | ID ASSIGN e ',' lista_id { int val = Eval($3, yylineno); addInTable(0, 0, $1, "variabila", 0, 0, "", "", 0, yylineno);}
         | ID ASSIGN NR_FLOAT { addInTable(0, 0, $1, "variabila", 0, $3, "", "", 0, yylineno);}
         | ID ASSIGN NR_FLOAT ',' lista_id { addInTable(0, 0, $1, "variabila", 0, $3, "", "", 0, yylineno);}
         | ID ASSIGN STRING { addInTable(0, 0, $1, "variabila", 0, 0, "", $3, 0, yylineno);}
         | ID ASSIGN STRING ',' lista_id { addInTable(0, 0, $1, "variabila", 0, 0, "", $3, 0, yylineno);}
         | ID ASSIGN CHAR { addInTable(0, 0, $1, "variabila", 0, 0, $3, "", 0, yylineno);}
         | ID ASSIGN CHAR ',' lista_id { addInTable(0, 0, $1, "variabila", 0, 0, $3, "", 0, yylineno);}
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
                            Verif($1, yylineno, 0);
                            if(strcmp(getIdType($1), "i32"))
                            {
                                sprintf(errMsg, "Linia %d, tip de date diferit", yylineno);
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
                                    sprintf(errMsg, "Linia %d, tip de date diferit", yylineno);
                                    print_error();
                                    exit(0);
                                }
                                int val = Eval($5, yylineno);
                                actualizareTabel(buff, "i32", val, yylineno, 0, "");
                              }
         | ID ASSIGN NR_FLOAT {
                                Verif($1, yylineno, 0);
                                if(strcmp(getIdType($1), "f32"))
                                {
                                    sprintf(errMsg, "Linia %d, tip de date diferit", yylineno);
                                    print_error();
                                    exit(0);
                                }
                                actualizareTabel($1, "f32", 0, yylineno, $3, "");
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

e : e '+' e { $$ = buildAST("+", $1, $3, OPERATOR); }
  | e '-' e { $$ = buildAST("-", $1, $3, OPERATOR); }
  | e '*' e { $$ = buildAST("*", $1, $3, OPERATOR); }
  | e '/' e { $$ = buildAST("/", $1, $3, OPERATOR); }
  | '(' e ')' { $$ = $2; }
  | ID { Verif($1, yylineno, 0); $$ = buildAST($1, NULL, NULL, IDENTIFICATOR);}
  | NR { char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", $1); $$ = buildAST(nr, NULL, NULL, NUMAR); }
  | ID '[' NR ']' {Verif($1, yylineno, 1); int val = getArrVal($1, $3, yylineno); char nr[100]; bzero(&nr, 100); sprintf(nr, "%d", val); $$ = buildAST(nr, NULL, NULL, NUMAR); }
  | ID '(' lista_apel ')' { VerifFct($1, $3, yylineno);
                            $$ = buildAST("0", NULL, NULL, NUMAR);
                          }
  | ID '.' ID { snprintf(buff,100,"%s.%s", $1, $3); Verif(buff, yylineno, 0);  $$ = buildAST($1, NULL, NULL, IDENTIFICATOR);}
  | ID '.' ID '(' lista_apel ')' { snprintf(buff,100,"%s.%s", $1, $3); VerifFct(buff, $3, yylineno); $$ = buildAST("0", NULL, NULL, NUMAR);}
  ;

pseudo_e : pseudo_e '+' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(errMsg, "Linia %d, tip de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '-' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(errMsg, "Linia %d, tip de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '/' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(errMsg, "Linia %d, tip de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | pseudo_e '*' pseudo_e {
                                    if(strcmp($1, $3))
                                    {
                                        sprintf(errMsg, "Linia %d, tip de date diferit!", yylineno);
                                        print_error();
                                        exit(0);
                                    }
                                    $$ = $1;
                                 }
         | '(' pseudo_e ')' { $$ = $2; }
         | ID {Verif($1, yylineno, 0); $$ = getIdType($1);}
         | NR {$$ = "i32";}
         | NR_FLOAT {$$ = "f32";}
         | ID '[' NR ']' {Verif($1, yylineno, 1); $$ = getIdType($1);}
         | ID '(' lista_apel ')' { VerifFct($1, $3, yylineno); $$ = FctRetType($1);}
         | ID '.' ID {snprintf(buff,100,"%s.%s", $1, $3); Verif($1, yylineno, 1); $$ = getIdType(buff);}
         | ID '.' ID '(' lista_apel ')' { snprintf(buff,100,"%s.%s", $1, $3); VerifFct(buff, $5, yylineno); $$ = FctRetType(buff);}
         ;

lista_apel : e {
                struct AST* tree = $1;
                if(tree->st == NULL && tree->dr == NULL)
                {
                    if(tree->nodeType == IDENTIFICATOR)
                        $$ = getIdType(tree->nume);
                    else
                        $$ = "i32";
                }
                else
                    $$ = "i32";
            }
           | lista_apel ',' e {
                    struct AST* tree = $3;
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
                        strcpy(buff, $1);
                        strcat(buff, ",");
                        strcat(buff, tip);
                        $$ = buff;
                        // printf("%s.\n", tip);
                }
           | NR_FLOAT {$$ = "f32";}
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
