#include "engine/opcode.hxx"
#include "engine/state.hxx"
#include "fibre/fibre.hxx"
#include "./utility/debug.hxx"
#include "vminit/vminit.hxx"
#include <cstddef>
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
	
	SFXTray *tray = SFXTray::init();
	tray->functions = (void(**)(Fibre *f))malloc( sizeof( void(**)(Fibre *f) ) * 2 );
	tray->functions[0] = &fibre1;
	tray->functions[1] = &fibre2;
	tray->length+=2;
	
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

	start(tray, NULL, instructions);
	
	return 0;
	
}