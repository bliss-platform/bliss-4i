# Bliss Memory Model – Design Summary

This document summarizes the memory model and runtime architecture designed for the Bliss language.

The goal is to achieve:

- Strong memory safety (no undefined behavior)
- High performance (comparable to C/Rust on hot paths)
- Explicit control over dynamic memory
- Clear language semantics
- Predictable runtime behavior

---

## 1. Core Philosophy

Memory safety is not about preventing all mistakes.

It is about:

> Converting undefined behavior into deterministic runtime failure.

Invalid memory operations must:
- be detected
- produce precise errors
- never corrupt program state
- never continue execution silently

---

## 2. Fundamental Axioms

### Axiom 1 – Primitives are copied
All primitive values are passed by value.

No aliasing. No lifetime issues.

---

### Axiom 2 – Primitives are not objects
Primitives:
- do not use `new`
- do not support `clone` or `drop`
- are never heap allocated
- have no identity

---

### Axiom 3 – Objects are reference-based
Objects:
- are passed by reference
- require explicit `new`
- `clone` always means deep copy
- have identity

---

## 3. Dual-Mode Memory Model

Bliss uses **two distinct memory worlds**.

---

### A. Value / Struct Mode (Default)

Example:

```bliss
Data x = init Data();
```

Properties:

- Stack or register allocated
- Copy-by-value
- No heap
- No identity
- No vtables
- No metadata
- No `drop`, `clone`, or references
- Fully statically analyzed
- Zero runtime overhead

Equivalent to:

- C structs
- Rust stack values
- Swift structs

---

### B. Object / Self-Managed Mode (Explicit)

Example:

```bliss
Data x = new Data();
```

Properties:

- Heap allocated
- Has identity
- Uses handles (virtual pointers)
- Has metadata
- Optional vtable
- Supports mutation
- Supports shared references
- Supports `drop` and `clone`
- Runtime memory safety checks

Used only when semantics require:

- dynamic lifetime
- polymorphism
- shared ownership
- cyclic graphs
- escaping closures
- containers

---

## 4. Static Analysis Boundary

The compiler attempts to prove value-mode safety.

If it cannot, compilation fails:

```
[Compiler::Error]
Static memory safety analysis cannot safely track variable "counter".
Use `new` to create a self-managed object.
```

This makes dynamic memory:

- explicit
- intentional
- auditable
- predictable

---

## 5. Virtual Pointers (Handles)

Objects are not accessed via raw addresses.

Instead:

```text
Handle = { object_id, generation }
```

Runtime maintains:

```text
object_id → { data_ptr, generation, type_id, alive }
```

On access:

- generation must match
- object must be alive
- otherwise → runtime trap

This guarantees:

- use-after-free detection
- double-free detection
- pointer reuse safety
- type safety
- sandboxing

---

## 6. VTables (Selective)

VTables are used **only for self-managed objects** and only when:

- polymorphism
- interfaces
- dynamic dispatch

Struct/value types never use vtables.

Method dispatch:

```text
type_id → vtable → function
```

---

## 7. Instruction Set Split

### Value instructions

```
load32
store32
copy64
memcpy_struct
add
mul
```

No safety checks.

---

### Object instructions

```
newobj
dropobj
loadfld
storefld
callvirt
cloneobj
```

Always validated through the object table.

---

## 8. Allocation Model

`new Object()` performs:

1. Allocate object data
2. Allocate object_id slot
3. Initialize metadata
4. Return handle

Objects do not store headers inline.

Metadata is centralized for cache efficiency.

---

## 9. Memory Errors

Memory violations are **fatal runtime traps**, not catchable exceptions:

- use-after-free
- double free
- invalid handle
- type mismatch
- invalid object access

These errors:

- halt execution
- report allocation site
- report free site
- report access site

---

## 10. Performance Characteristics

### Value mode:
- Same performance as C/Rust
- Zero runtime overhead
- Cache-friendly
- Vectorizable

### Object mode:
- Handle lookup
- Generation check
- Optional vtable call

No:

- garbage collection
- tracing
- write barriers
- heap scanning
- stop-the-world pauses

On average:

> Faster than GC languages  
> Comparable to Rust  
> Predictable latency

---

## 11. Safety Guarantees

| Property | Value Mode | Object Mode |
|----------|------------|-------------|
| Use-after-free | Impossible | Detected |
| Double free | Impossible | Detected |
| Aliasing bugs | Impossible | Controlled |
| Pointer forgery | Impossible | Impossible |
| Silent corruption | Impossible | Impossible |

---

## 12. Design Outcome

Bliss achieves:

- Compile-time safety for simple code
- Runtime safety for complex code
- Explicit performance control
- Clear semantics
- No garbage collector
- No borrow checker
- No undefined behavior

---

## 13. One-sentence Summary

Bliss is a language where:

> Memory is safe by proof for values, safe by validation for objects, and unsafe code simply cannot execute silently.

---

End of document.
