# bliss-4i

> A research project exploring language design, runtime development, compiler architecture, and full‑pipeline execution.

---

## Overview

**bliss-4i** is a research project focused on exploring:

* Programming language design
* Runtime and memory model development
* Compiler and interpreter architecture
* Resource management (packages, modules, dependency resolution, build semantics)
* The full language pipeline: parsing → analysis → IR → execution

The project is intentionally experimental and iterative. Its purpose is to understand how modern languages are built *end‑to‑end*, and to prototype ideas around safety, performance, and explicit control at both compile time and runtime.

This repository is therefore best viewed as a **language laboratory**, not a finished product.

### About AI usage

AI tools are used as a development aid in this project, mainly for:

* Summarizing research papers and technical articles
* Discovering and comparing existing language and runtime designs
* Citing and organizing references and learning resources
* Assisting with debugging, design reviews, and documentation

All architectural decisions, implementations, and experiments are ultimately reviewed and directed by a human, but AI is treated as a productivity and research accelerator.

---

## Design Philosophy

bliss is built around a few core ideas:

### 1. Explicit Over Implicit

Nothing happens "magically" at runtime unless the programmer opts into it.

Memory ownership, reference counting, borrowing, and movement are all *visible concepts* in the language.

### 2. Layered Safety

Instead of choosing one model, bliss supports multiple safety layers:

| Layer              | Purpose                                                        |
| ------------------ | -------------------------------------------------------------- |
| Static analysis    | Detect ownership chains, invalid lifetimes, and aliasing risks |
| Reference counting | Automatic memory reclamation when safe                         |
| Manual memory      | Escape hatch for full control                                  |

Each layer can be used independently or together.

### 3. Pay Only for What You Use

Features like atomic reference counting, runtime checks, or tracing are opt-in.

The compiler should be able to remove unused safety layers entirely.

### 4. Runtime Transparency

You should be able to understand:

* Where memory is allocated
* Who owns it
* When it is freed
* Why it is freed

No hidden GC cycles. No opaque memory behavior.

---

## What does "4i" mean?

"4i" refers to the **fourth iteration** of the language and runtime architecture.

Earlier iterations explored:

* Pure manual memory management
* Pure reference counting
* Rust-like strict ownership

This version combines all three in a unified model.

---

## Key Features

### Ownership & Borrowing (Static Analysis)

The compiler tracks:

* Ownership chains
* Immutable borrows
* Mutable borrows
* Escaping references

But unlike Rust:

* The rules are *configurable*
* Violations can be warnings instead of hard errors
* Runtime fallback is possible

### Reference Counting (ARC)

Objects can be placed under automatic reference counting:

* Atomic by default
* Can be downgraded to non-atomic in single-threaded contexts
* Compiler can elide RC when provably unnecessary

### Manual Memory Support

You can still:

* Allocate raw memory
* Control object layout
* Use custom allocators
* Manage lifetimes manually

### Multi-layer Deallocation Model

Objects can be freed by:

1. Static proof (compile-time)
2. Reference count reaching zero
3. Explicit `free`

The compiler chooses the fastest valid strategy.

### Systems-oriented Design

Although bliss-4i is currently **interpreted**, it is designed with systems-level concerns in mind:

* Explicit memory management
* Predictable performance characteristics
* Control over allocation and object layout
* Runtime transparency
* Minimal hidden costs

It targets the same *problem domain* as systems languages (runtimes, engines, OS components, low-level services), even if the current execution model is interpreted rather than ahead-of-time compiled.

It is therefore best described as a **systems-oriented language and runtime experiment**, not a traditional scripting language.

It is not aimed at rapid prototyping or general-purpose scripting.

---

## Project Structure

```
bliss-4i/
├── compiler/        # Frontend + type system + borrow analysis
├── runtime/         # Memory manager, RC implementation, threading
├── stdlib/          # Core language library
├── tests/           # Compiler + runtime tests
├── examples/        # Example programs
├── docs/            # Design documents
└── tools/           # Build tools and experiments
```

(Structure may change as the project evolves.)

---

## Current Status

bliss-4i is currently in **active research & prototyping** phase.

Expect:

* Breaking changes
* Incomplete documentation
* Unstable syntax
* Experimental semantics

This project is not production-ready.

---

## Examples (Conceptual)

```bliss
std::console.log("Hello World!");
```

```bliss
//ranges are fun little thing that makes iteration easier in bliss

//ranges are explicit in bliss now!
for ( int i; 0 <= i < 5; i++ ) {
	
}

if ( a < b <= c ) {
	//range operator
}
```

```bliss
scope Math;

fx privateStuff() {
	//cannot be accessed because it not under any scope.
};

//define a sub-scope here
Math::SubScope::{

};

Math::{
	
	//private by default
	fx add(int a, int b): int {
		return a + b;
	}
	
	fx doSomeStuff() {
		privateStuff(); //this is valid.
	}
	
};

pub fx Math::sub(int a, int b): int {
	return a - b;
};
```

(Exact syntax may differ.)

---

## Non-goals

bliss intentionally does **not** aim to:

* Be simple
* Be beginner-friendly
* Replace mainstream languages
* Hide memory management

This is a research-driven systems language.

---

## Contributing

If you're interested in:

* Compiler design
* Memory models
* Runtime systems
* Programming language theory

Contributions, discussions, and design feedback are welcome.

---

## Roadmap (High level)

* [ ] Complete ownership + borrow checker
* [ ] Stable IR
* [ ] Pluggable allocator API
* [ ] Deterministic ARC optimizations
* [ ] Minimal standard library
* [ ] Self-hosting compiler prototype

---

## License
Apache-2.0

---

## Why this exists

bliss-4i exists to answer questions like:

* Can we statically reason about *most* memory while still allowing escape hatches?
* Can ARC be competitive with modern ownership-based models?
* Can language design reduce memory bugs *without* sacrificing systems-level control?

This project is a long-term exploration of those ideas.

---

If you are confused by the project, that is expected.

bliss-4i is not a product yet. It is a language laboratory.