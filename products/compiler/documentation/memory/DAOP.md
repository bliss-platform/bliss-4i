---
title: Data and Action Model
nav_order: 1
parent: Compiler
---

# Bliss Language Specification

## Data, Actions, Binded Types, and Calling Conventions

**Status:** Draft Specification
**Audience:** Language users, compiler implementers
**Scope:** Core type system, semantics, and call boundaries

---

## 1. Design Principles

Bliss is built around one central idea:

> **Meaning is chosen, never inferred.**

From this follow several non-negotiable principles:

* No implicit behavior
* No implicit meaning
* No semantic widening
* No global coherence rules
* All semantic changes are explicit and local

The type system exists to enforce these principles mechanically.

---

## 2. Type System Overview

Bliss has **three distinct kinds of types**, all first-class and mutually disjoint:

1. **Raw Data Types** – memory only
2. **Action Types** – behavior only
3. **Binded (Semantic) Types** – memory + behavior + meaning

None of these is derived implicitly from another. Transitions between them must be explicit.

---

## 3. Raw Data Types

### 3.1 Definition

A **data type** defines memory layout only.

```bliss
data Data {
    u64 byte_ptr;
    u32 size;
}
```

Properties:

* Define storage and representation
* Contain no behavior
* Carry no meaning
* Expose no methods
* Possess **open semantics**

A value of a data type is called **raw data**:

```bliss
Data a;
```

---

### 3.2 Raw Data Semantics

Raw data values expose no members:

```bliss
a.length();        // error
```

However, raw data may be **reinterpreted explicitly**:

```bliss
a::X.length();     // valid
a::Y.length();     // valid
```

> **Rule:** Raw data has no inherent behavior, but may be interpreted under any action or bind.

---

## 4. Action Types

### 4.1 Definition

An **action** represents a behavioral capability, independent of storage and meaning.

```bliss
action X {
    fx length(self) -> int;
}
```

Properties:

* Have no storage
* Have no instances
* Are not data
* Do not define meaning
* May be used as parameter types

Actions describe **required behavior**, not semantic intent.

---

### 4.2 Action Annotations

Actions may be annotated to refine validity rules:

```bliss
@reinterpret
action UTF8 {
    fx length(self) -> int;
}

@composable
action Printable {
    fx print(self);
}
```

Annotations:

* Affect validity and usage rules
* Never affect memory representation

---

## 5. Binded (Semantic) Types

### 5.1 Definition

A bind is how we interpret an action, or a set of actions towards some data.
This binding produces a interpretation token that can be used to add meaning
to a data.

```bliss
bind X, Data as SomeType {
    fx length(self) -> int { ... }
}
```

Facts:

* It is neither `Data` nor `X`
* It participates fully in the type system
* It has **closed semantics**

---

### 5.2 Construction of Binded Values

A binded value is constructed explicitly:

```bliss
Data::SomeBinding b;
Data::(BindA, BindB) c; //multi bindings
```

This is **semantic construction**, not reinterpretation.

---

## 6. Open vs Closed Semantics

### 6.1 Open Semantics (Raw Data)

```bliss
Data a;
```

Characteristics:

* No meaning
* No guarantees
* Reinterpretation allowed

```bliss
a::X.length();
a::Y.length();
```

---

### 6.2 Closed Semantics (Binded Types)

```bliss
Data::SomeBind b;
```

Characteristics:

* Meaning is fixed
* Semantics are sealed
* Reinterpretation is forbidden

```bliss
b.length();        // valid
b::X.length();     // error
```

> **Rule:** Only raw data may be reinterpreted.

---

## 7. Value-Level Action Composition

A value may expose multiple actions simultaneously:

```bliss
Type::(X, Y) k;
```

This means:

* Underlying data is unchanged
* Both actions are available
* No new semantic type is created
* Composition is local to the value

Rules:

* Composition does not create a bind
* No additional actions may be introduced later
* Ambiguity must be resolved explicitly

```bliss
k.length::X();
k.length::Y();
```

---

## 8. Binding

A **bind** associates a non-empty set of actions with a data type by creating an **interpretation token**.

An interpretation token does not introduce a new nominal data type. Instead, it establishes a sealed semantic relationship between:

* A specific data type (memory), and
* A specific unordered set of actions (behavior).

```bliss
bind (X, Y, Z), Data as A;
```

Here, `A` is an interpretation token representing:

```
InterpretationToken = (Data, ActionSet)
```

Actions themselves are not interpretation tokens.

* `X` is an action.
* `Data` is memory.
* `A` is the interpretation token joining them.

