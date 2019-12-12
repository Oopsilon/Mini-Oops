%include {
#include <iostream>
#include <list>

#include "front/ast/ast.h"
#include "front/ast/typeRepr.h"
#include "front/ast/expr.h"
#include "front/ast/class.h"
#include "front/ast/protocol.h"

template <class T> T passList(T * l)
{
    T rval = l ? *l : T();
    if (l) delete l;
    return rval;
}

AST::Symbol passSym(AST::Symbol * sym)
{
    AST::Symbol rval = *sym;
    delete sym;
    return rval;
}

}

%token_prefix TK_
%token_type { AST::Symbol * }
%extra_argument { ParserState * pState}

/* Main syntax. */
%nonassoc IN.
%nonassoc BelowSemi.
%left TBelowInvoc.
%left COMMA SEMICOLON TInvoc.
%nonassoc SLITERAL SYMLITERAL KEYW BLKARG RETURN INCLUDE.
%right ASSIGN.
%left ANGLE_OPEN BRACKET_OPEN SQB_OPEN ANGLE_CLOSE BRACKET_CLOSE SQB_CLOSE.
%right DOT DotPrec.

%type directive { AST::Directive * }

%type class { AST::Class * }
%type protocol { AST::Protocol * }

%type opt_meth_decl_list { AST::Method::List * }
%type meth_decl_list { AST::Method::List * }

%type meth_decl { AST::Method * }

/* Name, list of parameters */
%type type_decl { AST::TypeDecl * }

%type opt_formal_list { AST::Field::List * }
%type formal_list { AST::Field::List * }
%type field_list { AST::Field::List * }
%type opt_varlist { AST::Field::List *}
%type opt_cvarlist { AST::Field::List *}

%type opt_block_formals { AST::Field::List * }
%type block_formals { AST::Field::List * }

%type block_formal { AST::Field * }
%type field { AST::Field * }

%type opt_proto_list { AST::TypeRepr::List * }
%type proto_list { AST::TypeRepr::List *}
%type type_comma_list { AST::TypeRepr::List *}

%type opt_bracketed_type { AST::TypeRepr * }
%type type { AST::TypeRepr * }

%type prot_qualifiable { AST::TypeRepr * }
%type nom_invok_or_dyn { AST::TypeRepr * }
%type self_invok { AST::TypeRepr * }
%type primary_type { AST::TypeRepr * }
%type self_type { AST::TypeRepr * }
%type nil_type { AST::TypeRepr * }
%type dyn_type { AST::TypeRepr * }

%type opt_primary_type_list { AST::TypeRepr::List * }
%type primary_type_list { AST::TypeRepr::List * }

%type expr { AST::Expr * }
%type atomic_expr { AST::Expr * }
%type call { AST::Expr * }
%type block_expr { AST::Expr * }
%type msg_expr { AST::MsgExpr * }
%type ident_expr { AST::IdentExpr * }
%type assign_expr { AST::AssignExpr * }

%type expr_list { AST::Expr::List * }
%type opt_arg_list { AST::Expr::List * }
%type arg_list { AST::Expr::List * }

%type meth_ci_spec { bool }

%syntax_error {
  dbg("%d:%d: Syntax error\n", pState->last_line, pState->last_col);
}

file ::= EOF.
file ::= listings EOF.

listings ::= directive(D). { pState->addDirective(D); }
listings ::= listings directive(D).  { pState->addDirective(D); }

directive ::= class.
directive ::= protocol.

class(C)
    ::= CLASS type_decl(d) COLON type(t) opt_proto_list(p) opt_cvarlist(c) opt_varlist(i)
        opt_meth_decl_list(m) END.
    {
        C = new AST::Class(d, t, passList(p), passList(c), passList(i), passList(m));
    }

protocol(P)
    ::= PROTOCOL type_decl(d) opt_proto_list(p) opt_cvarlist(c) opt_varlist(i) opt_meth_decl_list(m) END.
    {
        P = new AST::Protocol(d, passList(p), passList(m));
    }

