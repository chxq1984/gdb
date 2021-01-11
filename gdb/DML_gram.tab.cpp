/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "DML_gram.y"

#include "Node.h"
#include "DML_gram.tab.h"

extern int yylex();
extern int yyerror(const char * format,...);

struct yy_buffer_state;
#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif
extern void yy_switch_to_buffer (YY_BUFFER_STATE new_buffer);
extern YY_BUFFER_STATE yy_scan_string ( const char *yy_str  );


/* Line 371 of yacc.c  */
#line 85 "DML_gram.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "DML_gram.tab.h".  */
#ifndef YY_YY_DML_GRAM_TAB_H_INCLUDED
# define YY_YY_DML_GRAM_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LF = 258,
     RF = 259,
     ST = 260,
     FM = 261,
     WH = 262,
     UPT = 263,
     DEL = 264,
     IST = 265,
     VAL = 266,
     INTO = 267,
     SET = 268,
     WHSPLIT = 269,
     T_LT = 270,
     T_LE = 271,
     T_GT = 272,
     T_GE = 273,
     T_EQ = 274,
     T_NE = 275,
     IN = 276,
     ORDER = 277,
     BY = 278,
     ORTYPE = 279,
     DISTINCT = 280,
     AGGRET = 281,
     EXIT = 282,
     NAME = 283,
     NUMBER = 284,
     PARA_STRING = 285,
     SUBQUERY = 286,
     NATURAL = 287,
     JOIN = 288,
     MULTI = 289,
     EXEC = 290,
     DISCARD = 291
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 19 "DML_gram.y"

	Attribute *attribute;
	OrderNode *orderNode;
	Relation *relation;
	Operator *soperator;
	SelList	*selList;
	FromList *fromList;
	Condition *condision;
	OrderList *orderList;
	GroupList *groupList;
	Query *query;
	Number* rNumber;
	ParaString* pString;
	
	Name* name;
    vector<Name*>* nameList;
    
	string* text;
	int type;
	
	Insert* insert;
	vector<string>* values;
	
	Delete* del;
	
	Update* upd;
	string* attr_index[2];
	map<string, string>* attr_indexs;

	PhyPlanNode* phyNode;
	vector<PhyPlanNode*>* phyNodes; 

	NodeStorage* nodestorage;


