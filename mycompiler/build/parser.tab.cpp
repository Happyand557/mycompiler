/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         SYSYSTYPE
/* Substitute the variable and function names.  */
#define yyparse         sysyparse
#define yylex           sysylex
#define yyerror         sysyerror
#define yydebug         sysydebug
#define yynerrs         sysynerrs
#define yylval          sysylval
#define yychar          sysychar

/* First part of user prologue.  */
#line 1 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"

    #include<stdio.h>
    #include<string.h>
    #include"ast_sysy.h"

    extern int sysylex();
    extern int lineno;
    extern char *sysytext;
    extern AST *root_sysy;
    extern TABLE *root_symtable;
    extern std::vector<TABLE *>symtable_vector;
    extern TABLE *symtable_ptr;
    
    void yyerror(char *str){
        printf("LINE %d in %s : %s\n",lineno, sysytext, str);
    };
    
    int NumberOfTemp;   //记录一个函数需要多少临时变量

#line 98 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_SYSY_HOME_RYJ_COMPILER_MYCOMPILERTEMP_MYCOMPILER_BUILD_PARSER_TAB_HPP_INCLUDED
# define YY_SYSY_HOME_RYJ_COMPILER_MYCOMPILERTEMP_MYCOMPILER_BUILD_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef SYSYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define SYSYDEBUG 1
#  else
#   define SYSYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define SYSYDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined SYSYDEBUG */
#if SYSYDEBUG
extern int sysydebug;
#endif

/* Token type.  */
#ifndef SYSYTOKENTYPE
# define SYSYTOKENTYPE
  enum sysytokentype
  {
    CONST = 258,
    INT = 259,
    VOID = 260,
    IF = 261,
    ELSE = 262,
    WHILE = 263,
    BREAK = 264,
    CONTINUE = 265,
    RETURN = 266,
    LE = 267,
    GE = 268,
    EQ = 269,
    NE = 270,
    AND = 271,
    OR = 272,
    IDENT = 273,
    INT_CONST = 274
  };
#endif

/* Value type.  */
#if ! defined SYSYSTYPE && ! defined SYSYSTYPE_IS_DECLARED
union SYSYSTYPE
{
#line 23 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"

    class AST *ast; //class关键字必需添加

#line 182 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"

};
typedef union SYSYSTYPE SYSYSTYPE;
# define SYSYSTYPE_IS_TRIVIAL 1
# define SYSYSTYPE_IS_DECLARED 1
#endif


extern SYSYSTYPE sysylval;

int sysyparse (void);

#endif /* !YY_SYSY_HOME_RYJ_COMPILER_MYCOMPILERTEMP_MYCOMPILER_BUILD_PARSER_TAB_HPP_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
         || (defined SYSYSTYPE_IS_TRIVIAL && SYSYSTYPE_IS_TRIVIAL)))

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   202

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  159

#define YYUNDEFTOK  2
#define YYMAXUTOK   274


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    20,     2,     2,     2,    19,     2,     2,
      21,    22,    17,    15,    28,    16,     2,    18,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    27,
      14,    12,    13,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    23,     2,    24,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,    26,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    29,    30,    31,
      32,    33,    34,    35,    36
};

#if SYSYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    41,    41,    45,    49,    54,    61,    66,    73,    82,
      87,    93,    98,   105,   126,   131,   138,   143,   147,   155,
     160,   166,   174,   179,   185,   198,   214,   219,   223,   231,
     236,   242,   242,   259,   259,   277,   282,   288,   304,   314,
     322,   326,   332,   337,   344,   355,   360,   364,   364,   373,
     382,   389,   396,   401,   406,   412,   419,   431,   439,   450,
     456,   463,   474,   483,   490,   497,   504,   522,   527,   533,
     541,   546,   552,   559,   566,   575,   586,   596,   606,   618,
     627,   636,   645,   654,   665,   674,   683,   694,   703,   714,
     720,   731
};
#endif

#if SYSYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONST", "INT", "VOID", "IF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "RETURN", "'='", "'>'", "'<'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'!'", "'('", "')'", "'['", "']'", "'{'",
  "'}'", "';'", "','", "LE", "GE", "EQ", "NE", "AND", "OR", "IDENT",
  "INT_CONST", "$accept", "CompUnit", "Decl", "ConstDecl", "ConstDef_temp",
  "BType", "ConstDef", "ConstExp_temp", "ConstInitVal",
  "ConstInitVal_temp", "VarDecl", "VarDef_temp", "VarDef", "InitVal",
  "InitVal_temp", "FuncDef", "$@1", "$@2", "FuncFParams", "FuncFParam",
  "Block", "BlockItem_temp", "BlockItem", "Stmt", "$@3", "Exp", "Cond",
  "LVal", "PrimaryExp", "UnaryExp", "UnaryOp", "FuncRParams", "MulExp",
  "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", "ConstExp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,    61,    62,    60,    43,    45,    42,    47,    37,
      33,    40,    41,    91,    93,   123,   125,    59,    44,   267,
     268,   269,   270,   271,   272,   273,   274
};
# endif

