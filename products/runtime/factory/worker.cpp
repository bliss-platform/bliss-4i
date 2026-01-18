#include "worker.hxx"
#include "../engine/engine.hxx"
#include "../utility/os_thread.hxx"
#include "../utility/debug.hxx"

Worker *Worker::init() {
	
	//for now, we will do simple allocations only.
	//TODO: Impement this even better.
	return (Worker*)calloc(1, sizeof(Worker));
	
}

void Worker::addFibre(Worker *worker, Fibre *fibre) {
	
	if ( worker->fibres == nullptr ) {
	
		worker->fibres = CDLLWrapper<Fibre>::init(fibre);
	
	} else {
		
		CDLLWrapper<Fibre> *node = CDLLWrapper<Fibre>::init(fibre);
		//now it will be inserted between the existing node
		//and it's right node.
		
		node->next = worker->fibres->next;
		node->prev = worker->fibres;
		
		worker->fibres->next->prev = node;
		worker->fibres->next = node;
		
		//node added successfully
	}
	
}

void Worker::execute(Worker *worker, Factory *factory) {

	//create the state to start.
	RunnerState *workerState = RunnerState::init(
		factory,
		worker
	);
	
	worker->thread = createThread<RunnerState>(&run, workerState);

}