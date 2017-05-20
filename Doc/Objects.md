# The Oopsilon Object Model

<img src="Logo/Oopsilon.png" alt="Oopsilon logo" width="585" height="129">

### Overview
An Object in Oopsilon has a very simple definition. It is something which can
respond to messages. Well, this is the basis of it - the implementation is
slightly more complex.


### An object

An object responds to messages. How does it do this? It runs a method. All
simple so far. How do we define what messages an object can respond to? The
answer is in its class.

### A class

A class is an object of a special sort: it describes how other objects are
created, and what messages they respond to, as well as any special