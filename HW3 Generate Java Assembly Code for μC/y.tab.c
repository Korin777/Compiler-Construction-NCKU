/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "compiler_hw3.y" /* yacc.c:339  */

    #include "common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1;

    #define codegen(...) \
        do { \
            for (int i = 0; i < INDENT; i++) { \
                fprintf(fout, "\t"); \
            } \
            fprintf(fout, __VA_ARGS__); \
        } while (0)

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;
    
    /* Other global variables */
    FILE *fout = NULL;
    bool HAS_ERROR = false;
    int INDENT = 0;
    
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
    int idindex = 0;
    int branchindex = 0;
    int loopindex = -1;
    int loop[10];
    int loopnum = -1;
    bool assignbegin = false;

    char print_type[10];
    char conversion_type[10];
    void dump_BinaryOpStack(int nextprecedence,char binary_op[],bool foreceDumps) {
        while(binary_op_stack_count >= 0 && (foreceDumps || binary_op_stack[binary_op_stack_count].precedence >= nextprecedence)) {
            if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"ADD")==0 || strcmp(binary_op_stack[binary_op_stack_count].binary_op,"SUB")==0) {
                if(strcmp(operand_type[operand_type_count],operand_type[operand_type_count-1]) != 0) {
                    printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno,binary_op_stack[binary_op_stack_count].binary_op,operand_type[operand_type_count-1],operand_type[operand_type_count]);
                    HAS_ERROR = true;
                }
                else {
                    if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"ADD")==0) {
                        if(strcmp(operand_type[operand_type_count],"int") == 0)
                            codegen("iadd\n");
                        else
                            codegen("fadd\n");
                    }
                    else {
                        if(strcmp(operand_type[operand_type_count],"int") == 0)
                            codegen("isub\n");
                        else
                            codegen("fsub\n");
                    }
                }
            }
            if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"REM")==0) {
                if(strcmp(operand_type[operand_type_count],"float") == 0) {
                    printf("error:%d: invalid operation: (operator %s not defined on %s)\n",yylineno,binary_op_stack[binary_op_stack_count].binary_op,operand_type[operand_type_count]);
                    HAS_ERROR = true;
                }
                else if(strcmp(operand_type[operand_type_count-1],"float") == 0) {
                    printf("error:%d: invalid operation: (operator %s not defined on %s)\n",yylineno,binary_op_stack[binary_op_stack_count].binary_op,operand_type[operand_type_count-1]);
                    HAS_ERROR = true;
                }
                else
                    codegen("irem\n");
            }
            if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"MUL")==0) {
                if(strcmp(operand_type[operand_type_count],"float") == 0 || strcmp(operand_type[operand_type_count-1],"float") == 0)
                    codegen("fmul\n");
                else
                    codegen("imul\n");
            } 
            if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"QUO")==0) {
                if(strcmp(operand_type[operand_type_count],"float") == 0 || strcmp(operand_type[operand_type_count-1],"float") == 0)
                    codegen("fdiv\n");
                else
                    codegen("idiv\n");
            }            
            if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"AND")==0 || strcmp(binary_op_stack[binary_op_stack_count].binary_op,"OR")==0) {
                if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"int") == 0) {
                    printf("error:%d: invalid operation: (operator %s not defined on %s)\n",yylineno,binary_op_stack[binary_op_stack_count].binary_op,binary_op_stack[binary_op_stack_count].binary_op);
                    HAS_ERROR = true;
                }
                else if(strcmp(operand_type[operand_type_count-1],"int") == 0) {
                    printf("error:%d: invalid operation: (operator %s not defined on %s)\n",yylineno,binary_op_stack[binary_op_stack_count].binary_op,operand_type[operand_type_count-1]);
                    HAS_ERROR = true;
                }
                else {
                    if(strcmp(binary_op_stack[binary_op_stack_count].binary_op,"AND")==0)
                        codegen("iand\n");
                    else
                        codegen("ior\n");
                }
            }
            if(strcmp(binary_op_stack[binary_op_stack_count].binary_op  ,"GTR")==0) {
                if(strcmp(operand_type[operand_type_count],"float") == 0 || strcmp(operand_type[operand_type_count-1],"float") == 0)
                    codegen("fcmpl\n");
                else
                    codegen("isub\n");
                codegen("ifgt L_cmp_%d\n",branchindex);
                codegen("iconst_0\n");
                codegen("goto L_cmp_%d\n",branchindex+1);
                INDENT--;
                codegen("L_cmp_%d:\n",branchindex);
                INDENT++;
                codegen("iconst_1\n");
                INDENT--;
                codegen("L_cmp_%d:\n",branchindex+1);
                branchindex += 2;
                INDENT++;
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
                HAS_ERROR = true;
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

            if(strcmp(type,"array") == 0) {
                codegen("newarray %s\n", elementType);
                codegen("astore %d\n", SymbolTable_current_count[SymbolTable_current]);
            }
            else if(strcmp(type,"int") == 0)
                codegen("istore %d\n", 10 * SymbolTable_current + SymbolTable_current_count[SymbolTable_current]);
            else if(strcmp(type,"float") == 0)
                codegen("fstore %d\n", 10 * SymbolTable_current + SymbolTable_current_count[SymbolTable_current]);
            else if(strcmp(type,"string") == 0)
                codegen("astore %d\n", 10 * SymbolTable_current + SymbolTable_current_count[SymbolTable_current]);
    
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


#line 278 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 219 "compiler_hw3.y" /* yacc.c:355  */

    int i_val;
    float f_val;
    char *s_val;
    /* ... */

#line 415 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 432 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   243

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   249,   249,   253,   254,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   271,   278,   281,   289,   293,   326,
     327,   328,   329,   330,   331,   334,   337,   340,   343,   356,
     371,   372,   373,   376,   385,   389,   393,   403,   406,   409,
     412,   415,   416,   417,   420,   423,   426,   454,   455,   462,
     463,   480,   481,   482,   483,   484,   488,   489,   490,   491,
     492,   493,   496,   497,   500,   501,   502,   505,   506,   507,
     511,   512,   513,   516,   517,   583,   586,   589,   590,   591,
     602,   605,   618,   635,   639,   640,   641,   642
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ADD", "SUB", "MUL", "QUO", "REM", "INC",
  "DEC", "GTR", "LSS", "GEQ", "LEQ", "EQL", "NEQ", "ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "QUO_ASSIGN", "REM_ASSIGN", "AND", "OR",
  "NOT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK",
  "SEMICOLON", "PRINT", "IF", "ELSE", "FOR", "WHILE", "INT_LIT",
  "FLOAT_LIT", "STRING_LIT", "IDENT", "INT", "FLOAT", "STRING", "BOOL_LIT",
  "BOOL", "$accept", "Program", "StatementList", "Statement",
  "DeclarationStmt", "AssignmentStmt", "AssignmentExpr", "assign_op",
  "ArithmeticStmt", "ArithmeticExpr", "IncDecStmt", "IncDecExpr", "IfStmt",
  "Condition", "WhileStmt", "BEGIN", "END", "ForStmt", "ForClause",
  "InitStmt", "PostStmt", "SimpleExpr", "Block",
  "INCSYBOLTABLECURRENTBRACE", "PrintStmt", "Expression", "UnaryExpr",
  "binary_op", "cmp_op", "add_op", "mul_op", "unary_op", "PrimaryExpr",
  "Operand", "INCPRECEDENCELPAREN", "Literal", "IndexExpr",
  "ConversionExpr", "Type", "TypeName", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF -50

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-50)))

