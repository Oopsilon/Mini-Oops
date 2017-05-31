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
    ::= class(c). { c.generate(); }
listings
    ::= listings class.

class(C)
    ::= CLASS SYM(b) COLON SYM(s) class_fields(f) class_methods(m) END.
    {
        C = {b, s, f};
    }

class_fields
    ::= fields.
class_fields
    ::= .

fields(FL)
    ::= field(f) SEMICOLON. { FL = new std::list<Field>({f}); }
fields(FL)
    ::= fields(fl) field(f) SEMICOLON. { FL = fl; FL->push_back({f}); }

class_methods
    ::= methods.
class_methods
    ::= .

methods
    ::= method .
methods
    ::= methods method.

method ::= method_type_specifier method_arg_list C_CODE.

method_type_specifier ::= CONSTRUCTOR.

method_arg_list ::= BRACKET_OPEN comma_separated_fields BRACKET_CLOSE.

comma_separated_fields
    ::= field.
comma_separated_fields
    ::= comma_separated_fields COMMA field.

field(F)
    ::= TYPE(t) SYM(s). { F = {t, s}; }
