/*	Definition section */
%{
    #include "common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1;

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    void yyerror (char const *s)
    {
        printf("error:%d: %s\n", yylineno, s);
    }

    struct SymbolTable {
        int index;
        char name[10];
        char type[10];
        int address;
        int lineno;
        char elementType[10];
    };

    struct SymbolTable MySymbolTable[100][100];
    int SymbolTable_current = 0, SymbolTable_current_count[100], uniqueAddress = 0;
    
    struct BinaryOpStack {
        int precedence;
        char binary_op[10];
    };
    struct BinaryOpStack binary_op_stack[50];
    int binary_op_stack_count = -1,precedence_paren = 0;

    char operand_type[100][10];
    int operand_type_count = -1;

    char print_type[10];
    char conversion_type[10];
    void dump_BinaryOpStack(int nextprecedence,char binary_op[],bool foreceDumps) {
        while(binary_op_stack_count >= 0 && (foreceDumps || binary_op_stack[binary_op_stack_count].precedence >= nextprecedence)) {
            if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"ADD")==0 || strcmp(binary_op_stack[binary_op_stack_count].binary_op,"SUB")==0) {
                if(strcmp(operand_type[operand_type_count],operand_type[operand_type_count-1]) != 0)
                    printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno,binary_op_stack[binary_op_stack_count].binary_op,operand_type[operand_type_count-1],operand_type[operand_type_count]);
            }
            if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"REM")==0) {
                if(strcmp(operand_type[operand_type_count],"float") == 0)
                    printf("error:%d: invalid operation: (operator %s not defined on %s)\n",yylineno,binary_op_stack[binary_op_stack_count].binary_op,operand_type[operand_type_count]);
                else if(strcmp(operand_type[operand_type_count-1],"float") == 0)
                    printf("error:%d: invalid operation: (operator %s not defined on %s)\n",yylineno,binary_op_stack[binary_op_stack_count].binary_op,operand_type[operand_type_count-1]);
            }
            if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"AND")==0 || strcmp(binary_op_stack[binary_op_stack_count].binary_op,"OR")==0) {
                if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"int") == 0)
                    printf("error:%d: invalid operation: (operator %s not defined on %s)\n",yylineno,binary_op_stack[binary_op_stack_count].binary_op,binary_op_stack[binary_op_stack_count].binary_op);
                else if(strcmp(operand_type[operand_type_count-1],"int") == 0)
                    printf("error:%d: invalid operation: (operator %s not defined on %s)\n",yylineno,binary_op_stack[binary_op_stack_count].binary_op,operand_type[operand_type_count-1]);
            }          
            printf("%s\n",binary_op_stack[binary_op_stack_count].binary_op);
            if(binary_op_stack_count == 0) {
                if(0 < binary_op_stack[binary_op_stack_count].precedence%7 && binary_op_stack[binary_op_stack_count].precedence%7 <= 3)
                    strcpy(print_type,"bool");
                else {
                    if(strcmp(print_type,"float") == 0)
                        strcpy(print_type,"float");
                    else
                        strcpy(print_type,"int");
                }
            }
            binary_op_stack_count--;
        }
        if(!foreceDumps) 
        {
            binary_op_stack_count++;
            strcpy(binary_op_stack[binary_op_stack_count].binary_op,binary_op); 
            binary_op_stack[binary_op_stack_count].precedence = nextprecedence; 
        }
    }


    /* Symbol table function - you can add new function if needed. */
    static void create_symbol() 
    {   
        SymbolTable_current++;
    }
    static void insert_symbol(int index,char name[],char type[],int address, int lineno, char elementType[])
    {
        bool error = false;
        for(int i = 0; i < SymbolTable_current_count[SymbolTable_current]; i++) {
            if(strcmp(MySymbolTable[SymbolTable_current][i].name,name) == 0) {
                error = true;
                printf("error:%d: %s redeclared in this block. previous declaration at line %d\n",yylineno,name,MySymbolTable[SymbolTable_current][i].lineno);
                break;
            }           
        }
        if(!error) {
            MySymbolTable[SymbolTable_current][SymbolTable_current_count[SymbolTable_current]].index = index;
            strcpy(MySymbolTable[SymbolTable_current][SymbolTable_current_count[SymbolTable_current]].name, name);
            strcpy(MySymbolTable[SymbolTable_current][SymbolTable_current_count[SymbolTable_current]].type, type);
            MySymbolTable[SymbolTable_current][SymbolTable_current_count[SymbolTable_current]].address = address;
            MySymbolTable[SymbolTable_current][SymbolTable_current_count[SymbolTable_current]].lineno = lineno;
            strcpy(MySymbolTable[SymbolTable_current][SymbolTable_current_count[SymbolTable_current]].elementType, elementType);
            printf("> Insert {%s} into symbol table (scope level: %d)\n",name,SymbolTable_current);
            SymbolTable_current_count[SymbolTable_current]++;
            uniqueAddress++;
        }
    }
    static void dump_symbol()
    {
        printf("> Dump symbol table (scope level: %d)\n", SymbolTable_current);
        printf("%-10s%-10s%-10s%-10s%-10s%s\n", "Index", "Name", "Type", "Address", "Lineno",
        "Element type");
        for(int i = 0; i < SymbolTable_current_count[SymbolTable_current]; i++)
            printf("%-10d%-10s%-10s%-10d%-10d%s\n",MySymbolTable[SymbolTable_current][i].index, MySymbolTable[SymbolTable_current][i].name,MySymbolTable[SymbolTable_current][i].type,MySymbolTable[SymbolTable_current][i].address, MySymbolTable[SymbolTable_current][i].lineno,MySymbolTable[SymbolTable_current][i].elementType);
        SymbolTable_current_count[SymbolTable_current] = 0;
        SymbolTable_current--;
    }
