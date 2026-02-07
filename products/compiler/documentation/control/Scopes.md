Scopes are logical separations in bliss.
They serve only one purpose - to make sure code is separated nicely.

Files are already indexed as lexical scope.

For example:

src/
	math/
		add.bls
	main.bls
	
So you can now access all source code via file scoping:

```bls
// src/math/add.bls
using std.types; //to use the standard types

pub scope addition {
	pub fx add(int a, int b) {
		return a + b;
	}
}

pub fx normal() {
	//can be normally accessed
}

```

and to access this in main.bls:

```bls

using src.math.addition.add;
using std.console.log;
using src.math.normal;

log("Hello World! { add( a + b ) }");

```

Note: this is working because the 'int' type has .toString() implemented.
int is basically an alias for:

alias i32::stdint as int;