#include "engine/opcode.hxx"
#include "engine/state.hxx"
#include "fibre/fibre.hxx"
#include "./utility/debug.hxx"
#include "memory/constants.hxx"
#include "vminit/vminit.hxx"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <sys/types.h>

void test(Fibre *f) {
	LOG("Hello World System Call\n");
}

void fibre1(Fibre *f) {
	LOG("Fibre @1 -- First Fibre\n");
}

void fibre2(Fibre *f) {
	LOG("Fibre @2 -- Second Fibre\n");
}

int main() {
	
	SFXTray *tray = SFXTray::init();
	tray->functions = (void(**)(Fibre *f))malloc( sizeof( void(**)(Fibre *f) ) * 2 );
	tray->functions[0] = &fibre1;
	tray->functions[1] = &fibre2;
	tray->length+=2;

	uint8_t *bytes = (uint8_t *)malloc(sizeof(uint8_t));
	Constant *ctx = Constant::init(bytes, 1);
	
	uint64_t* instructions = (uint64_t *)malloc(sizeof(uint64_t) * 28);
	int i = 0;
	
	// launch
	instructions[i++] = ((uint64_t)OPCODES::launch << 48);
	instructions[i++] = 14;
	
	// fibre 1
	instructions[i++] = ((uint64_t)yield  << 48);
	instructions[i++] = 0;
	
	instructions[i++] = ((uint64_t)uxsub  << 48);
	instructions[i++] = 1;
	
	instructions[i++] = ((uint64_t)scall  << 48);
	instructions[i++] = 0;
	
	instructions[i++] = ((uint64_t)eq     << 48);
	instructions[i++] = 0;
	
	instructions[i++] = ((uint64_t)jifn   << 48);
	instructions[i++] = 2;
	
	instructions[i++] = ((uint64_t)exitf  << 48);
	instructions[i++] = 0;
	
	
	// fibre 2
	instructions[i++] = ((uint64_t)uxadd  << 48) | ((uint64_t)RegisterID::R2 << 32);
	instructions[i++] = 6;
	
	instructions[i++] = ((uint64_t)scall  << 48);
	instructions[i++] = 1;
	
	instructions[i++] = ((uint64_t)yield  << 48);
	instructions[i++] = 0;
	
	instructions[i++] = ((uint64_t)uxsub  << 48) | ((uint64_t)RegisterID::R2 << 32);
	instructions[i++] = 1;
	
	instructions[i++] = ((uint64_t)eq     << 48);
	instructions[i++] = 0;
	
	instructions[i++] = ((uint64_t)jifn   << 48);
	instructions[i++] = 16;
	
	instructions[i++] = ((uint64_t)exitf  << 48);
	instructions[i++] = 0;

	start(tray, ctx, instructions);
	return 0;
	
}