#define YYTABLE_NINF -36

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,   -50,   -50,   -50,   -18,   -50,   -20,    55,   -19,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,    26,   -50,
      12,   -50,   -50,   -23,   -50,     0,   -50,     1,   -50,   -50,
     -29,   -50,   -50,    12,   -50,   183,   -50,    55,     5,   -50,
      55,   -50,   -50,   -50,    -5,   -50,    16,    55,    19,   204,
      55,   -50,   -50,   -50,   -50,   -50,    35,    33,   -50,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,    55,
      55,   -50,   -50,   -50,   -50,    55,   135,   212,    55,   159,
      28,   -50,   -50,    37,    36,   -50,   183,    55,   -50,   204,
     204,   107,   -50,    55,   -50,    55,   204,    39,   -24,    19,
      55,    40,   -50,   121,     7,   -50,   -50,   -50,   -50,    46,
      19,    52,   -50,    55,   -50,   -50,   -50,   -50,   -50
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    67,    68,    69,    76,    45,     0,     0,     0,    77,
      78,    80,    74,    84,    85,    86,    79,    87,     0,     2,
       4,     5,     6,     0,     7,     0,     8,     0,    10,    11,
       0,    12,     9,     4,    13,    26,    47,     0,    49,    70,
       0,    73,    71,    72,     0,    83,     0,     0,     0,    33,
       0,     1,     3,    17,    25,    27,     0,     0,    62,    63,
      64,    65,    66,    28,    29,    60,    58,    61,    59,    56,
      57,    19,    20,    21,    22,    23,    24,    52,    51,     0,
       0,    53,    54,    55,    50,     0,     0,     0,     0,     0,
      30,    41,    43,     0,     0,    39,    42,     0,    44,    18,
      48,     0,    75,     0,    14,     0,    82,     0,     0,     0,
       0,     0,    81,     0,     0,    46,    31,    32,    37,     0,
       0,     0,    16,     0,    36,    15,    38,    40,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -50,   -50,     8,   -50,   -50,   -50,   -49,   -16,   -50,   -50,
     -50,   -48,   -40,   -28,   -50,   -50,   -50,   -50,   -50,   -50,
     -50,   -39,   -44,   -50,   -50,    -7,    48,   -50,   -50,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,    82,   -50
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    18,    19,    20,    21,    22,    23,    79,    24,    25,
      26,    27,    28,    48,    29,    30,   128,    31,    93,    94,
     126,    95,    32,    33,    34,    35,    36,    80,    81,    82,
      83,    37,    38,    39,    40,    41,    42,    43,    44,    45
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      49,    91,    92,     5,    90,    47,    50,    56,    53,     7,
      58,    59,    60,    61,    62,     1,     2,    65,    66,    67,
      68,    69,    70,    13,    14,    15,    51,    17,    52,    77,
      78,    54,    55,    86,    85,    87,     3,     4,   122,     5,
      89,    57,    88,    96,     6,     7,     5,     8,   -35,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     1,     2,
      97,    98,   108,   109,   117,   118,   120,   110,   116,   111,
     115,   105,    99,   100,    91,    92,   124,   123,   101,     3,
       4,   106,   119,   125,   127,    84,    46,     0,     0,     0,
      49,     0,     9,    10,    11,    12,   113,     0,   114,    16,
       0,     0,     0,    49,     0,     0,     0,     0,     0,     0,
      58,    59,    60,    61,    62,     0,    96,    65,    66,    67,
      68,    69,    70,     0,    58,    59,    60,    61,    62,    77,
      78,    65,    66,    67,    68,    69,    70,   112,    58,    59,
      60,    61,    62,    77,    78,    65,    66,    67,    68,    69,
      70,   121,     0,     0,     0,     0,     0,    77,    78,     0,
       0,   102,    58,    59,    60,    61,    62,     0,     0,    65,
      66,    67,    68,    69,    70,     0,     0,     0,     0,     0,
       0,    77,    78,     0,     0,   107,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    58,    59,    60,
      61,    62,     0,     0,    65,    66,    67,    68,    69,    70,
       0,     0,     0,     0,     0,     0,    77,    78,    71,    72,
      73,    74,    75,    76,     0,     0,     0,     0,     0,     0,
       0,   103,     0,   104
};

