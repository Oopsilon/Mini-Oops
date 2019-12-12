<X of T> : <Object of: T> 

stage 1 of prepping protocol types:

ParameterisedType(Protocol(X) {"Of":T}
    WithSuperTypes: {
        ParameterisedType(Protocol (Object) of: T)
    }
)

stage 2:

ParameterisedType(Protocol(X) {"Of":T} withSubstitutionList:{T to Ref("T")}
    WithSuperTypes: {
        ParameterisedType(Protocol (Object) of: T)
    }
)

stage 3:

supertypes.each(effectSubstitution(subList))

(this only uses the substitution list given to it. no nesting.)

we lose the ParameterisedTypeInvocation here

ParameterisedType(Protocol(X) {"Of":T} withSubstitutionList:{T to Ref("T")}
    WithSuperTypes: {
        ParameterisedType(Protocol (Object) {of: T} withSubstitutionList:(T to Ref("T"))
    }
)


stage 4:

within that effectSubstitution method we reach no more supertypes -
means we have now created our canonical type.


Remember: in getting returntype of a method - how do we deal with finding
right type? can we use the type env of sending env?
how also do we deal with inference expressions?




==========



Things we want to do: complete parsing first! 

Merge all subtype parameters into the supertypes' type context. Can we unify
the parameter variables?

How about how we represent classes? We obviously can't resolve their type fields
because they may be used in multiple ways.

I think we should store classes with their generic parameters bound to their
bounds. Annotate them with something like "result of getting my instancetype is
without "