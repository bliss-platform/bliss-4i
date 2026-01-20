#ifndef RUNTIME_STATE
#define RUNTIME_STATE

#include "../fibre/fibre.hxx"
#include <cstdlib>

struct SFXTray {
	void (**functions)(Fibre* fib);
	int length;
	
	static SFXTray *init() noexcept {
		return (SFXTray *)calloc(1, sizeof( SFXTray ));
	}
	
	static void drop(SFXTray* tray) noexcept {
		free(tray->functions);
		free( tray );
	}
};

#endif