#define YYPACT_NINF (-125)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-34)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      99,    20,  -125,  -125,    96,  -125,  -125,   -19,  -125,  -125,
      -6,  -125,  -125,  -125,    18,    29,  -125,  -125,    78,  -125,
      21,    22,  -125,    25,    30,  -125,    -6,    20,    47,     2,
     156,  -125,  -125,   121,  -125,    46,    24,  -125,    60,  -125,
    -125,  -125,   156,   109,    73,  -125,  -125,  -125,    75,  -125,
    -125,   156,   161,   148,   148,    95,   134,  -125,  -125,  -125,
      60,    20,  -125,  -125,   104,  -125,  -125,   -15,    57,   156,
    -125,   156,   156,   156,   156,   156,  -125,  -125,  -125,   125,
     108,  -125,  -125,   112,  -125,  -125,     2,  -125,  -125,    67,
     116,  -125,  -125,  -125,   161,   161,  -125,   121,   122,   131,
     138,   141,   146,  -125,  -125,  -125,    25,  -125,  -125,    60,
     158,    32,  -125,  -125,   156,  -125,  -125,   156,   156,  -125,
    -125,  -125,   159,  -125,  -125,   156,  -125,   136,   148,     6,
      16,   154,   155,   166,  -125,   163,    55,   156,   156,   156,
     156,   156,   156,   156,   156,    55,  -125,   186,   148,   148,
     148,   148,     6,     6,    16,   154,  -125,    55,  -125
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    11,    12,     0,     4,     6,     0,     7,     5,
       0,     1,     2,     3,    15,     0,    22,    15,     0,     9,
      31,    24,    21,     0,     0,     8,     0,     0,     0,     0,
       0,    15,    23,     0,    10,     0,     0,    35,     0,    67,
      68,    69,     0,     0,    58,    62,    25,    26,    61,    63,
      72,     0,    76,    56,    91,     0,     0,    13,    16,    15,
       0,     0,    41,    34,     0,    27,    29,     0,     0,     0,
      66,     0,     0,     0,     0,     0,    14,    17,    19,     0,
      37,    32,    36,    47,    60,    28,     0,    65,    70,     0,
       0,    73,    74,    75,    77,    78,    18,     0,     0,     0,
       0,     0,     0,    39,    46,    42,     0,    40,    43,     0,
       0,    61,    30,    64,     0,    59,    20,     0,     0,    52,
      53,    55,     0,    48,    45,     0,    71,     0,    79,    84,
      87,    89,    57,     0,    54,     0,    47,     0,     0,     0,
       0,     0,     0,     0,     0,    47,    44,    50,    81,    80,
      82,    83,    85,    86,    88,    90,    51,    47,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -125,  -125,     0,  -125,  -125,     1,   168,    -8,   -48,  -125,
    -125,  -125,   172,   -36,  -125,   192,  -125,  -125,  -125,   137,
     -55,  -125,  -125,  -124,  -125,   -28,    79,   -77,  -125,   -41,
    -125,  -125,   100,   -30,    42,    56,    58,  -125,   170
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    18,     7,    19,    21,    57,    79,
       8,    15,    16,    46,    67,     9,    27,    28,    36,    37,
      63,    83,   107,   108,   109,   110,   127,    48,    49,    50,
      51,    89,    52,    53,   129,   130,   131,   132,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,    47,    10,    54,    12,    81,   111,    66,    78,    24,
      70,    85,   147,    86,    64,    47,    14,    39,    40,   137,
     138,   156,    41,    42,     2,     3,    54,    43,    35,    17,
      91,    92,    93,   158,    29,   139,   140,    44,    45,    20,
      88,    90,    33,   -33,   125,    30,    60,   141,   142,   116,
     112,    80,    61,    30,   123,    69,    22,    23,    47,   111,
      31,    98,    35,    99,   100,   101,   102,    54,   111,    38,
      39,    40,    39,    40,   122,    41,    42,    41,    42,    87,
     111,    59,   104,   105,   106,    62,   126,   128,   128,   113,
      44,    45,    44,    45,    68,   114,    11,   135,    69,     1,
       2,     3,     1,     2,     3,    25,    26,   148,   149,   150,
     151,   128,   128,   128,   128,     1,     2,     3,    98,    76,
      99,   100,   101,   102,    39,    40,    84,    39,    40,    41,
      42,    30,    41,    42,    43,    65,    39,    40,   103,   104,
     115,    41,    42,   117,    44,    45,    56,    44,    45,    39,
      40,    96,   118,    97,    41,    42,    44,    45,   136,    56,
      77,    39,    40,    74,    75,   119,    41,    42,   120,    44,
      45,    39,    40,   121,    94,    95,    41,    42,    71,    72,
      73,    44,    45,   152,   153,   124,   134,   143,   145,   144,
     146,    44,    45,   157,    34,    32,    13,   133,    82,   154,
      55,     0,   155
};

