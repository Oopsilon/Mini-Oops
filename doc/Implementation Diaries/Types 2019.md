# Types

<img src="../Logo/Oopsilon.png" alt="Oopsilon logo" width="520" height="129">

We need to face the facts: Oopsilon is best served by a robust gradual typing
model. It is desirable that this model resemble Oopsilon code to some extent.

For example, it is desirable that one be able to define some class C:
```
class C of: T
|
    (T of: InstanceType) someVar.
|

end
```

### Blocks

Blocks should not be special types. Implement instead by adding the ability to
take a *set of types* as a parameter in a type constructor.

```
class BlockClosure returns: RType withArgs: (Set) ArgTypes

- (RType) value :: ArgTypes = 0 ifFalse: thisMethod makeUnusable.

- (RType) value: (ArgTypes at: 1) :: ArgType = 1 ifFalse: thisMethod makeUnusable.

end
```

