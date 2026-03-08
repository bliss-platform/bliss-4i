# Summary

This page provides a concise reference of everything covered in this documentation.

## Project Structure

Every Bliss project requires two components:
- `bliss.toml` — marks the project root
- `src/main.bls` — the sole entry point of every Bliss program


## Core Concepts

### Expressions and Statements

- An **expression** produces a value: literals, identifiers, binary expressions, unary expressions, function calls, and data initialization.
- A **statement** performs an action but produces no value: variable declarations, reassignment, function definitions, control flow, blocks, `import`, and `use`.
- Assignment is always a statement. A function call is always an expression.

### Types

- Bliss is statically typed. All types are explicitly declared. There are no implicit conversions.
- **Scalar types:** `i8`, `i16`, `i32`, `i64`, `u8`, `u16`, `u32`, `u64`, `f32`, `f64`, `bool`, `void`
- **Composite types:** arrays (`Type[]`, `Type[size]`) and `data`
- **Strings** are `u8[]` — string literals are syntactic sugar for character arrays.

## Language Reference

### Variables

- Declared with `let <name>: <Type>` — type annotation is always required.
- Initialization is optional: `let x: i32 = 5` or `let x: i32`.
- Reassignment is valid: `x = 10`.
- Compound operators (`+=`, `-=`) are not valid.
- Array elements are assigned with `arr[index] = value` — out-of-bounds is an unrecoverable error.

### Functions

- Defined with `fx <name>( <args> ) -> <ReturnType> { }` — return type is optional.
- Arguments are written as `<name>: <type>` pairs.
- A function definition is a statement. A function call is always an expression.
- **Primitives** are passed by value. **Arrays and data types** are passed by reference.
- `copy` in the argument definition copies the entity into the function's stack frame.
- `copy` at the call site allocates a heap copy and passes a pointer to it.
- Taking a reference of a primitive is not permitted.

### Control Flow

- All control flow constructs are statements.
- Conditions must be boolean expressions that evaluate to `bool`.
- `if` can stand alone. `elif` and `else` must be preceded by `if`.
- `while` is the only loop construct. The body executes as long as the condition is `true`.

### Data

- Defined with `data <Name> { <field>: <Type>, ... }`.
- All fields must be initialized: `DataType { field = value, ... }`.
- `data` types are always passed by reference.

### Arrays

- Fixed in size — cannot be resized once created.
- Declared as `Type[]` (with values) or `Type[size]` (pre-defined size).
- Always passed by reference.
- Out-of-bounds assignment is an unrecoverable error.

### Directives

- `alias <Type> as <Name>` — masks a type under a new name. Compile-time only.
- `sub <name> = <expr>` — binds a name to an expression. Compile-time only.
- Neither `alias` nor `sub` produces a runtime value or can be reassigned.

## Module System

### Import

- `import <package>` — brings an external package into scope.
- `import <package>.<module>` — brings a specific module into scope.
- The last segment of the path is what enters scope.

### Use

- `use <path.to.file>` — brings an internal project file into scope.
- Paths are always resolved from the project root (`bliss.toml`), never relative.
- The last segment of the path is what enters scope.
- Only `pub` declarations are accessible from other files.