static const yytype_int8 yycheck[] =
{
       7,    50,    50,    27,    48,    25,    25,    36,    31,    33,
       3,     4,     5,     6,     7,     3,     4,    10,    11,    12,
      13,    14,    15,    41,    42,    43,     0,    45,    20,    22,
      23,    31,    31,    40,    29,    40,    24,    25,    31,    27,
      47,    33,    26,    50,    32,    33,    27,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     3,     4,
      25,    28,    34,    26,   108,   109,    26,    31,   108,    97,
      31,    87,    79,    80,   123,   123,   120,    31,    85,    24,
      25,    88,   110,    31,   123,    37,     4,    -1,    -1,    -1,
      97,    -1,    37,    38,    39,    40,   103,    -1,   105,    44,
      -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,    -1,   123,    10,    11,    12,
      13,    14,    15,    -1,     3,     4,     5,     6,     7,    22,
      23,    10,    11,    12,    13,    14,    15,    30,     3,     4,
       5,     6,     7,    22,    23,    10,    11,    12,    13,    14,
      15,    30,    -1,    -1,    -1,    -1,    -1,    22,    23,    -1,
      -1,    26,     3,     4,     5,     6,     7,    -1,    -1,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    23,    -1,    -1,    26,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,     3,     4,     5,
       6,     7,    -1,    -1,    10,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    22,    23,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    24,    25,    27,    32,    33,    35,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    47,    48,
      49,    50,    51,    52,    54,    55,    56,    57,    58,    60,
      61,    63,    68,    69,    70,    71,    72,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    84,    25,    59,    71,
      25,     0,    48,    31,    31,    31,    36,    48,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    53,
      73,    74,    75,    76,    72,    29,    71,    40,    26,    71,
      68,    52,    57,    64,    65,    67,    71,    25,    28,    71,
      71,    71,    26,    29,    31,    53,    71,    26,    34,    26,
      31,    59,    30,    71,    71,    31,    58,    68,    68,    59,
      26,    30,    31,    31,    68,    31,    66,    67,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    50,    50,    50,    51,    52,    53,
      53,    53,    53,    53,    53,    54,    55,    56,    57,    57,
      58,    58,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    67,    67,    68,    69,    70,    71,    71,    72,
      72,    73,    73,    73,    73,    73,    74,    74,    74,    74,
      74,    74,    75,    75,    76,    76,    76,    77,    77,    77,
      78,    78,    78,    79,    79,    79,    80,    81,    81,    81,
      81,    82,    83,    84,    85,    85,    85,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     6,     5,     2,     3,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     2,     2,
       3,     5,     5,     1,     7,     0,     0,     5,     5,     1,
       1,     1,     1,     1,     3,     1,     5,     1,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     4,     4,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 5:
#line 258 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy(print_type,"int"); operand_type_count = -1; assignbegin = false; }
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 259 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy(print_type,"int"); operand_type_count = -1; assignbegin = false; }
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 260 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy(print_type,"int"); operand_type_count = -1; assignbegin = false; }
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 261 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy(print_type,"int"); operand_type_count = -1; assignbegin = false; }
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 262 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy(print_type,"int"); operand_type_count = -1; assignbegin = false; }
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 263 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy(print_type,"int"); operand_type_count = -1; assignbegin = false; }
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 264 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy(print_type,"int"); operand_type_count = -1; assignbegin = false; }
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 265 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy(print_type,"int"); operand_type_count = -1; assignbegin = false; }
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 266 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy(print_type,"int"); operand_type_count = -1; assignbegin = false; }
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 271 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            if(strcmp((yyvsp[-2].s_val),"int") == 0)
                codegen("ldc 0\n");
            else if(strcmp((yyvsp[-2].s_val),"float") == 0)
                codegen("ldc 0.000000\n");
            insert_symbol(SymbolTable_current_count[SymbolTable_current],(yyvsp[-1].s_val),(yyvsp[-2].s_val),uniqueAddress,yylineno,"-");
    }
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 278 "compiler_hw3.y" /* yacc.c:1646  */
    {
            insert_symbol(SymbolTable_current_count[SymbolTable_current],(yyvsp[-4].s_val),"array",uniqueAddress,yylineno,(yyvsp[-5].s_val));
    }
