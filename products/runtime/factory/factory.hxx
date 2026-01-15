#ifndef FACTORY
#define FACTORY

#include <cstdint>
#include "../memory/constants.hxx"
#include "../engine/state.hxx"

#include "worker.hxx"

struct Factory {
	
	//a factory consists of workers, isolated, and have fibres under them.
	Worker *workers;
	int worker_count;
	
	uint64_t *instructions;
	Constant *constantPool;
	SFXTray *tray;
	
	static Factory *init(SFXTray *tray, Constant* pool, uint64_t* instruction);
	static void spawnWorker(Factory* factory);
	
};

#endif