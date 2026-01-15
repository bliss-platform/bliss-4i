#include "factory.hxx"
#include <cstdlib>
Factory *Factory::init( SFXTray *tray, Constant* pool, uint64_t* instruction ) {
	
	Factory *factory = (Factory*)calloc(1, sizeof(Factory));
	factory->constantPool = pool;
	factory->instructions = instruction;
	factory->tray = tray;
	
	return factory;
	
}