Therefore:

```bliss
Data::A      // valid
Data::X      // illegal
Data::(X,Y)  // illegal
```

Only interpretation tokens may be used with the `::` operator.

---

### 8.1 Binding Rules

1. The action set must be non-empty.
2. The action set is unordered.
3. Duplicate actions are illegal.
4. The action set is sealed at bind time.
5. No additional actions may be introduced after binding.
6. An interpretation token is uniquely identified by its data type and exact action set.
7. Binding does not imply subtyping relationships.

---

### 8.2 Identity of Interpretation Tokens

Interpretation tokens are **nominal declarations**.

Each `bind` statement introduces a distinct interpretation token, even if:

* The underlying data type is identical, and
* The action sets are identical.

Example:

```bliss
bind (X), Data as A;
bind (X), Data as B;
```

`A` and `B` are distinct interpretation tokens.

They represent separate semantic commitments, even though they relate the same data type and action set.

Interpretation token identity is therefore defined by declaration identity, not by structural equivalence of `(Data, ActionSet)`.

No structural widening relationship exists between tokens.

---

### 8.3 Closed Semantics

An interpretation token defines a closed semantic universe.

For a value:

```bliss
Data::A v;
```

* Only actions in the token’s action set are accessible.
* Reinterpretation into additional actions is forbidden.
* Semantic widening is illegal.

---

### 8.4 Prohibited Forms

The following are illegal:

```bliss
bind (), Data as A;          // empty action set
bind (X, X), Data as A;      // duplicate actions
Data::X;                     // action is not a token
Data::(X,Y);                 // actions are not tokens
```

Binding never implies structural subtyping, automatic widening, or action inference.

---

## 9. Method Resolution

### 9.1 Unqualified Calls

```bliss
value.method();
```

Legal only if:

* The value is binded
* Exactly one bound action defines `method`

---

### 9.2 Qualified Calls

```bliss
value.method::X();
```

Legal only if `X` is part of the value’s bind or value-level composition.

Qualification never introduces new semantics.

---

## 10. Function Parameters and Calling Conventions

Function parameters explicitly determine **which semantic layer is preserved** across the call boundary.

---

### 10.1 Data Parameters (Semantic Erasure)

```bliss
fx someStuff(Data x);
```

Rules:

* Accepts any binded type with underlying `Data`
* All actions and meaning are stripped
* Only raw data is visible

```bliss
Data::A a;
Data::B b;

someStuff(a);   // valid
someStuff(b);   // valid
```

---

### 10.2 Binded Parameters (Semantic Preservation)

```bliss
fx process(Data::A a);
```

Rules:

* Bind must match exactly
* Meaning is guaranteed
* No reinterpretation allowed

```bliss
process(a);   // valid
process(b);   // invalid
```

---

### 10.3 Action Parameters (Behavioral Polymorphism)

```bliss
fx doThing(ActionType x);
```

Rules:

* Any binded type implementing the action is accepted
* Underlying data is inaccessible
* Only behavior is visible

```bliss
Data1::ActionType a;
Data2::ActionType b;

doThing(a);
doThing(b);
```

---

## 11. Explicit Semantic Projection

### 11.1 Data Extraction (`ext`)

`ext` explicitly destroys meaning and behavior, recovering raw data.

```bliss
Data x = ext Data::(A, B, C, D);
```

Rules:

* All actions are removed
* Result has open semantics
* No meaning is preserved

---

### 11.2 Reinterpretation After Extraction

```bliss
Data::B y = (ext Data::A)::B;
```

Rules:

* Extraction always precedes reinterpretation
* This is legal only because the intermediate value is raw data
* Semantic changes are explicit and local

---

## 12. Invalid Semantic Operations

The following are always illegal:

```bliss
b::Y.length();        // semantic widening
b.length::Y();        // accessing non-existent semantics
```

Binded types define a **closed semantic universe**.

---

## 13. Reinterpretable Actions and Guidelines

Actions annotated with `@reinterpret` assign meaning to raw data.

```bliss
@reinterpret
action UTF8 { }
```

Guidelines:

* Prefer using one reinterpretation at a time
* Multiple reinterpretations may conflict
* The compiler does not enforce semantic consistency

Binded types exist to lock meaning and avoid ambiguity.

---

## 14. Type aliasing and qualified names

Type definitions where binders are used a lot can be a handful to
write. To tackle this, a syntactic sugar for type aliasing is
suggested.