static const yytype_int16 yycheck[] =
{
      30,    29,     1,    33,     4,    60,    83,    43,    56,    17,
      51,    26,   136,    28,    42,    43,    35,    15,    16,    13,
      14,   145,    20,    21,     4,     5,    56,    25,    27,    35,
      71,    72,    73,   157,    12,    29,    30,    35,    36,    21,
      68,    69,    12,    22,    12,    23,    22,    31,    32,    97,
      86,    59,    28,    23,   109,    23,    27,    28,    86,   136,
      35,     6,    61,     8,     9,    10,    11,    97,   145,    22,
      15,    16,    15,    16,   102,    20,    21,    20,    21,    22,
     157,    35,    27,    83,    83,    25,   114,   117,   118,    22,
      35,    36,    35,    36,    21,    28,     0,   125,    23,     3,
       4,     5,     3,     4,     5,    27,    28,   137,   138,   139,
     140,   141,   142,   143,   144,     3,     4,     5,     6,    24,
       8,     9,    10,    11,    15,    16,    22,    15,    16,    20,
      21,    23,    20,    21,    25,    26,    15,    16,    26,    27,
      24,    20,    21,    21,    35,    36,    25,    35,    36,    15,
      16,    26,    21,    28,    20,    21,    35,    36,    22,    25,
      26,    15,    16,    15,    16,    27,    20,    21,    27,    35,
      36,    15,    16,    27,    74,    75,    20,    21,    17,    18,
      19,    35,    36,   141,   142,    27,    27,    33,    22,    34,
      27,    35,    36,     7,    26,    23,     4,   118,    61,   143,
      30,    -1,   144
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    38,    39,    40,    42,    47,    52,
      42,     0,    39,    52,    35,    48,    49,    35,    41,    43,
      21,    44,    27,    28,    44,    27,    28,    53,    54,    12,
      23,    35,    49,    12,    43,    42,    55,    56,    22,    15,
      16,    20,    21,    25,    35,    36,    50,    62,    64,    65,
      66,    67,    69,    70,    70,    75,    25,    45,    75,    35,
      22,    28,    25,    57,    62,    26,    50,    51,    21,    23,
      66,    17,    18,    19,    15,    16,    24,    26,    45,    46,
      44,    57,    56,    58,    22,    26,    28,    22,    62,    68,
      62,    66,    66,    66,    69,    69,    26,    28,     6,     8,
       9,    10,    11,    26,    27,    39,    42,    59,    60,    61,
      62,    64,    50,    22,    28,    24,    45,    21,    21,    27,
      27,    27,    62,    57,    27,    12,    62,    63,    70,    71,
      72,    73,    74,    63,    27,    62,    22,    13,    14,    29,
      30,    31,    32,    33,    34,    22,    27,    60,    70,    70,
      70,    70,    71,    71,    72,    73,    60,     7,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    38,    38,    39,    39,    40,    41,
      41,    42,    42,    43,    44,    44,    45,    45,    45,    46,
      46,    47,    48,    48,    49,    49,    50,    50,    50,    51,
      51,    53,    52,    54,    52,    55,    55,    56,    56,    57,
      58,    58,    59,    59,    60,    60,    60,    61,    60,    60,
      60,    60,    60,    60,    60,    60,    62,    63,    64,    64,
      65,    65,    65,    66,    66,    66,    66,    67,    67,    67,
      68,    68,    69,    69,    69,    69,    70,    70,    70,    71,
      71,    71,    71,    71,    72,    72,    72,    73,    73,    74,
      74,    75
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     1,     4,     1,
       3,     1,     1,     4,     4,     0,     1,     2,     3,     1,
       3,     3,     1,     3,     2,     4,     1,     2,     3,     1,
       3,     0,     7,     0,     6,     1,     3,     3,     2,     3,
       2,     0,     1,     1,     4,     2,     1,     0,     2,     7,
       5,     5,     2,     2,     3,     2,     1,     1,     1,     4,
       3,     1,     1,     1,     4,     3,     2,     1,     1,     1,
       1,     3,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if SYSYDEBUG

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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#else /* !SYSYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !SYSYDEBUG */


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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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
  case 2:
#line 41 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                            {
                (yyvsp[-1].ast)->son.push_back((yyvsp[0].ast));
                (yyval.ast) = (yyvsp[-1].ast);
            }