%}

%error-verbose

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */
%union {
    int i_val;
    float f_val;
    char *s_val;
    /* ... */
}

/* Token without return */
%token ADD SUB MUL QUO REM INC DEC GTR LSS GEQ LEQ EQL NEQ
%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN QUO_ASSIGN REM_ASSIGN
%token AND OR NOT LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK SEMICOLON 
%token PRINT IF ELSE FOR WHILE

/* Token with return, which need to sepcify type */
%token <i_val> INT_LIT
%token <f_val> FLOAT_LIT
%token <s_val> STRING_LIT IDENT INT FLOAT STRING BOOL_LIT BOOL

/* Nonterminal with return, which need to sepcify type */
%type <s_val> Type TypeName Expression binary_op add_op mul_op PrimaryExpr ConversionExpr
%type <s_val> unary_op  cmp_op UnaryExpr assign_op Operand Literal IndexExpr

/* Yacc will start at this nonterminal */
%start Program

/* Grammar section */
%%

Program: 
      StatementList
;

StatementList:
      Statement StatementList
    |
;

Statement:
      DeclarationStmt { strcpy(print_type,"int"); operand_type_count = -1; }
    | AssignmentStmt { strcpy(print_type,"int"); operand_type_count = -1; }
    | ArithmeticStmt { strcpy(print_type,"int"); operand_type_count = -1; }
    | IncDecStmt { strcpy(print_type,"int"); operand_type_count = -1; }
    | Block { strcpy(print_type,"int"); operand_type_count = -1; }
    | IfStmt { strcpy(print_type,"int"); operand_type_count = -1; }
    | WhileStmt { strcpy(print_type,"int"); operand_type_count = -1; }
    | ForStmt { strcpy(print_type,"int"); operand_type_count = -1; }
    | PrintStmt { strcpy(print_type,"int"); operand_type_count = -1; }
;

DeclarationStmt:
      Type IDENT SEMICOLON { 
            insert_symbol(SymbolTable_current_count[SymbolTable_current],$2,$1,uniqueAddress,yylineno,"-");
    }
    | Type IDENT LBRACK Expression RBRACK SEMICOLON {
            insert_symbol(SymbolTable_current_count[SymbolTable_current],$2,"array",uniqueAddress,yylineno,$1);
    }
    | Type IDENT assign_op Expression SEMICOLON { 
            insert_symbol(SymbolTable_current_count[SymbolTable_current],$2,$1,uniqueAddress,yylineno,"-");
    } 
;
AssignmentStmt:
      AssignmentExpr SEMICOLON
;
AssignmentExpr:
      Expression assign_op Expression { 
            if(strcmp($1,"INT_LIT") == 0)
                printf("error:%d: cannot assign to int\n",yylineno);
            else if(strcmp($1,"FLOAT_LIT") == 0)
            printf("error:%d: cannot assign to float\n",yylineno);
            else if(strcmp($1,"null")!=0 && strcmp($3,"null")!=0) {
                if(strcmp($1,"INT_LIT") == 0)
                    $1 = "int";
                if(strcmp($3,"INT_LIT") == 0)
                    $3 = "int";
                if(strcmp($1,"FLOAT_LIT") == 0)
                    $1 = "float";
                if(strcmp($3,"FLOAT_LIT") == 0)
                    $3 = "float";
                if(strcmp($1,$3) != 0)
                    printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno,$2,$1,$3);
            }
            printf("%s\n",$2);            
    }
