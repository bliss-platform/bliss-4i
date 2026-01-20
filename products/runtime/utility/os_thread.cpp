#include "os_thread.hxx"

void thread_lock(
	#ifndef _WIN32
	pthread_mutex_t *id
	#endif
) noexcept {
		
	#ifndef _WIN32
	pthread_mutex_lock(id);
	#endif
		
}

void thread_release(
	#ifndef _WIN32
	pthread_mutex_t *id
	#endif
) noexcept {
		
	#ifndef _WIN32
	pthread_mutex_unlock(id);
	#endif
		
}