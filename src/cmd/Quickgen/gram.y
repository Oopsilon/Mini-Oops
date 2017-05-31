%include {
#include <string>
#include <list>

#include "oops-platform/misc.h"

#include "AST.h"
#include "Quickgen.h"
}

%token_prefix TK_
%token_type { std::string * }

%type instructions { std::list<Instruction> *}
%type instruction { Instruction }

%type fields { std::list<Field> * }
%type method_arg_list { std::list<Field> * }
%type opt_comma_separated_fields { std::list<Field> * }
%type comma_separated_fields { std::list<Field> * }
%type field { Field }

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
    ::= VM SYM(b)
        OP_TYPE EQ TYPE(ot) SEMICOLON
        instructions(i)
        END.
    {
        qg.add_vm(VM(*b, *ot, *i));
    }

instructions
    ::= instruction.
instructions
    ::= instructions instruction.

instruction(I)
    ::= INSTRUCTION SYM(n) method_arg_list(a)
        SQB_OPEN opt_comma_separated_fields(st) EQEQ
                 opt_comma_separated_fields(sg) SQB_CLOSE
        C_CODE(c).

fields(FL)
    ::= field(f) SEMICOLON. { FL = new std::list<Field>({f}); }
fields(FL)
    ::= fields(fl) field(f) SEMICOLON. { FL = fl; FL->push_back({f}); }

method_arg_list(FL)
    ::= BRACKET_OPEN comma_separated_fields(fl) BRACKET_CLOSE.
    {
        FL = fl;
    }

opt_comma_separated_fields
    ::= comma_separated_fields.
opt_comma_separated_fields(FL)
    ::= . { FL = new std::list<Field>; }

comma_separated_fields(FL)
    ::= field(f).  { FL = new std::list<Field>({f}); }
comma_separated_fields(FL)
    ::= comma_separated_fields(fl) COMMA field(f).
    {
        FL = fl;
        FL->push_back({f});
    }

field(F)
    ::= TYPE(t) SYM(s). { F = {t, s}; }
