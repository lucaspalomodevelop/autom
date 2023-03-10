all:
	mkdir -p bin
	g++ -c ./src/main.cpp
	g++ -c ./src/command.cpp
	g++ -std=c++11 main.o command.o -o ./bin/autom
	./bin/autom help