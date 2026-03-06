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

## Examples

```bls
fx add( x: int, y: int ) -> int {
    // returns an int
}
```

```bls
fx greet( name: str ) {
    // no return type
}
```

```bls
fx doSomething() {
    // no arguments, no return type
}
```

Calling them:

```bls
add( 3, 5 );
greet( "Alice" );
doSomething();
```

## Syntax Reference

| Part | Required? | Description |
|---|---|---|
| `name` | ✅ | The function's identifier |
| `( ... )` | ✅ | Argument list, can be empty |
| `-> ReturnType` | ❌ | The type the function returns |
| `{ ... }` | ✅ | The function body |