/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_SYSY_HOME_RYJ_COMPILER_MYCOMPILER_BUILD_PARSER_TAB_HPP_INCLUDED
# define YY_SYSY_HOME_RYJ_COMPILER_MYCOMPILER_BUILD_PARSER_TAB_HPP_INCLUDED
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
#line 23 "/home/ryj/compiler/mycompiler/src/parser.y"

    class AST *ast; //class关键字必需添加

#line 89 "/home/ryj/compiler/mycompiler/build/parser.tab.hpp"

};
typedef union SYSYSTYPE SYSYSTYPE;
# define SYSYSTYPE_IS_TRIVIAL 1
# define SYSYSTYPE_IS_DECLARED 1
#endif


extern SYSYSTYPE sysylval;

int sysyparse (void);

#endif /* !YY_SYSY_HOME_RYJ_COMPILER_MYCOMPILER_BUILD_PARSER_TAB_HPP_INCLUDED  */
