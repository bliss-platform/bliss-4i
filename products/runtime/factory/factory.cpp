#include "factory.hxx"
#include "worker.hxx"
#include <cstdlib>

Factory *Factory::init( SFXTray *tray, Constant* pool, uint64_t* instruction ) {
	
	Factory *factory = (Factory*)calloc(1, sizeof(Factory));
	factory->constantPool = pool;
	factory->instructions = instruction;
	factory->tray = tray;
	
	return factory;
	
}

void Factory::spawnWorker(Factory *factory, Worker *worker) {
	
	if ( factory->workers == nullptr ) {
		factory->workers = CDLLWrapper<Worker>::init(worker);
	} else {
		CDLLWrapper<Worker> *node = CDLLWrapper<Worker>::init(worker);
		
		node->next = factory->workers->next;
		node->prev = factory->workers->prev;
		
		factory->workers->next->prev = node;
		factory->workers->next = node;
	}
	
}