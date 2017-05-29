# Blocks

<img src="../Logo/Oopsilon.png" alt="Oopsilon logo" width="585" height="129">

### Blocks
A block is a feature in Smalltalk-80, and also in Oopsilon. Other languages
often have similar features called lambda expressions.

### Capture
In Smalltalk-80 blocks are not reentrant; they have no activation record of
their own, they piggyback on the activation record of the method they were
defined in.

I am not doing this with Oopsilon. Let's introduce some terminology:

 1. **Block**: an expression like { :param1 :param2 | whatever }. Result of
 executing such an expression is an object of type Block.