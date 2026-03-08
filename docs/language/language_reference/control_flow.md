# Control Flow

Control flow constructs direct the execution path of a Bliss program. All control flow constructs are **statements** — they produce no value.

## Conditions

Both `if` and `while` require a condition. A condition must be a **boolean expression** — any expression that evaluates to a value of type `bool`. Since Bliss has built-in `true` and `false`, the condition must resolve to one of these values. Arithmetic or other non-boolean expressions are not valid conditions.

| Expression | Valid? | Reason |
|---|---|---|
| `x > 5` | ✅ | Comparison returns `bool` |
| `isReady` | ✅ | Variable of type `bool` |
| `true` | ✅ | Built-in boolean literal |
| `x + 5` | ❌ | Returns a number, not `bool` |
| `x + 1` | ❌ | Returns a number, not `bool` |

---

## Conditionals

Bliss uses standard conditional branching with `if`, `elif`, and `else`.

### Syntax

```bls
if ( <condition> ) {

} elif ( <condition> ) {

} else {

}
```

### Rules

- `if` can stand alone.
- `elif` and `else` must be preceded by an `if` (or another `elif`).
- Each `<condition>` must satisfy the condition rules defined above.

### Examples

```bls
if ( x > 5 ) {
    // runs when x is greater than 5
}
```

```bls
if ( x > 10 ) {
    // x is greater than 10
} elif ( x > 5 ) {
    // x is between 6 and 10
} else {
    // x is 5 or less
}
```

---

## Loops

Bliss has a single loop construct: the `while` loop.

### Syntax

```bls
while ( <condition> ) {

}
```

### Rules

- The `<condition>` must satisfy the condition rules defined above.
- The loop body executes repeatedly for as long as the condition remains `true`.
- If the condition is `false` on the first check, the body never executes.

### Examples

```bls
while ( x > 0 ) {
    // runs until x is no longer greater than 0
}
```

```bls
while ( true ) {
    // infinite loop
}
```