CXX = clang++-20

UTILITY = \
	utility/os_thread.cpp

VMINIT = \
	vminit/vminit.cpp

MEMORY = \
	memory/constants.cpp
	
FACTORY = \
	factory/factory.cpp \
	factory/worker.cpp

SOURCES = main.cpp engine/engine.cpp fibre/fibre.cpp $(UTILITY) $(FACTORY) $(VMINIT) $(MEMORY)

# this part is AI generated, because it's debug build flags
DEBUG_FLAGS = -std=c++20 -stdlib=libc++

RELEASE_FLAGS = \
	-std=c++20 \
	-stdlib=libc++ \
	-O3 \
	-march=native \
	-fno-exceptions \
	-fno-rtti \
	-fvisibility=hidden \
	-flto

debug: $(SOURCES)
	@$(CXX) $(DEBUG_FLAGS) $(SOURCES) -DRTDBG -o debug
	@./debug

release: $(SOURCES)
	@$(CXX) $(RELEASE_FLAGS) $(SOURCES) -o release
	@./release

.PRECIOUS: debug release
	
all: debug
	@./debug