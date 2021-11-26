/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ADD = 258,
    SUB = 259,
    MUL = 260,
    QUO = 261,
    REM = 262,
    INC = 263,
    DEC = 264,
    GTR = 265,
    LSS = 266,
    GEQ = 267,
    LEQ = 268,
    EQL = 269,
    NEQ = 270,
    ASSIGN = 271,
    ADD_ASSIGN = 272,
    SUB_ASSIGN = 273,
    MUL_ASSIGN = 274,
    QUO_ASSIGN = 275,
    REM_ASSIGN = 276,
    AND = 277,
    OR = 278,
    NOT = 279,
    LPAREN = 280,
    RPAREN = 281,
    LBRACE = 282,
    RBRACE = 283,
    LBRACK = 284,
    RBRACK = 285,
    SEMICOLON = 286,
    PRINT = 287,
    IF = 288,
    ELSE = 289,
    FOR = 290,
    WHILE = 291,
    INT_LIT = 292,
    FLOAT_LIT = 293,
    STRING_LIT = 294,
    IDENT = 295,
    INT = 296,
    FLOAT = 297,
    STRING = 298,
    BOOL_LIT = 299,
    BOOL = 300
  };
#endif
/* Tokens.  */
#define ADD 258
#define SUB 259
#define MUL 260
#define QUO 261
#define REM 262
#define INC 263
#define DEC 264
#define GTR 265
#define LSS 266
#define GEQ 267
#define LEQ 268
#define EQL 269
#define NEQ 270
#define ASSIGN 271
#define ADD_ASSIGN 272
#define SUB_ASSIGN 273
#define MUL_ASSIGN 274
#define QUO_ASSIGN 275
#define REM_ASSIGN 276
#define AND 277
#define OR 278
#define NOT 279
#define LPAREN 280
#define RPAREN 281
#define LBRACE 282
#define RBRACE 283
#define LBRACK 284
#define RBRACK 285
#define SEMICOLON 286
#define PRINT 287
#define IF 288
#define ELSE 289
#define FOR 290
#define WHILE 291
#define INT_LIT 292
#define FLOAT_LIT 293
#define STRING_LIT 294
#define IDENT 295
#define INT 296
#define FLOAT 297
#define STRING 298
#define BOOL_LIT 299
#define BOOL 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 124 "compiler_hw2.y" /* yacc.c:1909  */

    int i_val;
    float f_val;
    char *s_val;
    /* ... */

#line 151 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
