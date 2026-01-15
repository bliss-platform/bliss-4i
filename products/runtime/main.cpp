#include "engine/engine.hxx"
#include "engine/opcode.hxx"
#include "engine/state.hxx"
#include "factory/factory.hxx"
#include "factory/worker.hxx"
#include "fibre/fibre.hxx"
#include "debug.hxx"
#include <cstdint>
#include <cstdlib>

void test(Fibre *f) {
	LOG("Hello World System Call\n");
}

void fibre1(Fibre *f) {
	LOG("Fibre @1\n");
}

void fibre2(Fibre *f) {
	LOG("Fibre @2\n");
}

int main() {
	
	Fibre *fib = Fibre::init();
	FibreNode *head = FibreNode::init(fib);
	
	//these are virtual registers
	fib->registers[RegisterID::R1].u64 = 5;
	fib->registers[RegisterID::R2].u64 = 0;
	
	SFXTray *tray = SFXTray::init();
	tray->functions = (void(**)(Fibre *f))malloc( sizeof( void(**)(Fibre *f) ) * 2 );
	tray->functions[0] = &fibre1;
	tray->functions[1] = &fibre2;
	tray->length+=2;
	
	RTState *state = (RTState *)calloc(1, sizeof(RTState));
	state->tray = tray;
	
	uint64_t instructions[] = {
		(uint64_t)OPCODES::launch << 48, 14, //0
		//fibre1
		(uint64_t)yield << 48, 0, //2
		(uint64_t)uxsub << 48, 1, //4
		(uint64_t)scall << 48, 0, //6
		(uint64_t)eq << 48, 0, //if the registers are equal or not 8
		(uint64_t)jifn << 48, 2, //10
		(uint64_t)exitf << 48, 0, //12
	
	 	//fibre2
		(uint64_t)uxadd << 48 | (uint64_t) RegisterID::R2 << 32, 6, //14
		(uint64_t)scall << 48, 1, //16
		(uint64_t)yield << 48, 0,
		(uint64_t)uxsub << 48 | (uint64_t) RegisterID::R2 << 32, 1,
		(uint64_t)eq << 48, 0,
		(uint64_t)jifn << 48, 16, 
		(uint64_t)exitf << 48, 0
	};
	
	Worker *worker = Worker::init();
	Worker::addFibre(worker, fib);
	
	RunnerState *app_state = RunnerState::init(
		Factory::init(tray, nullptr, instructions),
		worker
	);
	
	run(app_state);
	return 0;
	
}