Static Typing System
====================

The formal grammar does not directly correspond to the concrete syntax
of Oopsilon, but it does closely match it in a simplified way.

Types
~~~~~

Oopsilon incorporates the following kinds of types:

+-------------------------------------------------+-----------------------------------+
| Example                                         | Kind                              |
+=================================================+===================================+
| ``Object``                                      | Class (nominal)                   |
+-------------------------------------------------+-----------------------------------+
| ``id``                                          | Dynamic (pseudonominal)           |
+-------------------------------------------------+-----------------------------------+
| ``id <Ordinal, Circular>``                      | Protocol-constrained dynamic      |
+-------------------------------------------------+-----------------------------------+
| ``Self``                                        | Self                              |
+-------------------------------------------------+-----------------------------------+
| ``ClassType``                                   | Self class                        |
+-------------------------------------------------+-----------------------------------+
| ``InstanceType``                                | Self instance                     |
+-------------------------------------------------+-----------------------------------+
| ``Dictionary of: String to: Integer``           | Parameterised-nominal             |
+-------------------------------------------------+-----------------------------------+
| ``Self of: String to: Integer``                 | Parameterised-self                |
+-------------------------------------------------+-----------------------------------+
| ``id <Functor of: String>``                     | Parameterised protocol-           |
|                                                 | constrained dynamic               |
+-------------------------------------------------+-----------------------------------+
| ``T``                                           | Type variable (nominal)           |
+-------------------------------------------------+-----------------------------------+
| ``Integer | Float``                             | Sum                               |
+-------------------------------------------------+-----------------------------------+
| ``[^Integer, String]``                          | Lambda                            |
+-------------------------------------------------+-----------------------------------+
| ``[^Y, [^Object] :: Y: (arg: 1) returnType]``   | Lambda with inference expression  |
+-------------------------------------------------+-----------------------------------+

Any nominal or pseudonominal type can be constrained to require that the
concrete type implements some protocol.


Inference expressions
~~~~~~~~~~~~~~~~~~~~~

An inference expression refers to some type. In
parametrically-polymorphic signatures, they provide a mechanism for
obtaining the types to bind type variables to on a per-invocation basis.

Inference expressions can refer to the type of actual arguments to a
method and to their return types.

Class types
~~~~~~~~~~~

A class type C is composed of a set of messages which can be
understood by the type, plus those of its superclass ς.

``C ::= [ ς ]``

Grammar
~~~~~~~

Parsing Expression Grammar-like representation is used.

Wherein 𝕃 ranges over the names of all classes, ℙ ranges over protocol names, 𝕏
over type variables names, and 𝔾 over the keyword parameter names to a
parameterised type.

Expressions
^^^^^^^^^^^

.. productionlist::
    τ:   ((`Nominal` `Constructor`?) | `Dynamic`) `Protocols`?
     : | `Self` `Constructor`?
     : | `λ`
     : | `τ` + `τ`
     :
    λ: (`τ`* ➡️ `τ`) `Mappings`?
    Nominal: 𝕃 | 𝕏
    Self: 'Self' | 'InstanceType' | 'ClassType'
    Dynamic: 'id'
           :
    Protocols: (ℙ `Constructor`?)+
    Constructor: (𝔾:`τ`)+
    Mappings: (𝕏:`𝓔`)+

Declarations
^^^^^^^^^^^^

.. productionlist::
    𝕮: 𝕃 (𝔾:𝕏)* (: τ)? (<τ+>)?
    𝕻: ℙ (𝔾:𝕏)* (: τ+)?

-  a class type declaration, 𝕻, is:
    -  a protocol name;
    -  followed by an optional mapping of keyword parameter names to type
       variable names, which results in the type declaration producing a
       parameterised type;
    -  followed by an optional type expression, which this class shall be
       a subtype of;
    -  followed by an optional list of protocol type expressions, which this
       class shall be considered to implement,
-  a protocol type declaration, 𝕻, is:
    -  a protocol name;
    -  followed by an optional mapping of keyword parameter names to type
       variable names, which results in the type declaration producing a
       parameterised type;
    -  followed by an optional list of supertype expressions, which shall
       form the set of types which the new protocol type is a subtype of.

