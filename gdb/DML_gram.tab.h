/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2058 of yacc.c  */
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


/* Line 2058 of yacc.c  */
#line 129 "DML_gram.tab.h"
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
