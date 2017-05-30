%{
#include "Classgen.h"
#include "gram.tab.h"
%}

%option reentrant
%option noyywrap
%option stack
%option yylineno
%option extra-type = "Classgen *"

%{

#define RVAL yyextra->lexResult

#define YY_USER_INIT \
    yyextra->last_line = 0; \
    yyextra->last_col = 0;

#define YY_USER_ACTION \
    yyextra->first_line = yyextra->last_line; \
    yyextra->first_col = yyextra->last_col; \
    \
    for(int i = 0; yytext[i] != '\0'; i++) \
    { \
        if(yytext[i] == '\n') \
        { \
            yyextra->last_line++; \
            yyextra->last_col = 0; \
        } \
        else \
            yyextra->last_col++; \
    }
%}

DECIMAL_INTEGER [1-9][0-9]*
ST   ([a-zA-Z\x80-\xf3])*
SYM  [^ \t\v\n\r\f:/.\(\)/+-/*//;.{@<>]
NL \n

 /* shuts up codelite */

KEYW {ST}({SYM}{ST}|{ST}?)+":"
SYML {ST}({SYM}{ST}|{ST}?)+

%x STRING
%x CQUOTE
%x CTYPE
%x INCLUDE
%x SC

%%

[ \t\r\n]+

{SYML} {
           RVAL = new std::string(yytext);
           return TK_SYM;
       }
