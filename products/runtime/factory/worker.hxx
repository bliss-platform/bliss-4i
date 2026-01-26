#ifndef RUNTIME_WORKER
#define RUNTIME_WORKER

#include "../utility/cdll_wrapper.hxx"
#include "../utility/llwrapper.hxx"
#include "../fibre/fibre.hxx"
#include "../memory/allocator.hxx"
#include "message.hxx"
#include <cstdint>

//forward declaration
struct Factory;

struct Worker {
	
	uint32_t id; //a worker needs an ID to even work.
	CDLLWrapper<Fibre> *fibres;
	LLWrapper<Message> *mailbox_head;
	LLWrapper<Message> *mailbox_tail;
	Memory *memory;
	
	static Worker *init() noexcept;
	void terminate() noexcept;
	
	void addFibre(Fibre *fibre) noexcept;
	void drop() noexcept;
	void execute(Factory *factory) noexcept;
	void putmsg(Message *msg, Factory *factory) noexcept;
		
};

#endif