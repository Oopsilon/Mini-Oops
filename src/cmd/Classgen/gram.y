%include {
#include <string>
#include <list>

#include "oops-platform/misc.h"

#include "Classgen.h"
}

%token_prefix TK_
%token_type { std::string * }

%syntax_error {
  dbg("%d:%d: Syntax error\n", cg.last_line, cg.last_col);
}

file ::= EOF.
file ::= listings EOF.

listings ::= SYM.

