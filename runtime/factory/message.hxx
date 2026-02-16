#ifndef RUNTIME_MESSAGE
#define RUNTIME_MESSAGE

#include <cstdint>
#include <span>

struct Message {
	std::span<uint8_t> bytes;
	uint32_t sender_id;
	
	static Message *init() noexcept;
	static void *drop( Message *message ) noexcept;
};

#endif