# Import

The `import` keyword brings an external package into scope. A package is a collection of Bliss code intended for use across codebases.

## Syntax

```bls
import <package>;
import <package>.<module>;
```

## What Enters Scope

The last segment of the import path is what enters scope.

```bls
import std;          // `std` enters scope
import std.console;  // `console` enters scope
```

## Rules

- The last segment of the path is what enters scope, regardless of path depth.
- A package must be available to the project — how packages are resolved and managed is covered in the `bliss.toml` section.

## Examples

```bls
import std;

std.doSomething();
```

```bls
import std.console;

console.print("Hello");
```

## Invalid Usage

```bls
import std.console;

std.console.print("Hello");  // ❌ — `std` is not in scope, only `console` is
```