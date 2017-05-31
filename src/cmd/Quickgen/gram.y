%include {
#include <string>
#include <list>

#include "oops-platform/misc.h"

#include "AST.h"
#include "Quickgen.h"
}

%token_prefix TK_
%token_type { std::string * }

%type vm { VM }

%syntax_error {
  dbg("%d:%d: Syntax error\n", qg.last_line, qg.last_col);
}

file
    ::= listings EOF.

listings
    ::= vm(c). {  }
listings
    ::= listings vm(c). { }

vm(C)
    ::= VM SYM(b) END.
    {
    }

fields(FL)
    ::= field(f) SEMICOLON. { /*FL = new std::list<Field>({f});*/ }
fields(FL)
    ::= fields(fl) field(f) SEMICOLON. { /*FL = fl; FL->push_back({f});*/ }


method_arg_list(FL)
    ::= BRACKET_OPEN comma_separated_fields(fl) BRACKET_CLOSE.
    {
        FL = fl;
    }

comma_separated_fields(FL)
    ::= field(f).  { /*FL = new std::list<Field>({f});*/ }
comma_separated_fields(FL)
    ::= comma_separated_fields(fl) COMMA field(f).
    {
        /*FL = fl;
        FL->push_back({f});*/
    }

field(F)
    ::= TYPE(t) SYM(s). { /*F = {t, s};*/ }

c_code ::= C_CODE.