type_decl(D)
    ::= sym_lit(n) opt_formal_list(f).
    {
        D = new AST::TypeDecl(*n, passList(f));
        delete n;
    }

opt_proto_list(P) ::= . { P = NULL; }
opt_proto_list    ::= proto_list.

proto_list(L) ::= ANGLE_OPEN type_comma_list(l) ANGLE_CLOSE. { L = l; }

type_comma_list(L) ::= type(t). { L = new AST::TypeRepr::List({t}); } 
type_comma_list(L)
    ::= type_comma_list(l) COMMA type(t).
    {
        (L = l)->push_back(t);
    }

opt_meth_decl_list(L)
    ::= . { L = NULL; }
opt_meth_decl_list
    ::= meth_decl_list.

meth_decl_list(L)
    ::= meth_decl(m). { L = new AST::Method::List({m}); }
meth_decl_list(L)
    ::= meth_decl_list(l) meth_decl(m). { (L = l)->push_back(m); }

meth_decl(M)
    ::= meth_ci_spec(ci) opt_bracketed_type(r) sym_lit(n) opt_formal_list(f)
        opt_inf_clause SQB_OPEN opt_varlist(v) expr_list(e) SQB_CLOSE.
    {
        M = new AST::Method(ci, r, passSym(n), passList(f), passList(v), passList(e));
    }

opt_cvarlist (L) ::= CBAR field_list(l) BAR. { L = l; } 
opt_cvarlist (L) ::= . { L = NULL; }

opt_varlist(L) ::= BAR field_list(l) BAR. { L = l; }
opt_varlist(L) ::= . { L = NULL; }

opt_bracketed_type(T)
    ::= BRACKET_OPEN type(t) BRACKET_CLOSE.
    {
        T = t;
    }
opt_bracketed_type(T)
    ::= . { T = AST::PlaceholderTypeRepr::instance(); }

meth_ci_spec(C)
    ::= PLUS. { C = true; }
meth_ci_spec(C)
    ::= MINUS. { C = false; }

opt_inf_clause(I)
    ::= . [TBelowInvoc] { I = NULL; }
opt_inf_clause
    ::= WHERE inf_bind_list.

inf_bind_list ::= inf_bind.
inf_bind_list ::= inf_bind_list COMMA inf_bind.

inf_bind ::= sym_lit EQUALS inf_expr.

opt_formal_list
    ::= field_list.
opt_formal_list(L)
    ::= . { L = NULL; }

field_list(L)
    ::= field(f). { L = new AST::Field::List({f}); }
field_list(L)
    ::= field_list(l) field(f).
    {
        L = l;
        L->push_back(f);
    }

field(F)
    ::= opt_bracketed_type(t) sym_lit(s). { F = new AST::Field(*s, t); delete s;  }

inf_expr ::= comp_inf_expr.

basic_inf_expr ::= THIS DOT inf_op.

comp_inf_expr ::= basic_inf_expr.
comp_inf_expr ::= comp_inf_expr DOT inf_op.

inf_op ::= RETURNTYPE.
inf_op ::= ARG int_lit.

type ::= prot_qualifiable.

prot_qualifiable
    ::= nom_invok_or_dyn. [TBelowInvoc]
prot_qualifiable(T)
    ::= nom_invok_or_dyn(t) proto_list(p). [TInvoc]
    {
        T = new AST::ProtQualTypeRepr(t, *p);
        delete p;
    }

nom_invok_or_dyn
    ::= primary_type. [TBelowInvoc]
nom_invok_or_dyn(T)
    ::= primary_type(t) primary_type_list(a). [TInvoc]
    {
        T = new AST::TypeInvocationRepr(t, *a);
        delete a;
    }

dyn_type(T) ::= ID. { T = AST::IdTypeRepr::instance(); }

