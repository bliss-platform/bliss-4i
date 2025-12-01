# The Bliss Package Manager Specificaion, 4I

Mayukh Chakraborty
30th November, 2025

## Purpose & Scope

Bliss Package Manager is a part of the Bliss Platform
that is concerned with managing dependencies, projects,
build pipelines, workspaces and the supply chain
scope of Bliss Platform

## Terminology

1. `bliss` is the core command where we start the package manager.
2. `project` is a well structured codebase that will be compiled
		to an executable.
3. `library` is a well structured codebase that will be used by
		other libraries or projects.
4. `workspace` is a collection of projects and libraries in a single
		place, used to produce multiple targets in a monorepo style
		management.
5. `dependencies` refers to libraries that other projects or libraries
	 depends on.
6. `std` referes to the standard package of bliss programming language.
7. `bpkg` is another name to refer Bliss Package Manager binary

## Architecture Model

The task of bpkg is following:

- Manage `projects`
- Manage `libraries`
- Manage `workspaces`
- Manage `dependencies`

And the function of each of them are as follows:

### Projects

To manage a project, we need to do the following:

- create a `project` with a name
- add `dependencies`
- remove `dependencies`
- update `dependencies`
- build the `project`

and it DOES NOT:

- tracks changes like version control
- syncs with cloud providers

### Libraries

To manage a library, we need to do the following:

- create a `library` with a name
- strict versioning rule that starts with `XI-Y` convention,
	X is the bliss iteration version and Y is the sub-version
- add `dependencies`
- remove `dependencies`
- update `dependencies`

and it DOES NOT:

- tracks changes like version control
- syncs with cloud provider
- host the library in a dedicated supply chain

### Workspaces

To manage a workspace, we need to do the following:

- create a `library` to that workspace
- remove a `library` from that workspace
- create a `project` to that workspace
- remove a `project` from that workspace
- add `dependencies`
- remove `dependencies`
- update `dependencies`
- override `dependencies` for that specific workspace

### Dependencies

To manage dependency, we need to do the following:

- store the dependency in a structured place
- store multiple version of same dependency
- add `dependencies`
- update `dependencies`
- remove `dependencies`
- resolve confilicting `dependencies`

## Operational Semantics

## External Interfaces

## Data formats & serialization

## Invariants and Constraints

## Error Model

## Security and Safety Gurantees

## Rationale

## Appendix