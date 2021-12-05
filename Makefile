CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++20 -g -fstandalone-debug

exec: bin/exec
tests: bin/tests

bin/exec: ./src/main.cc ./src/command.cc
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o bin/exec $@


# obj/catch.o: tests/catch.hpp
#       $(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

# bin/tests: ./tests/tests.cc obj/catch.o obj/cs128string.o ./src/branched-linked-list.cc
#        $(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@


bin/tests: tests/tests.cc src/command.cc
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o bin/tests $@
.DEFAULT_GOAL := bin/exec
.PHONY: clean bin/exec #tests

clean:
	rm -fr bin/* obj/*