#line 1479 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 3:
#line 45 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                               {
                (yyvsp[-1].ast)->son.push_back((yyvsp[0].ast));
                (yyval.ast) = (yyvsp[-1].ast);
            }
#line 1488 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 4:
#line 49 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                   {
                root_sysy = new AST(_CompUnit);
                root_sysy->son.push_back((yyvsp[0].ast));
                (yyval.ast) = root_sysy;
            }
#line 1498 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 5:
#line 54 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                      {
                root_sysy = new AST(_CompUnit);
                root_sysy->son.push_back((yyvsp[0].ast));
                (yyval.ast) = root_sysy;
            }
#line 1508 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 6:
#line 61 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                    {
            AST *temp = new AST(_Decl);
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 1518 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 7:
#line 66 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                  {
            AST *temp = new AST(_Decl);
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 1528 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 8:
#line 73 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                            {
                AST *temp = new AST(_ConstDecl);
                temp->son.push_back((yyvsp[-3].ast));
                temp->son.push_back((yyvsp[-2].ast));
                temp->son.push_back((yyvsp[-1].ast));
                (yyval.ast) = temp;
            }
#line 1540 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 9:
#line 82 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                           {
                    AST *temp = new AST(_ConstDef_temp);
                    temp->son.push_back((yyvsp[0].ast));
                    (yyval.ast) = temp;
                }
#line 1550 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 10:
#line 87 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                             {
                    (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
                    (yyval.ast) = (yyvsp[-2].ast);
                }
#line 1559 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 11:
#line 93 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
              {
            AST *temp = new AST(_BType);
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 1569 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 12:
#line 98 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
               {
            AST *temp = new AST(_BType);
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 1579 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 13:
#line 105 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                                   {
                (yyvsp[-3].ast)->entry = new ENTRY_VAL((yyvsp[-3].ast)->id, symtable_ptr,(yyvsp[-2].ast)->val*4);
                ((ENTRY_VAL *)(yyvsp[-3].ast)->entry)->isConst = true;
                if((yyvsp[-2].ast)->son.size() != 0){
                    ((ENTRY_VAL *)(yyvsp[-3].ast)->entry)->isArray = true;
                    for(int i=0;i<(yyvsp[-2].ast)->son.size();i++){
                        ((ENTRY_VAL *)(yyvsp[-3].ast)->entry)->shape.push_back((yyvsp[-2].ast)->son[i]->val);
                    }
                }
                //还没想好怎么处理常量数组的赋值
                if((yyvsp[0].ast)->son.size() == 1 && (yyvsp[0].ast)->son[0]->type == _ConstExp){
                    ((ENTRY_VAL *)(yyvsp[-3].ast)->entry)->val = (yyvsp[0].ast)->son[0]->val;
                }
                AST *temp = new AST(_ConstDef);
                temp->son.push_back((yyvsp[-3].ast));
                temp->son.push_back((yyvsp[-2].ast));
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 1603 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 14:
#line 126 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                                 {
                    (yyvsp[-3].ast)->son.push_back((yyvsp[-1].ast));
                    (yyvsp[-3].ast)->val *= (yyvsp[-1].ast)->val;
                    (yyval.ast) = (yyvsp[-3].ast);
                }
#line 1613 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 15:
#line 131 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                  {
                    AST *temp = new AST(_ConstExp_temp);
                    temp->val = 1;
                    (yyval.ast) = temp;
                }
#line 1623 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 16:
#line 138 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                           {
                    AST *temp = new AST(_ConstInitVal);
                    temp->son.push_back((yyvsp[0].ast));
                    (yyval.ast) = temp;
                }
#line 1633 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 17:
#line 143 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                          {
                    AST *temp = new AST(_ConstInitVal);
                    (yyval.ast) = temp;
                }
#line 1642 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 18:
#line 147 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                            {
                    AST *temp = new AST(_ConstInitVal);
                    temp->son = (yyvsp[-1].ast)->son;
                    delete (yyvsp[-1].ast);
                    (yyval.ast) = temp;
                }
#line 1653 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 19:
#line 155 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                   {
                        AST *temp = new AST(_ConstInitVal_temp);
                        temp->son.push_back((yyvsp[0].ast));
                        (yyval.ast) = temp;
                    }
