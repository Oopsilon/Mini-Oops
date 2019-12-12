Imagine 


```class Base T1 T2 : Nil

+ (Instance) new
[
    self
]```

end

`Base new` should return:

```Base(id, id)```


```class Derived TD1 : Base TD1 Int

end```

Then `Derived new` should return
`Derived(id)`

Derived(id) must be usable wherever Base(id, id) is, but not where Base(id, String)
for example.

What happens if Derived(Something) is asked: "Can you be subbed with Base(Something, Int)"?

I presume Derived(Something) will have a member superType. superType will be... a
paramterisedtypeinvocation(Base, TD1, Int).
But do we simply substitute TD1 with 'id' everywhere inside the class? 