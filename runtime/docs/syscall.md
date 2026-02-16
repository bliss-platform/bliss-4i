# System Calls in Bliss Runtime

syscalls are those special out-of-runtime calls where the context
is moved from the runtime itself and to an external function written
in some other language.

System calls are conceptually same as calling a regular function, just
with a special keyword here.

There is a tray of function, each with a fixed identifier, is called.
That is called the SFXTray.

in a tray, there is the following attributes:

1. array of functions that can be called (via index)
2. the size of the array of the functions (basically length)

The tray is part of an essential system state that is independent of the
fibre itself.

When a system call is done, it is assumed that the said fibre is now
blocked, even if the call itself is non-blocking, or event driven.

There is a special register, RFX. This register tells all the functions and
even the system call to act in certain way.