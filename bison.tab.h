
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     AND = 258,
     ADD = 259,
     OR = 260,
     LW = 261,
     SW = 262,
     SUB = 263,
     BEQ = 264,
     J = 265,
     ADDU = 266,
     MFLO = 267,
     JR = 268,
     JAL = 269,
     JALR = 270,
     ADDI = 271,
     ORI = 272,
     LUI = 273,
     SLTI = 274,
     BGTZ = 275,
     BLEZ = 276,
     LB = 277,
     SB = 278,
     BGEZ = 279,
     BLTZ = 280,
     MULT = 281,
     NOR = 282,
     SLL = 283,
     SLLV = 284,
     SLTU = 285,
     MADD = 286,
     Q = 287,
     W = 288,
     E = 289,
     R = 290,
     T = 291,
     Y = 292,
     U = 293,
     QQ = 294,
     WW = 295,
     EE = 296,
     RR = 297,
     TT = 298,
     YY = 299,
     UU = 300
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 370 "bison.y"

	char* nod;
	int nodd;



/* Line 1676 of yacc.c  */
#line 104 "bison.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


