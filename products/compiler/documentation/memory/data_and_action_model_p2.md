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
    ptr bytes;
    int size;
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

A **bind** creates a new **nominal semantic type** by attaching an action to a data type.

```bliss
bind X, Data as SomeType {
    fx length(self) -> int { ... }
}
```

Facts:

* `SomeType` is a real, nominal type
* It is neither `Data` nor `X`
* It participates fully in the type system
* It has **closed semantics**

---

### 5.2 Construction of Binded Values

A binded value is constructed explicitly:

```bliss
Data::SomeType b;
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
Data::SomeType b;
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

## 8. Binding Rules

### 8.1 Single-Action Binding

Each bind associates **exactly one action** with a data type.

```bliss
bind X, Data as A;
```

Illegal:

```bliss
bind (X, Y), Data as W;   // error
```

> Binds never compose actions.

---

### 8.2 Multiple Binds over the Same Data

```bliss
bind X, Z as A;
bind X, Z as B;
```

Properties:

* `A` and `B` are distinct nominal types
* Both implement `X`
* Both have closed semantics

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

## 14. Canonical Summary

> **Data defines memory.**
> **Actions define behavior.**
> **Binded types define meaning.**

> **Meaning is chosen, never inferred.**

---

*End of specification.*