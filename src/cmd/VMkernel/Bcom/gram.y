%include {
#include <iostream>
#include <list>

#include "Bcom/MsgSyntax.h"
#include "Bcom/AST.h"
#include "Bcom/Defs.h"
#include "Bcom/Expressions.h"
}

%token_prefix TK_
%token_type { AST::Symbol * }
%extra_argument { ParserState * pState}

/* Main syntax. */
%nonassoc SLITERAL SYMLITERAL KEYW BLKARG RETURN INCLUDE.
%right ASSIGN.
%left PLUS MINUS.
%left BRACKET_OPEN BRACKET_CLOSE.
%left AssignPrec.
%left MsgPrec.

%type class { AST::Class * }

%type block_formal_list { AST::Symbol::List * }
%type block_vardefs { AST::Symbol::List *}

%type opt_vardefs { AST::Symbol::List * }
%type vardefs  { AST::Symbol::List * }
%type opt_vdecl_list  { AST::Symbol::List * }
%type vdecl_list  { AST::Symbol::List * }
%type vdecl { AST::Symbol  * }

%type directive { AST::Directive * }
%type unary_decl { AST::Symbol * }
%type binary_decl { std::pair<AST::Symbol, AST::Symbol> *}
%type keyw_decl_list { std::vector<AST::SelectorDecl::KeywDecl> * }
%type keyw_decl { AST::SelectorDecl::KeywDecl * }
%type sel_decl { AST::SelectorDecl * }

%type meth_decl { AST::Method * }
%type meth_is_class_specifier { bool }

%type code { AST::Code * }

%type opt_statements { AST::Expr::List * }
%type statements { AST::Expr::List * }
%type statement { AST::Expr * }

%type operand { AST::Expr * }
%type expression { AST::Expr * }
%type ident_expr { AST::IdentExpr * } 
%type literal_expr { AST::Expr * }
%type block_expr { AST::Block * }

%type binary_msg_operand { AST::Expr * }
%type keyw_msg_argument { AST::Expr * }

%type unary_msg { AST::UnaryMsg * }
%type unary_msg_chain { MsgChainEntry::List *}
%type opt_unary_msg_chain { MsgChainEntry::List * }

%type binary_msg { AST::BinMsg * }
%type binary_msg_chain { MsgChainEntry::List * }
%type opt_binary_msg_chain { MsgChainEntry::List * }

%type keyw_msg_segment { AST::KeywMsgPart * }
%type keyw_msg { AST::KeywMsg * }
%type opt_keyw_msg { AST::KeywMsg * }

%type msg_chain { MsgChainEntry::List * }
%type msg_expr { AST::MsgExpr * }

%syntax_error {
  dbg("%d:%d: Syntax error\n", pState->last_line, pState->last_col);
}

file ::= EOF.
file ::= listings EOF.

listings ::= directive(D). { pState->addDirective(D); }
listings ::= listings directive(D).  { pState->addDirective(D); }

directive ::= class.
directive ::= meth_decl.

class(i)
    ::= CLASS sym_lit(N) COLON sym_lit (S) END.
    {
        i = new AST::Class(*N, *S,  {}, {});
        delete N;
        delete S;
    }
class(i)
    ::= CLASS sym_lit(N) COLON sym_lit (S) vardefs(IV) opt_vdecl_list(CV)
        BAR END.
    {
        i = new AST::Class(*N, *S,  *IV, *CV);
        delete N;
        delete S;
        delete IV;
        delete CV;
    }
class(i)
    ::= CLASS sym_lit(N) COLON sym_lit (S) vardefs(IV) END.
    {
        i = new AST::Class(*N, *S,  *IV, {});
        delete N;
        delete S;
        delete IV;
    } 

meth_decl(M)
    ::= meth_is_class_specifier(c) sym_lit(o) sel_decl(s)
        BR_OPEN opt_vardefs(v) code(code) BR_CLOSE.
    {
        M = new AST::Method(c, *o, *s, *v, *code);
        delete o, s, v, code;
    }

meth_is_class_specifier(C) ::= PLUS. { C = true; }
meth_is_class_specifier(C) ::= MINUS. { C = false; }

