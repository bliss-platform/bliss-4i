# Function Model - How functions work in Bliss

Functions are unit of code basically. They are allocated on a special
memory called Function Storage Memory which is thread local (Or Worker)

What happens is a function is:

1. Computed size at compile time
2. A function frame size is generated

Whenever a function is "called", the bliss generates static allocation
code that allocates the function frame on the function memory region (extremely fast)

But there are limitations to that as well.

## Allocation rules:

All local values and objects are allocated on the function frame unless
it escapes via a closure, or is set to some external variable.

```bls

fx doSomething() {
	
	DataGrid n = new DataGrid();
	
	return fx () {
		return n.value();
	};

}

```

we can see that 'n' escapes. This simply means that the closure itself references
a value from the above function.

The function itself is now allocated to a different region instead of the original
function region.

As long as the closure lives, so does the function. So how do we prevent memory
leaks here?