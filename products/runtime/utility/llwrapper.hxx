/*
 * Generic linked list for useage in fibres, workers
 * and more.
 */

#ifndef RUNTIME_UTILITY_LLWRAPPER
#define RUNTIME_UTILITY_LLWRAPPER
#include <cstdlib>

template<typename T>
struct LLWrapper {
	
	LLWrapper<T> *next;
	T *node;
	
	static LLWrapper<T> *init( T *node ) {
		LLWrapper<T> *wp = (LLWrapper<T> *)calloc(1, sizeof(LLWrapper<T>));
		wp->next = wp;
		wp->node = node;
		
		return wp;
	}
	
	//WARNING: wp->node must be freed before.
	static void drop(LLWrapper<T> *wp) {
		//assuming the node is free.
		wp->next = nullptr;
		free(wp);
	}
	
};

#endif