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

## Scalar Types

Scalar variables hold a single value. Bliss provides the following scalar types:

| Category | Types |
|---|---|
| Signed integers | `i8`, `i16`, `i32`, `i64` |
| Unsigned integers | `u8`, `u16`, `u32`, `u64` |
| Floating point | `f32`, `f64` |
| Boolean | `bool` — valid values are `true` and `false` |

```bls
let age: u8 = 21;
let temperature: f32 = 36.6;
let active: bool = true;
```

## Arrays

Arrays hold a sequence of values of the same type. In Bliss, arrays are **fixed in size** and cannot be resized once created.

There are two ways to declare an array:

```bls
let name: Type[] = [];        // initialized with values
let name: Type[size];         // pre-defined size, uninitialized
```

```bls
let scores: u8[] = [ 10, 20, 30 ];
let buffer: u8[256];
```

### Array Assignment

Individual elements can be assigned using an index:

```bls
arr[index] = 10;
```

If the index is out of bounds, Bliss raises an **unrecoverable error**. Because array assignment is a statement and not an expression, it does not resolve into a `Result` — there is no way to handle or recover from the failure.

## Rules

- A type annotation is always required.
- The initializer expression is optional — a variable can be declared without one, leaving it unassigned.
- When provided, the expression must evaluate to a value compatible with the declared type.
- Arrays are fixed — their size cannot change after creation.
- Out-of-bounds array assignment is an unrecoverable error.

## Reassignment

A variable can be reassigned after declaration using `=`:

```bls
x = 10;
active = false;
```

Compound assignment operators are **not** valid in Bliss:

```bls
x += 1;  // ❌ invalid
x -= 1;  // ❌ invalid
```

Use a full reassignment instead:

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
| `Type[]` | ✅ | Array of `Type`, initialized with values |
| `Type[size]` | ✅ | Array of `Type` with a pre-defined fixed size |
| `arr[index] = <expr>` | — | Assigns a value to an array element; out-of-bounds is unrecoverable |