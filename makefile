all: clean 2048.o main.cpp agent.cpp
	g++ -std=c++11 -o a main.cpp 2048.o
2048.o:2048.cpp 2048.h
	g++ -std=c++11 -c 2048.cpp
clean:
	del -f a 2048.o 