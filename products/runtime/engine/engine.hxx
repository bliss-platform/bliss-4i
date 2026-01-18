#ifndef WATERFALL_ENGINE
#define WATERFALL_ENGINE

#include "../factory/factory.hxx"
#include <cstdlib>

struct RunnerState {
	Factory *factory; //this is like the global data pointer here.
	Worker *worker;
	
	static RunnerState *init(Factory* factory, Worker *worker) {
		RunnerState *state = (RunnerState *)calloc(1, sizeof( RunnerState ));
		state->factory = factory;
		state->worker = worker;
		return state;
	}
};

void *run( void *args );

#endif