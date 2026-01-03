#include "engine/engine.hxx"
#include "engine/opcode.hxx"
#include "fibre/fibre.hxx"
#include <cstdint>

int main() {
	
	Fibre *fib = Fibre::init();
	FibreNode *head = FibreNode::init(fib);
	
	fib->registers[RegisterID::R1].f64 = -88.8675;
	fib->registers[RegisterID::R2].f64 = -88.8675;
	
	uint64_t instructions[] = {
		(uint64_t)eq << 48, 0,
		(uint64_t)inspect << 48, 0,
		(uint64_t)pend << 48, 0, 
	};
	
	run(head, instructions);
	return 0;
	
}