/* Line 387 of yacc.c  */
#line 200 "DML_gram.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_DML_GRAM_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 228 "DML_gram.tab.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   104

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNRULES -- Number of states.  */
#define YYNSTATES  113

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
       2,     2,    38,     2,    39,     2,    40,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
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
      35,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    16,    20,    24,
      26,    29,    31,    33,    35,    37,    40,    42,    47,    53,
      56,    59,    62,    65,    67,    69,    72,    75,    80,    83,
      85,    89,    93,    95,    97,   101,   103,   107,   109,   113,
     115,   118,   120,   124,   129,   131,   136,   139,   141,   145,
     153,   155,   159,   161,   165,   169,   171,   173,   177,   179,
     181,   183,   185,   187,   189
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    44,    -1,    48,    37,    -1,    45,    37,
      -1,    46,    37,    -1,    49,    -1,    34,    47,    35,    -1,
      34,    47,    36,    -1,    48,    -1,    48,    47,    -1,    50,
      -1,    51,    -1,    52,    -1,    67,    -1,    27,    37,    -1,
      53,    -1,     9,     6,    28,    57,    -1,     8,    28,    13,
      69,    57,    -1,    54,    56,    -1,    53,    57,    -1,    53,
      61,    -1,     5,    55,    -1,    64,    -1,    38,    -1,    25,
      55,    -1,     6,    64,    -1,     6,     3,    53,     4,    -1,
       7,    58,    -1,    59,    -1,    59,    14,    58,    -1,    65,
      73,    60,    -1,    65,    -1,    29,    -1,     3,    53,     4,
      -1,    72,    -1,    22,    23,    62,    -1,    63,    -1,    63,
      39,    62,    -1,    66,    -1,    66,    24,    -1,    65,    -1,
      65,    39,    64,    -1,    65,    32,    33,    64,    -1,    66,
      -1,    26,     3,    66,     4,    -1,    65,    28,    -1,    28,
      -1,    28,    40,    28,    -1,    10,    12,    28,    11,     3,
      68,     4,    -1,    71,    -1,    71,    39,    68,    -1,    70,
      -1,    70,    39,    69,    -1,    28,    19,    71,    -1,    72,
      -1,    29,    -1,    41,    28,    41,    -1,    15,    -1,    16,
      -1,    17,    -1,    18,    -1,    19,    -1,    20,    -1,    21,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    90,    90,    91,    95,    99,   106,   110,   129,   136,
     141,   149,   154,   158,   162,   169,   176,   203,   234,   267,
     273,   278,   287,   294,   304,   311,   319,   329,   337,   345,
     350,   362,   396,   403,   409,   416,   425,   432,   438,   446,
     452,   461,   467,   472,   483,   487,   493,   502,   508,   519,
     543,   548,   556,   562,   571,   580,   584,   591,   600,   604,
     608,   612,   616,   620,   624
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LF", "RF", "ST", "FM", "WH", "UPT",
  "DEL", "IST", "VAL", "INTO", "SET", "WHSPLIT", "T_LT", "T_LE", "T_GT",
  "T_GE", "T_EQ", "T_NE", "IN", "ORDER", "BY", "ORTYPE", "DISTINCT",
  "AGGRET", "EXIT", "NAME", "NUMBER", "PARA_STRING", "SUBQUERY", "NATURAL",
  "JOIN", "MULTI", "EXEC", "DISCARD", "';'", "'*'", "','", "'.'", "'\\''",
  "$accept", "command", "utility", "dowork", "cancelwork", "dmls", "dml",
  "exit", "query", "delete", "update", "stmt", "st_list", "st_nodes",
  "fm_list", "wh_list", "whname_list", "whname", "whvalue", "order",
  "order_list", "order_node", "name_list", "table_attr", "attr_name",
  "insert", "value_list", "set_list", "set_value", "insert_value",
  "para_string", "op", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    59,    42,    44,
      46,    39
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    43,    43,    43,    44,    45,    46,    47,
      47,    48,    48,    48,    48,    49,    50,    51,    52,    53,
      53,    53,    54,    55,    55,    55,    56,    56,    57,    58,
      58,    59,    60,    60,    60,    60,    61,    62,    62,    63,
      63,    64,    64,    64,    65,    65,    65,    66,    66,    67,
      68,    68,    69,    69,    70,    71,    71,    72,    73,    73,
      73,    73,    73,    73,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     1,     3,     3,     1,
       2,     1,     1,     1,     1,     2,     1,     4,     5,     2,
       2,     2,     2,     1,     1,     2,     2,     4,     2,     1,
       3,     3,     1,     1,     3,     1,     3,     1,     3,     1,
       2,     1,     3,     4,     1,     4,     2,     1,     3,     7,
       1,     3,     1,     3,     3,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     2,     0,
       0,     0,     6,    11,    12,    13,    16,     0,    14,     0,
       0,    47,    24,    22,    23,    41,    44,     0,     0,     0,
      15,     0,     9,     1,     4,     5,     3,     0,     0,    20,
      21,     0,    19,    25,     0,     0,    46,     0,     0,     0,
       0,     0,     7,     8,    10,    28,    29,     0,     0,     0,
      26,     0,    48,     0,    42,     0,     0,    52,    17,     0,
       0,    58,    59,    60,    61,    62,    63,    64,     0,    36,
      37,    39,     0,    45,    43,     0,    18,     0,     0,    30,
       0,    33,     0,    31,    32,    35,     0,    40,    27,    56,
      54,    55,    53,     0,    50,     0,     0,    38,    49,     0,
      34,    57,    51
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    31,    32,    12,    13,    14,
      15,    16,    17,    23,    42,    39,    55,    56,    93,    40,
      79,    80,    24,    25,    26,    18,   103,    66,    67,   104,
     101,    78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -56
