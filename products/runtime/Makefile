CXX = clang++-20

VMINIT = \
	vminit/vminit.cpp

MEMORY = \
	memory/constants.cpp
	
FACTORY = \
	factory/factory.cpp \
	factory/worker.cpp

SOURCES = main.cpp engine/engine.cpp fibre/fibre.cpp $(FACTORY) $(VMINIT) $(MEMORY)

# this part is AI generated, because it's debug build flags
DEBUG_FLAGS = -std=c++20 -stdlib=libc++

debug: $(SOURCES)
	@$(CXX) $(DEBUG_FLAGS) $(SOURCES) -DRTDBG -o debug
	@./debug

.PRECIOUS: debug
	
all: debug
	@./debug