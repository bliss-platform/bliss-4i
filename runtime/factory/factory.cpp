#include "../utility/os_thread.hxx"
#include "factory.hxx"
#include "worker.hxx"
#include "../utility/debug.hxx"
#include <pthread.h>
#include <cstdlib>

Factory *Factory::init( SFXTray *tray, Constant* pool, uint64_t* instruction ) noexcept {
	
	Factory *factory = (Factory*)calloc(1, sizeof(Factory));
	factory->constantPool = pool;
	factory->instructions = instruction;
	factory->tray = tray;
	factory->mutex = PTHREAD_MUTEX_INITIALIZER;
	
	return factory;
	
}

void Factory::spawnWorker(Worker *worker) noexcept {
	
	CDLLWrapper<Worker> *node = CDLLWrapper<Worker>::init(worker);
	
	if ( this->workers == nullptr ) {
	
		this->workers = node;
	
	} else {
		
		node->next = this->workers->next;
		node->prev = this->workers->prev;
		
		this->workers->next->prev = node;
		this->workers->next = node;
	
	}
	
}

void Factory::drop() noexcept {
	printf("Total opcode ran: %lu\n", this->opcode_counter);
	free(this);
}

void Factory::lock() noexcept {
	thread_lock(&this->mutex);	
}

void Factory::release() noexcept {
	thread_release(&this->mutex);
}