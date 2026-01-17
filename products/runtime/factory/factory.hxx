#ifndef FACTORY
#define FACTORY

#include <cstdint>
#include "../memory/constants.hxx"
#include "../engine/state.hxx"
#include "../utility/cdll_wrapper.hxx"

#include "worker.hxx"

struct Factory {
	
	//a factory consists of workers, isolated, and have fibres under them.
	CDLLWrapper<Worker> *workers;
	int worker_count = 0;
	
	uint64_t *instructions;
	Constant *constantPool;
	SFXTray *tray;
	
	static Factory *init(SFXTray *tray, Constant* pool, uint64_t* instruction);
	static void spawnWorker(Factory* factory, Worker *worker);
	
};

#endif