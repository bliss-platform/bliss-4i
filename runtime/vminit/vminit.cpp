#include "vminit.hxx"
#include "../factory/factory.hxx"
#include "../utility/debug.hxx"

void start(SFXTray *tray, Constant *pool, uint64_t* instruction) noexcept {
	
	//first create a factory
	Factory *factory = Factory::init(tray, pool, instruction);
	
	//let's create the main worker
	Worker *worker_main = Worker::init();
	Fibre *fibre_main = Fibre::init();
	
	//testing purpose
	fibre_main->registers[RegisterID::R1].u64 = 10;
	
	worker_main->addFibre(fibre_main);
	factory->spawnWorker(worker_main);;
	
	//start the execution
	worker_main->execute(factory);
	
	//free everything
	SFXTray::drop(tray);
	free(instruction);
	pool->drop();
	factory->drop();
	
}