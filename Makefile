.PHONY: all
all: labyrinth

.PHONY: labyrinth
labyrinth: main.o
	g++ -o labyrinth main.o -lSDL2
	./labyrinth

main.o: main.cpp
	g++ -c main.cpp