#line 1663 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 20:
#line 160 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                                         {
                        (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
                        (yyval.ast) = (yyvsp[-2].ast);
                    }
#line 1672 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 21:
#line 166 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                {
            AST *temp = new AST(_VarDecl);
            temp->son.push_back((yyvsp[-2].ast));
            temp->son.push_back((yyvsp[-1].ast));
            (yyval.ast) = temp;
        }
#line 1683 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 22:
#line 174 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                     {
                AST *temp = new AST(_VarDef_temp);
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 1693 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 23:
#line 179 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                     {
                (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
                (yyval.ast) = (yyvsp[-2].ast);
            }
#line 1702 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 24:
#line 185 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                              {
            (yyvsp[-1].ast)->entry = new ENTRY_VAL((yyvsp[-1].ast)->id, symtable_ptr,(yyvsp[0].ast)->val*4);
            if((yyvsp[0].ast)->son.size() != 0){
                ((ENTRY_VAL *)(yyvsp[-1].ast)->entry)->isArray = true;
                for(int i=0;i<(yyvsp[0].ast)->son.size();i++){
                    ((ENTRY_VAL *)(yyvsp[-1].ast)->entry)->shape.push_back((yyvsp[0].ast)->son[i]->val);
                }
            }
            AST *temp = new AST(_VarDef);
            temp->son.push_back((yyvsp[-1].ast));
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 1720 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 25:
#line 198 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                          {
            (yyvsp[-3].ast)->entry = new ENTRY_VAL((yyvsp[-3].ast)->id, symtable_ptr,(yyvsp[-2].ast)->val*4);
            if((yyvsp[-2].ast)->son.size() != 0){
                ((ENTRY_VAL *)(yyvsp[-3].ast)->entry)->isArray = true;
                for(int i=0;i<(yyvsp[-2].ast)->son.size();i++){
                    ((ENTRY_VAL *)(yyvsp[-3].ast)->entry)->shape.push_back((yyvsp[-2].ast)->son[i]->val);
                }
            }
            AST *temp = new AST(_VarDef);
            temp->son.push_back((yyvsp[-3].ast));
            temp->son.push_back((yyvsp[-2].ast));
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 1739 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 26:
#line 214 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
              {
            AST *temp = new AST(_InitVal);
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 1749 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 27:
#line 219 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                  {
            AST *temp = new AST(_InitVal);
            (yyval.ast) = temp;
        }
#line 1758 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 28:
#line 223 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                               {
            AST *temp = new AST(_InitVal);
            temp->son = (yyvsp[-1].ast)->son;
            delete (yyvsp[-1].ast);
            (yyval.ast) = temp;
        }
#line 1769 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 29:
#line 231 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                          {
                    AST *temp = new AST(_InitVal_temp);
                    temp->son.push_back((yyvsp[0].ast));
                    (yyval.ast) = temp;
                }
#line 1779 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 30:
#line 236 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                           {
                    (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
                    (yyval.ast) = (yyvsp[-2].ast);
                }
#line 1788 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 31:
#line 242 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                          {
            symtable_ptr = new TABLE("func", symtable_ptr);
            symtable_vector.push_back(symtable_ptr);
            NumberOfTemp = 0;
        }
#line 1798 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 32:
#line 246 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                 {
            symtable_ptr->space = (yyvsp[-5].ast)->id;
            bool isreturn = ((yyvsp[-6].ast)->son[0]->type == _INT);
            (yyvsp[-5].ast)->entry = new ENTRY_FUNC((yyvsp[-5].ast)->id, symtable_ptr->father,isreturn, symtable_ptr,NumberOfTemp,(yyvsp[-2].ast)->son.size());
            NumberOfTemp = 0;
            AST *temp = new AST(_FuncDef);
            temp->son.push_back((yyvsp[-6].ast));
            temp->son.push_back((yyvsp[-5].ast));
            temp->son.push_back((yyvsp[-2].ast));
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
            symtable_ptr = symtable_ptr->father;
        }
#line 1816 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 33:
#line 259 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                          {
            symtable_ptr = new TABLE("func", symtable_ptr);
            symtable_vector.push_back(symtable_ptr);
            NumberOfTemp = 0;
        }
#line 1826 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 34:
#line 263 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                     {
            symtable_ptr->space = (yyvsp[-4].ast)->id;
            bool isreturn = ((yyvsp[-5].ast)->son[0]->type == _INT);
            (yyvsp[-4].ast)->entry = new ENTRY_FUNC((yyvsp[-4].ast)->id, symtable_ptr->father, isreturn, symtable_ptr,NumberOfTemp,0);
            NumberOfTemp = 0;
            AST *temp = new AST(_FuncDef);
            temp->son.push_back((yyvsp[-5].ast));
            temp->son.push_back((yyvsp[-4].ast));
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
            symtable_ptr = symtable_ptr->father;
        }
