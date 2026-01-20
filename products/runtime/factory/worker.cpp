#include "worker.hxx"
#include "../engine/engine.hxx"
#include "../utility/os_thread.hxx"
#include "../utility/debug.hxx"
#include "message.hxx"
#include <cstdlib>
#include <pthread.h>

Worker *Worker::init() noexcept {
	
	//for now, we will do simple allocations only.
	//TODO: Impement this even better.
	Worker *worker = (Worker*)calloc(1, sizeof(Worker));
	worker->mailbox_tail = nullptr;
	worker->mailbox_head = nullptr;
	
	//memory will be provided by the factory, but for testing purposes we are using allocator
	//invocation for now.
	worker->memory = Memory::init();
	return worker;
	
}

void Worker::addFibre(Fibre *fibre) noexcept {
	
	if ( this->fibres == nullptr ) {
	
		this->fibres = CDLLWrapper<Fibre>::init(fibre);
	
	} else {
		
		CDLLWrapper<Fibre> *node = CDLLWrapper<Fibre>::init(fibre);
		//now it will be inserted between the existing node
		//and it's right node.
		
		node->next = this->fibres->next;
		node->prev = this->fibres;
		
		this->fibres->next->prev = node;
		this->fibres->next = node;
		
		//node added successfully
	}
	
}

void Worker::execute(Factory *factory) noexcept {

	//create the state to start.
	RunnerState *workerState = RunnerState::init(
		factory,
		this
	);
	
	Thread id;
	createThread<RunnerState>(&run, workerState, &id);
	pthread_join(id, NULL);

}

void Worker::drop() noexcept {
	free(this);
}

void Worker::putmsg(Message *msg, Factory* factory) noexcept {

	factory->lock();
	LLWrapper<Message> *node = LLWrapper<Message>::init(msg);
	
	if ( this->mailbox_tail != nullptr ) {
		this->mailbox_tail->next = node;
	}
	
	this->mailbox_tail = node;
	factory->lock();

}