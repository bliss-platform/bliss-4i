#ifndef __OS_THREAD__
#define __OS_THREAD__
	
	#ifndef _WIN32
		#include <pthread.h>
		using Thread = pthread_t; //for linux
	#else
		#include <windows.h>
	#endif
	
	template<typename Arg>
	Thread createThread(void *(*start_routine)(void *), Arg *arg) {
			
		Thread id;
			
		#ifndef _WIN32
			//linux platform
			pthread_create(&id, NULL, start_routine, arg);
			return id;
			
		#endif
			
	}
	
#endif