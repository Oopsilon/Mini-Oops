```C++
class Thing
{
    virtual void rebind(Thing * parent, std::string key, Thing * newVal);
};

class Name : Thing
{
    std::string aName;
    
    Name(std::string name) : aName(name) {}
};

class Instantiation : Thing
{
    std::list<std::pair<std::string, Thing *>> Mappings;
    Thing * Of;

    void rebind(Thing * parent, std::string key, Thing * newVal)
    {
        if (!Mappings[key])
            return Of->rebind(this, key, newVal);
        else
        {
            /* Logic needed here. See below. */
        }
    }
};

class Parameterized : Thing
{
    Thing * Subsumes;
    
    void rebind(Thing * parent, std::string key, Thing * newVal)
    {
        return Subsumes->rebind(this, key, newVal);
    }
};

I have described below an example of what an object graph may look like at runtime:


Instantiation
{
    Mappings = { { "Key", Name("String") }, { "Val", Name("Content") } };
    
    Of =
        Parameterised
        {
            Subsumes =
                Instantiation
                {
                    Mappings = 
                        { {"El",  Instantiation
                                {
                                    Mappings = { {"T1", Name("Key") }, {"T2", Name("Val") } };
                                    Of =
                                        ParameterisedType { Subsumes = NULL; };
                                };
                                }; };
                    Of = 
                        Parameterised { Subsumes = NULL; }
                };
        };
};

Suppose I want to replace the value of the mapping for "El".

I want to replace it with another one that has mappings from T1 to something
and T2 to something.

Where Name("Key") is found is a sort of dependency on the value of the mapping
for "Key" (as found in the root Instantiation) is there. I.e. an Instantiation
can lookup what a Name stands for by searching through its owners' mappings
(it is passed pointers to its parents) for a value that matches in one of the
Instantiations. 

I want to replace the Instantiation for "El" with a whole Instantiation at once
though. The new instantiation will have something like:

Mappings = { { "T1", someThing}, { "T2", someOtherThing } };

In other words I want to do:

newElValue = Instantiation 
    { Mappings = { { "T1", someThing}, { "T2", someOtherThing }; Of = don't care; };

topLevelObject.rebind(0, "El", newElValue);

What I want to do is to have the mappings for Key and Val in the top-level
Instantation update with respect to the new Mapping for El. Key needs to be
rebound to the value of T1, and Val needs to be rebound to the value of T2.
```

```
[02:15:07] <JX7P> my current rough idea: /* logic */ will tell Of, "give me all the mapping names that have a Name() as their value". it will store those pairs locally, {oldKey, oldValue}, do the replacement, then it will tell the new Of, for each of the pairs, "give me the value for oldKey", it will then do a rebind operation only that it searches upwards to replace all mapping values which correspond to oldValue.aName with the new values, then it will do 
[02:15:07] <JX7P> a rebind downwards again to replace the new values for oldKey with oldValue again
[02:15:42] <JX7P> in this way it restores the old situation and reunifies the links
```

Getting type of vars - GlobalVar will return resolvedClassName.invoke() and
invoke() will create a ParameterisedTypeInvocation with placeholder values
if the class is parameterised, if not it will just pass back the class type.

Must think about class type binding. When we resolve the 'Object' part of
SomeClass<Object>, what happens? Is it resolved to (Object AST)->invoke() ?
(of course it is, I think?)

Type checking steps:

For each class, enter its methods and get all the types that can be resolved
to be resolved.

Do the 'advice' functions, invoke all types needing invoked, basically do
everything other than the checking proper. Generic invocations with
placeholders should become unified by their use, which fills in type
info for them. Any remaining placeholders probably constitutes an error.

Do thisProtocol->typeCheckOwnMethods(). Then type check for each of our
invocations:
```
    someImplementedProtocol->typeCheckOwnMethodsWithTypeInContext(invocation);
```

Remember that parent type context, if it is another invoation, should only be
checked for names we have found we reference in our local type context; not for
all purposes.