#line 1701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 281 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            insert_symbol(SymbolTable_current_count[SymbolTable_current],(yyvsp[-3].s_val),(yyvsp[-4].s_val),uniqueAddress,yylineno,"-");
    }
#line 1709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 293 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            if(strcmp((yyvsp[-2].s_val),"INT_LIT") == 0)
                printf("error:%d: cannot assign to int\n",yylineno);
            else if(strcmp((yyvsp[-2].s_val),"FLOAT_LIT") == 0)
            printf("error:%d: cannot assign to float\n",yylineno);
            else if(strcmp((yyvsp[-2].s_val),"null")!=0 && strcmp((yyvsp[0].s_val),"null")!=0) {
                if(strcmp((yyvsp[-2].s_val),"INT_LIT") == 0)
                    (yyvsp[-2].s_val) = "int";
                if(strcmp((yyvsp[0].s_val),"INT_LIT") == 0)
                    (yyvsp[0].s_val) = "int";
                if(strcmp((yyvsp[-2].s_val),"FLOAT_LIT") == 0)
                    (yyvsp[-2].s_val) = "float";
                if(strcmp((yyvsp[0].s_val),"FLOAT_LIT") == 0)
                    (yyvsp[0].s_val) = "float";
                if(strcmp((yyvsp[-2].s_val),(yyvsp[0].s_val)) != 0)
                    printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno,(yyvsp[-1].s_val),(yyvsp[-2].s_val),(yyvsp[0].s_val));
            }
            if(strcmp(MySymbolTable[idindex/10][idindex%10].type,"array") == 0) {
                if(strcmp(conversion_type,"int") == 0)
                    codegen("iastore\n");
                if(strcmp(conversion_type,"float") == 0)
                    codegen("fastore\n");
            }
            else {
                if(strcmp(conversion_type,"int") == 0)
                    codegen("istore %d\n",idindex);
                if(strcmp(conversion_type,"float") == 0)
                    codegen("fstore %d\n",idindex);
            }
            printf("%s\n",(yyvsp[-1].s_val));            
    }
