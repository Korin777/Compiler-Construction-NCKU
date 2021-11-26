/* Definition section */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    #define YY_NO_UNPUT
    #define YY_NO_INPUT

    int line_num = 0;
    int comment_num = 0;

    void printupper(char *str){
        unsigned char *p = (unsigned char *)str;
        while (*p) {
            printf("%c",toupper((unsigned char)*p));
            p++;
        }
        printf("\n");
    }
    void printstring(char *str) {
        int count = 0;
        unsigned char *p = (unsigned char *)str;
        printf("%-8s \t %s\n", "\"", "QUOTA");
        while (*(++p)) {
            if(!*(p+1))
                break;
            printf("%c",(unsigned char)*p);
            count++;
        }
        int i;
        for(i = count;i < 8; i++) {
            printf(" ");
        }
        printf(" \t %s\n", "STRING_LIT");
        printf("%-8s \t %s\n", "\"", "QUOTA");
    }
    void printCcomment(char *str) {
        unsigned char *p = (unsigned char *)str;
        while (*p) {
            if((unsigned char)*p == '\n') {
                printf(" \t %s", "C Comment");
                line_num++;
                comment_num++;
            }
            printf("%c",(unsigned char)*p);
            p++;
        }
        printf(" \t %s\n", "C Comment");
        comment_num++;
    }


%}

/* Define regular expression label */
letter [a-zA-Z_]
digit [0-9]
id {letter}+({letter}|{digit})*
inumber {digit}+
fnumber ({digit}*\.{digit}+)
string \"((\\+\")|[^"])*\"
keyword print|return|if|else|for|while|int|float|string|bool|true|false|continue|break|void
Cpluspluscomment "//".* 
Ccomment "/*"((\*+[^/*])|([^*]))*\**"*/"



/* Rules section */
%%

"+"         { printf("%-8s \t %s\n", yytext, "ADD"); }
"-"         { printf("%-8s \t %s\n", yytext, "SUB"); }
"*"         { printf("%-8s \t %s\n", yytext, "MUL"); }
"/"         { printf("%-8s \t %s\n", yytext, "QUO"); }
"%"         { printf("%-8s \t %s\n", yytext, "REM"); }
"++"        { printf("%-8s \t %s\n", yytext, "INC"); }
"--"        { printf("%-8s \t %s\n", yytext, "DEC"); }
">"         { printf("%-8s \t %s\n", yytext, "GTR"); }
"<"         { printf("%-8s \t %s\n", yytext, "LSS"); }
">="        { printf("%-8s \t %s\n", yytext, "GEQ"); }
"<="        { printf("%-8s \t %s\n", yytext, "LEQ"); }
"=="        { printf("%-8s \t %s\n", yytext, "EQL"); }
"!="        { printf("%-8s \t %s\n", yytext, "NEQ"); }
"="         { printf("%-8s \t %s\n", yytext, "ASSIGN"); }
"+="        { printf("%-8s \t %s\n", yytext, "ADD_ASSIGN"); }
"-="        { printf("%-8s \t %s\n", yytext, "SUB_ASSIGN"); }
"*="        { printf("%-8s \t %s\n", yytext, "MUL_ASSIGN"); }
"/="        { printf("%-8s \t %s\n", yytext, "QUO_ASSIGN"); }
"%="        { printf("%-8s \t %s\n", yytext, "REM_ASSIGN"); }
"&&"        { printf("%-8s \t %s\n", yytext, "AND"); }
"||"        { printf("%-8s \t %s\n", yytext, "OR"); }
"!"         { printf("%-8s \t %s\n", yytext, "NOT"); }
"("         { printf("%-8s \t %s\n", yytext, "LPAREN"); }
")"         { printf("%-8s \t %s\n", yytext, "RPAREN"); }
"["         { printf("%-8s \t %s\n", yytext, "LBRACK"); }
"]"         { printf("%-8s \t %s\n", yytext, "RBRACK"); }
"{"         { printf("%-8s \t %s\n", yytext, "LBRACE"); }
"}"         { printf("%-8s \t %s\n", yytext, "RBRACE"); }
";"         { printf("%-8s \t %s\n", yytext, "SEMICOLON"); }
","         { printf("%-8s \t %s\n", yytext, "COMMA"); }
"\""        { printf("%-8s \t %s\n", yytext, "QUOTA"); }
"\n"        {line_num++;}


{Ccomment} { printCcomment(yytext); }
{Cpluspluscomment} { printf("%-8s \t %s\n", yytext, "C++ Comment"); comment_num++; }
{keyword}   { printf("%-8s \t ", yytext);printupper(yytext);}
{id}        { printf("%-8s \t %s\n", yytext, "IDENT"); }
{inumber}   { printf("%-8s \t %s\n", yytext, "INT_LIT"); }
{fnumber}   { printf("%-8s \t %s\n", yytext, "FLOAT_LIT"); }
{string}    { printstring(yytext); }

<<EOF>>     { line_num++; yyterminate(); }
.           {;}

%%

/*  C Code section */
int yywrap(void)
{
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    yylex();
    printf("\nFinish scanning,\n");
    printf("total line: %d\n", line_num);
    printf("comment line: %d\n", comment_num);
    fclose(yyin);
    return 0;
}
