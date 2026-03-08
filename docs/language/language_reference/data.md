# Data in Bliss

A `data` type stores a structured group of named values, similar to a record or struct.

## Definition Syntax

```bls
data <Name> {
    <field1>: <Type1>,
    <field2>: <Type2>
}
```

## Initialization Syntax

```bls
let <name>: <DataType> = <DataType>{ <field1> = <expr1>, <field2> = <expr2> };
```

All fields **must** be initialized — partial initialization is not valid.

## Example

```bls
data User {
    name: u8[],
    age: u8
}

let user0: User = User{ name = "Hello World", age = 21 };
```

## Strings and Character Arrays

Bliss does not have a dedicated string type. A string literal like `"Hello"` is syntactic sugar for an array of `u8` characters:

```bls
"x"  // sugar for [ 'x', .. ]
```

So `u8[]` is the natural type for text data.

## Syntax Reference

| Part | Required? | Description |
|---|---|---|
| `data <Name>` | ✅ | Declares a new data type |
| `<field>: <Type>` | ✅ | A named, typed field |
| `<DataType>{ ... }` | ✅ | Initializer; all fields must be provided |
| `<field> = <expr>` | ✅ | Field value assignment in initializer |