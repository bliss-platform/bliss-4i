# Bliss: An Explicit Reinterpretation–Based Type System

**Author:** Mayukh Chakraborty
**Status:** Draft / Research-Oriented
**Audience:** Language designers, systems programmers, compiler researchers

---

## Abstract

Bliss introduces an explicit reinterpretation–based semantic model that separates **data representation**, **behavior**, and **meaning**. Unlike conventional object-oriented or trait-based systems, Bliss does not attach behavior to data implicitly. Instead, behavior is applied through **actions**, and semantic meaning is selected **explicitly at the use site**.

This design eliminates hidden coherence rules, implicit method resolution, and accidental semantic composition, while preserving the expressiveness required for systems programming.

---

## 1. Motivation

Modern programming languages conflate three distinct concerns:

1. Data layout
2. Behavioral capability
3. Semantic interpretation

This conflation leads to:

* hidden behavior injection (traits, extensions)
* semantic ambiguity
* global coherence constraints
* accidental meaning changes due to imports or scope

Bliss proposes a model where:

* data is inert
* behavior is external
* meaning is explicit

The result is a system that favors **semantic honesty** over implicit convenience.

---

## 2. Core Design Principles

1. Data has no behavior
2. Behavior is never implicit
3. Meaning is chosen explicitly
4. Ambiguity is surfaced, not resolved silently
5. The compiler never lies about semantics

---

## 3. Data Types

A **data type** defines memory layout only.

```bliss
data RawString {
    ptr bytes;
    int length;
}
```

Properties:

* No methods
* No behavior
* No semantic assumptions
* Always refers to raw memory

A bare type name always refers to **data only**.

---

## 4. Actions

An **action** defines behavior that may be applied to data.

```bliss
action UTF8 {
    fx length(self) -> int;
    fx at(self, int index) -> rune;
}
```

Properties:

* No storage
* No identity
* No attachment to data
* May assume semantic invariants

Actions are **interpretations**, not inherent capabilities.

---

## 5. Action Annotations

Actions may be annotated to describe intent.

```bliss
@reinterpret
action UTF8 { ... }

@capability
action Serializable { ... }
```

### 5.1 `@reinterpret`

Indicates that the action defines a **semantic interpretation** of data.

* Often mutually exclusive with other reinterpretations
* Composition is allowed but discouraged
* Used for diagnostics and tooling

### 5.2 `@capability`

Indicates additive behavior without reinterpretation.

* Freely composable
* Orthogonal by design
* No semantic invariants introduced

Annotations:

* do **not** affect legality
* do **not** affect method resolution
* exist for warnings, tooling, and documentation

---

## 6. Bindings (Named Semantic Types)

A **binding** connects an action to a data type and produces a named semantic type.

```bliss
bind UTF8Utils, RawString as String {
    fx length(self) -> int { ... }
    fx at(self, int i) -> rune { ... }
}
```

Effects:

* Introduces a new **semantic type**
* Does not modify the data type
* Does not attach behavior implicitly

Bindings are **closed semantic contracts**.

---

## 7. Reinterpretation Types

### 7.1 Action Sets

A value may expose multiple actions:

```bliss
RawString::(UTF8, ASCII)
```

This means:

* The value is raw `RawString`
* Multiple interpretations are available
* No single meaning is implied

This form:

* is local-only
* is not exportable
* creates no new semantic type

---

### 7.2 Named Bindings as Types

```bliss
fx print(s: String) {
    int n = s.length();
}
```

Guarantees:

* Fixed semantic meaning
* No ambiguity
* Stable API surface

---

## 8. Method Resolution Rules

### 8.1 Qualified Calls (Always Legal)

```bliss
x.length::UTF8();
x.serialize::Serializable();
```

Meaning:

* Explicit semantic selection
* No ambiguity
* No persistent semantic state

This is called **action-qualified invocation**.

---

### 8.2 Unqualified Calls

```bliss
x.length();
```

Legal only if:

* Exactly one active action defines `length`

Illegal if:

* Multiple actions define `length`
* No action defines `length`

The compiler must emit an error.

---

### 8.3 No Implicit Binding

```bliss
RawString x;
x.length(); // ❌ illegal
```

All semantics must be explicit.

---

## 9. Ephemeral Reinterpretation

```bliss
RawType x;
x.doSomething::Z();
```

Properties:

* No type change
* No behavior attachment
* No semantic state stored
* Local to the expression

Reinterpretation is **ephemeral**, not persistent.

---

## 10. Narrowing (Optional Sugar)

```bliss
String s = raw::UTF8;
s.length();
```

* Zero-cost
* No data copy
* Creates a semantic view

---

## 11. Composition Model

### 11.1 Action Composition

```bliss
Type::(X, Y, Z)
```

Rules:

* All actions are available
* No implicit override
* No precedence rules
* Conflicts require qualification

---

### 11.2 Conflict Handling

```bliss
t.length();        // ❌ ambiguous
t.length::X();     // OK
t.length::Z();     // OK
```

Ambiguity is never resolved implicitly.

---

## 12. Interpretation vs Capability Guidance

### 12.1 Reinterpretation Actions

```bliss
String::(UTF8, ASCII)
```

* Represents conflicting interpretations
* Allowed but discouraged
* Compiler emits warnings
* All calls must be explicit

### 12.2 Capability Actions

```bliss
User::(Serializable, Formatter, Colors)
```

* Additive behavior
* Safe to compose
* Encouraged

### Design Guideline (Non-Enforced)

> Composing multiple reinterpretations should be avoided.
> Composing capabilities is encouraged.

---

## 13. Safety Model

### 13.1 Guarantees

* No hidden semantics
* No implicit behavior injection
* No accidental coherence
* Local reasoning only

### 13.2 Non-Goals

Bliss does **not** guarantee semantic correctness across interpretations.

```bliss
int n = s.length::UTF8();
byte b = s.at::ASCII(n); // logically wrong, but explicit
```

This is a conscious design choice.

---

## 14. Export Rules

Exportable:

* `data`
* `action`
* named `bind` results

Not exportable:

* anonymous reinterpretation sets
* ad-hoc action views

This ensures API stability.

---

## 15. Compilation Model (Informal)

* Actions compile to method tables
* Qualified calls are statically resolvable
* No dynamic dispatch unless explicit
* Reinterpretation has zero runtime overhead

---

## 16. Core Laws of Bliss

1. Data defines memory
2. Actions define behavior
3. Bindings name meaning
4. Reinterpretation is explicit
5. Ambiguity is never hidden

---

## 17. Canonical Definition

> **Bliss is a language where data defines memory, actions define interpretation, and meaning is chosen explicitly at the point of use.**

---

## 18. Conclusion

Bliss embraces a fundamental truth of programming:

> Broken logic cannot be prevented — only made explicit.

By rejecting implicit semantics and exposing reinterpretation directly in the type system, Bliss provides a powerful, honest foundation for systems programming and language research.

---

*End of specification.*