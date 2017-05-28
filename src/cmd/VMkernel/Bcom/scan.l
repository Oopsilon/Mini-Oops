%{
#include "Bcom/State.h"
#include "Bcom/AST.h"
#include "VMkernel.h"
#include "gram.tab.h"
%}

%option reentrant
%option noyywrap
%option stack
%option yylineno
%option extra-type = "ParserState *"

%{

#define RVAL yyextra->result()

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

#define AsLit(x) (*(dynamic_cast<AST::Symbol *>(x)))
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

"class"		return TK_CLASS;
"end" 		return TK_END;

":="        return TK_ASSIGN;
"|" 		return TK_BAR;
"." 		return TK_DOT;
":"			return TK_COLON;
"("         return TK_BRACKET_OPEN;
")"         return TK_BRACKET_CLOSE;
"+"         return TK_PLUS;
"-"         return TK_MINUS;
"^"         return TK_RETURN;
"{"         return TK_BR_OPEN;
"}"         return TK_BR_CLOSE;

"@<syscall" {
    BEGIN(SC);
    return TK_SYSCALL;
}

<SC>">" {
    BEGIN(INITIAL);
    return TK_END_SYSCALL;
}

<SC>{SYML} {
    yyextra->setResult(new AST::Symbol(yyextra));
    AsLit(RVAL).setSymLiteral();
    AsLit(RVAL).assign(yytext);
    return TK_SYMLITERAL;
}

 /* @include(path/to/file) */
"@include("   {
    BEGIN(INCLUDE);
    yyextra->setResult(new AST::Symbol(yyextra));
}
<INCLUDE>")" {
    yyextra->oc.parse(AsLit(RVAL));
    BEGIN(INITIAL);
}
<INCLUDE>.|\n AsLit(RVAL) += yytext;

 /* String literal */
\'  {
        BEGIN(STRING);
        yyextra->setResult(new AST::Symbol(yyextra));
        AsLit(RVAL).setStringLiteral();
    }
<STRING><<EOF>>
<STRING>[^\\\'\r\n\"]+              AsLit(RVAL) += yytext;
<STRING>{NL}+                       AsLit(RVAL) += yytext;
<STRING>"'"                         BEGIN(INITIAL); return TK_SLITERAL;

{KEYW} {
           yyextra->setResult(new AST::Symbol(yyextra));
           AsLit(RVAL).setSymLiteral();
           AsLit(RVAL).assign(yytext);
           return TK_KEYW;
       }

{SYML} {
           yyextra->setResult(new AST::Symbol(yyextra));
           AsLit(RVAL).setSymLiteral();
           AsLit(RVAL).assign(yytext);
           return TK_SYMLITERAL;
       }
