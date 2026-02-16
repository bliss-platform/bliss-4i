BLISS RUNTIME – FACTORY MODEL (REFERENCE)

Factory / Core
- Top-level runtime
- Owns all Workers
- Initializes system resources
- Creates / destroys Workers
- Does NOT execute user code

Worker
- 1 Worker = 1 OS thread
- Scheduled by OS (preemption, cores)
- Managed by runtime (logic)
- Owns:
  - Mailbox
  - Fibre run-queue
- Runs exactly 1 Fibre at a time
- No shared mutable memory with other Workers

Thread vs Worker vs Fibre
- Thread  : OS scheduling entity
- Worker  : Bliss abstraction mapped 1:1 to OS thread
- Fibre   : User-level execution unit inside a Worker

Fibre
- Lightweight, cooperative
- Multiple Fibres per Worker
- Never migrates between Workers
- Explicit yield / suspend
- Never blocks OS thread
- Lifecycle:
  Created -> Ready -> Running -> Suspended -> Ready -> Dead

Mailbox
- One mailbox per Worker
- Message queue / array
- MPSC (multi-producer, single-consumer)
- Inbox-only
- Workers communicate ONLY via mailboxes
- No shared state, no locks between Workers

Message Rules
- Structured (type + size + payload)
- Copyable / serializable
- No raw pointers
- Network-safe by design

Scheduling Model
- OS schedules Workers
- Runtime schedules Fibres
- Hybrid model (OS + user-level)

Core Rule
- Workers are isolated
- All communication is message passing

Philosophy
- OS schedules time
- Bliss schedules meaning