%include {
#include <string>
#include <list>

#include "oops-platform/misc.h"

#include "AST.h"
#include "Classgen.h"
}

%token_prefix TK_
%token_type { std::string * }

%type class { Class }
%type class_fields { std::list<Field> * }
%type fields { std::list<Field> * }
%type field { Field }

%syntax_error {
  dbg("%d:%d: Syntax error\n", cg.last_line, cg.last_col);
}

file
    ::= listings EOF.

listings
    ::= class.
listings
    ::= listings class.

class(C)
    ::= CLASS SYM(b) COLON SYM(s) class_fields(f) END.
    {
        C = {b, s, f};
    }

class_fields
    ::= fields.
class_fields
    ::= .

fields(FL)
    ::= field(f). { FL = new std::list<Field>({f}); }
fields(FL)
    ::= fields(fl) field(f). { FL = fl; FL->push_back({f}); }

field(F)
    ::= TYPE(t) SYM(s) SEMICOLON. { F = {t, s}; }
