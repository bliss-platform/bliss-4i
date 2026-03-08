# Project Structure

A Bliss project is defined by two required components:

```
project/
├── bliss.toml
└── src/
    └── main.bls
```

## `bliss.toml`

The `bliss.toml` file marks the **root of the project**. Any directory containing a `bliss.toml` is recognized as a Bliss project. The contents of this file will be covered in a later section.

## `src/main.bls`

Every Bliss program starts execution from `src/main.bls`. This file is the mandatory entry point — it must exist and must be located at `src/main.bls` relative to the project root.

## Additional Files and Folders

Beyond the two required components, the project layout is open. Any files and folders can be created under the project root. These files are brought into scope using the `use` keyword, with all paths resolved from the project root.

```
project/
├── bliss.toml
├── src/
│   ├── main.bls
│   └── utils.bls
└── math/
    └── vector.bls
```

```bls
// src/main.bls
use src.utils;
use math.vector;
```

## Rules

- `bliss.toml` must exist at the project root.
- `src/main.bls` must exist and serves as the sole entry point.
- All `use` paths are resolved from the project root, never relative to the current file.