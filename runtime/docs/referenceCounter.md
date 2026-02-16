# Reference Counting in Bliss

Reference counting is an important aspect of bliss memory
management. The point is that when memory is tracked by
how many "nodes" are connected to it.

I am actively researching new ways of implementing reference
counting across values so that it becomes easier to work
with.

## Issues with Reference Counting

Cycle detection issues

A -> B -> A (1st index)

the reference node cannot be freed based on the cycle detection
because freeing it is an issue.

## Static analysis and ownership proofs

Before reference counting is even introduced, static analysis
takes over the language.

This benefits two kinds of people:

1. The one who writes good code
-> if you write good code, the statically ownership may cover
	 a lot of cases, and might reduce runtime memory checks completely

2. The one who is starting to write code
-> if you are just starting out with bliss, bliss don't punish
	 bad code. You can just write your own logic however you want and
   at worst case, your performance will be simillar to a fast GC language.