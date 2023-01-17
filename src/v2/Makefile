OBJS	= GameManager.o Window.o Entity.o Room.o DynamicArray.o main.o
SOURCE	= includes/GameManager.cpp includes/Window.cpp includes/Entity.cpp includes/Room.cpp includes/DynamicArray.cpp main.cpp
HEADER	= includes/GameManager.hpp includes/Window.hpp includes/Entity.hpp includes/Room.hpp includes/DynamicArray.hpp
OUT		= main
CC	 	= g++
FLAGS	= -g -c -Wall -std=c++17
LFLAGS	= -lncurses

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

GameManager.o: includes/GameManager.cpp
	$(CC) $(FLAGS) includes/GameManager.cpp

Window.o: includes/Window.cpp
	$(CC) $(FLAGS) includes/Window.cpp

Entity.o: includes/Entity.cpp
	$(CC) $(FLAGS) includes/Entity.cpp

Room.o: includes/Room.cpp
	$(CC) $(FLAGS) includes/Room.cpp

DynamicArray.o: includes/DynamicArray.cpp
	$(CC) $(FLAGS) includes/DynamicArray.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

clean:
	rm -f $(OBJS) $(OUT)