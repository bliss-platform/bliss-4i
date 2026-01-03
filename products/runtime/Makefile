CXX = clang++-20
SOURCES = main.cpp engine/engine.cpp
FLAGS = -std=c++20 -stdlib=libc++

debug: $(SOURCES)
	@$(CXX) $(FLAGS) $(SOURCES) -DRTDBG -o debug
	@./debug

all: debug
	@./debug