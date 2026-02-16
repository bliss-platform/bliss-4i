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
	void createThread(void *(*start_routine)(void *), Arg *arg, Thread *id) noexcept {
		
		#ifndef _WIN32
			//linux platform
			pthread_create(id, NULL, start_routine, arg);
			
		#endif
			
	}
	
	void thread_lock(
		#ifndef _WIN32
			pthread_mutex_t *id
		#endif
	) noexcept;
	
	void thread_release(
		#ifndef _WIN32
			pthread_mutex_t *id
		#endif
	) noexcept;
	
#endif