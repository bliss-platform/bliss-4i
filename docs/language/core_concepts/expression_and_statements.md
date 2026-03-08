# Expressions and Statements

Bliss draws a strict distinction between expressions and statements. This distinction is not a convention — it is enforced by the language.

## Expressions

An expression is any construct that **produces a value**. Expressions can be used anywhere a value is expected — as an initializer, as a function argument, or as a condition.

The following are expressions in Bliss:

**Literals** — a direct value written in source code.
```bls
21
true
"Hello"
'x'
```

**Identifiers** — a named value.
```bls
x
age
isReady
```

**Binary expressions** — two expressions combined with an operator, producing a value.
```bls
x + 5
age >= 18
a && b
```

**Unary expressions** — a single expression preceded by an operator.
```bls
!isReady
-x
```

**Function calls** — always an expression in Bliss, regardless of whether the function returns a meaningful value or `void`.
```bls
add(3, 5)
greet("Alice")
```

**Data initialization** — a data type paired with a field initializer block. The block here is part of the expression, not a standalone construct.
```bls
User { name = "Alice", age = 21 }
```

## Statements

A statement is any construct that **performs an action** but produces no value. Statements cannot be used where a value is expected.

The following are statements in Bliss:

**Variable declaration** — declares a variable and optionally binds it to an expression.
```bls
let x: i32 = 5;
let name: u8[];
```

**Reassignment** — binds a new expression to an existing variable.
```bls
x = x + 1;
arr[0] = 10;
```

**Function definition** — defines a named function.
```bls
fx add(x: i32, y: i32) -> i32 {

}
```

**Control flow** — `if`, `elif`, `else`, and `while` are all statements.
```bls
if ( x > 0 ) {

}

while ( isRunning ) {

}
```

**Blocks** — a `{ }` block is a statement. It is structural and produces no value on its own. The only context where a block appears as part of an expression is data initialization.

**`import` and `use`** — bring external packages and internal files into scope.
```bls
import std;
use src.utils;
```

## The Distinction in Practice

Because assignment is a statement and not an expression, constructs like the following are **not valid** in Bliss:

```bls
let x: i32 = let y: i32 = 5;  // ❌ declaration is not an expression
while ( x = 5 ) { }           // ❌ assignment is not an expression
```

A function call, however, is always an expression and can appear as a standalone statement by itself:

```bls
greet("Alice");   // valid — expression used as a statement
```