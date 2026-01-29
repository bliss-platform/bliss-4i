#include "allocator.hxx"
#include <cstdlib>

Memory* Memory::init() noexcept {	
	return (Memory *)calloc(1, sizeof(Memory));
}

void Memory::drop() noexcept {
	free(this);
}