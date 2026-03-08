# Types

Bliss is statically typed. Every value has a type, and that type is always explicitly declared. There are no implicit conversions — a value of one type can never be used where another type is expected.

## Scalar Types

Scalar types hold a single value.

### Integers

Bliss provides both signed and unsigned integers across four sizes:

| Type | Description |
|---|---|
| `i8`, `i16`, `i32`, `i64` | Signed integers |
| `u8`, `u16`, `u32`, `u64` | Unsigned integers |

The number denotes the bit width. A signed integer can represent negative values, an unsigned integer cannot.

### Floating Point

| Type | Description |
|---|---|
| `f32` | 32-bit floating point |
| `f64` | 64-bit floating point |

### Boolean

| Type | Valid Values |
|---|---|
| `bool` | `true`, `false` |

### Void

| Type | Description |
|---|---|
| `void` | Represents the absence of a meaningful value |

`void` is a valid type in Bliss. A function that returns nothing has a return type of `void`. It can be declared as a type annotation, though a `void` value carries no data.

## Composite Types

### Arrays

An array holds a fixed sequence of values of the same type. Arrays cannot be resized once created.

```bls
let scores: u8[] = [ 10, 20, 30 ];   // initialized with values
let buffer: u8[256];                  // pre-defined fixed size
```

`Type[]` is a valid type annotation throughout the language. `Type[size]` additionally constrains the array to a specific size. The implications of size mismatches in certain contexts are covered in the Functions section.

### Data

`data` is the only composite type in Bliss. It groups named, typed fields into a single structure.

```bls
data User {
    name: u8[],
    age: u8
}
```

`data` types are covered in full in the Data section.

## Strings

Bliss has no dedicated string type. A string literal is syntactic sugar for a `u8[]` array:

```bls
"Hello"  // sugar for [ 'H', 'e', 'l', 'l', 'o' ]
```

`u8[]` is therefore the natural type for text in Bliss.

## Type Strictness

Bliss enforces strict type compatibility. A value of one type cannot be used where another type is expected — even between types of the same family:

```bls
let x: i32 = 5;
let y: i64 = x;  // ❌ invalid — i32 is not i64
```

Type conversion will be introduced in a later revision of the language.