# Bliss Light Stack

The **Light Stack** is a lightweight, fixed-size function call stack
used by the Bliss runtime for control flow tracking and debugging.\
It stores only *call metadata* (not local variables or arguments),
making it fast, predictable, and extremely debugger-friendly.

------------------------------------------------------------------------

## Overview

Traditional stacks mix:

-   Local variables\
-   Function arguments\
-   Return addresses\
-   Debug information\
-   Saved registers

Bliss separates these concerns.

The Light Stack stores only:

-   Return address
-   Function identifier

All other execution state lives in frames or the heap.

------------------------------------------------------------------------

## Data Structure

``` c++
struct CallStackItem {
	uint64_t returnAddress;
	uint64_t stackFrameAddrs; // Return address / previous execution point
	uint16_t id;             // Function identifier
};
```

------------------------------------------------------------------------

## Call Mechanism

When a function is called:

1.  The runtime uses either:

    -   `callx` → heap-based frame (closure)
    -   `callf` → stack/frame-based call (non-closure)

2.  The current instruction pointer is stored as `stackFrameAddrs`.

3.  A `CallStackItem` is pushed into the Light Stack.

4.  The **RFX register** is updated to point to the current stack index.

------------------------------------------------------------------------

## Return Mechanism

On `ret`:

1.  The runtime decrements the RFX register.
2.  Reads the stored `stackFrameAddrs`.
3.  Jumps back to that address.

No stack unwinding or frame scanning is required.

------------------------------------------------------------------------

## What the Light Stack Solves

### 1. Location Independence

Functions can be stored anywhere in memory.\
Call tracking does not depend on physical layout or ABI conventions.

------------------------------------------------------------------------

### 2. Trivial Stack Traces

The Light Stack can be dumped directly:

``` text
[0] main
[1] parse_input
[2] optimize_ir
[3] generate_code
```

An internal `stacktrace` opcode can output the full call history
instantly.

------------------------------------------------------------------------

### 3. Symbol-Friendly Debugging

If the bytecode includes an `id → function name` mapping, stack traces
become fully human-readable.

------------------------------------------------------------------------

### 4. Predictable Memory Usage

-   Fixed size
-   No recursive memory explosion
-   Safe upper bound on call depth
-   No stack overflow vulnerabilities

------------------------------------------------------------------------

## Architectural Properties

  Feature                  Behavior
  ------------------------ ---------------------
  Stack size               Fixed
  Stores locals            ❌ No
  Stores arguments         ❌ No
  Stores return address    ✅ Yes
  Stores function ID       ✅ Yes
  Stack traces             O(1)
  Tail-call optimization   Naturally supported
  JIT friendly             Yes
  Async friendly           Yes

------------------------------------------------------------------------

## Conceptual Model

The Light Stack is a **call metadata stack**, not a data stack.

Execution state is split into:

-   **Registers** → live execution
-   **Frames / Heap** → locals and captured values
-   **Light Stack** → call history

This design aligns with modern VM architectures (JVM, Lua VM,
WebAssembly, Erlang VM).

------------------------------------------------------------------------

## Future Extensions (Optional)

Possible enhancements:

-   Add flags (closure call, native call, async boundary, etc.)
-   Add frame references for richer debugging
-   Built-in tail-call frame reuse
-   Controlled overflow trapping with diagnostics

------------------------------------------------------------------------

## Summary

The Bliss Light Stack provides:

-   Deterministic call tracking\
-   Zero-cost stack tracing\
-   ABI independence\
-   VM-friendly execution\
-   Strong debugging guarantees

It is a foundational runtime feature designed for correctness, tooling,
and long-term scalability.

------------------------------------------------------------------------