code(C) ::= expression(e). { C = new AST::Code({}, e); }
code(C) ::= opt_statements(s). { C = new AST::Code(*s); delete s; }
code(C) ::= statements(s) expression(e). { C = new AST::Code(*s, e); delete s; }

opt_statements(E) ::= statements(e). { E = e; }
opt_statements(E) ::= . { E = new AST::Expr::List; }

statements(E) ::= statement(s). { E = new AST::Expr::List( { s } ); }
statements(E) ::= statements(l) statement(s). {
    E = l;
    E->push_back(s);
}

statement(S) ::= expression(e) DOT. { S = e; }
statement(S) ::= SYSCALL sym_lit(s) END_SYSCALL DOT. {
    S = new AST::SyscallStmt(*s);
    delete s;
}
statement(S) ::= RETURN expression(e) DOT. {
    S = new AST::ReturnStmt(e);
}

expression(E) ::= operand(l) ASSIGN expression(r). {
    E = new AST::AssignExpr(l, r);
}
expression ::= msg_expr.

operand    ::= literal_expr.
operand    ::= ident_expr.
operand    ::= block_expr.
operand(E) ::= BRACKET_OPEN expression(e) BRACKET_CLOSE. { E = e; }

unary_msg ::= sym_lit.

unary_msg_chain(L) ::= unary_msg(u). { L = new MsgChainEntry::List({ u }); }
unary_msg_chain(L) ::= unary_msg_chain(l) unary_msg(u). {
    L = l;
    L->push_back(u);
}

opt_unary_msg_chain    ::= unary_msg_chain.
opt_unary_msg_chain(L) ::= . { L = NULL; }

binary_msg_operand(O) ::= operand(o) opt_unary_msg_chain(c). {
    if (c)
        O = unpackMsgChain(o, c);
    else
        O = o;
}
binary_msg(B) ::= binary_selector(s) binary_msg_operand(o). {
    B = new AST::BinMsg(*s, o);
}

binary_msg_chain(C) ::= binary_msg(m). { C = new MsgChainEntry::List({ m }); }
binary_msg_chain(C) ::= binary_msg_chain(c) binary_msg(m). {
    C = c;
    C->push_back(m);
}

opt_binary_msg_chain    ::= binary_msg_chain.
opt_binary_msg_chain(C) ::= . { C = NULL; }

keyw_msg_argument(O) ::= binary_msg_operand(o) opt_binary_msg_chain(c). {
    if (c)
        O = unpackMsgChain(o, c);
    else
        O = o;
}

keyw_msg_segment(K) ::= keyw_lit(k) keyw_msg_argument(e). {
    K = new AST::KeywMsgPart(*k, e);
}

keyw_msg(L) ::= keyw_msg_segment(k). { L = new AST::KeywMsg({*k}); }
keyw_msg(L) ::= keyw_msg(l) keyw_msg_segment(k). {
    L = l;
    L->keyws.push_back(*k); 
}

opt_keyw_msg(K) ::= . { K = NULL; }
opt_keyw_msg    ::= keyw_msg .

/* So what happens here? Let's represent the receiver as R.
 * R is sent U. (R U) is sent UC[1], then ((R U) UC[1]) is sent UC[2...]
 * (((R U) UC[1]) UC[n]) could be sent stuff from bc, but fuck that for now -
 * this is already a pain to unpack.
 * Finally we get ((((R U) UC[1])UC[n]) kw). */
msg_chain(M)
    ::= unary_msg(u) opt_unary_msg_chain(uc) opt_binary_msg_chain(bc)
        opt_keyw_msg(kw).
    {
        M = new MsgChainEntry::List({u});
        if (uc) M->insert(M->end(), uc->begin(), uc->end());
        if (bc) M->insert(M->end(), bc->begin(), bc->end());
        if (kw) M->push_back(kw);
    }
msg_chain(M)
    ::= binary_msg(b) opt_binary_msg_chain(bc) opt_keyw_msg(kw).
    {
        M = new MsgChainEntry::List({b});
        if (bc) M->insert(M->end(), bc->begin(), bc->end());
        if (kw) M->push_back(kw);
    }
msg_chain(M) ::= keyw_msg(k). { M = new MsgChainEntry::List({k}); }

