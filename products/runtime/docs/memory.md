# Paging Model of Memory - How Allocations Work.

1. Global State, or Read Only Memory.

The global state is read by all threads, all fibres, and contains read-only information.
information such as the instructions, constant table, then system call function tray.

Each global state holds the following:

- An array of OS threads.

Each thread is guaranteed to be non-deadlocable, as only a single thread space is allowed
for each thread.

Each thread has a pool of fibre.

The actual task happens in the fibre part.

Each thread consists of the following:

- An array of 'pages' for memory
- An array of fibres.

The pages are of two type: