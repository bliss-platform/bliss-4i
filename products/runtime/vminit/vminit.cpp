#include "vminit.hxx"
#include "../factory/factory.hxx"
#include "../utility/debug.hxx"

void start(SFXTray *tray, Constant *pool, uint64_t* instruction) {
	
	//first create a factory
	Factory *main = Factory::init(tray, pool, instruction);
	
	//let's create the main worker
	Worker *worker_main = Worker::init();
	Fibre *fibre_main = Fibre::init();
	
	//testing purpose
	fibre_main->registers[RegisterID::R1].u64 = 5;
	
	Worker::addFibre(worker_main, fibre_main);
	Factory::spawnWorker(main, worker_main);
	
	//start the execution
	Worker::execute(worker_main, main);
	
}