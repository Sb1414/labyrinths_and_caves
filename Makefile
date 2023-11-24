CC=g++ -Wall -Werror -Wextra -std=c++17 -g
CHECKFLAGS=-lgtest -lgmock -pthread
GCOVFLAGS = -fprofile-arcs -ftest-coverage
GCOV=--coverage
OS = $(shell uname)

all: install

install:
	rm -rf build*
	mkdir build
	cd Maze && qmake && make && make clean && rm Makefile && cd ../ && mv Maze/maze.app build
	open build/maze.app

uninstall:
	rm -rf build*

test: clean
	$(CC) tests/tests.cpp Maze/matrix.cpp Maze/mazeSolver.cpp $(CHECKFLAGS) -o tests/tests
	./tests/tests
	rm -rf tests/tests

dvi:
	open Read_me.html

dist:
	rm -rf Archive_Maze/
	mkdir Archive_Maze/
	mkdir Archive_Maze/src
	cp -r ./build/Maze.app Archive_Maze/src/
	tar cvzf Archive_Maze.tgz Archive_Maze/
	rm -rf Archive_Maze/

check:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(shell find . -name "*.cpp" -or -name "*.cc" -or -name "*.h" -or -name "*.h")
	clang-format -n $(shell find . -name "*.cpp" -or -name "*.cc" -or -name "*.h" -or -name "*.h") --verbose -Werror
	rm .clang-format

clean:
	rm -f *.gcno *.gcda *.info *.out *.gch
	rm -rf ./gcov_rep.out.dSYM
	rm -rf ./report
	rm -rf ./*.o ./*.a
	rm -rf tests/tests
	rm -rf .clang-format