;
assign_op:
      ASSIGN { $$ = "ASSIGN"; }
    | ADD_ASSIGN { $$ = "ADD_ASSIGN"; }
    | SUB_ASSIGN { $$ = "SUB_ASSIGN"; }
    | MUL_ASSIGN { $$ = "MUL_ASSIGN"; }
    | QUO_ASSIGN { $$ = "QUO_ASSIGN"; }
    | REM_ASSIGN { $$ = "REM_ASSIGN"; }
;
ArithmeticStmt:
    ArithmeticExpr SEMICOLON
;
ArithmeticExpr:
    Expression { }
;
IncDecStmt:
      IncDecExpr SEMICOLON
;
IncDecExpr:
      Expression INC { printf("INC\n"); }
    | Expression DEC { printf("DEC\n"); }
;
IfStmt:
      IF Condition Block
    | IF Condition Block ELSE IfStmt
    | IF Condition Block ELSE Block
;
Condition:
      Expression { 
            if(strcmp(print_type,"bool") != 0)
                printf("error:%d: non-bool (type %s) used as for condition\n",yylineno+1,print_type);
            strcpy(print_type,"int"); 
    }
;
WhileStmt:
      WHILE LPAREN Condition RPAREN Block
;
ForStmt:
      FOR LPAREN ForClause RPAREN Block
;
ForClause:
      InitStmt SEMICOLON Condition SEMICOLON PostStmt
;
InitStmt:
      SimpleExpr
;
PostStmt:
      SimpleExpr 
;
SimpleExpr:
      AssignmentExpr
    | Expression
    | IncDecExpr
;
Block:
      INCSYBOLTABLECURRENTBRACE StatementList RBRACE { dump_symbol(); }
;
INCSYBOLTABLECURRENTBRACE:
      LBRACE { create_symbol(); }
;
PrintStmt:
      PRINT LPAREN Expression RPAREN SEMICOLON { printf("PRINT %s\n",print_type); }
;

Expression:
      UnaryExpr { $$ = $1; }
    | Expression binary_op Expression { 
            dump_BinaryOpStack(0,"forcedump",true); 
            $$ = $1;
    } 
;

UnaryExpr:
      PrimaryExpr { $$ = $1; }
    | unary_op UnaryExpr { printf("%s\n",$1); $$ = $2; }
;

binary_op:
      OR { dump_BinaryOpStack(precedence_paren*7+1, "OR",false); $$ = "OR"; }
    | AND { dump_BinaryOpStack(precedence_paren*7+2, "AND",false); $$ = "AND"; }
    | cmp_op { $$ = $1; }
    | add_op { $$ = $1; }
    | mul_op { $$ = $1; }
;

cmp_op:
      EQL { dump_BinaryOpStack(precedence_paren*7+3, "EQL",false); $$ = "EQL"; }
    | NEQ { dump_BinaryOpStack(precedence_paren*7+3, "NEQ",false); $$ = "NEQ"; }
    | LSS { dump_BinaryOpStack(precedence_paren*7+3, "LSS",false); $$ = "LSS"; }
    | LEQ { dump_BinaryOpStack(precedence_paren*7+3, "LEQ",false); $$ = "LEQ"; }
    | GTR { dump_BinaryOpStack(precedence_paren*7+3, "GTR",false); $$ = "GTR"; }
    | GEQ { dump_BinaryOpStack(precedence_paren*7+3, "GEQ",false); $$ = "GEQ"; }
;
add_op:
      ADD { dump_BinaryOpStack(precedence_paren*7+4, "ADD",false); $$ = "ADD"; }
    | SUB { dump_BinaryOpStack(precedence_paren*7+4, "SUB",false); $$ = "SUB"; }
;
mul_op:
      MUL { dump_BinaryOpStack(precedence_paren*7+5, "MUL",false); $$ = "MUL"; }
    | QUO { dump_BinaryOpStack(precedence_paren*7+5, "QUO",false); $$ = "QUO"; }
    | REM { dump_BinaryOpStack(precedence_paren*7+5, "REM",false); $$ = "REM"; }
;
unary_op:
      ADD { $$ = "POS"; }
    | SUB { $$ = "NEG"; }
    | NOT { $$ = "NOT"; }
;

