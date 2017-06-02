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
    ::= vm EOF.
vm
    ::= VM SYM(b) intf_requires(ir) impl_requires(mr)
        OP_TYPE EQ TYPE(ot) SEMICOLON
        instructions(i)
        END.
    {
        qg.vm = VM(*b, *ot, *i);
    }

intf_requires(IR)
    ::= INTF_REQUIRES C_CODE(c). { IR = c; }
intf_requires(IR)
    ::= . { IR = new std::string; }

impl_requires(MR)
    ::= IMPL_REQUIRES C_CODE(c). { MR = c; }
impl_requires(MR)
    ::= . { MR = new std::string; }

instructions(IL)
    ::= instruction(i). { IL = new std::list<Instruction>({i}); }
instructions(IL)
    ::= instructions(il) instruction(i).
    {
        IL = il;
        IL->push_back(i);
    }

instruction(I)
    ::= INSTRUCTION SYM(n) method_arg_list(a)
        SQB_OPEN opt_comma_separated_fields(st) DASHDASH
                 opt_comma_separated_fields(sg) SQB_CLOSE SEMICOLON.
    {
        I = {n, a, st, sg};
    }

fields(FL)
    ::= field(f) SEMICOLON. { FL = new std::list<Field>({f}); }
fields(FL)
    ::= fields(fl) field(f) SEMICOLON. { FL = fl; FL->push_back({f}); }

method_arg_list(FL)
    ::= BRACKET_OPEN opt_comma_separated_fields(fl) BRACKET_CLOSE.
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
        FL->push_back(f);
    }

field(F)
    ::= TYPE(t) SYM(s). { F = {t, s}; }
