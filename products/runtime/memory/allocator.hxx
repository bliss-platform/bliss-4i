#ifndef RUNTIME_MEMORY
#define RUNTIME_MEMORY

//thread-safe memory BTW.
struct Memory {

	void *heap;
	void *stack;
	
	static Memory* init() noexcept;
	
	//and this parts reuses iallocator
	void rtalloc() noexcept;
	void rtfree() noexcept;
	void falloc() noexcept;
	
	void drop() noexcept;
	
};

#endif