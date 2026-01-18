#include "worker.hxx"
#include "../engine/engine.hxx"
#include "../utility/os_thread.hxx"
#include "../utility/debug.hxx"
#include "message.hxx"
#include <cstdlib>
#include <pthread.h>

Worker *Worker::init() {
	
	//for now, we will do simple allocations only.
	//TODO: Impement this even better.
	Worker *worker = (Worker*)calloc(1, sizeof(Worker));
	worker->mailbox_tail = nullptr;
	worker->mailbox_head = nullptr;
	return worker;
	
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
	
	Thread id;
	createThread<RunnerState>(&run, workerState, &id);
	pthread_join(id, NULL);

}

void Worker::drop(Worker *worker) {
	free(worker);
}

void Worker::putmsg(Message *msg, Factory* factory, Worker *worker) {

	pthread_mutex_lock(&factory->mutex);
	LLWrapper<Message> *node = LLWrapper<Message>::init(msg);
	
	if ( worker->mailbox_tail != nullptr ) {
		worker->mailbox_tail->next = node;
	}
	
	worker->mailbox_tail = node;
	pthread_mutex_unlock(&factory->mutex);

}