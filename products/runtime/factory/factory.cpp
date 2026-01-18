#include "factory.hxx"
#include "worker.hxx"
#include <pthread.h>
#include <cstdlib>

Factory *Factory::init( SFXTray *tray, Constant* pool, uint64_t* instruction ) {
	
	Factory *factory = (Factory*)calloc(1, sizeof(Factory));
	factory->constantPool = pool;
	factory->instructions = instruction;
	factory->tray = tray;
	factory->mutex = PTHREAD_MUTEX_INITIALIZER;
	
	return factory;
	
}

void Factory::spawnWorker(Factory *factory, Worker *worker) {
	
	CDLLWrapper<Worker> *node = CDLLWrapper<Worker>::init(worker);
	
	if ( factory->workers == nullptr ) {
	
		factory->workers = node;
	
	} else {
		
		node->next = factory->workers->next;
		node->prev = factory->workers->prev;
		
		factory->workers->next->prev = node;
		factory->workers->next = node;
	
	}
	
}

void Factory::drop(Factory *factory) {
	free(factory);
}