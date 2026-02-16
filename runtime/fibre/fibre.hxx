#ifndef RUNTIME_FIBRE
#define RUNTIME_FIBRE

#include <cstdint>
#include <cstdlib>

union Register {
	uint64_t u64;
	uint32_t u32;
	uint16_t u16;
	uint8_t u8;
	
	int64_t i64;
	int32_t i32;
	int16_t i16;
	int8_t i8;
	
	float f32;
	double f64;
};

enum RegisterID {
	R1,R2, ROUT, __COUNT__
};

enum FibreStatus {
	ACTIVE, WAITING
};

struct Fibre {
	
	Register registers[RegisterID::__COUNT__];
	uint64_t RPC;
	uint32_t id;
	uint8_t flag; //used by boolean operators.
	FibreStatus status;
	
	static Fibre *init() noexcept;
	void drop() noexcept;
	
};

#endif