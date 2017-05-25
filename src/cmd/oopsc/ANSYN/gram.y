%include {
#include <iostream>
#include <list>

#include "ANSYN/MsgSyntax.h"
#include "AST/AST.h"
#include "AST/Symbol.h"
#include "AST/ClassDef.h"
}

%token_prefix TK_
%token_type { AST::Symbol * }
%extra_argument { ParserState * pState}

/* Main syntax. */
%nonassoc SLITERAL SYMLITERAL KEYW BLKARG RETURN INCLUDE CQUOTE.
%right ASSIGN.
%left PLUS MINUS.
%left STAR PERCENT SLASH.
%left BRACKET_OPEN BRACKET_CLOSE.

%type unary_decl { AST::Symbol * }
%type binary_decl { std::pair<AST::Symbol, AST::Symbol> *}
%type keyw_decl_list { std::vector<AST::SelectorDecl::KeywDecl> * }
%type keyw_decl { AST::SelectorDecl::KeywDecl * }
%type sel_decl { AST::SelectorDecl * }

%type meth_decl { AST::Method * }

%type meth_is_class_specifier { bool }

%syntax_error {
  dbg("%d:%d: Syntax error\n", pState->last_line, pState->last_col);
}

file ::= EOF.
file ::= listings EOF.

listings ::= directive(D).
listings ::= listings directive(D).

directive ::= class.

class(i) ::= CLASS sym_lit(N) COLON sym_lit (S) opt_meth_decl_list(m) END.
class(i) ::= CLASS sym_lit(N) COLON sym_lit (S) vardefs(IV) opt_vdecl_list(CV)
             BAR opt_meth_decl_list(m) END.
class(i) ::= CLASS sym_lit(N) COLON sym_lit (S) vardefs(IV) 
             opt_meth_decl_list(m) END. 

opt_meth_decl_list ::= meth_decl_list.
opt_meth_decl_list(L) ::= .

meth_decl_list(L) ::= meth_decl(m).
meth_decl_list(L) ::= meth_decl_list(l) meth_decl(m).

meth_decl(M) ::= meth_is_class_specifier(c) sel_decl(s) comp_stmt(code). {
    M = new AST::Method({c, *s});
}

meth_is_class_specifier(C) ::= PLUS. { C = true; }
meth_is_class_specifier(C) ::= MINUS. { C = false; }

comp_stmt(C) ::= SQB_OPEN opt_vardefs(v) opt_statements(e) SQB_CLOSE.

comp_stmt(C) ::= cquote_stmt(c).

cquote_stmt(C) ::= cquote(c).

opt_statements(E) ::= statements(e). { E = e;}
opt_statements(E) ::= .

statements(E) ::= statement(e).
statements(E) ::= statements(l) statement(e).

statement ::= comp_stmt.
statement ::= expression DOT.

expression ::= assignment_expression.

assignment_expression ::= primary_expression.

assignment_expression(A) ::= expression(v1) ASSIGN expression(v2).

primary_expression    ::= operand.
primary_expression    ::= msg_expr.

operand    ::= literal_expr.
operand    ::= ident_expr.
operand    ::= block_expr.
operand(E) ::= BRACKET_OPEN expression(e) BRACKET_CLOSE. { E = e; }

unary_msg(U) ::= sym_lit(s).

unary_msg_chain(L) ::= unary_msg(u). { /*L = new MsgChainEntry::List({ u });*/ }
unary_msg_chain(L) ::= unary_msg_chain(l) unary_msg(u).

opt_unary_msg_chain    ::= unary_msg_chain.
opt_unary_msg_chain(L) ::= . { L = NULL; }

binary_msg_operand ::= operand opt_unary_msg_chain.
binary_msg ::= BINARYSEL binary_msg_operand.

binary_msg_chain ::= binary_msg.
binary_msg_chain ::= binary_msg_chain binary_msg.

opt_binary_msg_chain    ::= binary_msg_chain.
opt_binary_msg_chain(C) ::= . { C = NULL; }

keyw_msg_argument ::= binary_msg_operand opt_binary_msg_chain.

keyw_msg_segment(K) ::= keyw_lit(k) keyw_msg_argument(e).

keyw_msg(L) ::= keyw_msg_segment(k).
keyw_msg(L) ::= keyw_msg(l) keyw_msg_segment(k).

opt_keyw_msg(K) ::= . { K = NULL; }
opt_keyw_msg    ::= keyw_msg .