opt_primary_type_list(L) ::= . { L = NULL; }
opt_primary_type_list    ::= primary_type_list .

primary_type_list(L) ::= primary_type(t). { L = new AST::TypeRepr::List({t});}
primary_type_list(L)
    ::= primary_type_list(l) COMMA primary_type(t).
    {
        (L = l)->push_back(t);
    }

primary_type(T)
    ::= sym_lit(s). { T = new AST::NamedTypeRepr(*s); delete s; }
primary_type
    ::= nil_type.
primary_type
    ::= dyn_type.
primary_type
    ::= self_type.
primary_type(T)
    ::= SQB_OPEN opt_primary_type_list(f) RETURN type(r) SQB_CLOSE.
    {
        T = new AST::BlockTypeRepr(r, passList(f));
    }
primary_type(T)
    ::= BRACKET_OPEN type(t) BRACKET_CLOSE. { T = t; }

self_type(T)
    ::= INSTANCE. { T = AST::InstanceTypeRepr::instance(); }
self_type(T)
    ::= SELF. { T = AST::SelfTypeRepr::instance(); }
self_type(T)
    ::= UCLASS. { T = AST::ClassTypeRepr::instance(); }

nil_type(T)
    ::= NIL. { T = AST::NilTypeRepr::instance(); }

expr_list(L) ::= expr(e). { L = new AST::Expr::List({e}); }
expr_list(L) ::= expr_list(l) SEMICOLON expr(e). { (L = l)->push_back(e); }

expr ::= atomic_expr.
expr ::= msg_expr.

opt_arg_list(O) ::= . { O = NULL; }
opt_arg_list    ::= arg_list.

arg_list(L) ::= atomic_expr(e). { L = new AST::Expr::List({e}); }
arg_list(L) ::= arg_list(l) atomic_expr(e). { (L = l)->push_back(e); }

atomic_expr(E)
    ::= BRACKET_OPEN expr(e) BRACKET_CLOSE. { E = e; }
atomic_expr(E)
    ::= ident_expr.
atomic_expr
    ::= block_expr.
atomic_expr
    ::= assign_expr.

assign_expr(A)
    ::= ident_expr(i) ASSIGN atomic_expr(e).
    {
        A = new AST::AssignExpr(i, e);
    }

ident_expr(I) ::= sym_lit(s). { I = new AST::IdentExpr(passSym(s)); }

block_expr(B)
    ::= SQB_OPEN opt_block_formals(f) opt_varlist(v)
        expr_list(e) SQB_CLOSE.
    {
        B = new AST::BlockExpr(AST::PlaceholderTypeRepr::instance(),
                               passList(f), passList(v), passList(e));
    }

msg_expr(M)
    ::= atomic_expr(r) DOT sym_lit(s) opt_arg_list(a).
    {
        //C = NULL;
        M = new AST::MsgExpr(r, passSym(s), passList(a));
    }

opt_block_formals
    ::= block_formals.
opt_block_formals(F)
    ::= . { F = NULL; }

block_formals(L) ::= block_formal(f). { L = new AST::Field::List({f}); }
block_formals(L)
    ::= block_formals(l) block_formal(f). { (L = l)->push_back(f); }

block_formal(F)
    ::= quotesym_lit(s).
    {
        F = new AST::Field(passSym(s), AST::PlaceholderTypeRepr::instance());
    }

int_lit         ::= INT.
sym_lit(S)      ::= SYMLITERAL(L). { S = dynamic_cast<AST::Symbol *>(L); }
keyw_lit(S)     ::= KEYW(L). { S = dynamic_cast<AST::Symbol *>(L); }
str_lit(S)      ::= SLITERAL(L). { S = dynamic_cast<AST::Symbol *>(L); }
cquote_lit(S)   ::= CQUOTE(L). { S = dynamic_cast<AST::Symbol *>(L); }
quotesym_lit(S) ::= QUOTESYM(L). { S = dynamic_cast<AST::Symbol *>(L); }