#line 1843 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 35:
#line 277 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                         {
                AST *temp = new AST(_FuncFParams);
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 1853 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 36:
#line 282 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                         {
                (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
                (yyval.ast) = (yyvsp[-2].ast);
            }
#line 1862 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 37:
#line 288 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                         {
                (yyvsp[-1].ast)->entry = new ENTRY_VAL((yyvsp[-1].ast)->id, symtable_ptr,(yyvsp[0].ast)->val*4);
                //((ENTRY_VAL *)$2->entry)->shape.push_back(1);
                if((yyvsp[0].ast)->son.size() != 0){
                    for(int i=0;i<(yyvsp[0].ast)->son.size();i++){
                        ((ENTRY_VAL *)(yyvsp[-1].ast)->entry)->shape.push_back((yyvsp[0].ast)->son[i]->val);
                    }
                }
                ((ENTRY_VAL *)(yyvsp[-1].ast)->entry)->isArray = true;
                ((ENTRY_VAL *)(yyvsp[-1].ast)->entry)->isParam = true;
                AST *temp = new AST(_FuncFParam);
                temp->son.push_back((yyvsp[-2].ast));
                temp->son.push_back((yyvsp[-1].ast));
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 1883 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 38:
#line 304 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                           {
                (yyvsp[0].ast)->entry = new ENTRY_VAL((yyvsp[0].ast)->id, symtable_ptr,4);
                ((ENTRY_VAL *)(yyvsp[0].ast)->entry)->isParam = true;
                AST *temp = new AST(_FuncFParam);
                temp->son.push_back((yyvsp[-1].ast));
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 1896 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 39:
#line 314 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                 {
            AST *temp = new AST(_Block);
            temp->son = (yyvsp[-1].ast)->son;
            delete (yyvsp[-1].ast);
            (yyval.ast) = temp;
        }
#line 1907 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 40:
#line 322 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                           {
                    (yyvsp[-1].ast)->son.push_back((yyvsp[0].ast));
                    (yyval.ast) = (yyvsp[-1].ast);
                }
#line 1916 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 41:
#line 326 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                  {
                    AST *temp = new AST(_BlockItem_temp);
                    (yyval.ast) = temp;
                }
#line 1925 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 42:
#line 332 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                   {
                AST *temp = new AST(_BlockItem);
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 1935 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 43:
#line 337 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                   {
                AST *temp = new AST(_BlockItem);
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 1945 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 44:
#line 344 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                           {
            if((yyvsp[-3].ast)->son.size() == 2){
                NumberOfTemp++;
            } else if((yyvsp[-3].ast)->son.size() > 2){
                NumberOfTemp += 2;
            }
            AST *temp = new AST(_Stmt);
            temp->son.push_back((yyvsp[-3].ast));
            temp->son.push_back((yyvsp[-1].ast));
            (yyval.ast) = temp;
        }
#line 1961 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 45:
#line 355 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                  {
            AST *temp = new AST(_Stmt);
            temp->son.push_back((yyvsp[-1].ast));
            (yyval.ast) = temp;
        }
#line 1971 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 46:
#line 360 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
              {
            AST *temp = new AST(_Stmt);
            (yyval.ast) = temp;
        }
#line 1980 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 47:
#line 364 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
          {
            symtable_ptr = new TABLE("block", symtable_ptr);
            symtable_vector.push_back(symtable_ptr);
        }
#line 1989 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 48:
#line 367 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                {
            symtable_ptr = symtable_ptr->father;
            AST *temp = new AST(_Stmt);
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2000 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 49:
#line 373 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                         {
            AST *temp = new AST(_Stmt);
            temp->son.push_back((yyvsp[-6].ast));
            temp->son.push_back((yyvsp[-4].ast));
            temp->son.push_back((yyvsp[-2].ast));
            temp->son.push_back((yyvsp[-1].ast));
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2014 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 50:
#line 382 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                               {
            AST *temp = new AST(_Stmt);
            temp->son.push_back((yyvsp[-4].ast));
            temp->son.push_back((yyvsp[-2].ast));
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2026 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 51:
#line 389 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                  {
            AST *temp = new AST(_Stmt);
            temp->son.push_back((yyvsp[-4].ast));
            temp->son.push_back((yyvsp[-2].ast));
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2038 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 52:
#line 396 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                    {
            AST *temp = new AST(_Stmt);
            temp->son.push_back((yyvsp[-1].ast));
            (yyval.ast) = temp;
        }
