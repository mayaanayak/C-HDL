CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++20 -g -fstandalone-debug

exec: bin/exec
tests: bin/tests

bin/exec: ./src/main.cc ./src/command.cc
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o $@

bin/tests: tests/tests.cc src/command.cc
	${CXX} ${CXXFLAGS} ${CXXEXTRAS} ${INCLUDES} $^ -o $@
	
.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
