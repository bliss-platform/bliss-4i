---
title: Log Convention for The Bliss Platform
nav_order: 2
parent: Articles
---

# Log Convention for The Bliss Platform
Version: bliss-4i  
Date: 8 December 2025

## 1. Introduction
The Bliss Platform requires unified diagnostic logging across all official tools including the runtime, compiler, packager, VM, assembler, and bootstrap scripts. This specification defines a strict, machine-parseable, human-friendly logging format. Logs represent serious diagnostic states: errors, warnings, and structured success messages. Normal program output MUST NOT be considered a log.

---

## 2. Axioms of Logging in Bliss
A log is a structured diagnostic emitted by Bliss tools. User programs may write to stderr, but only Bliss tools emit official logs. Logs follow a fixed multi-line structure and are colorized when printed to ANSI-capable terminals.

General format:
```
[TARGET::LEVEL] CODE
Title
Description
```

Example:
```
[RUNTIME::ERROR] 4RT006
Invalid bytecode
The bytecode being processed is malformed and cannot be executed further.
```
---

## 3. Log Header Specification
Header format:
```
[TARGET::LEVEL] CODE
```

**TARGET** — Name of the subsystem producing the log. Valid targets:
- RUNTIME  
- COMPILER  
- PACKAGER
- BLISS

**LEVEL** — Log severity:
- ERROR  
- WARN  
- INFO  
- DEBUG  

**CODE** — Encoded identifier of the form:
```
N<PLATFORM><ID>
```

Where:
- **N** = Bliss iteration major number (4 for bliss-4i)  
- **PLATFORM** = Two-letter subsystem code: RT, CP, PK, SH  
- **ID** = Three-digit identifier  

Examples: `4RT006`, `4CP110`, `4PK041`

---

## 4. Full Structured Log Format
A valid Bliss log contains:

Line 1: `[TARGET::LEVEL] CODE`  
Line 2: **Title** — one-line summary  
Line 3+: **Description** — detailed explanation  

Example:
```
[COMPILER::WARN] 4CP042
Unused variable
The variable 'result' is never read after assignment.
```

---

## 5. Success and Completion Logs
Success messages are **not diagnostic logs**.

Format:
```
[DONE] Message
```

Examples:
```
[DONE] Build completed
[DONE] Package installed successfully
```

---

## 6. Color Guidance (ANSI)

Bliss tools SHOULD emit colorized logs when connected to a TTY.  
Color MUST NOT affect parsing and is purely ornamental.

This specification adopts a **modern, non-clashing, harmonious 2025 palette**,  
inspired by Nord/Catppuccin/JetBrains styling.

### Recommended Colors

| Element        | Color Name      | ANSI Code        | Notes |
|----------------|------------------|------------------|-------|
| **TARGET**     | Frost Cyan       | `38;5;117`       | Modern, soft cyan used in many modern CLIs |
| **ERROR**      | Aurora Red       | `38;5;203`       | Red–magenta blend, strong but not harsh |
| **WARN**       | Muted Amber      | `38;5;180`       | Soft yellow-orange, avoids neon clutter |
| **INFO**       | Frost Blue       | `38;5;111`       | Clean and calm informational blue |
| **DEBUG**      | Storm Gray       | `38;5;245`       | Professional neutral gray |
| **CODE**       | Lavender         | `38;5;141`       | Premium purple accent used for IDs |
| **Description**| Dim Gray         | `2`              | Secondary, subdued text |
| **DONE**       | Soft Green       | `38;5;114`       | Modern success indicator (non-neon) |

![Sample Log Screenshot](../assets/logger.png)

---

## 7. Separation of Logs and Output
- Logs appear only for warnings and errors.  
- Success messages use `[DONE]`.  
- User output MUST NOT be treated as logs.  
- Spoofing is theoretically possible but practically rare and governed by ecosystem policy.  
- Tools MUST treat official logs as coming from Bliss tools only.

---

## 8. Examples
```
[PACKAGER::ERROR] 4PK020
Failed to resolve package
Package 'std@1.x.x@4i' could not be resolved via any configured registry profile.
```

```
[RUNTIME::WARN] 4RT102
Deprecated instruction
The instruction 'mov8' is deprecated and replaced by 'mv8'.
```

```
[DONE] Compilation completed successfully
```

End of Specification.

---