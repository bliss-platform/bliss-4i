#ifndef __VMINIT__
#define __VMINIT__

#include "../engine/state.hxx"
#include "../memory/constants.hxx"
#include <cstdint>

void start(SFXTray *tray, Constant *pool, uint64_t* instruction);

#endif