```
using std.actions.summary;

data UserData {
	String name;
	int age;
}

bind summary, UserData as UserBinder {
	fx summarize(self) {
		return "Name: { self.name }\nAge: { self.age }"
	}
}

alias UserData::UserBinder as User; //this is just a dumb rename
alias UserData::UserBinder as SameButDifferent; //again dumb rename
```

---

## 15. Standalone Bindings

Whenever we bind some data, we might want a standalone type without type
aliasing.

By default, all bindings are types as well, so they can stand solo as well.

```
bind summary, UserData as User { ... } //implementations
```

so the `User` is a bound semantic type formed from `UserData` and the `summary` action.

---
## 16. Singleton Actions and Bindings

In some situations, a behavior consists of a **single action function** that does not naturally belong to a larger conceptual group. Creating a dedicated action block in such cases adds syntactic structure without providing additional semantic value.

To address this, Bliss provides a **singleton action syntax** as a purely syntactic convenience. This allows single-responsibility behaviors to be expressed directly, without forcing artificial grouping.

---

### 16.1 Singleton Action Definition

A singleton action can be declared inline using the following form:

```bls
action fx Walkable.walk(self) -> void;
```

This declaration is syntactic sugar for an action containing exactly one function. It does not introduce a new kind of action, nor does it weaken the action model in any way. All semantic rules applicable to regular actions continue to apply unchanged.

---

### 16.2 Singleton Binding

A singleton action may be bound directly to a data type using an inline bind expression:

```bls
bind Walkable.walk(self) {
    self.steps += 20;
}, DogData as WalkableDog;
```

This form is semantically equivalent to a standard bind involving a single-action action type. The resulting type `WalkableDog` is a nominal binded (semantic) type with closed semantics, exactly as defined by the core binding rules.

---

### 16.3 Aliasing as a Unified View

If a simpler or more expressive name is desired, the resulting binded type may be aliased:

```bls
alias DogData::WalkableDog as Dog;
```

This alias introduces no new meaning. It merely provides a more convenient name for an existing semantic type.

---

### 16.4 Rationale

Singleton actions exist to support **single-responsibility behaviors** without encouraging premature or artificial abstraction. They reduce boilerplate, improve readability, and make refactoring easier, while remaining fully consistent with the Data–Action–Bind model.

No runtime overhead is introduced, and all semantics remain explicit and local.

---

## 17. Field Values

In Bliss, fields inside a `data` definition may take different forms depending on how they are intended to be accessed and mutated. By default, all fields are **readable and writable** from any context.

Bliss refines this behavior using a small set of **field modifiers**. These modifiers do not change the DAOP model itself; instead, they precisely control **visibility** and **mutability** of fields.

The available modifiers are:

* `private`
* `hide`
* `readonly`

They may be used individually or in combination.

---

### 17.1 `private`

`private` is the **strongest** field modifier.

A `private` field is:

* Visible **only during construction** of the data value
* Completely inaccessible afterward
* Not readable or writable by actions
* Not part of the observable semantic state

`private` fields exist solely for **runtime or native-layer mechanisms**, such as internal handles, storage anchors, or capability tokens.

They are intentionally excluded from DAOP reasoning.

---

### 17.2 `hide`

`hide` restricts field visibility to **actions only**.

A `hide` field is:

* Invisible to user-level code
* Fully accessible within actions bound to the data
* Part of the semantic state of the data

This modifier is intended for **internal state** that affects behavior but should not be exposed as part of the public data surface.

---

### 17.3 `readonly`

`readonly` restricts **when** a field may be written.

A `readonly` field:

* May be assigned only during construction
* Cannot be overwritten outside of actions
* Remains readable according to its visibility rules

This modifier enforces immutability guarantees while preserving DAOP semantics.

---

### 17.4 Combined Modifiers

Modifiers may be combined to further refine behavior.

#### `readonly hide` / `hide readonly`

This combination produces a field that:

* Is visible only to actions
* Can be assigned only during construction
* Cannot be mutated afterward

Such fields are useful for **internal constants**, cached metadata, or invariant state that should remain stable throughout the lifetime of the data value.

---

### Summary

Field modifiers in Bliss refine *access* and *mutability* without altering the DAOP model itself:

* `private` removes a field from semantic visibility entirely
* `hide` limits visibility to actions
* `readonly` limits mutability to construction time

Together, these modifiers allow precise control over data representation while keeping data–action separation explicit and intact.

---

## 18. Canonical Summary

> **Data defines memory.**
> **Actions define behavior.**
> **Binded types define meaning.**

> **Meaning is chosen, never inferred.**

---

*End of specification.*