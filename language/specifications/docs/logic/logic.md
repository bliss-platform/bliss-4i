The control flow in bliss is extremely simple.
It's normally how you would use.

1. Conditional flow

if () {

} elif () {

} else {

}

2. Enum matching

match Enum {
	a {
	
	},
	
	b {
	
	},
	
	c(K) {
	
	}
}

3. error handling

handle Err {
	Ok(x) {}
	Err(msg) {}
}

4. Control flow

for () {

} //simple for loop

