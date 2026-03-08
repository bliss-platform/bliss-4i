# Conditions in Bliss

Bliss uses standard conditional branching with `if`, `elif`, and `else`.

## Syntax

```bls
if ( <condition> ) {

} elif ( <condition> ) {

} else {

}
```

## Rules

- `if` can stand alone.
- `elif` and `else` must be preceded by an `if` (or another `elif`).
- Each `<condition>` must be a **boolean expression** — any expression that evaluates to a value of type `bool`.

Since Bliss has built-in `true` and `false`, the condition must resolve to one of these values. Arithmetic or other non-boolean expressions are not valid conditions on their own.

## Examples

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

## Valid and Invalid Conditions

| Expression | Valid? | Reason |
|---|---|---|
| `x > 5` | ✅ | Comparison returns `bool` |
| `isReady` | ✅ | Variable of type `bool` |
| `true` | ✅ | Built-in boolean literal |
| `x + 5` | ❌ | Returns a number, not `bool` |