static const yytype_int8 yypact[] =
{
       2,    25,   -19,     7,    -7,   -21,    52,    30,   -56,   -11,
       4,    18,   -56,   -56,   -56,   -56,    10,    53,   -56,    25,
      66,    31,   -56,   -56,   -56,    26,   -56,    57,    44,    45,
     -56,    32,    52,   -56,   -56,   -56,   -56,    38,    51,   -56,
     -56,     5,   -56,   -56,    47,    48,   -56,    46,    38,    49,
      71,    69,   -56,   -56,   -56,   -56,    67,    28,    47,    77,
     -56,    79,   -56,    38,   -56,    65,    71,    50,   -56,    82,
      38,   -56,   -56,   -56,   -56,   -56,   -56,   -56,    -1,   -56,
      54,    62,    16,   -56,   -56,   -23,   -56,    49,   -23,   -56,
      77,   -56,    59,   -56,    60,   -56,    47,   -56,   -56,   -56,
     -56,   -56,   -56,    86,    55,    17,    56,   -56,   -56,   -23,
     -56,   -56,   -56
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,   -56,   -56,   -56,    63,    91,   -56,   -56,   -56,
     -56,   -55,   -56,    73,   -56,   -47,    29,   -56,   -56,   -56,
       0,   -56,   -26,   -36,   -44,   -56,    -9,    11,   -56,    19,
      23,   -56
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      61,    57,    90,    68,    82,    29,    99,     1,    59,    27,
       2,     3,     4,    28,    81,    60,    30,    37,    92,    86,
      98,   110,    64,    37,    37,    20,    34,    21,    91,     5,
      33,    20,    38,    21,    57,   105,     6,    84,    38,    38,
      92,    35,    94,    71,    72,    73,    74,    75,    76,    77,
      19,    20,    81,    21,    46,    36,    46,     1,    47,    41,
       2,     3,     4,    22,    20,    48,    21,    52,    53,    44,
      49,    45,    50,    51,    58,    21,    62,    65,    37,    63,
      69,    70,     1,    83,    85,    88,    97,   106,    46,    87,
     108,    11,    43,    96,   109,    54,   107,   111,   102,    89,
     112,    95,     0,     0,   100
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-56)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      44,    37,     3,    50,    59,    12,    29,     5,     3,    28,
       8,     9,    10,     6,    58,    41,    37,     7,    41,    66,
       4,     4,    48,     7,     7,    26,    37,    28,    29,    27,
       0,    26,    22,    28,    70,    90,    34,    63,    22,    22,
      41,    37,    78,    15,    16,    17,    18,    19,    20,    21,
      25,    26,    96,    28,    28,    37,    28,     5,    32,     6,
       8,     9,    10,    38,    26,    39,    28,    35,    36,     3,
      13,    40,    28,    28,    23,    28,    28,    28,     7,    33,
      11,    14,     5,     4,    19,     3,    24,    28,    28,    39,
       4,     0,    19,    39,    39,    32,    96,    41,    87,    70,
     109,    78,    -1,    -1,    85
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     8,     9,    10,    27,    34,    43,    44,    45,
      46,    48,    49,    50,    51,    52,    53,    54,    67,    25,
      26,    28,    38,    55,    64,    65,    66,    28,     6,    12,
      37,    47,    48,     0,    37,    37,    37,     7,    22,    57,
      61,     6,    56,    55,     3,    40,    28,    32,    39,    13,
      28,    28,    35,    36,    47,    58,    59,    65,    23,     3,
      64,    66,    28,    33,    64,    28,    69,    70,    57,    11,
      14,    15,    16,    17,    18,    19,    20,    21,    73,    62,
      63,    66,    53,     4,    64,    19,    57,    39,     3,    58,
       3,    29,    41,    60,    65,    72,    39,    24,     4,    29,
      71,    72,    69,    68,    71,    53,    28,    62,     4,    39,
       4,    41,    68
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
/* Line 1792 of yacc.c  */
#line 92 "DML_gram.y"
    {
		YYACCEPT;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 96 "DML_gram.y"
    {
		YYACCEPT;
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 100 "DML_gram.y"
    {
		YYACCEPT;
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 111 "DML_gram.y"
    {
		//dmls内即为各物理计划树根节点
		if(PhysicalPlan::canFinish(*(yyvsp[(2) - (3)].phyNodes)))
		{
			//说明可以完成事务
			for (PhyPlanNode* root : *(yyvsp[(2) - (3)].phyNodes)) 
			{
				//调用执行函数
			}
		}
		else
		{
			cout<<"违反事务"<<endl;
		}
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 130 "DML_gram.y"
    {
		cout<<"已取消事务"<<endl;
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 137 "DML_gram.y"
    {	
		(yyval.phyNodes) = new vector<PhyPlanNode*>;
		(yyval.phyNodes)->push_back((yyvsp[(1) - (1)].phyNode));
	}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 142 "DML_gram.y"
    {
		(yyvsp[(2) - (2)].phyNodes)->push_back((yyvsp[(1) - (2)].phyNode));
		(yyval.phyNodes) = (yyvsp[(2) - (2)].phyNodes);
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 150 "DML_gram.y"
    {
		//$$即为物理计划根节点,此处调用执行函数即可
		(yyval.phyNode) = (yyvsp[(1) - (1)].phyNode);
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 155 "DML_gram.y"
    {
		(yyval.phyNode) = (yyvsp[(1) - (1)].phyNode);
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 159 "DML_gram.y"
    {
		(yyval.phyNode) = (yyvsp[(1) - (1)].phyNode);
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 163 "DML_gram.y"
    {
		(yyval.phyNode) = (yyvsp[(1) - (1)].phyNode);
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 170 "DML_gram.y"
    {
		YYACCEPT;
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 177 "DML_gram.y"
    {
		Query* query = (yyvsp[(1) - (1)].query);
		query->showInfo();

		
		SqlGrammer sqlgrammer;
		sqlgrammer.root = query->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		sqlgrammer.optimiza();
		cout << "-------------------------------"<<endl;

		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		(yyval.phyNode) = physicalPlan.root;

		
		cout<<endl;
		//YYACCEPT;
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 204 "DML_gram.y"
    {
		Delete * del = new Delete();
		del->tableName = *(yyvsp[(3) - (4)].text);
		del->condition = (yyvsp[(4) - (4)].condision);
		del->showInfo();
		
		//$$ = new Delete();
		//$$->tableName = $3;
		//$$->condition = $4;
		//$$->showInfo();
		
		SqlGrammer sqlgrammer;
		//sqlgrammer.root = $$->transform2Grammer();
		sqlgrammer.root = del->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		cout << "-------------------------------"<<endl;
		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		(yyval.phyNode) = physicalPlan.root;
		
		cout<<endl;
		//YYACCEPT;
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 235 "DML_gram.y"
    {
		Update* upt = new Update();
		upt->tableName = *(yyvsp[(2) - (5)].text);
		upt->attr_indexs = *(yyvsp[(4) - (5)].attr_indexs);
		upt->condition = (yyvsp[(5) - (5)].condision);
		upt->showInfo();
		
		//$$ = new Update();
		//$$->tableName = $2;
		//$$->attr_indexs = $4;
		//$$->condition = $5;
		//$$->showInfo();
		
		SqlGrammer sqlgrammer;
		//sqlgrammer.root = $$->transform2Grammer();
		sqlgrammer.root = upt->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		cout << "-------------------------------"<<endl;
		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		(yyval.phyNode) = physicalPlan.root;
		
		cout<<endl;
		//YYACCEPT;
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 268 "DML_gram.y"
    {
		(yyval.query) = new Query();
		(yyval.query)->selList = (yyvsp[(1) - (2)].selList);
		(yyval.query)->fromList = (yyvsp[(2) - (2)].fromList);
	}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 274 "DML_gram.y"
    {
		(yyvsp[(1) - (2)].query)->condition = (yyvsp[(2) - (2)].condision);
		(yyval.query) = (yyvsp[(1) - (2)].query);
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 279 "DML_gram.y"
    {
		(yyvsp[(1) - (2)].query)->orderList = (yyvsp[(2) - (2)].orderList);
		(yyval.query) = (yyvsp[(1) - (2)].query);
	}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 288 "DML_gram.y"
    {
		(yyval.selList) = (yyvsp[(2) - (2)].selList);
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 295 "DML_gram.y"
    {
		(yyval.selList) = new SelList();
		for(int m=0;m<(yyvsp[(1) - (1)].nameList)->size();m++){
			Attribute* attr = new Attribute();
			Name* name = (yyvsp[(1) - (1)].nameList)->at(m);
			attr->setName(name);
			(yyval.selList)->addAttribute(attr);
		}
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 305 "DML_gram.y"
    {
		(yyval.selList) = new SelList();
		Attribute* attr = new Attribute();
		attr->attrName = "*";
		(yyval.selList)->addAttribute(attr);
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 312 "DML_gram.y"
    {
        cout<<"distinct，暂不进行处理"<<endl;
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 320 "DML_gram.y"
    {
		(yyval.fromList) = new FromList();
		for(int m=0;m<(yyvsp[(2) - (2)].nameList)->size();m++){
			Relation* rl = new Relation();
			rl->relationName = (yyvsp[(2) - (2)].nameList)->at(m)->attrName;
			rl->alias = (yyvsp[(2) - (2)].nameList)->at(m)->alias;
			(yyval.fromList)->addNode(rl);
		}
	}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 330 "DML_gram.y"
    {
        cout<<"子查询，暂不进行处理"<<endl;
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 338 "DML_gram.y"
    {
		(yyval.condision) = (yyvsp[(2) - (2)].condision);
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 346 "DML_gram.y"
    {
        //可能有多个condition
		(yyval.condision) = (yyvsp[(1) - (1)].condision);
	}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 351 "DML_gram.y"
    {
		Condition* condition = new Condition();
		condition->lCnode = (yyvsp[(3) - (3)].condision);

		condition->soperator = (yyvsp[(2) - (3)].soperator);
		condition->rCnode = (yyvsp[(1) - (3)].condision);
		(yyval.condision) = condition;
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 363 "DML_gram.y"
    {
        //【】op【】:a=b
		Condition* condition = new Condition();
		(yyval.condision) = condition;
		Attribute* lattr = new Attribute();
		lattr->setName((yyvsp[(1) - (3)].name));
		condition->Lattr = lattr;

		int ttype = (yyvsp[(3) - (3)].nodestorage)->type;
		if(ttype == NUMBER){
            
			condition->rNumber = (yyvsp[(3) - (3)].nodestorage)->rNumber;
            
		}else if(ttype == PARA_STRING){
			
			condition->pString = (yyvsp[(3) - (3)].nodestorage)->pString;
			
		}else if(ttype == NAME){

			Attribute* rattr = new Attribute();
			rattr->setName((yyvsp[(3) - (3)].nodestorage)->name);
			condition->Rattr = rattr;
            
		}else if(ttype == SUBQUERY){
            //子查询
            condition->query = (yyvsp[(3) - (3)].nodestorage)->query;
		}
		condition->soperator = (yyvsp[(2) - (3)].soperator);
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 397 "DML_gram.y"
    {
        //where a=【】,可为表名,数字，子查询
		(yyval.nodestorage) = new NodeStorage();
		(yyval.nodestorage)->name = (yyvsp[(1) - (1)].name);
		(yyval.nodestorage)->type = NAME;
	}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 404 "DML_gram.y"
    {
		(yyval.nodestorage) = new NodeStorage();
		(yyval.nodestorage)->rNumber = (yyvsp[(1) - (1)].rNumber);
		(yyval.nodestorage)->type = NUMBER;
	}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 410 "DML_gram.y"
    {
		(yyval.nodestorage) = new NodeStorage();
		(yyval.nodestorage)->query = (yyvsp[(2) - (3)].query);
		(yyval.nodestorage)->type = SUBQUERY;

	}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 417 "DML_gram.y"
    {
		(yyval.nodestorage) = new NodeStorage();
		(yyval.nodestorage)->pString = (yyvsp[(1) - (1)].pString);
		(yyval.nodestorage)->type = PARA_STRING;
	}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 426 "DML_gram.y"
    {
		(yyval.orderList) = (yyvsp[(3) - (3)].orderList);
	}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 433 "DML_gram.y"
    {
		//可能有多个排序节点
		(yyval.orderList) = new OrderList();
		(yyval.orderList)->addOrderNode((yyvsp[(1) - (1)].orderNode));
	}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 439 "DML_gram.y"
    {
		(yyvsp[(3) - (3)].orderList)->addOrderNode((yyvsp[(1) - (3)].orderNode));
		(yyval.orderList) = (yyvsp[(3) - (3)].orderList);
	}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 447 "DML_gram.y"
    {
		//排序节点,可带rule也可不带
		(yyval.orderNode) = new OrderNode();
		(yyval.orderNode)->attr.setName((yyvsp[(1) - (1)].name)->attrName,(yyvsp[(1) - (1)].name)->tableName);
	}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 453 "DML_gram.y"
    {
		(yyval.orderNode) = new OrderNode();
		(yyval.orderNode)->attr.setName((yyvsp[(1) - (2)].name)->attrName,(yyvsp[(1) - (2)].name)->tableName);
		(yyval.orderNode)->rule = *(yyvsp[(2) - (2)].text);
	}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 462 "DML_gram.y"
    {
		//名字列表
		(yyval.nameList) = new vector<Name*>;
   		(yyval.nameList)->push_back((yyvsp[(1) - (1)].name));
   }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 468 "DML_gram.y"
    {
		(yyvsp[(3) - (3)].nameList)->push_back((yyvsp[(1) - (3)].name));
   		(yyval.nameList) = (yyvsp[(3) - (3)].nameList);
   }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 473 "DML_gram.y"
    {
		Name *name = new Name();
		name->attrName = "@natural@";//@natural@作为指示符
        (yyvsp[(4) - (4)].nameList)->push_back(name);
        (yyvsp[(4) - (4)].nameList)->push_back((yyvsp[(1) - (4)].name));
        (yyval.nameList) = (yyvsp[(4) - (4)].nameList);
   }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 484 "DML_gram.y"
    {
		(yyval.name) = (yyvsp[(1) - (1)].name);
	}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 488 "DML_gram.y"
    {
		Name* name = (yyvsp[(3) - (4)].name);
		name->aggFunc = *(yyvsp[(1) - (4)].text);
		(yyval.name) = name;
	}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 494 "DML_gram.y"
    {
		Name* name = (yyvsp[(1) - (2)].name);
		name->alias = *(yyvsp[(2) - (2)].text);
		(yyval.name) = name;
	}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 503 "DML_gram.y"
    {
		Name* name = new Name();
		name->attrName = *(yyvsp[(1) - (1)].text);
		(yyval.name) = name;
	}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 509 "DML_gram.y"
    {
		Name* name = new Name();
		name->tableName = *(yyvsp[(1) - (3)].text);
		name->attrName = *(yyvsp[(3) - (3)].text);

		(yyval.name) = name;
	}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 520 "DML_gram.y"
    {
		Insert * insert = new Insert();
		insert->attributes = *(yyvsp[(6) - (7)].values);
		insert->tableName = *(yyvsp[(3) - (7)].text);
		insert->showInfo();
		
		SqlGrammer sqlgrammer;
		sqlgrammer.root = insert->transform2Grammer();
		cout << "-------------------------------"<<endl;
		sqlgrammer.showInfo();
		cout << "-------------------------------"<<endl;
		
		PhysicalPlan physicalPlan;
		physicalPlan.root = sqlgrammer.transform2PhysicPlan();
		physicalPlan.showPlan();
		
		(yyval.phyNode) = physicalPlan.root;

		cout<<endl;
	}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 544 "DML_gram.y"
    {
		(yyval.values) = new vector<string>;
		(yyval.values)->push_back(*(yyvsp[(1) - (1)].text));
	}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 549 "DML_gram.y"
    {
		(yyvsp[(3) - (3)].values)->push_back(*(yyvsp[(1) - (3)].text));
		(yyval.values) = (yyvsp[(3) - (3)].values);
	}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 557 "DML_gram.y"
    {
		(yyval.attr_indexs) = new map<string,string>;
		string **tmp = (yyvsp[(1) - (1)].attr_index);
		(yyval.attr_indexs)->insert(pair<string, string>(*tmp[0], *tmp[1]));
	}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 563 "DML_gram.y"
    {
		string **tmp = (yyvsp[(1) - (3)].attr_index);
		(yyvsp[(3) - (3)].attr_indexs)->insert(pair<string,string>(*tmp[0],*tmp[1]));
		(yyval.attr_indexs) = (yyvsp[(3) - (3)].attr_indexs);
	}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 572 "DML_gram.y"
    {
		string** tmp = (yyval.attr_index);
		tmp[0] = (yyvsp[(1) - (3)].text);
		tmp[1] = (yyvsp[(3) - (3)].text);
	}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 581 "DML_gram.y"
    {
		(yyval.text) = &(yyvsp[(1) - (1)].pString)->parameter;
	}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 585 "DML_gram.y"
    {
		(yyval.text) = &(yyvsp[(1) - (1)].rNumber)->number;
	}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 592 "DML_gram.y"
    {
		ParaString* pstring = new ParaString();
		pstring->parameter = "\'" + *(yyvsp[(2) - (3)].text) +"\'";
        (yyval.pString) = pstring;
	}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 601 "DML_gram.y"
    {
		(yyval.soperator) = (yyvsp[(1) - (1)].soperator);
	}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 605 "DML_gram.y"
    {
		(yyval.soperator) = (yyvsp[(1) - (1)].soperator);
	}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 609 "DML_gram.y"
    {
		(yyval.soperator) = (yyvsp[(1) - (1)].soperator);
	}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 613 "DML_gram.y"
    {
		(yyval.soperator) = (yyvsp[(1) - (1)].soperator);
	}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 617 "DML_gram.y"
    {
		(yyval.soperator) = (yyvsp[(1) - (1)].soperator);
	}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 621 "DML_gram.y"
    {
		(yyval.soperator) = (yyvsp[(1) - (1)].soperator);
	}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 625 "DML_gram.y"
    {
		(yyval.soperator) = (yyvsp[(1) - (1)].soperator);
	}
    break;


/* Line 1792 of yacc.c  */
#line 2207 "DML_gram.tab.cpp"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 630 "DML_gram.y"


int parser_dml_sql(string sql){

	yy_switch_to_buffer(yy_scan_string(sql.c_str()));
	if(yyparse())
		return -1;
	else{
		return 1;
	}
}

string getInputSql(){
	//获取输入的sql语句
	string sql;
	getline(cin, sql);
	while (sql.back() != ';') {
		string tmp;
		getline(cin, tmp);
		sql += " " + tmp;
	}
	return sql;
}