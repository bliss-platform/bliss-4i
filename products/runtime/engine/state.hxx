#ifndef RUNTIME_STATE
#define RUNTIME_STATE

#include "../fibre/fibre.hxx"
#include <cstdlib>

struct SFXTray {
	void (**functions)(Fibre* fib);
	int length;
	
	static SFXTray *init() {
		return (SFXTray *)calloc(1, sizeof( SFXTray ));
	}
	
	static void drop(SFXTray* tray) {
		free(tray->functions);
		free( tray );
	}
};

#endif