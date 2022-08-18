OBJS	= main.o GameManager.o Window.o
SOURCE	= main.cpp includes/GameManager.cpp includes/Window.cpp
HEADER	= includes/GameManager.hpp includes/Window.hpp
OUT	= main
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lncurses

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

GameManager.o: includes/GameManager.cpp
	$(CC) $(FLAGS) includes/GameManager.cpp

Window.o: includes/Window.cpp
	$(CC) $(FLAGS) includes/Window.cpp

clean:
	rm -f $(OBJS) $(OUT)