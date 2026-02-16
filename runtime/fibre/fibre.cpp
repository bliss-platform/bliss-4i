#include "fibre.hxx"

Fibre *Fibre::init() noexcept {
	return (Fibre*)calloc( 1, sizeof( Fibre ) );
}

void Fibre::drop() noexcept {
	free(this);
}