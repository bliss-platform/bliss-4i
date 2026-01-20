#ifndef RUNTIME_FACTORY
#define RUNTIME_FACTORY

#include <cstdint>
#include "../memory/constants.hxx"
#include "../engine/state.hxx"
#include "../utility/cdll_wrapper.hxx"

#include "worker.hxx"

struct Factory {
	
	//a factory consists of workers, isolated, and have fibres under them.
	CDLLWrapper<Worker> *workers;
	int worker_count = 0;
	pthread_mutex_t mutex;
	
	//DEBUG PROPERTY
	uint64_t opcode_counter;
	//DEBUG PROPERTY
	
	uint64_t *instructions;
	Constant *constantPool;
	SFXTray *tray;
	
	static Factory *init(SFXTray *tray, Constant* pool, uint64_t* instruction) noexcept;
	
	void drop() noexcept;
	void spawnWorker(Worker *worker) noexcept;
	void lock() noexcept;
	void release() noexcept;
	
};

#endif