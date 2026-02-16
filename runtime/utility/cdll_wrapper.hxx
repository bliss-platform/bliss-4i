/*
 * Generic circular doubly linked list for useage in fibres, workers
 * and more.
 */

#ifndef RUNTIME_UTILITY_CDLLWRAPPER
#define RUNTIME_UTILITY_CDLLWRAPPER
#include <cstdlib>

template<typename T>
struct CDLLWrapper {
	
	CDLLWrapper<T> *next;
	T *node;
	CDLLWrapper<T> *prev;
	
	static CDLLWrapper<T> *init( T *node ) noexcept {
		CDLLWrapper<T> *wp = (CDLLWrapper<T> *)calloc(1, sizeof(CDLLWrapper<T>));
		wp->next = wp;
		wp->prev = wp;
		wp->node = node;
		
		return wp;
	}
	
	//WARNING: wp->node must be freed before.
	void drop() noexcept {
		//assuming the node is free.
		this->next = nullptr;
		this->prev = nullptr;
		free(this);
	}
	
};

#endif