#line 2048 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 53:
#line 401 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                       {
            AST *temp = new AST(_Stmt);
            temp->son.push_back((yyvsp[-1].ast));
            (yyval.ast) = temp;
        }
#line 2058 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 54:
#line 406 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                         {
            AST *temp = new AST(_Stmt);
            temp->son.push_back((yyvsp[-2].ast));
            temp->son.push_back((yyvsp[-1].ast));
            (yyval.ast) = temp;
        }
#line 2069 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 55:
#line 412 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                     {
            AST *temp = new AST(_Stmt);
            temp->son.push_back((yyvsp[-1].ast));
            (yyval.ast) = temp;
        }
#line 2079 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 56:
#line 419 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
             {
        AST *temp = new AST(_Exp);
        if((yyvsp[0].ast)->son.size() > 1){
            NumberOfTemp++;
        }
        temp->val = (yyvsp[0].ast)->val;
        temp->isint = (yyvsp[0].ast)->isint;
        temp->son.push_back((yyvsp[0].ast));
        (yyval.ast) = temp;
    }
#line 2094 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 57:
#line 431 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                 {
            AST *temp = new AST(_Cond);
            temp->isint = (yyvsp[0].ast)->isint;
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2105 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 58:
#line 439 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                {
            if(symtable_ptr->Find(true,(yyvsp[0].ast)->id,true)){
                (yyvsp[0].ast)->entry = symtable_ptr->FindAndReturn(true,(yyvsp[0].ast)->id);
            } else{
                yyerror("cite non-decleared variable\n");
            }
            AST *temp = new AST(_LVal);
            temp->val = ((ENTRY_VAL *)(yyvsp[0].ast)->entry)->val;
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2121 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 59:
#line 450 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                           {
            (yyvsp[-3].ast)->son.push_back((yyvsp[-1].ast));
            (yyval.ast) = (yyvsp[-3].ast);
        }
#line 2130 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 60:
#line 456 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                          {
                AST *temp = new AST(_PrimaryExp);
                temp->val = (yyvsp[-1].ast)->val;
                temp->isint = (yyvsp[-1].ast)->isint;
                temp->son.push_back((yyvsp[-1].ast));
                (yyval.ast) = temp;
            }
#line 2142 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 61:
#line 463 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                   {
                AST *temp = new AST(_PrimaryExp);
                if((yyvsp[0].ast)->son.size() == 2){
                    NumberOfTemp++;
                } else if((yyvsp[0].ast)->son.size() > 2){
                    NumberOfTemp += 2;
                }
                temp->val = (yyvsp[0].ast)->val;
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 2158 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 62:
#line 474 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                        {
                AST *temp = new AST(_PrimaryExp);
                temp->val = (yyvsp[0].ast)->val;
                temp->isint = true;
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 2170 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 63:
#line 483 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                         {
                AST *temp = new AST(_UnaryExp);
                temp->val = (yyvsp[0].ast)->val;
                temp->isint = (yyvsp[0].ast)->isint;
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 2182 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 64:
#line 490 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                        {
                NumberOfTemp++;
                AST *temp = new AST(_UnaryExp);
                temp->son.push_back((yyvsp[-3].ast));
                temp->son.push_back((yyvsp[-1].ast));
                (yyval.ast) = temp;
            }
#line 2194 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 65:
#line 497 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                            {
                NumberOfTemp++;
                AST *temp = new AST(_UnaryExp);
                temp->lineno = lineno;
                temp->son.push_back((yyvsp[-2].ast));
                (yyval.ast) = temp;
            }
