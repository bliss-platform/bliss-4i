#include "worker.hxx"
#include <cstdlib>

Worker *Worker::init() {
	
	//for now, we will do simple allocations only.
	//TODO: Impement this even better.
	return (Worker*)calloc(1, sizeof(Worker));
	
}

void Worker::addFibre(Worker *worker, Fibre *fibre) {
	
	if ( worker->fibres == nullptr ) {
	
		worker->fibres = FibreNode::init(fibre);
	
	} else {
		
		FibreNode *node = FibreNode::init(fibre);
		//now it will be inserted between the existing node
		//and it's right node.
		
		node->next = worker->fibres->next;
		node->prev = worker->fibres;
		
		worker->fibres->next->prev = node;
		worker->fibres->next = node;
		
		//node added successfully
	}
	
}