
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 2 "bison.y"


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "code.h"
#include <string.h>

char* tobinary(char*);
	
	char iperfect[20];
	//iperfect = malloc(20*sizeof(char));
	int ic_s = 0;
	int iassc = 0;
	char ireplpol[20];
	//ireplpol = malloc(20*sizeof(char));
	int iwthru = 0;
	int ib_s = 0;
	char dperfect[20];
	//dperfect = malloc(20*sizeof(char));
	int dc_s = 0;
	int dassc = 0;
	char dreplpol[20];
	//dreplpol = malloc(20*sizeof(char));
	int dwthru = 0;
	int db_s = 0;

int hextoint(char* a)
{
	int res=0;
	int i,t;
	if(strlen(a)!=10)
		return -1;
	for(i=2;i<10;i++)
	{
		if(i==4)
			t=4;
		else
			t=0;
		switch (a[i])
        {
	        case '0':
	            res = res + (0-t)*pow(16,9-i);break;
	        case '1':
	            res = res + (1-t)*pow(16,9-i);break;
	        case '2':
	            res = res + (2-t)*pow(16,9-i);break;
	        case '3':
	            res = res + (3-t)*pow(16,9-i);break;
	        case '4':
	            res = res + (4-t)*pow(16,9-i);break;
	        case '5':
	            res = res + (5-t)*pow(16,9-i);break;
	        case '6':
	            res = res + (6-t)*pow(16,9-i);break;
	        case '7':
	            res = res + (7-t)*pow(16,9-i);break;
	        case '8':
	            res = res + (8-t)*pow(16,9-i);break;
	        case '9':
	            res = res + (9-t)*pow(16,9-i);break;
	        case 'A':
	            res = res + (10-t)*pow(16,9-i);break;
	        case 'B':
	            res = res + (11-t)*pow(16,9-i);break;
	        case 'C':
	            res = res + (12-t)*pow(16,9-i);break;
	        case 'D':
	            res = res + (13-t)*pow(16,9-i);break;
	        case 'E':
	            res = res + (14-t)*pow(16,9-i);break;
	        case 'f':
	            res = res + (15-t)*pow(16,9-i);break;
	        case 'a':
	            res = res + (10-t)*pow(16,9-i);break;
	        case 'b':
	            res = res + (11-t)*pow(16,9-i);break;
	        case 'c':
	            res = res + (12-t)*pow(16,9-i);break;
	        case 'd':
	            res = res + (13-t)*pow(16,9-i);break;
	        case 'e':
	            res = res + (14-t)*pow(16,9-i);break;
	        case 'F':
	            res = res + (15-t)*pow(16,9-i);break;
	        default:
	            return -1;
        }
	}
	//printf("ans: %d\n",res);;
	return res;
}



char* tobinary(char* a)
{	
	char* b = (char *) malloc(32*sizeof(char));

	int i;
	for(i=0;i<8;i++)
	{
		//printf("%c\n",a[i]);
		switch (a[i])
        {
	        case '0':
	            b[i*4]='0'; b[i*4 + 1]='0'; b[i*4 + 2]='0'; b[i*4 + 3]='0';break;
	        case '1':
	            b[i*4]='0'; b[i*4 + 1]='0'; b[i*4 + 2]='0'; b[i*4 + 3]='1'; break;
	        case '2':
	            b[i*4]='0'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case '3':
	            b[i*4]='0'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        case '4':
	            b[i*4]='0'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='0'; break;
	        case '5':
	            b[i*4]='0'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='1'; break;
	        case '6':
	            b[i*4]='0'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case '7':
	            b[i*4]='0'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        case '8':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='0'; b[i*4 + 3]='0'; break;
	        case '9':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='0'; b[i*4 + 3]='1'; break;
	        case 'A':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case 'B':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        case 'C':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='0'; break;
	        case 'D':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='1'; break;
	        case 'E':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case 'f':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        case 'a':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case 'b':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        case 'c':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='0'; break;
	        case 'd':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='1'; break;
	        case 'e':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case 'F':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        default:
	            printf("Invalid hexa digit %c ", a[i]);
	            return 0;
        }
	}
	b[32]='\0';
	return b;
}
extern FILE *yyin;
extern FILE *yyout;

void stat(char* s, char* t)
{
    while(*s != '\0')
        *s++;
    while(*s++ = *t++)
        ;
}
 
