#ifndef FIBRE
#define FIBRE

#include <cstdint>
#include <cstdlib>

typedef union Register Register;
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
	R1,R2,ROUT
};

typedef struct Fibre Fibre;
struct Fibre {
	Register registers[3];
	uint64_t RPC;
	uint8_t flag; //used by boolean operators.
	
	static Fibre *init() {
		return (Fibre*)calloc( 1, sizeof( Fibre ) );
	}
	
	static void drop(Fibre* fibre) {
		free(fibre);
	}
};

typedef struct FibreNode FibreNode;
struct FibreNode {
	Fibre *root;
	Fibre *next;
	Fibre *prev;
	
	static FibreNode *init(Fibre *root) {
		FibreNode *list = (FibreNode*)calloc( 1, sizeof( FibreNode ) );
		list->root = root;
		return list;
	}
	
	static void drop(FibreNode *node) {
		free(node);
	}
};

#endif