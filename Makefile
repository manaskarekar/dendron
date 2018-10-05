#CXX=g++
#CXXFLAGS=-std=c++11 -Wall -Wpedantic -Wextra
#LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
#SOURCES=main.cpp
#TODO: Don't be lazy, finish the file.

dendron:
	g++ -std=c++11 -C src/main.cpp -o dendron -Os -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm dendron