void convertinstr()
{
    //read the if_id.name and decode into various instructions
    //get the cases Rd,RT,Rd,offset and store in char* new variable
    char tmp[20] = "";
    char tmpa[20] = "";
    char tmpb[20] = "";
    char tmpc[20] = "";
 
    
    if(!strcmp(if_id.name_write, "add") || !strcmp(if_id.name_write,"and") || !strcmp(if_id.name_write,"nor") || !strcmp(if_id.name_write,"or") || !strcmp(if_id.name_write,"sub"))
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.inst_data_15_11_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad1_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        stat(if_id.instr_name_read,tmp);
*/      //printf("case1\n");
 
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.inst_data_15_11_write);
        stat(tmp,tmpa);
        stat(tmp," $");
        sprintf(tmpb,"%d",if_id.rf_rad1_write);
        stat(tmp,tmpb);
        stat(tmp," $");
        sprintf(tmpc,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpc);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
    }
    else if(!strcmp(if_id.name_write, "addi") || !strcmp(if_id.name_write,"ori") || !strcmp(if_id.name_write,"slti"))
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad1_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,tmp);
        printf("case2\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpa);
        stat(tmp," $");
        sprintf(tmpb,"%d",if_id.rf_rad1_write);
        stat(tmp,tmpb);
        stat(tmp," $");
        sprintf(tmpc,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpc);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
 
 
    }
    else if(!strcmp(if_id.name_write,"mult")|| !strcmp(if_id.name_write,"madd") )
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad1_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,if_id.inst_data_15_0_write);
        printf("case3\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad1_write);
        stat(tmp,tmpa);
        stat(tmp," $");
        sprintf(tmpb,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpb);
        stat(tmp," $");
        sprintf(tmpc,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpc);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
 
    }
    else if(!strcmp(if_id.name_write, "lui"))
    {
        //printf("yes\n");
        /*
        if_id.instr_name_read = if_id.name_read;
        printf("no\n");
        //stat(if_id.instr_name_read," $");
        
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        printf("see\n");
        printf("%s\n",tmp);
        stat(if_id.instr_name_read,tmp);
        printf("serio\n");
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,tmp);
        printf("case4\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpa);
        stat(tmp," @");
        sprintf(tmpb,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpb);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
 
 
    }
    else if(!strcmp(if_id.name_write, "beq"))
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad1_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,tmp);
        printf("case5\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad1_write);
        stat(tmp,tmpa);
        stat(tmp," $");
        sprintf(tmpb,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpb);
        stat(tmp," $");
        sprintf(tmpc,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpc);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
 
    }
    else if(!strcmp(if_id.name_write, "bgez") || !strcmp(if_id.name_write,"bgtz") || !strcmp(if_id.name_write,"blez") || !strcmp(if_id.name_write,"bltz"))
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad1_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,tmp);
        printf("case6\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad1_write);
        stat(tmp,tmpa);
        stat(tmp," @");
        sprintf(tmpb,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpb);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
 
    }
    else if(!strcmp(if_id.name_write, "lb") || !strcmp(if_id.name_write,"lw") || !strcmp(if_id.name_write,"sb") || !strcmp(if_id.name_write,"sw"))
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,tmp);
        printf("case7\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpa);
        stat(tmp," @");
        sprintf(tmpb,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpb);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
    }
}




/* Line 189 of yacc.c  */
#line 442 "bison.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 370 "bison.y"

	char* nod;
	int nodd;



/* Line 214 of yacc.c  */
#line 530 "bison.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 542 "bison.tab.c"

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
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   88

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  2
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNRULES -- Number of states.  */
#define YYNSTATES  89

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    33,    35,    37,
      39,    41,    43,    45,    47,    49,    51,    53,    55,    57,
      59,    61,    63,    65,    67,    69,    71,    73,    75,    77,
      79,    81,    83,    85,    87,    89,    92,    95,    98,   101,
     104,   107,   110,   113,   116,   119,   122,   125,   128,   131,
     134,   137,   140,   143,   146,   149,   152,   155,   158,   161,
     164,   167,   170,   173,   176,   179,   182,   185,   188,   191,
     194,   197,   200,   203,   206,   209,   212,   215
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,     3,    -1,     4,    -1,     5,    -1,     6,
      -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,    11,
      -1,    12,    -1,    13,    -1,    15,    -1,    14,    -1,    16,
      -1,    17,    -1,    18,    -1,    19,    -1,    20,    -1,    21,
      -1,    22,    -1,    23,    -1,    31,    -1,    24,    -1,    25,
      -1,    26,    -1,    27,    -1,    28,    -1,    29,    -1,    30,
      -1,    32,    -1,    33,    -1,    34,    -1,    35,    -1,    36,
      -1,    37,    -1,    38,    -1,    39,    -1,    40,    -1,    41,
      -1,    42,    -1,    43,    -1,    44,    -1,    45,    -1,    47,
      32,    -1,    47,    33,    -1,    47,    34,    -1,    47,    35,
      -1,    47,    36,    -1,    47,    37,    -1,    47,    38,    -1,
      47,    39,    -1,    47,    40,    -1,    47,    41,    -1,    47,
      42,    -1,    47,    43,    -1,    47,    44,    -1,    47,    45,
      -1,    47,     3,    -1,    47,     4,    -1,    47,     5,    -1,
      47,     6,    -1,    47,     7,    -1,    47,     8,    -1,    47,
       9,    -1,    47,    10,    -1,    47,    11,    -1,    47,    12,
      -1,    47,    13,    -1,    47,    15,    -1,    47,    14,    -1,
      47,    16,    -1,    47,    17,    -1,    47,    18,    -1,    47,
      19,    -1,    47,    20,    -1,    47,    21,    -1,    47,    22,
      -1,    47,    23,    -1,    47,    24,    -1,    47,    25,    -1,
      47,    26,    -1,    47,    27,    -1,    47,    28,    -1,    47,
      29,    -1,    47,    30,    -1,    47,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   383,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,   414,   415,   416,   417,   418,   420,   421,
     422,   423,   424,   425,   426,   428,   429,   430,   431,   432,
     433,   434,   436,   437,   438,   439,   440,   441,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "ADD", "OR", "LW", "SW", "SUB",
  "BEQ", "J", "ADDU", "MFLO", "JR", "JAL", "JALR", "ADDI", "ORI", "LUI",
  "SLTI", "BGTZ", "BLEZ", "LB", "SB", "BGEZ", "BLTZ", "MULT", "NOR", "SLL",
  "SLLV", "SLTU", "MADD", "Q", "W", "E", "R", "T", "Y", "U", "QQ", "WW",
  "EE", "RR", "TT", "YY", "UU", "$accept", "exp", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    14,    13,    15,    16,    17,    18,    19,    20,
      21,    22,    24,    25,    26,    27,    28,    29,    30,    23,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,     0,     1,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    71,    70,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    44
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1
static const yytype_int8 yypact[] =
{
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     0,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -1,    -1
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      45,     0,     0,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

static const yytype_int8 yycheck[] =
{
       0,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    47,     0,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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

/* Prevent warnings from -Wmissing-prototypes.  */
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
        case 2:

/* Line 1455 of yacc.c  */
#line 383 "bison.y"
    {im[N].name="and";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 384 "bison.y"
    {im[N].name="add";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 385 "bison.y"
    {im[N].name="or";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 386 "bison.y"
    {im[N].name="lw";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 387 "bison.y"
    {im[N].name="sw";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 388 "bison.y"
    {im[N].name="sub";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 389 "bison.y"
    {im[N].name="beq";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 390 "bison.y"
    {im[N].name="j";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 391 "bison.y"
    {im[N].name="addu";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 392 "bison.y"
    {im[N].name="mflo";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 393 "bison.y"
    {im[N].name="jr";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 394 "bison.y"
    {im[N].name="jalr";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 395 "bison.y"
    {im[N].name="jal";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 396 "bison.y"
    {im[N].name="addi";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 397 "bison.y"
    {im[N].name="ori";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 398 "bison.y"
    {im[N].name="lui";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 399 "bison.y"
    {im[N].name="slti";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 400 "bison.y"
    {im[N].name="bgtz";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 401 "bison.y"
    {im[N].name="blez";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 402 "bison.y"
    {im[N].name="lb";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 403 "bison.y"
    {im[N].name="sb";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 404 "bison.y"
    {im[N].name="madd";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 405 "bison.y"
    {im[N].name="bgez";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 406 "bison.y"
    {im[N].name="bltz";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 407 "bison.y"
    {im[N].name="mult";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 408 "bison.y"
    {im[N].name="nor";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 409 "bison.y"
    {im[N].name="sll";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 410 "bison.y"
    {im[N].name="sllv";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 411 "bison.y"
    {im[N].name="sltu";im[N].instr=(yyvsp[(1) - (1)].nod);N++;;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 412 "bison.y"
    {strcpy(iperfect , "false");printf("%s\n\n\n\n\n\n",(yyvsp[(1) - (1)].nod));;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 413 "bison.y"
    {strcpy(iperfect , "true");printf("%s\n\n\n\n\n\n",(yyvsp[(1) - (1)].nod));;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 414 "bison.y"
    {ic_s = ((yyvsp[(1) - (1)].nodd)); printf("%d\n\n\n\n\n\n",(yyvsp[(1) - (1)].nodd));;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 415 "bison.y"
    {iassc = ((yyvsp[(1) - (1)].nodd));printf("%d\n\n\n\n\n\n",(yyvsp[(1) - (1)].nodd));;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 416 "bison.y"
    {iwthru = ((yyvsp[(1) - (1)].nodd));printf("%d\n\n\n\n\n\n",(yyvsp[(1) - (1)].nodd));;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 417 "bison.y"
    {ib_s = ((yyvsp[(1) - (1)].nodd));printf("%d\n\n\n\n\n\n",(yyvsp[(1) - (1)].nodd));;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 418 "bison.y"
    {strcpy(ireplpol , "lru");printf("%s\n\n\n\n\n\n",(yyvsp[(1) - (1)].nod));;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 420 "bison.y"
    {strcpy(dperfect , "false");printf("%s\n\n\n\n\n\n",(yyvsp[(1) - (1)].nod));;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 421 "bison.y"
    {strcpy(dperfect , "true");printf("%s\n\n\n\n\n\n",(yyvsp[(1) - (1)].nod));;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 422 "bison.y"
    {dc_s = ((yyvsp[(1) - (1)].nodd));printf("%d\n\n\n\n\n\n",(yyvsp[(1) - (1)].nodd));;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 423 "bison.y"
    {dassc = ((yyvsp[(1) - (1)].nodd));printf("%d\n\n\n\n\n\n",(yyvsp[(1) - (1)].nodd));;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 424 "bison.y"
    {dwthru = ((yyvsp[(1) - (1)].nodd));printf("%d\n\n\n\n\n\n",(yyvsp[(1) - (1)].nodd));;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 425 "bison.y"
    {db_s = ((yyvsp[(1) - (1)].nodd));printf("%d\n\n\n\n\n\n",(yyvsp[(1) - (1)].nodd));;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 426 "bison.y"
    {strcpy(dreplpol , "lru");printf("%s\n\n\n\n\n\n",(yyvsp[(1) - (1)].nod));;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 428 "bison.y"
    {strcpy(iperfect , "false");;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 429 "bison.y"
    {strcpy(iperfect , "true");;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 430 "bison.y"
    {ic_s = ((yyvsp[(2) - (2)].nodd));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 431 "bison.y"
    {iassc = ((yyvsp[(2) - (2)].nodd));;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 432 "bison.y"
    {iwthru = ((yyvsp[(2) - (2)].nodd));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 433 "bison.y"
    {ib_s = ((yyvsp[(2) - (2)].nodd));;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 434 "bison.y"
    {strcpy(ireplpol , "lru");;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 436 "bison.y"
    {strcpy(dperfect , "false");;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 437 "bison.y"
    {strcpy(dperfect , "true");;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 438 "bison.y"
    {dc_s = ((yyvsp[(2) - (2)].nodd));;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 439 "bison.y"
    {dassc = ((yyvsp[(2) - (2)].nodd));;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 440 "bison.y"
    {dwthru = ((yyvsp[(2) - (2)].nodd));;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 441 "bison.y"
    {db_s = ((yyvsp[(2) - (2)].nodd));;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 442 "bison.y"
    {strcpy(dreplpol , "lru");;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 443 "bison.y"
    {im[N].name="and";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 444 "bison.y"
    {im[N].name="add";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 445 "bison.y"
    {im[N].name="or";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 446 "bison.y"
    {im[N].name="lw";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 447 "bison.y"
    {im[N].name="sw";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 448 "bison.y"
    {im[N].name="sub";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 449 "bison.y"
    {im[N].name="beq";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 450 "bison.y"
    {im[N].name="j";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 451 "bison.y"
    {im[N].name="addu";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 452 "bison.y"
    {im[N].name="mflo";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 453 "bison.y"
    {im[N].name="jr";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 454 "bison.y"
    {im[N].name="jalr";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 455 "bison.y"
    {im[N].name="jal";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 456 "bison.y"
    {im[N].name="addi";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 457 "bison.y"
    {im[N].name="ori";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 458 "bison.y"
    {im[N].name="lui";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 459 "bison.y"
    {im[N].name="slti";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 460 "bison.y"
    {im[N].name="bgtz";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 461 "bison.y"
    {im[N].name="blez";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 462 "bison.y"
    {im[N].name="lb";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 463 "bison.y"
    {im[N].name="sb";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 464 "bison.y"
    {im[N].name="bgez";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 465 "bison.y"
    {im[N].name="bltz";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 466 "bison.y"
    {im[N].name="mult";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 467 "bison.y"
    {im[N].name="nor";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 468 "bison.y"
    {im[N].name="sll";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 469 "bison.y"
    {im[N].name="sllv";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 470 "bison.y"
    {im[N].name="sltu";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 471 "bison.y"
    {im[N].name="madd";im[N].instr=(yyvsp[(2) - (2)].nod);N++;;}
    break;



/* Line 1455 of yacc.c  */
#line 2426 "bison.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 472 "bison.y"



main(int argc, char **argv)
{
	
	int i;

	trace = fopen("trace.log", "w");

	    char* wbins = "nop";
	for(i=0;i<1000;i++)
		mem[i] = 0;

	for(i=0;i<34;i++)
		rf[i] = 0;

	double max;
	/*FILE *myfile1 = fopen(argv[2], "w");
	if (!myfile1) {
		printf("can't open wr");
		return -1;
	}*/
	//yyout = myfile1;

	FILE *myfile = fopen(argv[1], "r");
	if (!myfile) {
		printf("can't open re");
		return -1;
	}
	yyin = myfile;
	do {
		yyparse();
	} 
	while (!feof(yyin));
	
	fclose(myfile);


	yyin=fopen("input.cfg","r");

	do {
		yyparse();
	} 
	while (!feof(yyin));
	fclose(yyin);	

	printf("========================================================================================%s\n",iperfect);
	printf("========================================================================================%d\n",ic_s);
	printf("========================================================================================%d\n",iassc);
	printf("========================================================================================%s\n",ireplpol);
	printf("========================================================================================%d\n",iwthru);
	printf("========================================================================================%d\n",ib_s);
	

	printf("========================================================================================%s\n",dperfect);
	printf("========================================================================================%d\n",dc_s);
	printf("========================================================================================%d\n",dassc);
	printf("========================================================================================%s\n",dreplpol);
	printf("========================================================================================%d\n",dwthru);
	printf("========================================================================================%d\n",db_s);


		id_ex.rn_read = 0;
		id_ex.rn_write = 0;
		id_ex.rm_read = 0;
		id_ex.rm_write = 0;

		mem_wb.mem_data_read    = 0;
		mem_wb.bypass_data_read = 0;
		mem_wb.mux_ans_read     = 0;
		mem_wb.mem_data_write   = 0;
		mem_wb.bypass_data_write= 0;
		mem_wb.mux_ans_write    = 0;

		id_ex.sa_read = 0;
		id_ex.sa_write = 0;

		ex_mem.add_ans_read = 0;
		ex_mem.alu_ans_read = 0;
		ex_mem.rf_data_read = 0;
		ex_mem.mux_ans_read = 0;

		ex_mem.add_ans_write = 0;
		ex_mem.alu_ans_write = 0;
		ex_mem.rf_data_write = 0;
		ex_mem.mux_ans_write = 0;

		id_ex.rf_outdata1_read      = 0;
		id_ex.rf_outdata2_read      = 0;
		id_ex.inst_data_15_0_read   = 0;
		id_ex.inst_data_20_16_read  = 0;
		id_ex.inst_data_15_11_read  = 0;
		id_ex.rf_outdata1_write     = 0;
		id_ex.rf_outdata2_write     = 0;
		id_ex.inst_data_15_0_write  = 0;
		id_ex.inst_data_20_16_write = 0;
		id_ex.inst_data_15_11_write = 0;

		
		if_id.rf_rad1_write = 0;
		if_id.rf_rad2_write = 0;
		if_id.inst_data_15_0_write = 0;
		if_id.inst_data_20_16_write = 0;
		if_id.inst_data_15_11_write = 0;

		
		if_id.rf_rad1_read = 0;
		if_id.rf_rad2_read = 0;
		if_id.inst_data_15_0_read = 0;
		if_id.inst_data_20_16_read = 0;
		if_id.inst_data_15_11_read = 0;

		if_id.add_write = 0;
		if_id.inst_write = "0";
		if_id.name_write = "0";
		id_ex.name_write = "0";
		ex_mem.name_write = "0";
		mem_wb.name_write = "0";

		write_datag_left = 0;

		id_ex.ALUSrc_write = 0;
		id_ex.ALUOp_write = "000";
		id_ex.RegDest_write = 0;
		id_ex.RegWrite_write = 0;
		id_ex.MemWrite_write = 0;
		id_ex.MemtoReg_write = 0;
		id_ex.MemRead_write = 0;
		id_ex.Branch_write = 0;
		id_ex.readdata1_write = 0;
		id_ex.readdata2_write = 0;
		//id_ex.extender_write;
		id_ex.inst20_16_write = 0;
		id_ex.inst15_11_write = 0;
		id_ex.add_write = 0;


		ex_mem.MemWrite_write  = 0;
		ex_mem.MemRead_write   = 0;
		ex_mem.Branch_write    = 0;
		ex_mem.Zero_write      = 0;
		ex_mem.RegWrite_write  = 0;
		ex_mem.MemtoReg_write  = 0;
		ex_mem.readdata2_write = 0;
		ex_mem.addresult_write = 0;
		ex_mem.aluresult_write = 0;
		ex_mem.write_register_write = 0;


		mem_wb.RegWrite_write       = 0;
		mem_wb.MemtoReg_write       = 0;
		mem_wb.readdata_write       = 0;
		mem_wb.addressbypass_write  = 0;
		mem_wb.write_register_write = 0;


		if_id.add_read = 0;
		if_id.inst_read = "0";
		if_id.name_read = "0";
		id_ex.name_read = "0";
		ex_mem.name_read = "0";
		mem_wb.name_read = "0";

		write_datag_right = 0;

		id_ex.ALUSrc_read = 0;
		id_ex.ALUOp_read = "000";
		id_ex.RegDest_read = 0;
		id_ex.RegWrite_read = 0;
		id_ex.MemWrite_read = 0;
		id_ex.MemtoReg_read = 0;
		id_ex.MemRead_read = 0;
		id_ex.Branch_read = 0;
		id_ex.readdata1_read = 0;
		id_ex.readdata2_read = 0;
		//id_ex.extender_read;
		id_ex.inst20_16_read = 0;
		id_ex.inst15_11_read = 0;
		id_ex.add_read = 0;


		ex_mem.MemWrite_read  = 0;
		ex_mem.MemRead_read   = 0;
		ex_mem.Branch_read    = 0;
		ex_mem.Zero_read      = 0;
		ex_mem.add_write      = 0;
		ex_mem.add_read      = 0;
		ex_mem.RegWrite_read  = 0;
		ex_mem.MemtoReg_read  = 0;
		ex_mem.readdata2_read = 0;
		ex_mem.addresult_read = 0;
		ex_mem.aluresult_read = 0;
		ex_mem.write_register_read = 0;


		mem_wb.RegWrite_read       = 0;
		mem_wb.MemtoReg_read       = 0;
		mem_wb.readdata_read       = 0;
		mem_wb.addressbypass_read  = 0;
		mem_wb.write_register_read = 0;

        if_id.instr_name_read = "nop";
        if_id.instr_name_write = "nop";        
        id_ex.instr_name_read = "nop";
        id_ex.instr_name_write = "nop";
        ex_mem.instr_name_write = "nop";
        ex_mem.instr_name_read = "nop";
        mem_wb.instr_name_write = "nop";
        mem_wb.instr_name_read = "nop";

	int temp = 200;
	int flag = 0;
	int break_temp = 0;
	int break_counter = 0;
	int break_array[1000]; 			//made only upto 1000 breakpoints
	int break_reached = 0;
	int break_continue = 0;
	for ( i = 0; i < 1000; ++i)
	{
		break_array[i] = 0;
	} 
	//highlight(0,1,0,1,0);
	while(flag != 4)
	{	
		//printf("new %d\n",PC );
		char* read = malloc(50*sizeof(char));
		char* read2 = malloc(50*sizeof(char));
		if(break_continue == 1)
			for (i = 0; i < break_counter; ++i)
			{
				if(break_array[i]==PC)
				{
					printf("breakpoint reached\n"); // %s\n",inttohex(break_array[i])); // need to tell which breakpoint
					break_reached = 1;
				}
			}
		if(break_reached==0 && break_continue==1)	//nice logic
			read = "step";
		else
		{
			printf("Shell>> ");
			scanf("%s",read);
		}
		if(!strcmp(read,"break"))
		{
			scanf("%s",read2);
			//printf("%s\n", read2);
			break_temp = hextoint(read2);
			if(break_temp==-1)
				printf("invalid address of breakpoint\n");
			else
			{		
				break_array[break_counter++] = break_temp;
				printf("breakpoint created\n");
			}
		}
		else if(!strcmp(read,"delete"))
		{
			scanf("%s",read2);
			//printf("%s\n", read2);
			break_temp = hextoint(read2);
			if(break_temp==-1)
				printf("invalid address of breakpoint\n");
			else
			{
				//delete breakpoints
				for (i = 0; i < break_counter; ++i)
				{
				 	if(break_temp==break_array[i])
				 		break;	
				}
				int j=0;
				for(j=i;j<break_counter-1;j++)
				{
					break_array[j]=break_array[j+1];
				}
				break_counter--;
				printf("breakpoint deleted\n");
			}
		}
		else if(!strcmp(read,"continue"))
		{
			break_continue=1;	//continue till next breakpoint
			break_reached=0;
			read = "step";
		}
		else if(!strcmp(read,"run"))
		{
			break_reached = 0;
			break_counter = 0;	//removes breakpoints
		}
		if(!strcmp(read,"step"))
		{

				//printf("------------------  %d\n",PC);
				/*int ghy = 10000;
				while(ghy--)
				{
				}
				char* sss = malloc(20*sizeof(char));
				scanf("%s",sss);
				*/
				

				//printf("((((((((((((((((((((((((((((((((((((((((  %d\n\n\n",temp);
				pthread_t IF,ID,EX,MEM,WB,DISPLAY;
				
				pthread_create(&IF,NULL,thread_IF,NULL);
				pthread_create(&ID,NULL,thread_ID,NULL);
				pthread_create(&EX,NULL,thread_EX,NULL);
				pthread_create(&MEM,NULL,thread_MEM,NULL);
				pthread_create(&WB,NULL,thread_WB,NULL);
				//pthread_create(&DISPLAY,NULL,display,NULL);

				//if(stall_left != 1)
				pthread_join(IF,NULL);
				pthread_join(ID,NULL);
				pthread_join(EX,NULL);
				pthread_join(MEM,NULL);
				pthread_join(WB,NULL);
				//pthread_join(DISPLAY,NULL);

				//printf("11111\n");
				if(stall_right != 1)
				{

					if_id.add_write =  if_id.add_read;
					if_id.inst_write = if_id.inst_read;
					if_id.name_write = if_id.name_read;

				

				//printf("if_id.instr : \n");
				//printf("%s\n",if_id.inst_read);
				//if(PC < N )
				//{

				char* aa = malloc(5*sizeof(char));
					for(i=6;i<11;i++)
						aa[i-6] = if_id.inst_read[i];
					aa[i-6] = '\0';
					if_id.rf_rad1_write = bin_to_dec(aa);// - bin_to_dec("01000");

				//printf("11111\n");

				char* bb = malloc(5*sizeof(char));
					for(i=11;i<16;i++)
						bb[i-11] = if_id.inst_read[i];
					bb[i-11] = '\0';
					//if(bb[0] == '0')
					if_id.rf_rad2_write = bin_to_dec(bb);// - bin_to_dec("01000");
					

				char* cc = malloc(16*sizeof(char));
				for(i=16;i<32;i++)
					cc[i-16] = if_id.inst_read[i];
				cc[i-16] = '\0';

				char* ddd = malloc(26*sizeof(char));
				for(i=6;i<32;i++)
					ddd[i-6] = if_id.inst_read[i];
				ddd[i-6] = '\0';
				if_id.j_mag_write = bin_to_dec(ddd);

				if(cc[0] == '0')
				if_id.inst_data_15_0_write = bin_to_dec(cc);
				else
				{
					//printf("i am hrer\n\n\n\n\n\n");
					for(i=0;i<16;i++)
						{
							if(cc[i] == '0')
								cc[i] = '1';
							else
								cc[i] = '0';
						}
							//cc[i] = '0';
							//cc[0] = '0';
							//printf("%s\n",cc);
							if_id.inst_data_15_0_write = -1*(bin_to_dec(cc)+1);
				}

				//printf("-------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>    %d\n", bin_to_dec(cc));

				char* dd= malloc(5*sizeof(char));
				for(i=11;i<16;i++)
					dd[i-11] = if_id.inst_read[i];
				dd[i-11] = '\0';

				//if(dd[0] == '0')
				if_id.inst_data_20_16_write = bin_to_dec(dd);// - bin_to_dec("01000");
				

				char* ee= malloc(5*sizeof(char));
				for(i=16;i<21;i++)
					ee[i-16] = if_id.inst_read[i];
				ee[i-16] = '\0';
				if_id.inst_data_15_11_write = bin_to_dec(ee);// - bin_to_dec("01000");

				}
				else
				{
					//printf("hiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n\n\n\n\\n\n\n\n\n\n\\n\n\n\n\n\n\n\n");
					//stall = 0;
				}

				//}
				//else
				//{
					/*if_id.rf_rad1_read = 0;
					if_id.rf_rad2_read = 0;
					if_id.inst_data_15_0_read = 0;
					if_id.inst_data_20_16_read = 0;
					if_id.inst_data_15_11_read  = 0;*/

					//stall_left = 0;
				//}
				
				wbins = mem_wb.name_write;
				id_ex.name_write = id_ex.name_read;
				ex_mem.name_write = ex_mem.name_read;
				mem_wb.name_write = mem_wb.name_read;
				write_datag_left = write_datag_right;
				rf_wdg_left = rf_wdg_right;
				rf_wadg_left = rf_wadg_right;


				id_ex.rf_outdata1_write     = id_ex.rf_outdata1_read    ;
				id_ex.rf_outdata2_write     = id_ex.rf_outdata2_read    ;
				id_ex.inst_data_15_0_write  = id_ex.inst_data_15_0_read ;
				id_ex.inst_data_20_16_write = id_ex.inst_data_20_16_read;
				id_ex.inst_data_15_11_write = id_ex.inst_data_15_11_read;

				id_ex.ALUSrc_write = id_ex.ALUSrc_read;
				id_ex.ALUOp_write = id_ex.ALUOp_read;
				id_ex.RegDest_write = id_ex.RegDest_read;
				id_ex.RegWrite_write = id_ex.RegWrite_read;
				id_ex.MemWrite_write = id_ex.MemWrite_read;
				id_ex.MemtoReg_write = id_ex.MemtoReg_read;
				id_ex.MemRead_write = id_ex.MemRead_read;
				id_ex.Branch_write = id_ex.Branch_read;
				id_ex.readdata1_write = id_ex.readdata1_read;
				id_ex.readdata2_write = id_ex.readdata2_read;
				//id_ex.extender_write;
				id_ex.inst20_16_write = id_ex.inst20_16_read;
				id_ex.inst15_11_write = id_ex.inst15_11_read;
				id_ex.add_write = id_ex.add_read;
				id_ex.sa_write = id_ex.sa_read;

				ex_mem.MemWrite_write  = ex_mem.MemWrite_read ;
				ex_mem.MemRead_write   = ex_mem.MemRead_read  ;
				ex_mem.Branch_write    = ex_mem.Branch_read   ;
				ex_mem.Zero_write      = ex_mem.Zero_read     ;
				ex_mem.RegWrite_write  = ex_mem.RegWrite_read ;
				ex_mem.MemtoReg_write  = ex_mem.MemtoReg_read ;
				ex_mem.add_write  	   = ex_mem.add_read 	  ;
				ex_mem.readdata2_write = ex_mem.readdata2_read;
				ex_mem.addresult_write = ex_mem.addresult_read;
				ex_mem.aluresult_write = ex_mem.aluresult_read;
				ex_mem.write_register_write = ex_mem.write_register_read;

				id_ex.rn_write = id_ex.rn_read;
				id_ex.rm_write = id_ex.rm_read;

				stall_left = stall_right; stall_right = 0;

				ex_mem.add_ans_write = ex_mem.add_ans_read;
				ex_mem.alu_ans_write = ex_mem.alu_ans_read;
				ex_mem.rf_data_write = ex_mem.rf_data_read;
				ex_mem.mux_ans_write = ex_mem.mux_ans_read;


				mem_wb.mem_data_write   = mem_wb.mem_data_read    ;
				mem_wb.bypass_data_write= mem_wb.bypass_data_read ;
				mem_wb.mux_ans_write    = mem_wb.mux_ans_read     ;

				mem_wb.RegWrite_write       = mem_wb.RegWrite_read      ;
				mem_wb.MemtoReg_write       = mem_wb.MemtoReg_read      ;
				mem_wb.readdata_write       = mem_wb.readdata_read     ;
				mem_wb.addressbypass_write  = mem_wb.addressbypass_read ;
				mem_wb.write_register_write = mem_wb.write_register_read;

        //printf("manu\n");
        convertinstr();
        //printf("mitraan\n");
        //wbins = mem_wb.name_write;
        id_ex.instr_name_write = id_ex.instr_name_read;
        ex_mem.instr_name_write = ex_mem.instr_name_read;
        mem_wb.instr_name_write = mem_wb.instr_name_read;

				if(mybranch == 1)
				{	
					id_ex.name_write = "nop";
						id_ex.ALUSrc_write = 0;
						id_ex.ALUOp_write = "000";
						id_ex.RegDest_write = 0;
						id_ex.RegWrite_write = 0;
						id_ex.MemWrite_write = 0;
						id_ex.MemtoReg_write = 0;
						id_ex.MemRead_write = 0;
						id_ex.Branch_write = 0;
						id_ex.readdata1_write = 0;
						id_ex.readdata2_write = 0;
						//id_ex.extender_write;
						id_ex.inst20_16_write = 0;
						id_ex.inst15_11_write = 0;
						id_ex.add_write = 0;
						id_ex.name_read = "nop";
						id_ex.ALUSrc_read = 0;
						id_ex.ALUOp_read = "000";
						id_ex.RegDest_read = 0;
						id_ex.RegWrite_read = 0;
						id_ex.MemWrite_read = 0;
						id_ex.MemtoReg_read = 0;
						id_ex.MemRead_read = 0;
						id_ex.Branch_read = 0;
						id_ex.readdata1_read = 0;
						id_ex.readdata2_read = 0;
						//id_ex.extender_read;
						id_ex.inst20_16_read = 0;
						id_ex.inst15_11_read = 0;
						id_ex.add_read = 0;

						if_id.name_write = "nop";
						if_id.name_read = "nop";

						ex_mem.name_write = "nop";
						ex_mem.name_read = "nop";
						ex_mem.MemWrite_write  = 0;
						ex_mem.MemRead_write   = 0;
						ex_mem.Branch_write    = 0;
						ex_mem.Zero_write      = 0;
						ex_mem.RegWrite_write  = 0;
						ex_mem.MemtoReg_write  = 0;
						ex_mem.readdata2_write = 0;
						ex_mem.addresult_write = 0;
						ex_mem.aluresult_write = 0;
						ex_mem.write_register_write = 0;
						ex_mem.MemWrite_read  = 0;
						ex_mem.MemRead_read   = 0;
						ex_mem.Branch_read    = 0;
						ex_mem.Zero_read      = 0;
						ex_mem.RegWrite_read  = 0;
						ex_mem.MemtoReg_read  = 0;
						ex_mem.readdata2_read = 0;
						ex_mem.addresult_read = 0;
						ex_mem.aluresult_read = 0;
						ex_mem.write_register_read = 0;
					
                ex_mem.instr_name_read = "nop";
                ex_mem.instr_name_write = "nop";
                if_id.instr_name_write = "nop";
                if_id.instr_name_read = "nop";
                id_ex.instr_name_write ="nop";
                id_ex.instr_name_read = "nop";
					mybranch = 0;
				}
				/*
				printf("===============================================================================================================================\n");
				
				printf("%s\n",if_id.name_write);
				printf("%s\n",id_ex.name_write);
				printf("%s\n",ex_mem.name_write);
				printf("%s\n",mem_wb.name_write);	
				printf("\n\n");*/

        		highlight(if_id.name_read, id_ex.name_read,ex_mem.name_read,mem_wb.name_read,wbins,argv[2]);

				if(strcmp(if_id.name_read,"nop") && strcmp(if_id.name_read,"0"))
					{	tim++;}
				else if(strcmp(id_ex.name_read,"nop") && strcmp(if_id.name_read,"0"))
					{	tim++;}
				else if(strcmp(ex_mem.name_read,"nop") && strcmp(if_id.name_read,"0"))
					{	tim++;}
				else if(strcmp(mem_wb.name_read,"nop") && strcmp(if_id.name_read,"0"))
					{	tim++;}
				else
				{
					flag++;
				}
				

				/*if( strcmpi("nop",if_id.name_write) && strcmpi("nop",id_ex.name_write) && strcmpi("nop",ex_mem.name_write) && strcmpi("nop",mem_wb.name_write))
					{}
				else if ( strcmpi("0",if_id.name_write) && strcmpi("0",id_ex.name_write) && strcmpi("0",ex_mem.name_write) && strcmpi("0",mem_wb.name_write))
					{}
				else
				{
					time++;
				}*/
				//printf("instruction : %s\n",if_id.inst_read);
				//printf("%s\n",if_id.name_read);
					/*
				printf("-> ADD : %d\n", if_id.add_write);
				printf("-> R1 : %d\n", if_id.rf_rad1_write);
				printf("-> R2 : %d\n", if_id.rf_rad2_write);
				printf("-> I1 : %d\n", if_id.inst_data_15_0_write);
				printf("-> I2 : %d\n", if_id.inst_data_20_16_write);
				printf("-> I3 : %d\n", if_id.inst_data_15_11_write);
				printf("\n\n");

				printf("%d\n",id_ex.add_write            );
				printf("%d\n",id_ex.rf_outdata1_write    );
				printf("%d\n",id_ex.rf_outdata2_write    );
				printf("%d\n",id_ex.inst_data_15_0_write );
				printf("%d\n",id_ex.inst_data_20_16_write);
				printf("%d\n",id_ex.inst_data_15_11_write);
				printf("\n\n");


				printf("%d\n",ex_mem.add_ans_write);
				printf("%d\n",ex_mem.alu_ans_write);
				printf("%d\n",ex_mem.rf_data_write);
				printf("%d\n",ex_mem.mux_ans_write);
				printf("\n\n");

				printf("%d\n",mem_wb.mem_data_write   ); 
				printf("%d\n",mem_wb.bypass_data_write); 
				printf("%d\n",mem_wb.mux_ans_write    ); 
				printf("\n\n");

				printf("%d\n",rf_wdg_right);
				printf("%d\n",rf_wdg_left);
				printf("%d\n",rf_wadg_right);
				printf("%d\n",rf_wadg_left);

				*/

				/*

				printf("->%d\n",if_id.add_read);
				printf("->%s\n",if_id.name_read);
				printf("\n\n");

				printf("%d\n",write_datag_right);
				printf("\n\n");

				printf("->%d\n",id_ex.ALUSrc_read);
				printf("->%s\n",id_ex.ALUOp_read);
				printf("->%d\n",id_ex.RegDest_read);
				printf("->%d\n",id_ex.RegWrite_write);
				printf("->%d\n",id_ex.MemWrite_write);
				printf("->%d\n",id_ex.MemtoReg_write);
				printf("->%d\n",id_ex.MemRead_write);
				printf("->%d\n",id_ex.Branch_write);
				printf("->%d\n",id_ex.readdata1_read);
				printf("->%d\n",id_ex.readdata2_read);
				printf("->%d\n",id_ex.inst15_11_read);
				printf("->%d\n",id_ex.add_read);
				printf("\n\n");


				printf("->%d\n",ex_mem.MemWrite_read );
				printf("->%d\n",ex_mem.MemRead_read  );
				printf("->%d\n",ex_mem.Branch_read   );
				printf("->%d\n",ex_mem.Zero_read     );
				printf("->%d\n",ex_mem.RegWrite_read );
				printf("->%d\n",ex_mem.MemtoReg_read );
				printf("->%d\n",ex_mem.readdata2_read);
				printf("->%d\n",ex_mem.addresult_read);
				printf("->%d\n",ex_mem.aluresult_read);
				printf("\n\n");

				printf("->%d\n",mem_wb.RegWrite_write      );
				printf("->%d\n",mem_wb.MemtoReg_write      );
				printf("->%d\n",mem_wb.readdata_write      );
				printf("->%d\n",mem_wb.addressbypass_write );
				printf("->%d\n",mem_wb.write_register_write);

				*/
				
				/*
				for(i=0;i<34;i++)
				{
					printf("####### R%d  =  %d\n",i,rf[i]);
				}
				
				for(i=0;i<20;i++)
				{
					printf("####### %d\n",mem[i]);
				}*/
				/*

				for(i=0;i<20;i++)
				{
					printf("####### %d\n",mem[i]);
				}*/
		}
		else if(!strcmp(read,"regdump"))
		{
			for(i=0;i<10;i++)
			{
				printf("$$0%d: 0x%x\n",i,rf[i]);
			}
			for(i=10;i<32;i++)
			{
				printf("$$%d: 0x%x\n",i,rf[i]);
			}

			printf("hi: 0x%x\n",rf[32]);
			printf("lo: 0x%x\n",rf[33]);
			printf("pc: 0x%x\n",PC);
		}
		else if(!strcmp(read,"memdump"))
		{
			int offset;
			int l;
			scanf("%x",&offset);
			//printf("%d",offset);
			scanf("%d",&l);
			//printf("%d\n",l);
			for(i=0;i<l;i++)
			{	
				if(offset >= 268500992)
				printf("0x%x: 0x%x\n",(offset + 4*i),mem[offset-268500992 + i]);
			}

			//printf("clear");
		}
		else if(!strcmp(read,"exit"))
		{
			break;
		}
	}

	FILE *fout = fopen(argv[3], "w");
	tim++;
	float ipc = num_inst/(float)tim;
	float t = tim/2.0;
	float it = (tim-num_inst)/2.0;
	float itp = (tim-num_inst)/(float)tim*100.0;
	fprintf(fout,"Instructions,%d\n",num_inst);
	fprintf(fout,"Cycles,%d\n",tim);
	fprintf(fout,"IPC,%.4f\n",ipc);
	fprintf(fout,"Time (ns),%.4f\n",t);
	fprintf(fout,"Idle time (ns),%.4f\n", it);
	fprintf(fout,"Idle time (%%),%.4f%%\n",itp);
	fprintf(fout,"Cache Summary\n");
	fprintf(fout,"Cache L1-I\n");
	fprintf(fout,"num cache accesses,%d\n",cachei);
	fprintf(fout,"Cache L1-D\n");
	fprintf(fout,"num cache accesses,%d\n",cached);
	
	

}

yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}

/*void firststage()
{
	char* instl = im[pc].instr; char* namel = im[pc].name;

}*/
/*
void secondstage()
{

	char* inst,char* name;

	if(!strcmp(name,"add"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		ALUOp = "010";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"sub"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		ALUOp = "110";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"and"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		ALUOp = "000";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"or"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		ALUOp = "001";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"lw"))
	{
		RegDest = 0;
		RegWrite = 1;
		ALUSrc = 1;
		ALUOp = "010";
		Branch = 0;
		MemRead = 1;
		MemWrite = 0;
		MemtoReg = 1;
	}
	else if(!strcmp(name,"addi"))
	{
		RegDest = 0;
		RegWrite = 1;
		ALUSrc = 1;
		ALUOp = "010";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"sw"))
	{
		//RegDest = 0;
		RegWrite = 0;
		ALUSrc = 1;
		ALUOp = "010";
		Branch = 0;
		MemRead = 0;
		MemWrite = 1;
		//MemtoReg = 0;	
	}
	else if(!strcmp(name,"beq"))
	{
		//RegDest = 0;
		RegWrite = 0;
		ALUSrc = 0;
		ALUOp = "110";
		Branch = 1;
		MemRead = 0;
		MemWrite = 0;
		//MemtoReg = 0;
	}
	else if(!strcmp(name,"j"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"slt"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		ALUOp = "111";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
}*/
