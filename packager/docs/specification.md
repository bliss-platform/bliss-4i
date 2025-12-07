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

## Project Specification

A project is defined by the presence of `project.toml` file in a directory. The responsibility of a project is to produce an executable binary compatible with bliss runtime of the same platform. With this file, there comes some assumption about the said folder.

The assumption are:

- The folder contains a `src` folder with atleast a `main.bpl` file
- The file `main.bpl` contains a valid bliss program
- The file `main.bpl` contains a valid main function
- The folder contains a valid `project.toml` file

And a non-enforcing assumption:

- The folder may contain `lockfile.toml`, but if it does, the package manager assumes that the `lockfile.toml` was not tampered with.

The package manager cannot guarantee that the `lockfile.toml` was tampered with, so this is a file that in any circumstance be never managed manually.

If any of the above assumptions are broken, then following errors are expected:

- **[ERROR]** src folder do not exist
- **[ERROR]** main.bpl file do not exist
- **[ERROR]** there is no main function to execute
- **[ERROR]** project.toml is malformed. Further actions cannot be taken

But the following cases do not break the assumption:

- creating other folders/files in presence of `src` and `src/main.bpl`
- creating multiple `.toml` files with different name
- creating a new project of same or different SDK.

and so on.

### `project.toml` file specification

The `project.toml` stores important information about the project itself. It includes primary information which are mandatory, and secondary information which can be added as meta data but are not used by bliss in any form.

The mandatory format looks like this:

```toml
[ project ]
name = "Name of Project"
root = "my_app"
version = "1.8.5-alpha-beta-any-possible-string"
platform = "4i" #corresponds to ni

[ dependencies ]
std.this = "1.0.0@4i"
std.scheme = "1.x.x@4i"

```

A project is fully described using these parameters. Any new additions, like
```toml
[ author ]
github = "https://github.com/author/repo"
```
and so on are additional metatdata and are not processed by the bliss platform tools **in context of project**.



---