#line 1745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 326 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = "ASSIGN"; }
#line 1751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 327 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = "ADD_ASSIGN"; }
#line 1757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 328 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = "SUB_ASSIGN"; }
#line 1763 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 329 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = "MUL_ASSIGN"; }
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 330 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = "QUO_ASSIGN"; }
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 331 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = "REM_ASSIGN"; }
#line 1781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 337 "compiler_hw3.y" /* yacc.c:1646  */
    { }
#line 1787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 343 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            printf("INC\n"); 
            if(strcmp(operand_type[operand_type_count],"int") == 0) {
                codegen("ldc 1\n"); 
                codegen("iadd\n"); 
                codegen("istore %d\n", idindex); 
            }
            else {
                codegen("ldc 1.000000\n"); 
                codegen("fadd\n"); 
                codegen("fstore %d\n", idindex); 
            }
    }
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 356 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            printf("DEC\n"); 
            if(strcmp(operand_type[operand_type_count],"int") == 0) {
                codegen("ldc 1\n"); 
                codegen("isub\n"); 
                codegen("istore %d\n", idindex); 
            }
            else {
                codegen("ldc 1.000000\n"); 
                codegen("fsub\n"); 
                codegen("fstore %d\n", idindex); 
            }
    }
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 376 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            if(strcmp(print_type,"bool") != 0)
                printf("error:%d: non-bool (type %s) used as for condition\n",yylineno+1,print_type);
            strcpy(print_type,"int");
            codegen("ifeq L_for_exit_%d\n",loopnum);
            loop[loopindex] = loopnum;
    }
#line 1835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 389 "compiler_hw3.y" /* yacc.c:1646  */
    { loopnum++; loopindex++; INDENT--; codegen("L_for_begin_%d :\n",loopnum); INDENT++; }
#line 1841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 393 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            codegen("goto L_for_begin_%d\n",loop[loopindex]); 
            INDENT--; 
            codegen("L_for_exit_%d :\n",loop[loopindex]); 
            INDENT++; 
            loopindex--;
        }
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 420 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_symbol(); }
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 423 "compiler_hw3.y" /* yacc.c:1646  */
    { create_symbol(); }
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 426 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            printf("PRINT %s\n",print_type); 
            codegen("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            codegen("swap\n"); 
            if(strcmp(print_type,"int") == 0)
                codegen("invokevirtual java/io/PrintStream/print(I)V\n");
            else if(strcmp(print_type,"float") == 0)
                codegen("invokevirtual java/io/PrintStream/print(F)V\n");
            else if(strcmp(print_type,"string") == 0)
                codegen("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
            else if(strcmp(print_type,"bool") == 0) {
                codegen("ifne L_cmp_%d\n",branchindex);
                codegen("ldc \"false\"\n");
                codegen("goto L_cmp_%d\n",branchindex+1);
                INDENT--;
                codegen("L_cmp_%d:\n",branchindex);
                INDENT++;
                codegen("ldc \"true\"\n");
                INDENT--;
                codegen("L_cmp_%d:\n",branchindex+1);
                INDENT++;
                branchindex += 2;
                codegen("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
            }
      }
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 454 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 455 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            dump_BinaryOpStack(0,"forcedump",true); 
            (yyval.s_val) = (yyvsp[-2].s_val);
    }
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 462 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 463 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            printf("%s\n",(yyvsp[-1].s_val)); 
            (yyval.s_val) = (yyvsp[0].s_val);
            if(strcmp((yyvsp[-1].s_val),"NEG") == 0) {
                if(strcmp(operand_type[operand_type_count],"int") == 0)
                    codegen("ineg\n");
                else
                    codegen("fneg\n");
            }
            else if(strcmp((yyvsp[-1].s_val),"NOT") == 0) {
                codegen("iconst_1\n");
                codegen("ixor\n");
            }
    }
