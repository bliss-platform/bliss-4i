#ifndef WORKER_MESSAGE
#define WORKER_MESSAGE

#include <cstdint>
#include <span>

struct Message {
	std::span<uint8_t> bytes;
	uint32_t sender_id;
	
	static Message *init();
	static void *drop( Message *message );
};

#endif