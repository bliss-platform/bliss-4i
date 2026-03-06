# Variables in Bliss

Variables are declared using the `let` keyword.

## Syntax

```bls
let <name>: <Type> = <expr>;
```

Or declared without an initial value:

```bls
let <name>: <Type>;
```

## Rules

- A type annotation is always required.
- The initializer expression is optional — a variable can be declared without one, leaving it unassigned.
- When provided, the expression must evaluate to a value compatible with the declared type.

## Examples

```bls
let x: int = 5;
let y: bool = x > 3;
let name: str = "Alice";
```

Declared without a value:

```bls
let x: int;
let ready: bool;
```

## Reassignment

A variable can be reassigned after declaration using `=`:

```bls
x = 10;
name = "Bob";
```

Compound assignment operators are **not** valid in Bliss:

```bls
x += 1;  // ❌ invalid
x -= 1;  // ❌ invalid
```

To achieve the same effect, use a full reassignment:

```bls
x = x + 1;  // ✅
x = x - 1;  // ✅
```

## Syntax Reference

| Part | Required? | Description |
|---|---|---|
| `name` | ✅ | The variable's identifier |
| `: Type` | ✅ | The variable's type |
| `= <expr>` | ❌ | Initial value; any expression of the matching type |