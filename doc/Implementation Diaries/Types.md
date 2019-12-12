# Types

<img src="../Logo/Oopsilon.png" alt="Oopsilon logo" width="520" height="129">

### Grammar

Extensions to Oopsilon syntax:

```EBNF

class_name          = name [ '(' ident { ',' ident } ')' ] ;

field               = [ angled_type_spec ] name ;

operand             = cast_expression ;
cast_expression     = angled_type_spec operand ;

sel_decl            = sel_decl inference_clause ;

inference_clause    = '::' inference_mapping { ',' inference_mapping } ;

inference_mapping   = keyword inference_expr ;

inference_expr      = inference_operand
                    | inference_operand 'returnType' ;

inference_operand   = '(' inference_expr ')' ;
                    | inference_arg_expr ;

inference_arg_expr  = 'Arg:' integer_literal ;

angled_type_spec    = '<' type_spec '>' ;

type_spec           = 'weak' type_spec
                    | named_type
                    | parameterised_type_invocation
                    | block_type
                    | c_type ;

named_type                      = ident ;

parameterised_type_invocation   = ident '(' type { ',' type } ')' ;

block_type                      = '[' '^' type { ',' type } ']' ;

c_type                          = 'CType:' string_literal ;
```

### Parametric types

Consider an Array:

`class Array (T)`

This would presumably result in...

```cpp
ParameterisedType
{
    Type = ClassType(Array);
    Names = { T };
};
```

### Parametric Polymorphism

We'll go with this:

```Smalltalk
class Array(T)
|
    <CType: "oop *"> contents.
|

- <Array(N)> map: <[^N, T]> aBlock ::
    N: (arg: 1) returnType.

end
```

How will map's declaration parse?

Perhaps produce AST like this:

```cpp
WhereType
{
    Mappings =
    {
        N = returnType
        {
            of =
                argAt
                {
                    Index = 1;
                };
        },
    };
    
    Type =
        FunctionType
        {
            ReturnType =
                ParameterisedTypeInvocation
                {
                    Type = Name("Array");
                    Argument = Name("N");
                };
            ArgTypes =
            {
                BlockType
                {
                    ReturnType = Name("N");
                    ArgTypes = { Name("T"), };
                },
            };
        };
};
```

### Transformation:

First, any instance will already specify a type for Array(T).
So:

`- <Array(N)> map: <[^N, oop]> aBlock ::
    N: (arg: 1) returnType.`

N should be registered as a "late-created" type.
Therefore we permit any N in [^N, oop]. Let's go with 'Box.'

`- <Array(N)> map: <[^Box, oop]> aBlock ::
    N: (arg: 1) returnType.`

Now the type must extract 'box':

`- <Array(Box)> map: <[^Box, oop]> aBlock ::
    N: (arg: 1) returnType.`

    
*How shall we do this?*

Thoughts: N doesn't really matter except at the top level, does it? Its use in
the `<[^N, T]>` block type is seemingly needless. Instead, why am I not using
'Object' or similar there instead of T, to reflect what is acceptable as an N?