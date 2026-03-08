# Module System

The module system is how Bliss code is organized and shared across files and packages. Bliss provides two distinct keywords for bringing code into scope: `import` and `use`.

## The Distinction

While both keywords bring code into scope, they serve fundamentally different purposes:

- `import` reaches **outward** — it brings in code from an external package.
- `use` reaches **inward** — it brings in code from within the current project.

This distinction is intentional. At any point in a Bliss file, it is immediately clear whether a dependency is external or internal based solely on the keyword used.

## Scope Rules

Both `import` and `use` follow the same scoping rule — the **last segment** of the path is what enters scope. This applies consistently regardless of how deep the path is.

## What's Covered

**Import** — how external packages are brought into a Bliss project.

**Use** — how files within the current project are brought into scope, and how the project root governs all paths.