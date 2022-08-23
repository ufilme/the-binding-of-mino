OBJS	= GameManager.o Window.o Entity.o main.o
SOURCE	= includes/GameManager.cpp includes/Window.cpp includes/Entity.cpp main.cpp
HEADER	= includes/GameManager.hpp includes/Window.hpp includes/Entity.hpp
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

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

clean:
	rm -f $(OBJS) $(OUT)