PrimaryExpr:
      Operand { $$ = $1; }
    | IndexExpr { $$ = $1; }
    | ConversionExpr  { $$ = $1; }
;
Operand:
      Literal { $$ = $1; }
    | IDENT { 
            $$ = "null";
            int tmpaddress = 0;
            bool find = false;
            for(int i = SymbolTable_current; i >= 0 ; i--) {
                for(int j = 0; j < SymbolTable_current_count[i]; j++) {
                    if(strcmp(MySymbolTable[i][j].name,$1) == 0) {
                        find = true;
                        tmpaddress = MySymbolTable[i][j].address;
                        if(strcmp(MySymbolTable[i][j].type,"array")==0)
                            $$ = MySymbolTable[i][j].elementType;
                        else
                            $$ = MySymbolTable[i][j].type;
                        if((strcmp(MySymbolTable[i][j].type,"int")==0) || (strcmp(MySymbolTable[i][j].elementType,"int") == 0)) {
                            strcpy(conversion_type,"int");
                            operand_type_count++;
                            strcpy(operand_type[operand_type_count], "int"); 
                        }
                        if((strcmp(MySymbolTable[i][j].type,"float")==0) || (strcmp(MySymbolTable[i][j].elementType,"float") == 0)) {
                            strcpy(print_type,"float");
                            strcpy(conversion_type,"float");
                            operand_type_count++;
                            strcpy(operand_type[operand_type_count], "float"); 
                        }
                        if((strcmp(MySymbolTable[i][j].type,"string")==0) || (strcmp(MySymbolTable[i][j].elementType,"string") == 0)) {
                            strcpy(print_type,"string");
                            operand_type_count++;
                            strcpy(operand_type[operand_type_count], "string"); 
                        }
                        if((strcmp(MySymbolTable[i][j].type,"bool")==0) || (strcmp(MySymbolTable[i][j].elementType,"bool") == 0)) {
                            strcpy(print_type,"bool");
                            operand_type_count++;
                            strcpy(operand_type[operand_type_count], "bool"); 
                        }
                        break;
                    }
                }
                if(find)
                    break;
            }
            if(find)
                printf("IDENT (name=%s, address=%d)\n",$1,tmpaddress); 
            else
                printf("error:%d: undefined: %s\n",yylineno,$1); 
    }
    | INCPRECEDENCELPAREN Expression RPAREN { precedence_paren--; $$ = $2; }
;
INCPRECEDENCELPAREN:
      LPAREN { precedence_paren++; }
;
Literal:
      INT_LIT { printf("INT_LIT %d\n",$1); strcpy(conversion_type,"int");  $$ = "INT_LIT"; operand_type_count++; strcpy(operand_type[operand_type_count], "int"); }
    | FLOAT_LIT { printf("FLOAT_LIT %.6f\n",$1); strcpy(print_type,"float"); strcpy(conversion_type,"float"); $$ = "FLOAT_LIT"; operand_type_count++; strcpy(operand_type[operand_type_count], "float"); }
    | BOOL_LIT { printf("%s\n",$1); strcpy(print_type,"bool"); $$ = "bool"; operand_type_count++; strcpy(operand_type[operand_type_count], "bool"); }
    | STRING_LIT { printf("STRING_LIT %s\n",$1); strcpy(print_type,"string"); $$ = "string"; operand_type_count++; strcpy(operand_type[operand_type_count], "string"); }
;
IndexExpr:
      PrimaryExpr LBRACK Expression RBRACK { $$ = $1; operand_type_count--; }
;
ConversionExpr:
      LPAREN Type RPAREN Expression { 
                $$ = $2;
                char origintype,casttype;
                if(strcmp(conversion_type,"int") == 0)
                    origintype  = 'I';
                else if(strcmp(conversion_type,"float") == 0)
                    origintype = 'F';
                if(strcmp($2,"int") == 0)
                    casttype = 'I';
                else if(strcmp($2,"float") == 0)
                    casttype = 'F';
                strcpy(operand_type[operand_type_count],$2);
                printf("%c to %c\n",origintype,casttype);
       }
;

Type:
      TypeName { $$ = $1; }
;

TypeName:
      INT { $$ = $1; }
    | FLOAT { $$ = $1; }
    | STRING { $$ = $1; }
    | BOOL { $$ = $1; }
;

%%

/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    for(int i = 0; i < 100; i++) {
        SymbolTable_current_count[i] = 0;
    }
    strcpy(print_type,"int");
    yyparse();
    dump_symbol();
	printf("Total lines: %d\n", yylineno);
    fclose(yyin);
    return 0;
}