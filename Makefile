CC=gcc -Wall -Werror -Wextra -std=c++17 -g
CHECKFLAGS=-lgtest -lgmock -pthread -lstdc++ -lm
GCOVFLAGS = -fprofile-arcs -ftest-coverage
GCOV=--coverage
OS = $(shell uname)

all: install

install:
	mkdir build
	cd Maze && qmake && make && make clean && rm Makefile && cd ../ && mv Maze/maze.app build
	open build/maze.app

uninstall:
	rm -rf build*

clean:
	rm -f *.gcno *.gcda *.info *.out *.gch
	rm -rf ./gcov_rep.out.dSYM
	rm -rf ./report
	rm -rf ./*.o ./*.a
	rm -rf test
	rm -rf .clang-format
