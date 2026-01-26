#ifndef RUNTIME_OPCODE
#define RUNTIME_OPCODE

/*
 * Fixed Size, 128-bit instruction pointers
 * 
 * [ opcode (2 bytes) ][ first value (2 bytes) ][ second value (4 bytes) ][ third value (8 bytes) ]
 * 
 * The algorithm is actually simple -
 * Load all 16 bytes at once - using vectorized instruction loader
 * goto jump_table[ instruction[ 0..2 ] ]
 * The opcode is then decoded further by the handler if required.
 */
 
 /*
  * How does function calls even work in Bliss?
  * 
  * Well, there are two kinds of function call to work with.
  * First is simply the default kind of function call as defined in bliss
  * 
  * 
  */

enum OPCODES {
	
	//mathematics on different numeric values.
	//basically ROUT = R1 ops R2, ops = addition, subtraction etc.
	iradd, uradd, fradd, dradd,
	irsub, ursub, frsub, drsub,
	irmul, urmul, frmul, drmul,
	irdiv, urdiv, frdiv, drdiv,
	// [ <t>ops ][ ... padding ]
	
	//these are inline math ops. so you provide the value inline
	// basically REGISTER (ops)= value, ops = addition, subtraction, etc.
	// 
	ixadd, uxadd, fxadd, dxadd,
	ixsub, uxsub, fxsub, dxsub,
	ixmul, uxmul, fxmul, dxmul,
	ixdiv, uxdiv, fxdiv, dxdiv,
	
	// [ <t>xops ][ v1 - register ][ padding ][ 64 bit value (v3) ]
	// resizes the integer values to certain bit sizes, while maintaining it's signed property
	rbcrop,
	lbcrop,
	//these are called right bit crop and left bit crop
	//these literally crops the bit and stores them on the lower half.
	//[ xbcrop ][ croping_width ] -> will literally crop in place
	drbcrop, //d(ynamic)r(ight)b(it)crop
	dlbcrop,
	// identical to above, but is dynamic. Will use the cropping width form R2.
	
	icf, fci, lcd, dcl,
	// [ <x>c<y> ][ padding ] basically meaning <x> convert to <y>.
	// i = integer (i32), f = float (f32), d = double (f64), l = long (i64)
	// conditional jump, pure jump, system call
	jif, jifn, jmp, scall,
	// [ jif/jmp/scall ][ padding ][ address ]
	// [ ret ][ padding ]
	
	// yields, i.e switches to a new fibre, and launch = launch a new lightweight thread
	yield, launch, launch_worker,
	// [ yield/launch ] [ padding ]
	sendmsg, //R1 = message pointer, R2 = worker ID. MSG will assume structure of [ 32 bit size of message ][ ptr_to_raw_data (64 bit) ];
	readmsg, //reads the first message from the worker mailbox pool
	
	// equality is type agnostic
	eq,
	// less than equal to needs type, R1 <= R2 is done
	ilteq, ulteq, flteq, dlteq,
	// less than needs type, R1 < R2 is done
	ilt, ult, flt, dlt,
	// [ cops ][ padding ] where cops = comparitive operators
	band, bor, bxor, bnot, //bitwise ops
	shl, shr, //bitshift left, bitshift right.
	
	// copy data between registers, clear data in a register
	mov, cls, movflag,
	// [ mov ][ from ][ padding ][ to ]
	// [ cls ][ adrs ][ padding ]
	
	//copy across memory.
	heapcopy, constcopy, 
	
	// allocate in heap memory, free in heap memory
	rtalloc, vialloc, falloc, //allocate on the memory, the virtual memory or the function memory.
	irtalloc, ivalloc, //inline variants.
	rtfree, vifree, ffree, //free from runtime, virtual or function space.
	// store data to register -> heap
	memtoreg, fmemtoreg,
	// load data to heap -> register
	regtomem, fregtomem,
	//program end
	inspect, //this is only for developer mode.
	exitf
	
};

#endif
