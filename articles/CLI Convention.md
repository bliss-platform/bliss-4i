---
layout: single
title: "CLI Convention for The Bliss Platform"
sidebar:
  nav: "articles"
---

For Platform bliss-4i\
7 December 2025

## 1. Introduction

The Bliss Platform is an ecosystem composed of multiple cooperating binaries that together compile, package, and execute Bliss programs.  
To maintain consistency across all components, Bliss defines a unified rule set for command-line interface (CLI) structure.  
This specification is known as the **Pure Function CLI Convention**.

Its purpose is to create predictable, minimal, and deterministic interfaces suitable for both local and cloud execution environments.

---

## 2. Pure Function CLI Convention

Under this convention, every CLI invocation behaves analogously to a *pure function call*:

- **Command name** → function name  
- **Fixed positional arguments** → function parameters  
- **No flags**, **no optional switches**, **no reordering**

This eliminates the complexity traditionally associated with CLI parsing.

### 2.1 Example

Traditional flag-based CLI:

```
$ add_binary --lhs 10 --rhs 20
```

Pure Function CLI equivalent:

```
$ add_binary add 10 20
```

Conceptual function mapping:

```
add(10, 20)
```

The CLI is simply a serialized representation of a pure function call.

---

## 3. Benefits

Adopting the Pure Function Convention provides several advantages:

### • Reduced Parser Complexity
No flags, long options, or ambiguous argument ordering.  
Parsing is trivial and deterministic.

### • Zero Ambiguity
The meaning of each argument is positionally fixed and cannot conflict with other parameters.

### • Consistent Interfaces Across All Binaries
The compiler, runtime, and packager all follow the same design principles, making the ecosystem coherent.

### • Easier Documentation
Each command has a clear signature that maps directly to internal functions.

### • Cloud-Friendly Behavior
The convention avoids reliance on environment variables, shell expansion, or platform-dependent behavior—ideal for sandboxed or containerized execution.

---

## 4. Downsides

The Pure Function approach introduces several tradeoffs:

### • Less Ergonomic for Traditional CLI Users
Users accustomed to flag-based commands (`--config`, `--output`) may find positional arguments harder to recall.

### • Lower Readability
Flags often convey intent explicitly; positional arguments rely on documentation or experience.

### • Limited Optionality
Positional arguments restrict how optional or advanced parameters can be expressed.

---

## 5. Rationale and Tradeoff

Bliss adopts this convention because the underlying binaries are **not** intended for direct daily use.  
The platform ships the following core executables:

- `bliss_runtime_4i`  
- `bliss_compiler_4i`  
- `bliss_packager_4i`

These names are intentionally verbose and explicit.

Instead, Bliss provides a higher-level wrapper:

- `bliss.sh` on POSIX systems  
- `bliss.bat` on Windows

The wrapper scripts:

### • Provide a Developer-Friendly Interface
Flags, aliases, subcommands, and nicer help output exist only in this layer.

### • Centralize Argument Parsing
The wrapper handles validation, formatting, and environment resolution before delegating to the binaries.

### • Improve Cloud Integration
Because the binaries themselves avoid system lookups, the wrapper can enforce strict, deterministic behavior ideal for isolated environments.

### • Enable Efficient, Minimal Internal Binaries
The internal tools remain small, predictable, and optimized for speed.

---

## 6. Summary

The Pure Function CLI Convention:

- Ensures strict, deterministic execution  
- Simplifies parsing and reduces internal complexity  
- Unifies the CLI across all Bliss binaries  
- Delegates user ergonomics to top-level scripts (`bliss.sh` / `bliss.bat`)  

This design makes the platform more maintainable, more predictable, and well-suited for both local and cloud-native workflows.

---