/* So what happens here? Let's represent the receiver as R.
 * R is sent U. (R U) is sent UC[1], then ((R U) UC[1]) is sent UC[2...]
 * (((R U) UC[1]) UC[n]) could be sent stuff from bc, but fuck that for now -
 * this is already a pain to unpack.
 * Finally we get ((((R U) UC[1])UC[n]) kw). */
msg_chain(M) ::= unary_msg(u) opt_unary_msg_chain(uc) opt_binary_msg_chain(bc)
              opt_keyw_msg(kw). {
    /*M = u ? new MsgChainEntry::List({u}) : new MsgChainEntry::List;
    if (uc) M->insert(M->end(), uc->begin(), uc->end());
    if (kw) M->push_back(kw);*/
}
msg_chain(M) ::= binary_msg opt_binary_msg_chain opt_keyw_msg. {
}
msg_chain(M) ::= keyw_msg(k). { /*M = new MsgChainEntry::List({k});*/ }

msg_expr(M) ::= operand(r) msg_chain(k). { /*M = unpackMsgChain(r, k);*/ }


sel_decl(S) ::= sym_lit(s). {
    S = new AST::SelectorDecl(*s);
}
sel_decl(S) ::= binary_decl(b). {
    S = new AST::SelectorDecl(*b);
}
sel_decl(S) ::= keyw_decl_list(k). {
    S = new AST::SelectorDecl(*k);
}

keyw_decl_list(L) ::= keyw_decl(k). {
    L = new std::vector<AST::SelectorDecl::KeywDecl>({*k});
}
keyw_decl_list(L) ::= keyw_decl_list(l) keyw_decl(k). { 
    L = l;
    L->push_back(*k);
}

keyw_decl(K) ::= keyw_lit(k) optional_type_annotation(t) sym_lit(s). {
    K = new AST::SelectorDecl::KeywDecl({*k, *s});
}

binary_decl(B) ::= BINOP(b) sym_lit(s). {
    B = new std::pair<AST::Symbol, AST::Symbol>(*b, *s);
}

unary_decl(U) ::= sym_lit(s).

optional_type_annotation(T) ::= .

opt_vardefs(L)		::=	vardefs(V).
opt_vardefs(L)		::= . 

vardefs(L)			::= BAR vdecl_list(V) BAR.

opt_vdecl_list		::= vdecl_list.
opt_vdecl_list(L)	::= .

vdecl_list(L) ::= vdecl(v) DOT.
vdecl_list(L) ::= vdecl_list(l) vdecl(v) DOT.

/* Variable declaration part (someType someVar) */
vdecl(V) ::= type(t) sym_lit(s).

enclosed_type(T) ::= BRACKET_OPEN sym_type(t) BRACKET_CLOSE.
/* CQuote types are already enclosed */
enclosed_type(T) ::= cquote_type(c).

type ::= sym_type.
type ::= cquote_type.

sym_type(T) ::= sym_lit(s).
cquote_type(T) ::= ctype(c).

opt_sym_literal_list    ::= sym_literal_list.
opt_sym_literal_list(L) ::= .

sym_literal_list(L) ::= sym_lit(s).
sym_literal_list(L) ::= sym_literal_list(l) sym_lit(s).
    {
        //L = l;
        //L->push_back(*s);
    }

ident_expr(E) ::= sym_lit(s). { /*E = new AST::IdentExpr(*s);*/ }
literal_expr(E) ::= str_lit(s). { /*E = new AST::LiteralExpr(*s);*/ }

/* Block syntax:
 * ^ :hello :world [ ]
 */
block_expr(B) ::= BLK optional_type_annotation(t) opt_block_formal_list(f)
                  comp_stmt(c).

opt_block_formal_list    ::= block_formal_list.
opt_block_formal_list(L) ::= .

block_formal_list(L) ::= block_formal(f).
block_formal_list(L) ::= block_formal_list(l) block_formal(f).

block_formal(F) ::= COLON optional_type_annotation(t) sym_lit(s).

ctype(S) ::= CTYPE(L). { S = static_cast<AST::Symbol *>(L); }
cquote(S) ::= CQUOTE(L). { S = static_cast<AST::Symbol *>(L); }
sym_lit(S) ::= SYMLITERAL(L). { S = dynamic_cast<AST::Symbol *>(L); }
keyw_lit(S) ::= KEYW(L). { S = dynamic_cast<AST::Symbol *>(L); }
str_lit(S) ::= SLITERAL(L). { S = dynamic_cast<AST::Symbol *>(L); }