#ifndef RUNTIME_UTILITY_OS_THREAD
#define RUNTIME_UTILITY_OS_THREAD
	
#include <cstdlib>

	#ifndef _WIN32
		#include <pthread.h>
		using Thread = pthread_t; //for linux
	#else
		#include <windows.h>
	#endif
	
	template<typename Arg>
	void createThread(void *(*start_routine)(void *), Arg *arg, Thread *id) {
		
		#ifndef _WIN32
			//linux platform
			pthread_create(id, NULL, start_routine, arg);
			
		#endif
			
	}
	
#endif