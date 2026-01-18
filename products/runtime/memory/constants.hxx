#ifndef CONSTANT_POOL
#define CONSTANT_POOL

#include <cstddef>
#include <cstdint>

struct Constant {
	uint8_t *bytes;
	size_t size;
	
	static Constant *init(uint8_t *bytes, size_t size);
	static void drop(Constant *constant);
};

#endif