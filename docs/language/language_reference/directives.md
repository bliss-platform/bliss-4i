# Directives

Bliss provides two compile-time naming constructs: `alias` and `sub`. Neither produces a runtime value — both are resolved entirely at compile time.

## `alias` — Type Names

`alias` masks an existing type under a new name. It introduces no new type — it is purely a naming convenience.

### Syntax

```bls
alias <Type> as <Name>
```

### Rules

- The aliased name is interchangeable with the original type everywhere a type annotation is expected.
- An alias does not create a distinct type — `alias u8[] as String` does not make `String` and `u8[]` incompatible.

### Example

```bls
alias u8[] as String

let name: String = "Hello World";  // equivalent to let name: u8[] = "Hello World"
```

---

## `sub` — Expression Names

`sub` binds a name to a valid expression. Wherever the name appears, it is replaced by the expression directly.

### Syntax

```bls
sub <name> = <expr>
```

### Rules

- The bound expression must be a valid Bliss expression.
- `sub` is not a variable — it holds no memory and cannot be reassigned.
- Wherever the name appears, the expression is substituted in place at compile time.

### Example

```bls
sub MaxAge = 100
sub IsAdult = age >= 18

while ( IsAdult ) {
    // equivalent to while ( age >= 18 )
}
```

---

## Comparison

| | `alias` | `sub` |
|---|---|---|
| Applies to | Types | Expressions |
| Runtime value | ❌ | ❌ |
| Resolved at | Compile time | Compile time |
| Creates new type | ❌ | — |
| Can be reassigned | ❌ | ❌ |