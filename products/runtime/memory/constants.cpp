#include "constants.hxx"
#include <cstdlib>

Constant *Constant::init(uint8_t *bytes, size_t size) noexcept {
	Constant *ct = (Constant *)calloc(1, sizeof(Constant));
	ct->bytes = bytes;
	ct->size = size;
	return ct;
}

void Constant::drop() noexcept {
	free(this->bytes);
	free(this);
}