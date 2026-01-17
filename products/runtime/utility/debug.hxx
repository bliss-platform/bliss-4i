//RTDBG stands for runtime debug mode.
#ifdef RTDBG
	#include <cstdio>
	#define LOG(...) printf(__VA_ARGS__)
#else
	#define LOG(...)
#endif