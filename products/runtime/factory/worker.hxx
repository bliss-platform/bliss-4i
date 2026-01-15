#ifndef WORKER
#define WORKER

#include "../fibre/fibre.hxx"
#include <cstdint>

struct Worker {
	
	uint32_t id; //a worker needs an ID to even work.
	FibreNode *fibres;
	void *memory; //boring old memory. to be used by custom allocators ofc.
	
	static Worker *init();
	static void addFibre(Worker *worker, Fibre *fibre);
	static void drop(Worker *worker);
	
};

#endif