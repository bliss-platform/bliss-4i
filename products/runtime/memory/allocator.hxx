#ifndef RUNTIME_MEMORY
#define RUNTIME_MEMORY

//thread-safe memory BTW.
struct Memory {

	void *heap;
	void *functionRegion;
	
	static Memory* init() noexcept;
	
	//and this parts reuses iallocator
	void rtalloc() noexcept;
	void vialloc() noexcept;
	void falloc() noexcept;
	
	void vifree() noexcept;
	void rtfree() noexcept;
	void ffree() noexcept;
	
	void drop() noexcept;
	
};

#endif