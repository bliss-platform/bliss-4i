---
title: Packager Specification
nav_order: 1
parent: Packager
---

# The Bliss Package Manager Specification

The bliss package manager is responsible for managing the following concepts:

- Project
- Workspace
- Library
- Dependency

This specification will only cover the above four usage case, their respective specifications, and how they can be implemented in context of `bliss-packager-4i` binary.

This document will **NOT COVER** command specification and implementation detail of `bliss.sh` or `bliss.bat` because those are initiation scripts and are governed by different specifications.

---

# Project Specification

A **project** in the Bliss ecosystem is any directory containing a `project.toml` file.  
A project's responsibility is to produce an executable binary compatible with the Bliss runtime of the same platform iteration.

The presence of a `project.toml` implies a well-defined directory structure and certain guarantees that the package manager and compiler rely on.

---

## 1. Project Structure Assumptions

A valid project directory **must** satisfy:

1. The directory contains a `src/` folder.  
2. `src/` contains a file named `main.bpl`.  
3. `main.bpl` contains:  
   - a valid Bliss program  
   - a valid `main` function  
4. The directory contains a syntactically valid `project.toml`.

These guarantees allow the compiler to reliably locate a project’s entry point and metadata.

---

## 2. Error Conditions

If any enforced assumption fails, tools must stop and emit:

- `src` folder does not exist  
- `main.bpl` file does not exist  
- `main` function not found  
- `project.toml` is malformed — further actions cannot be taken  

### Allowed Non-breaking Cases

These do **not** invalidate a project:

- additional files or folders inside the directory  
- multiple `.toml` files with arbitrary names  
- using any SDK or tool version (SDKs do not affect project structure)  

---

## `project.toml` Specification

A `project.toml` contains two classes of information:

- **Primary fields** — interpreted by Bliss tooling  
- **Secondary fields** — metadata fields ignored by Bliss tools but available for authors or external tooling  

---

## 3. Mandatory Structure

```toml
[project]
name = "Name of Project"
root = "my_app"
version = "1.8.5-alpha-any-string"
platform = "4i"  # bliss platform iteration

[packages]
std = ["1.5.8@4i", "1.x.x@4i"]
```

---

## 4. Meaning of the `project` Fields

### **1. `name`**
A human-readable descriptive name for the project.

### **2. `root`**
Defines the project’s import namespace.  
The root value corresponds to the internal module path prefix.

Example:

```
root = "my_app"
```

Directory structure:

```
src/
  main.bpl
  utils/math.bpl
```

Import:

```bliss
import my_app.utils.math
```

resolves to:

```
src/utils/math.bpl
```

### **3. `version`**
A descriptive and unrestricted version string for the project.  
This version is not used for dependency resolution.

### **4. `platform`**
Specifies the Bliss platform iteration (e.g., `4i`, `5i`).  
Each iteration defines the runtime ABI and instruction semantics.

**If the project's platform does not match the platform of an installed dependency, the compiler MUST reject the project.**

---

## 5. Metadata Fields (Ignored by Bliss Tools)

Metadata fields may appear as additional tables or entries.  
They do not affect compilation or packaging behavior.

Example:

```toml
[author]
github = "https://github.com/username/repo"
```

Bliss tools ignore all such fields.

---

## Dependency Specification

Bliss does not use a separate lockfile.  
**Each dependency entry stores:**

- the *current* installed version  
- the version *scheme* that determines future updates  

This makes the dependency entry act as both the version requirement and the lockfile.

> Modifying dependency entries by hand is NOT RECOMMENDED because the packager cannot guarantee correctness for manually edited entries.

---

## Dependency Entry Format

```toml
package_name = [ "current_version", "scheme" ]
```

Example:

```toml
std = ["1.5.8@4i", "1.x.x@4i"]
```

### Meaning of Fields

- **`current_version`**  
  The exact version currently installed.  
  Also serves as the minimum allowed version for future updates.

- **`scheme`**  
  Defines which components may change when performing an update.

---

## Scheme Semantics

A scheme describes which version components are fixed vs. variable.

Example:

```
1.x.x@4i
```

Means:

- **major = fixed (1)**  
- **minor = variable**  
- **patch = variable**  
- **platform = must match 4i**

Allowed examples:  
`1.5.8@4i`, `1.5.9@4i`, `1.6.0@4i`

Disallowed examples:  
`1.4.9@4i`, `2.0.0@4i`, `1.6.0@5i`

---

## Multiple Sources (Profiles)

Projects may retrieve packages from multiple sources such as:

- the default Bliss registry  
- a local package database  
- custom enterprise registries  

This is managed using **profiles**, which map dependency tables to different sources.

Example:

```toml
[packages]
std = ["1.0.0@4i", "1.x.x@4i"]

[packages.local]
my_amazing_package = ["1.0.2@4i", "x.x.x@4i"]

[packages.work]
in_house_std = ["5.2.3@4i", "5.2.x@4i"]
```

Each `packages.*` table is isolated and corresponds to a specific profile defined in the dependency specification.

> The `[packages.*]` tables do not inherit from each other.

---

## Dependency Clashing

If two packages of the **same name** appear under **different profiles**, it is considered a hard conflict.  
There is no priority order.  
The compiler MUST treat this as an error.

When attempting to add a dependency that already exists in another source, the packager will explicitly ask the user to:

- **reject** the addition, or  
- **override** the existing entry  

---

## Project Operations

Inside a valid project directory, the package manager supports:

1. **Add dependency**  
2. **Remove dependency**  
3. **Update dependency**  
4. **Upgrade dependency**

Build and run operations are handled by the global `bliss` script, which orchestrates multiple tooling components. It is not part of this specification.

---

## Adding a Dependency

Creates:

```toml
dep_name = [ "current_version", "scheme" ]
```

Added to `[packages]` by default, or under a profile if specified.

---

## Removing a Dependency

Removes the dependency entry.  
The compiler will error if the project still references imports from that package.

---

## Updating a Dependency (Scheme-Respecting)

`update`:

- respects the scheme mask  
- updates only `current_version`  
- never changes the scheme  
- guarantees compatibility  

Example:

```toml
# before
std = ["1.5.8@4i", "1.x.x@4i"]

# after update
std = ["1.7.4@4i", "1.x.x@4i"]
```

---

## Upgrading a Dependency (Explicit, Scheme-Ignoring)

`upgrade`:

- ignores the scheme mask  
- installs the latest available version  
- requires explicit user confirmation  
- updates `current_version`  
- regenerates the scheme according to the new major version  

Example:

```toml
# before
std = ["1.5.8@4i", "1.x.x@4i"]

# after upgrade
std = ["2.3.0@4i", "2.x.x@4i"]
```

---

All further rules for dependency resolution, version comparison, profiles, and transitive dependencies are defined in the **Dependency Specification**.

---