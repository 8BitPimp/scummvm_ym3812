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
     UNARY = 258,
     CASTREF = 259,
     VOID = 260,
     VAR = 261,
     POINT = 262,
     RECT = 263,
     ARRAY = 264,
     SYMBOL = 265,
     INT = 266,
     THEENTITY = 267,
     THEENTITYWITHID = 268,
     FLOAT = 269,
     BLTIN = 270,
     BLTINNOARGS = 271,
     ID = 272,
     STRING = 273,
     HANDLER = 274,
     tDOWN = 275,
     tELSE = 276,
     tNLELSIF = 277,
     tEND = 278,
     tEXIT = 279,
     tFRAME = 280,
     tGLOBAL = 281,
     tGO = 282,
     tIF = 283,
     tINTO = 284,
     tLOOP = 285,
     tMACRO = 286,
     tMCI = 287,
     tMCIWAIT = 288,
     tMOVIE = 289,
     tNEXT = 290,
     tOF = 291,
     tPREVIOUS = 292,
     tPUT = 293,
     tREPEAT = 294,
     tSET = 295,
     tTHEN = 296,
     tTO = 297,
     tWHEN = 298,
     tWITH = 299,
     tWHILE = 300,
     tNLELSE = 301,
     tFACTORY = 302,
     tMETHOD = 303,
     tALERT = 304,
     tBEEP = 305,
     tCLOSERESFILE = 306,
     tCLOSEXLIB = 307,
     tCURSOR = 308,
     tDELAY = 309,
     tGE = 310,
     tLE = 311,
     tGT = 312,
     tLT = 313,
     tEQ = 314,
     tNEQ = 315,
     tAND = 316,
     tOR = 317,
     tNOT = 318,
     tCONCAT = 319,
     tCONTAINS = 320,
     tSTARTS = 321,
     tSPRITE = 322,
     tINTERSECTS = 323,
     tWITHIN = 324
   };
#endif
/* Tokens.  */
#define UNARY 258
#define CASTREF 259
#define VOID 260
#define VAR 261
#define POINT 262
#define RECT 263
#define ARRAY 264
#define SYMBOL 265
#define INT 266
#define THEENTITY 267
#define THEENTITYWITHID 268
#define FLOAT 269
#define BLTIN 270
#define BLTINNOARGS 271
#define ID 272
#define STRING 273
#define HANDLER 274
#define tDOWN 275
#define tELSE 276
#define tNLELSIF 277
#define tEND 278
#define tEXIT 279
#define tFRAME 280
#define tGLOBAL 281
#define tGO 282
#define tIF 283
#define tINTO 284
#define tLOOP 285
#define tMACRO 286
#define tMCI 287
#define tMCIWAIT 288
#define tMOVIE 289
#define tNEXT 290
#define tOF 291
#define tPREVIOUS 292
#define tPUT 293
#define tREPEAT 294
#define tSET 295
#define tTHEN 296
#define tTO 297
#define tWHEN 298
#define tWITH 299
#define tWHILE 300
#define tNLELSE 301
#define tFACTORY 302
#define tMETHOD 303
#define tALERT 304
#define tBEEP 305
#define tCLOSERESFILE 306
#define tCLOSEXLIB 307
#define tCURSOR 308
#define tDELAY 309
#define tGE 310
#define tLE 311
#define tGT 312
#define tLT 313
#define tEQ 314
#define tNEQ 315
#define tAND 316
#define tOR 317
#define tNOT 318
#define tCONCAT 319
#define tCONTAINS 320
#define tSTARTS 321
#define tSPRITE 322
#define tINTERSECTS 323
#define tWITHIN 324




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 69 "engines/director/lingo/lingo-gr.y"
{
	Common::String *s;
	int i;
	double f;
	int e[2];	// Entity + field
	int code;
	int narg;	/* number of arguments */
	Common::Array<double> *arr;
}
/* Line 1529 of yacc.c.  */
#line 197 "engines/director/lingo/lingo-gr.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

