%{
/*
 * (C) Copyright 2011
 * Alex Waterman <imNotListening@gmail.com>
 *
 * myrt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * myrt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with myrt.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Handles reading the state machine files.
 */

#include <stdio.h>
#include <parser.h>

/* To communicate with the program propper. */
extern char *__parsed_text;
extern int   __line_no;

%}

%option noyywrap
%option nounput
%option noinput

DIGIT		[\-0-9]
INTEGER		{DIGIT}+
FLOAT		{DIGIT}+"."{DIGIT}*
VECTOR		\[[ \t]*({INTEGER}|{FLOAT})[ \t]+({INTEGER}|{FLOAT})[ \t]+({INTEGER}|{FLOAT})[ \t]*\]
COMMAND		[a-zA-Z0-9_\-]+

%%

#.*		return TOKEN_COMMENT;

{VECTOR}	__parsed_text = yytext; return TOKEN_VECTOR;
{INTEGER}	__parsed_text = yytext; return TOKEN_INTEGER;
{FLOAT}		__parsed_text = yytext; return TOKEN_FLOAT;
{COMMAND}	__parsed_text = strdup(yytext); return TOKEN_COMMAND;
\n		__line_no++; return TOKEN_NEWLINE;
[ \t]*		
<<EOF>>		return TOKEN_EOF;

%%
