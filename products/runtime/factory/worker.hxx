#ifndef RUNTIME_WORKER
#define RUNTIME_WORKER

#include "../utility/cdll_wrapper.hxx"
#include "../fibre/fibre.hxx"
#include <cstdint>

//forward declaration
struct Factory;

struct Worker {
	
	uint32_t id; //a worker needs an ID to even work.
	CDLLWrapper<Fibre> *fibres;
	void *memory; //boring old memory. to be used by custom allocators ofc.
	
	static Worker *init();
	static void addFibre(Worker *worker, Fibre *fibre);
	static void drop(Worker *worker);
	static void execute(Worker *worker,  Factory *factory);
	static void terminate(Worker *worker);
	
};

#endif