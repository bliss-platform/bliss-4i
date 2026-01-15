#include "fibre.hxx"

Fibre *Fibre::init() {
	return (Fibre*)calloc( 1, sizeof( Fibre ) );
}

void Fibre::drop(Fibre* fibre) {
	free(fibre);
}

FibreNode *FibreNode::init(Fibre *root) {
	FibreNode *list = (FibreNode*)calloc( 1, sizeof( FibreNode ) );
	list->node = root;
	list->next = list;
	list->prev = list;
	
	root->status = FibreStatus::ACTIVE;
	
	return list;
}

void FibreNode::drop(FibreNode *node) {
	free(node);
}