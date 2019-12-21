%{
#include "front/state.h"
#include "front/ast/ast.h"
#include "OopsC.h"
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

SYM_ST [^ \t\v\n\r\f:/.\(\)/+-/*//;.{@<>\[\]\^(0-9)]
SYM_END [^ \t\v\n\r\f:/.\(\)/+-/*//;.{@<>\[\]\^]
NL \n
COMMENT \"(\\.|[^"])*\"

 /* shuts up codelite */

KEYW {SYM_ST}({SYM_END}?)+":"
SYML {SYM_ST}({SYM_END}?)+
SYLI ":"{SYM_ST}({SYM_END}?)+

%x STRING
%x CQUOTE
%x CTYPE
%x INCLUDE
%x SC

%%

[ \t\r\n]+

{COMMENT}

"Instance"  return TK_INSTANCE;
"Self"      return TK_SELF;
"Class"     return TK_UCLASS;

"class"		return TK_CLASS;
"protocol"	return TK_PROTOCOL;
"end" 		return TK_END;

 /* Inference clause tokens. */
"this"      return TK_THIS;
"arg"		return TK_ARG;
"returnType" return TK_RETURNTYPE;
"where"     return TK_WHERE;

"in"        return TK_IN;

"Nil"       return TK_NIL;

"<-"        return TK_ASSIGN;

"="         return TK_EQUALS;
"." 		return TK_DOT;
":"			return TK_COLON;
";"         return TK_SEMICOLON;
"("         return TK_BRACKET_OPEN;
")"         return TK_BRACKET_CLOSE;
"["         return TK_SQB_OPEN;
"]"         return TK_SQB_CLOSE;
"^"         return TK_RETURN;
"<"			return TK_ANGLE_OPEN;
">"			return TK_ANGLE_CLOSE;
","			return TK_COMMA;
"+"         return TK_PLUS;
"-"         return TK_MINUS;
"C|"        return TK_CBAR;
"|"         return TK_BAR;
"/"			return TK_FSLASH;
"\\"			return TK_BSLASH;

 /* Brace-enclosed C code. */
"{"	{
		BEGIN(CQUOTE);
		yyextra->brace_depth = 0;
		yyextra->setResult(new AST::Symbol(yyextra));
        AsLit(RVAL).setCQuoteLiteral();
	}
<CQUOTE>"{" yyextra->brace_depth++; AsLit(RVAL) += yytext;
<CQUOTE>"}" {
		if (yyextra->brace_depth-- == 0)
		{
			BEGIN(INITIAL);
			return TK_CQUOTE;
		}
		else
			AsLit(RVAL) += yytext;
	}
<CQUOTE>.|\n AsLit(RVAL) += yytext;

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

{DECIMAL_INTEGER} {
			yyextra->setResult(new AST::Symbol(yyextra));
			AsLit(RVAL).assign(yytext);
			return TK_INT;
		}

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

{SYLI} {
           yyextra->setResult(new AST::Symbol(yyextra));
           AsLit(RVAL).setSymLiteral();
           AsLit(RVAL).assign(yytext);
           return TK_QUOTESYM;
       }
