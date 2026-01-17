#include "fibre.hxx"

Fibre *Fibre::init() {
	return (Fibre*)calloc( 1, sizeof( Fibre ) );
}

void Fibre::drop(Fibre* fibre) {
	free(fibre);
}