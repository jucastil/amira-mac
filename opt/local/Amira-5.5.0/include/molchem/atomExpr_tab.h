/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     ID = 260,
     NAME = 261,
     EQNOP = 262,
     GROUPPART = 263,
     GROUPSPECIFIER = 264,
     BONDORDERCHAR = 265,
     SMARTSSTR = 266,
     NOT = 267,
     ALL = 268,
     CS = 269,
     SMARTSH = 270,
     SMARTS = 271,
     GROUP = 272,
     BONDED = 273,
     WITHIN = 274,
     XOR = 275,
     OR = 276,
     AND = 277
   };
#endif
/* Tokens.  */
#define INT 258
#define FLOAT 259
#define ID 260
#define NAME 261
#define EQNOP 262
#define GROUPPART 263
#define GROUPSPECIFIER 264
#define BONDORDERCHAR 265
#define SMARTSSTR 266
#define NOT 267
#define ALL 268
#define CS 269
#define SMARTSH 270
#define SMARTS 271
#define GROUP 272
#define BONDED 273
#define WITHIN 274
#define XOR 275
#define OR 276
#define AND 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 25 "atomExpr.ny"
{
    AE::Expression* atoms;
    int numInt;
    float numFloat;
    char *str;
}
/* Line 1489 of yacc.c.  */
#line 100 "atomExpr_tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE atomExpr_yylval;