#line 1935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 480 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+1, "OR",false); (yyval.s_val) = "OR"; }
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 481 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+2, "AND",false); (yyval.s_val) = "AND"; }
#line 1947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 482 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 483 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1959 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 484 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 488 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+3, "EQL",false); (yyval.s_val) = "EQL"; }
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 489 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+3, "NEQ",false); (yyval.s_val) = "NEQ"; }
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 490 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+3, "LSS",false); (yyval.s_val) = "LSS"; }
#line 1983 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 491 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+3, "LEQ",false); (yyval.s_val) = "LEQ"; }
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 492 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+3, "GTR",false); (yyval.s_val) = "GTR"; }
#line 1995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 493 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+3, "GEQ",false); (yyval.s_val) = "GEQ"; }
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 496 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+4, "ADD",false); (yyval.s_val) = "ADD"; }
#line 2007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 497 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+4, "SUB",false); (yyval.s_val) = "SUB"; }
#line 2013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 500 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+5, "MUL",false); (yyval.s_val) = "MUL"; }
#line 2019 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 501 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+5, "QUO",false); (yyval.s_val) = "QUO"; }
#line 2025 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 502 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_BinaryOpStack(precedence_paren*7+5, "REM",false); (yyval.s_val) = "REM"; }
#line 2031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 505 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = "POS"; }
#line 2037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 506 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = "NEG"; }
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 507 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = "NOT"; }
#line 2049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 511 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 512 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2061 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 513 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 516 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 517 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            (yyval.s_val) = "null";
            int tmpaddress = 0;
            bool find = false;
            for(int i = SymbolTable_current; i >= 0 ; i--) {
                for(int j = 0; j < SymbolTable_current_count[i]; j++) {
                    if(strcmp(MySymbolTable[i][j].name,(yyvsp[0].s_val)) == 0) {
                        find = true;
                        tmpaddress = MySymbolTable[i][j].address;
                        if(strcmp(MySymbolTable[i][j].type,"array")==0)
                            (yyval.s_val) = MySymbolTable[i][j].elementType;
                        else
                            (yyval.s_val) = MySymbolTable[i][j].type;
                        if((strcmp(MySymbolTable[i][j].type,"int")==0) || (strcmp(MySymbolTable[i][j].elementType,"int") == 0)) {
                            strcpy(conversion_type,"int");
                            operand_type_count++;
                            strcpy(operand_type[operand_type_count], "int"); 
                            if((strcmp(MySymbolTable[i][j].elementType,"int") == 0))
                                codegen("aload %d\n",10*i+j);
                            else {
                                if(assignbegin)
                                    assignbegin = false;
                                else
                                    codegen("iload %d\n",10*i+j);
                            }
                            idindex = 10 * i + j;
                        }
                        if((strcmp(MySymbolTable[i][j].type,"float")==0) || (strcmp(MySymbolTable[i][j].elementType,"float") == 0)) {
                            strcpy(print_type,"float");
                            strcpy(conversion_type,"float");
                            operand_type_count++;
                            strcpy(operand_type[operand_type_count], "float");
                            if((strcmp(MySymbolTable[i][j].elementType,"float") == 0))
                                codegen("aload %d\n",10*i+j);
                            else {
                                if(assignbegin)
                                    assignbegin = false;
                                else
                                    codegen("fload %d\n",10*i+j); 
                            }
                            idindex = 10 * i + j;
                        }
                        if((strcmp(MySymbolTable[i][j].type,"string")==0) || (strcmp(MySymbolTable[i][j].elementType,"string") == 0)) {
                            strcpy(print_type,"string");
                            operand_type_count++;
                            strcpy(operand_type[operand_type_count], "string");
                            codegen("aload %d\n",10*i+j); 
                            idindex = 10 * i + j;
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
            if(find) {
                printf("IDENT (name=%s, address=%d)\n",(yyvsp[0].s_val),tmpaddress); 
            }
            else
                printf("error:%d: undefined: %s\n",yylineno,(yyvsp[0].s_val)); 
    }
#line 2144 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 583 "compiler_hw3.y" /* yacc.c:1646  */
    { precedence_paren--; (yyval.s_val) = (yyvsp[-1].s_val); }
#line 2150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 586 "compiler_hw3.y" /* yacc.c:1646  */
    { precedence_paren++; }
#line 2156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 589 "compiler_hw3.y" /* yacc.c:1646  */
    { printf("INT_LIT %d\n",(yyvsp[0].i_val)); codegen("ldc"); codegen("%d\n",(yyvsp[0].i_val)); strcpy(conversion_type,"int");  (yyval.s_val) = "INT_LIT"; operand_type_count++; strcpy(operand_type[operand_type_count], "int"); }
#line 2162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 590 "compiler_hw3.y" /* yacc.c:1646  */
    { printf("FLOAT_LIT %.6f\n",(yyvsp[0].f_val)); strcpy(print_type,"float"); codegen("ldc"); codegen("%f\n",(yyvsp[0].f_val)); strcpy(conversion_type,"float"); (yyval.s_val) = "FLOAT_LIT"; operand_type_count++; strcpy(operand_type[operand_type_count], "float"); }
#line 2168 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 591 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            printf("%s\n",(yyvsp[0].s_val));
            strcpy(print_type,"bool"); 
            (yyval.s_val) = "bool";
            if(strcmp((yyvsp[0].s_val),"TRUE") == 0)
                codegen("iconst_1\n");
            else
                codegen("iconst_0\n"); 
            operand_type_count++; 
            strcpy(operand_type[operand_type_count], "bool"); 
    }
#line 2184 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 602 "compiler_hw3.y" /* yacc.c:1646  */
    { printf("STRING_LIT %s\n",(yyvsp[0].s_val)); strcpy(print_type,"string"); codegen("ldc"); codegen("\"%s\"\n",(yyvsp[0].s_val)); (yyval.s_val) = "string"; operand_type_count++; strcpy(operand_type[operand_type_count], "string"); }
#line 2190 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 605 "compiler_hw3.y" /* yacc.c:1646  */
    { 
            (yyval.s_val) = (yyvsp[-3].s_val); operand_type_count--;
            if(assignbegin)
                assignbegin = false;
            else {
                if(strcmp(MySymbolTable[idindex/10][idindex%10].elementType,"int")==0) 
                    codegen("iaload\n");
                else if(strcmp(MySymbolTable[idindex/10][idindex%10].elementType,"float")==0)
                    codegen("faload\n");
            }
      }
#line 2206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 618 "compiler_hw3.y" /* yacc.c:1646  */
    { 
                (yyval.s_val) = (yyvsp[-2].s_val);
                char origintype,casttype;
                if(strcmp(conversion_type,"int") == 0)
                    origintype  = 'I';
                else if(strcmp(conversion_type,"float") == 0)
                    origintype = 'F';
                if(strcmp((yyvsp[-2].s_val),"int") == 0)
                    casttype = 'I';
                else if(strcmp((yyvsp[-2].s_val),"float") == 0)
                    casttype = 'F';
                strcpy(operand_type[operand_type_count],(yyvsp[-2].s_val));
                printf("%c to %c\n",origintype,casttype);
       }
#line 2225 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 635 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2231 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 639 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2237 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 640 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2243 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 641 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2249 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 642 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.s_val) = (yyvsp[0].s_val); }
#line 2255 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2259 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 645 "compiler_hw3.y" /* yacc.c:1906  */


/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    /* Codegen output init */
    char *bytecode_filename = "hw3.j";
    fout = fopen(bytecode_filename, "w");
    codegen(".source hw3.j\n");
    codegen(".class public Main\n");
    codegen(".super java/lang/Object\n");
    codegen(".method public static main([Ljava/lang/String;)V\n");
    codegen(".limit stack 100\n");
    codegen(".limit locals 100\n");
    INDENT++;

    yyparse();

	printf("Total lines: %d\n", yylineno);

    /* Codegen end */
    codegen("return\n");
    INDENT--;
    codegen(".end method\n");
    fclose(fout);
    fclose(yyin);

    if (HAS_ERROR) {
        remove(bytecode_filename);
    }
    return 0;
}
