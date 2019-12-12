# Compiler passes

<img src="../Logo/Oopsilon.png" alt="Oopsilon logo" width="520" height="129">

### The Passes

The Oopsilon compiler arrives at its target (which might be LLVM IR, C, or some
target I haven't thought of yet) through the following distinct phases:

1. *Lexical Analysis*:
    - The source code is converted from a text stream into into a stream of
    simple tokens. These are such things as `COMMA` or `KEYWORD`.

2. *Syntaxic Analysis*:
    - The stream of tokens is parsed into a tree, the AST.

3. *Name Resolution*:
    - Each place where a name is introduced, it is declared in a LexicalContext
    structure. These contexts also form a tree.
    - A LexicalContext is introduced wherever some new bindings occur - so that
    is one for the whole unit, one for each module, one for each class
    (instance variables, `self`, etc,) one for each method, and one for each
    block.
    - The created LexicalContexts are associated with their counterpart AST
    node by placing them in the 'ctx' member variable of those nodes.

4. *Type Context Tree Formation*:
    - Each place where new types may be introduced gets its own TypeContext;
    this is a similar in concept to a LexicalContext, only it binds type names
    to type descriptors rather than variable names to variable descriptors.
    - Wherever a new type is introduced, it is added to the relevant
    TypeContext.

5. *Type Resolution* (repetible):
    - `NamedTypeRepr`s, which are introduced by the parser, are resolved to
    real types where possible.

6. *Type Checking* (repetible):
    - Assignments and message-sends are checked for type-correctness.
    - Where a NamedTypeRepr remains or there is a Placeholder type, the
    compiler will try to infer what it should become based on the
    assignment/message-send.
    - If an Inference Clause is found then its expression is evaluated and the
    name bound. The result may still refer to placeholder types or to
    NamedTypeReprs.
    - If either of those possibilities occurs then type resolution is
    reinitiated to update with respect to the new information.

7. *LexicalContext Lowering*:
    - Use of variables in blocks triggers the creation of the appropriate
    HeapVars (vectors of variables in a lexical scope used by a block said
    scope contains) descriptors in the LexicalContext to which the variables
    belong, and the creation of new bindings for these names in the context in
    which they are accessed, in each case providing the correct expression for
    access to the variables.

8. *MLIR Generation*:
    - AST + LexicalContext are merged and lowered to produce MLIR, a
    lower-level intermediate representation.

9. *CR Generation*:
    - MLIR is lowered to CR, which is an intermediate representation that
    resembles a C or Pascal like language of SSA style, only simpler.

10. *Code Generation*:
    - CR is trivially converted to our output form.