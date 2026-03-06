# Loops in Bliss

Bliss has a single loop construct: the `while` loop.

## Syntax

```bls
while ( <condition> ) {

}
```

## Rules

- The `<condition>` follows the same rules as in conditionals — it must be a **boolean expression** that evaluates to a value of type `bool`.
- The loop body executes repeatedly for as long as the condition remains `true`.
- If the condition is `false` on the first check, the body never executes.

## Examples

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

## Valid and Invalid Conditions

| Expression | Valid? | Reason |
|---|---|---|
| `x > 0` | ✅ | Comparison returns `bool` |
| `isRunning` | ✅ | Variable of type `bool` |
| `true` | ✅ | Built-in boolean literal |
| `x + 1` | ❌ | Returns a number, not `bool` |