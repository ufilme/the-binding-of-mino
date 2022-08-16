# main: main.o GameManager.o
# 	g++ -o main main.o GameManager.o -lncurses

# main.o: main.cpp includes/GameManager.hpp
# 	g++ -Wall -c main.cpp -lncurses

# GameManager.o: includes/GameManager.cpp includes/GameManager.hpp includes/Window.hpp
# 	g++ -Wall -c includes/GameManager.cpp -lncurses

# Window.o: includes/Window.cpp includes/Window.hpp
# 	g++ -Wall -c includes/Window.cpp -lncurses

# clean:
# 	rm *.o main

OBJS	= main.o GameManager.o Window.o
SOURCE	= main.cpp includes/GameManager.cpp includes/Window.cpp
HEADER	= includes/GameManager.hpp includes/Window.hpp
OUT	= main
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) -lncurses

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -lncurses

GameManager.o: includes/GameManager.cpp
	$(CC) $(FLAGS) includes/GameManager.cpp -lncurses

Window.o: includes/Window.cpp
	$(CC) $(FLAGS) includes/Window.cpp -lncurses


clean:
	rm -f $(OBJS) $(OUT)