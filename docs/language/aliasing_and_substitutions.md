# Aliasing and Substitution in Bliss

## Aliasing

An alias masks an existing type under a new name. It introduces no new type — it is purely a naming convenience.

## Syntax

```bls
alias <Type> as <Name>
```

## Example

```bls
alias u8[] as String

let name: String = "Hello World";  // equivalent to let name: u8[] = "Hello World"
```

---

## Substitution

A substitution binds a name to a valid **expression**. It is not a variable — it is replaced by the expression directly wherever it is used.

## Syntax

```bls
sub <name> = <expr>
```

## Example

```bls
sub MaxAge = 100
sub IsAdult = age >= 18

while ( IsAdult ) {
    // equivalent to while ( age >= 18 )
}
```

## Comparison

| | `alias` | `sub` |
|---|---|---|
| Applies to | Types | Expressions |
| Runtime value | ❌ | ❌ |
| Acts as | A type name | An inline expression |