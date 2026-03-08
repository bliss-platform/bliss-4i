# Use

The `use` keyword brings a file from within the current project into scope. Paths are always resolved from the project root — the directory containing `bliss.toml`. There are no relative paths in Bliss.

## Syntax

```bls
use <path.to.file>;
```

## What Enters Scope

The last segment of the path is what enters scope, consistent with how `import` behaves.

```bls
use src.utils;   // `utils` enters scope
use math.vector; // `vector` enters scope
```

## Rules

- Paths are always resolved from the project root, never relative to the current file.
- The last segment of the path is what enters scope.
- The path must correspond to a valid `.bls` file within the project.
- Only declarations marked with `pub` in the target file are accessible.

## Examples

Given this project structure:

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
// src/utils.bls
pub fx helper() {}
```

```bls
// src/main.bls
use src.utils;
use math.vector;

utils.helper();
vector.doSomething();
```

## Invalid Usage

```bls
// from src/main.bls
use utils;  // ❌ — path must be resolved from project root, not current file
```

```bls
use src.utils;

src.utils.helper();  // ❌ — only `utils` is in scope, not `src`
```