msg_expr(M)
    ::= operand(r) msg_chain(k). [MsgPrec] { M = unpackMsgChain(r, k); }

sel_decl(S) ::= sym_lit(s). { S = new AST::SelectorDecl(*s); delete s; }
sel_decl(S) ::= binary_decl(b). { S = new AST::SelectorDecl(*b); delete b; }
sel_decl(S) ::= keyw_decl_list(k). { S = new AST::SelectorDecl(*k); delete k; }

keyw_decl_list(L) ::= keyw_decl(k). {
    L = new std::vector<AST::SelectorDecl::KeywDecl>({*k});
    delete k;
}
keyw_decl_list(L) ::= keyw_decl_list(l) keyw_decl(k). { 
    L = l;
    L->push_back(*k);
    delete k;
}

keyw_decl(K) ::= keyw_lit(k) sym_lit(s). {
    K = new AST::SelectorDecl::KeywDecl({*k, *s});
    delete k;
    delete s;
}

binary_decl(B) ::= BINOP(b) sym_lit(s). {
    B = new std::pair<AST::Symbol, AST::Symbol>(*b, *s);
    delete b;
    delete s;
}

opt_vardefs     ::=	vardefs.
opt_vardefs(L)  ::= . { L = new AST::Symbol::List; }

vardefs(L) ::= BAR opt_vdecl_list(V) BAR. { L = V; }

opt_vdecl_list      ::= vdecl_list.
opt_vdecl_list(L)   ::= . { L = new AST::Symbol::List; }

vdecl_list(L)
    ::= vdecl(v) DOT.
    {
        L = new AST::Symbol::List({*v});
        delete v; 
    }
vdecl_list(L)
    ::= vdecl_list(l) vdecl(v) DOT.
    {
        L = l;
        L->push_back(*v);
        delete v;
    }

/* Variable declaration part (someType someVar) */
vdecl ::= sym_lit.

ident_expr(E) ::= sym_lit(s). { E = new AST::IdentExpr(*s); }
literal_expr(E) ::= str_lit(s). { /*E = new AST::LiteralExpr(*s);*/ }

/* Block syntax:
 * { :hello :world | local. vars. | statements }
 * { :hello :world | statements }
 * { | local. vars. | statements }
 * { statements }
 * Note that a ^ return symbol in a block represents a non-local return: it
 * returns back to the method context from which was called the method context
 * within which the block was defined. opt_expression represents an expression,
 * the last within the block, which will be returned as the value of the block
 * rather than the block itself (which is a block's default return value) if
 * it is found - i.e. that final expression must NOT be followed with a dot.
 */
block_expr(B)
    ::= BR_OPEN block_formal_list(f) block_vardefs(v) code(c) BR_CLOSE.
    {
        B = new AST::Block(*f, *v, *c);
        delete f, v, c;
    }
block_expr(B)
    ::= BR_OPEN block_formal_list(f) code(c) BR_CLOSE.
    {
        B = new AST::Block(*f, {}, *c);
        delete f, c;
    }
block_expr(B) ::= BR_OPEN vardefs(v) code(c) BR_CLOSE.
    {
        B = new AST::Block({}, *v, *c);
        delete v, c;
    }
block_expr(B) ::= BR_OPEN code(c) BR_CLOSE.
    {
        B = new AST::Block({}, {}, *c);
        delete c;
    }

block_vardefs ::= opt_vdecl_list BAR.

block_formal_list(L)
    ::= block_formal(f). { L = new AST::Symbol::List({*f}); delete f; }
block_formal_list(L)
    ::= block_formal_list(l) block_formal(f).
    {
        L = l;
        l->push_back(*f);
        delete f;
    }

block_formal(F) ::= COLON sym_lit(s). { F = s; }

binary_selector ::= BINARYSEL.
binary_selector ::= arith_selector.

arith_selector ::= plus.
arith_selector ::= minus.

plus ::= PLUS.
minus ::= MINUS.

sym_lit(S) ::= SYMLITERAL(L). { S = dynamic_cast<AST::Symbol *>(L); }
keyw_lit(S) ::= KEYW(L). { S = dynamic_cast<AST::Symbol *>(L); }
str_lit(S) ::= SLITERAL(L). { S = dynamic_cast<AST::Symbol *>(L); }