# The Bliss Platform - 4i

> A language laboratory exploring static analysis, reference counting, and manual memory management.

[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Status](https://img.shields.io/badge/Status-Active_Research-orange.svg)]()

**bliss-4i** is an experimental, research-driven platform for building and studying a programming language end-to-end — from syntax design to execution. It is not a production language. It is a laboratory.

The platform consists of several actively researched tools: a **language frontend** (with its own compiler and interpreter), a **runtime**, and a **package manager** — all developed together under a unified iteration.

⚠️ *Active research and prototyping phase. Expect breaking changes, experimental semantics, and incomplete documentation.*

---

## What does "4i" mean?

Bliss is developed in **iterations** — similar to how Rust has editions, or how Apple unifies versioning across its software. Each iteration may introduce breaking changes to the language and its tooling, and lives in its own repository.

**4i** means this is the **fourth iteration** of Bliss. All tools in this repository — the compiler, interpreter, runtime, and packager — conform to the `4i` specification.

---

## The Bliss Philosophy

Bliss is built around a few core ideas:

- **Explicit over implicit.** Memory ownership, borrowing, and movement are visible concepts — nothing happens magically at runtime unless you opt into it.
- **Layered safety.** Rather than enforcing a single paradigm, Bliss supports multiple composable safety layers that you can mix as needed.
- **Pay only for what you use.** Features like atomic reference counting and runtime checks are opt-in. Unused safety layers are compiled away entirely.
- **Runtime transparency.** You always know where memory is allocated, who owns it, and when and why it is freed.

---

## Repository Structure

```text
bliss-4i/
├── .github/workflows/   # CI configuration
├── docs/                # Design documents and specs
├── language/            # Rust workspace
│   ├── compiler/        # compiler
│   └── interpreter/     # interpreter
├── packager/            # Package manager
├── runtime/             # The bliss runtime
└── scripts/             # the root script
```

---

## Non-Goals

Bliss intentionally does **not** aim to:

- Be simple or beginner-friendly.
- Serve as a rapid prototyping or general-purpose scripting language.
- Hide memory management.
- Replace mainstream production languages.

---

## Contributing

**I am not currently accepting Pull Requests or external code contributions.** This is a personal research project, and the architecture is evolving too rapidly for external contributions to be practical right now.

That said, if you are interested in compiler design, memory models, runtime systems, or programming language theory — **discussions, issues, and design feedback are very welcome.**

---

*AI tools are used strictly as a development aid (summarizing research, debugging, and documentation). All architectural decisions and implementations are directed and authored by a human.*