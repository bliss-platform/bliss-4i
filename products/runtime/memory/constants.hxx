#ifndef CONSTANT_POOL
#define CONSTANT_POOL

#include <cstdint>

struct Constant {
	uint8_t *bytes;
	int size;
	
	static Constant *init();
	static void drop(Constant *constant);
};

#endif