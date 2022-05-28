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

#ifndef YY_TIGGER_HOME_RYJ_COMPILER_MYCOMPILERTEMP_MYCOMPILER_BUILD_TIGGER_TAB_HPP_INCLUDED
# define YY_TIGGER_HOME_RYJ_COMPILER_MYCOMPILERTEMP_MYCOMPILER_BUILD_TIGGER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef TIGGERDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define TIGGERDEBUG 1
#  else
#   define TIGGERDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define TIGGERDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined TIGGERDEBUG */
#if TIGGERDEBUG
extern int tiggerdebug;
#endif

/* Token type.  */
#ifndef TIGGERTOKENTYPE
# define TIGGERTOKENTYPE
  enum tiggertokentype
  {
    IF = 258,
    RETURN = 259,
    VARIABLE = 260,
    NUM = 261,
    MALLOC = 262,
    END = 263,
    FUNCTION = 264,
    LOGICOP = 265,
    OP = 266,
    GOTO = 267,
    LABEL = 268,
    CALL = 269,
    STORE = 270,
    LOAD = 271,
    LOADADDR = 272,
    Reg = 273
  };
#endif

/* Value type.  */
#if ! defined TIGGERSTYPE && ! defined TIGGERSTYPE_IS_DECLARED
union TIGGERSTYPE
{
#line 17 "/home/ryj/compiler/mycompilertemp/mycompiler/src/tigger.y"

    class AST *ast;

#line 88 "/home/ryj/compiler/mycompilertemp/mycompiler/build/tigger.tab.hpp"

};
typedef union TIGGERSTYPE TIGGERSTYPE;
# define TIGGERSTYPE_IS_TRIVIAL 1
# define TIGGERSTYPE_IS_DECLARED 1
#endif


extern TIGGERSTYPE tiggerlval;

int tiggerparse (void);

#endif /* !YY_TIGGER_HOME_RYJ_COMPILER_MYCOMPILERTEMP_MYCOMPILER_BUILD_TIGGER_TAB_HPP_INCLUDED  */