Inference expressions
^^^^^^^^^^^^^^^^^^^^^

.. productionlist::
    𝓑: ('arg':ℕ)
    𝓞: 𝓑 | 'returnType'
    𝓔: 𝓑 𝓞*

-  A basic operator, 𝓑, is:
    -  an argument selection expression with a natural number denoting the
       argument whose type shall be selected,
-  an ordinary operator, 𝓞, is either:
    -  a basic operator;
    -  or a returnType operator,
-  an inference expression, 𝓔, is:
    -  a basic operator;
    -  followed by an optional sequence of one or more ordinary operators.

Type constructors
~~~~~~~~~~~~~~~~~

A parameterised type declaration introduces a type constructor. Type
constructors are functions from argument types for a parameterised type
to a type. They are akin to keyword messages in form.

For a parameterised type declaration:

``𝕋 (𝔾:𝕏)+``

a type constructor is produced of the following form:

::

    Name = 𝕋;
    Keywords = (𝔾:𝕏)+;

which is associated with the type ℙ. Type constructors are
properties of types, rather than independent entities, and their
behaviour is dependent on the type to which they are associated.

Upon invoking the constructor with ``(𝔾:τ)+``, each formal parameter 𝕏 is
bound to actual argument τ. This produces a *parameterised type
invocation*.

Inherited type constructors
^^^^^^^^^^^^^^^^^^^^^^^^^^^

The terms "supertype" and "inherit" are used in a special way in this section
to refer to both their usual meanings and to "protocol declared to be
implemented" and "to declare implementation of a protocol" respectively. This
simplifies the necessary wording.

Inheritance from a parametric type produces inheritance of its type
constructors. This occurs because, as noted above, type constructors are
not independent entities but are properties of a parameteric type.

They may be restricted by the inheritance: the constraint introduced is
that the arguments to the type constructor must hold the relationship
known as *lateral substitutability* with the arguments given by the
superprotocol clause of the type to the concerned supertypes' type
constructor.

Wherein 𝗔 denotes the argument given to the type constructor of the
supertype in the supertype specification by the type which has inherited
it, and 𝗕 denotes the argument given to the inherited type constructor:

The following rule defines lateral substitutability:

- If it is the case that:

    1. 𝗔 refers - either directly or, if 𝗔 is a parameterised type
       invocation, within the arguments - to one or more type variables of
       the inheriting type;
    2. and 𝗕 otherwise matches 𝗔 in form, except in substituting types in
       place of type variables referenced in 𝗔;

- then 𝗔 is *laterally substitutable* with 𝗕.

In such an instance the type variable which has been substituted will be
*reverse-propagated*. This means that the inheriting type will be
reconstructed with the new value of the type variables substituted
passed as arguments to the inheriting types' constructor.

Self-referential type constructors
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The self-reference types - in the case that they are used in a
parameterised protocol - can be paired with a parameterised type
invocation to produce an invocation of the type in which the
self-reference appears. The type constructor to which they refer will be
that of the type in which they were declared; however, the binding of
``Self`` and other self-referential type variables will always be to the
*concrete type*; that is, they are transient and track subtyping. To
avoid such behaviour, one may model the self-reference with a
recursively-boundedly quantified parametric type.

Subtyping relationships
~~~~~~~~~~~~~~~~~~~~~~~

+------------------------------------------------------+-------------------------+
| Rule                                                 | Kind                    |
+======================================================+=========================+
| ``P implements ς ⇒ P ⊆ ς``                           | Prototype composition   |
|                                                      | implies subtyping       |
+------------------------------------------------------+-------------------------+
| ``(T₁ ⊇ S₁) & (T₂ ⊆ S₂) ⇒                            | Return-type Covariance, |
| (T₁ ➡️ T₂) ⊆ (S₁ ➡️ S₂)``                            | Argument Contravariance |
+------------------------------------------------------+-------------------------+

-  If protocol P has superprotocol ς, then protocol P is a subtype of ς.
-  If T₁ is a subtype of S₁ and T₂ is a supertype of S₂, then a function
   from T₂ to T₁ is a subtype of a function from S₂ to S₁.
