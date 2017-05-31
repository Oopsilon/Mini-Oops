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
%type comma_separated_fields { std::list<Field> * }
%type fields { std::list<Field> * }
%type field { Field }

%type class_methods { std::list<Method> * }
%type methods { std::list<Method> * }
%type method { Method }
%type method_type_specifier { Method::MethType }
%type method_arg_list { std::list<Field> * }

%syntax_error {
  dbg("%d:%d: Syntax error\n", cg.last_line, cg.last_col);
}

file
    ::= listings EOF.

listings
    ::= class(c). { cg.add_class(c); }
listings
    ::= listings class(c). { cg.add_class(c); }

class(C)
    ::= CLASS SYM(b) COLON SYM(s) klass_intf_requires(kir) klass_impl_requires(kmr) class_fields(f) class_methods(m) END.
    {
        C = {b, s, f, m, kir, kmr};
    }

klass_intf_requires(KIR)
    ::= KLASS_INTF_REQUIRES C_CODE(c). { KIR = c; }
klass_intf_requires(KIR)
    ::= . { KIR = new std::string; }

klass_impl_requires(KMR)
    ::= KLASS_IMPL_REQUIRES C_CODE(c). { KMR = c; }
klass_impl_requires(KMR)
    ::= . { KMR = new std::string; }

desc_intf_requires(DIR)
    ::= DESC_INTF_REQUIRES C_CODE(c). { DIR = c; }

desc_impl_requires(DMR)
    ::= DESC_IMPL_REQUIRES C_CODE(c). { DMR = c; }

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

methods(ML)
    ::= method(m). { ML = new std::list<Method>({m}); }
methods(ML)
    ::= methods(ml) method(m). { ML = ml; ML->push_back(m); }

method(M)
    ::= method_type_specifier(t) SYM(n) method_arg_list(l) C_CODE(c).
    {
        M = {t, new std::string, n, l, c};
    }

method_type_specifier(T) ::= CONSTRUCTOR. { T = Method::EConstructor; }

method_arg_list(FL)
    ::= BRACKET_OPEN comma_separated_fields(fl) BRACKET_CLOSE.
    {
        FL = fl;
    }

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
