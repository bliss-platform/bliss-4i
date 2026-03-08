# Functions in Bliss

Functions are defined using the `fx` keyword.

## Definition Syntax

```bls
fx <name>( <arg1>: <type1>, <arg2>: <type2> ) -> <ReturnType> {
    // statements or expressions
}
```

The return type is optional. If omitted, the function returns nothing.

## Call Syntax

```bls
<name>( <arg1>, <arg2> );
```

## Rules

- A function definition is itself a statement.
- Arguments are written as `<name>: <type>` pairs, separated by commas.
- A function can be defined with no arguments and/or no return type.

## Passing Conventions

Bliss has built-in passing conventions that cannot be changed:

- **Primitives** (scalars) are always **passed by value** — a copy is made automatically.
- **Arrays and `data` types** are always **passed by reference** — a pointer is passed instead.

```bls
fx increment( x: i32 ) {
    // x is a copy — the original is unaffected
}

fx fill( buffer: u8[] ) {
    // buffer is a reference — modifications affect the original
}
```

> Taking a reference of a primitive is not permitted.

## Copying

When passing arrays or `data` types, Bliss provides two mechanisms to pass a copy instead of a reference.

### 1. Copy in the Argument Definition

Placing `copy` in the argument declaration allocates space for the entire entity **within the function's own stack frame**:

```bls
fx process( items: copy u8[size] ) {
    // items is a full copy living in this function's frame
}
```

### 2. Copy at the Call Site

Placing `copy` at the call site allocates a new copy **on the heap** and passes a pointer to it:

```bls
fx process( items: u8[] ) {
    // receives a pointer to a heap-allocated copy
}

process( copy buffer );
```

### Difference

| | `copy` in argument | `copy` at call site |
|---|---|---|
| Where copy lives | Function's stack frame | Heap |
| What is passed | The value itself | Pointer to heap copy |
| Size required in signature | ✅ Yes | ❌ No |

## Examples

```bls
fx add( x: i32, y: i32 ) -> i32 {
    // x and y are copies of the passed values
}

fx transform( data: copy u8[64] ) {
    // entire 64-byte array copied into this frame
}

fx process( items: u8[] ) {
    // receives reference (or heap copy if called with `copy`)
}

process( copy myBuffer );  // heap copy passed
add( 3, 5 );
```

## Syntax Reference

| Part | Required? | Description |
|---|---|---|
| `name` | ✅ | The function's identifier |
| `( ... )` | ✅ | Argument list, can be empty |
| `-> ReturnType` | ❌ | The type the function returns |
| `{ ... }` | ✅ | The function body |
| `copy` in argument | ❌ | Copies entity into the function's stack frame |
| `copy` at call site | ❌ | Allocates a heap copy and passes a pointer |