#line 2206 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 66:
#line 504 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                               {
                AST *temp = new AST(_UnaryExp);
                if((yyvsp[-1].ast)->son[0]->op == '-'){
                    temp->val = 0-((yyvsp[0].ast)->val);
                    temp->isint = (yyvsp[0].ast)->isint;
                } else if((yyvsp[-1].ast)->son[0]->op == '!'){
                    if((yyvsp[0].ast)->val != 0){
                        temp->val = 0;
                    } else{
                        temp->val = 1;
                    }
                }
                temp->son.push_back((yyvsp[-1].ast));
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 2227 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 67:
#line 522 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
              {
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2237 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 68:
#line 527 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
              {
            NumberOfTemp++;
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2248 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 69:
#line 533 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
              {
            NumberOfTemp++;
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2259 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 70:
#line 541 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                  {
                AST *temp = new AST(_FuncRParams);
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 2269 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 71:
#line 546 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                                  {
                (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
                (yyval.ast) = (yyvsp[-2].ast);
            }
#line 2278 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 72:
#line 552 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                   {
            AST *temp = new AST(_MulExp);
            temp->val = (yyvsp[0].ast)->val;
            temp->isint = (yyvsp[0].ast)->isint;
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2290 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 73:
#line 559 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                              {
            (yyvsp[-2].ast)->val = (yyvsp[-2].ast)->val * (yyvsp[0].ast)->val;
            (yyvsp[-2].ast)->isint = (yyvsp[-2].ast)->isint && (yyvsp[0].ast)->isint;
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2302 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 74:
#line 566 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                              {
            if((yyvsp[0].ast)->val != 0){
                (yyvsp[-2].ast)->val = (yyvsp[-2].ast)->val / (yyvsp[0].ast)->val;
                (yyvsp[-2].ast)->isint = (yyvsp[-2].ast)->isint && (yyvsp[0].ast)->isint;
            }
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2316 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 75:
#line 575 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                              {
            if((yyvsp[0].ast)->val != 0){
                (yyvsp[-2].ast)->val = (yyvsp[-2].ast)->val % (yyvsp[0].ast)->val;
                (yyvsp[-2].ast)->isint = (yyvsp[-2].ast)->isint && (yyvsp[0].ast)->isint;
            }
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2330 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 76:
#line 586 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                 {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            AST *temp = new AST(_AddExp);
            temp->val = (yyvsp[0].ast)->val;
            temp->isint = (yyvsp[0].ast)->isint;
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2345 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 77:
#line 596 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                            {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            (yyvsp[-2].ast)->val = (yyvsp[-2].ast)->val + (yyvsp[0].ast)->val;
            (yyvsp[-2].ast)->isint = (yyvsp[-2].ast)->isint && (yyvsp[0].ast)->isint;
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2360 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 78:
#line 606 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                            {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            (yyvsp[-2].ast)->val = (yyvsp[-2].ast)->val - (yyvsp[0].ast)->val;
            (yyvsp[-2].ast)->isint = (yyvsp[-2].ast)->isint && (yyvsp[0].ast)->isint;
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2375 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 79:
#line 618 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                 {
            AST *temp = new AST(_RelExp);
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            temp->isint = (yyvsp[0].ast)->isint;
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2389 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 80:
#line 627 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                            {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            (yyvsp[-2].ast)->isint = false;
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2403 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 81:
#line 636 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                            {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            (yyvsp[-2].ast)->isint = false;
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2417 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 82:
#line 645 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                           {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            (yyvsp[-2].ast)->isint = false;
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2431 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 83:
#line 654 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                           {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            (yyvsp[-2].ast)->isint = false;
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2445 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 84:
#line 665 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                 {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            AST *temp = new AST(_EqExp);
            temp->isint = (yyvsp[0].ast)->isint;
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2459 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 85:
#line 674 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                          {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            (yyvsp[-2].ast)->isint = false;
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2473 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 86:
#line 683 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                          {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            (yyvsp[-2].ast)->isint = false;
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2487 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 87:
#line 694 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            AST *temp = new AST(_LAndExp);
            temp->isint = (yyvsp[0].ast)->isint;
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2501 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 88:
#line 703 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                            {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            (yyvsp[-2].ast)->isint = false;
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2515 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 89:
#line 714 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                  {
            AST *temp = new AST(_LOrExp);
            temp->isint = (yyvsp[0].ast)->isint;
            temp->son.push_back((yyvsp[0].ast));
            (yyval.ast) = temp;
        }
#line 2526 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 90:
#line 720 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                            {
            if((yyvsp[0].ast)->son.size() > 1){
                NumberOfTemp++;
            }
            (yyvsp[-2].ast)->isint = false;
            (yyvsp[-2].ast)->son.push_back((yyvsp[-1].ast));
            (yyvsp[-2].ast)->son.push_back((yyvsp[0].ast));
            (yyval.ast) = (yyvsp[-2].ast);
        }
#line 2540 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;

  case 91:
#line 731 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
                     {
                AST *temp = new AST(_ConstExp);
                if((yyvsp[0].ast)->son.size() > 1){
                    NumberOfTemp++;
                }
                temp->val = (yyvsp[0].ast)->val;
                temp->isint = (yyvsp[0].ast)->isint;
                temp->son.push_back((yyvsp[0].ast));
                (yyval.ast) = temp;
            }
#line 2555 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"
    break;


#line 2559 "/home/ryj/compiler/mycompilertemp/mycompiler/build/parser.tab.cpp"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 743 "/home/ryj/compiler/mycompilertemp/mycompiler/src/parser.y"
