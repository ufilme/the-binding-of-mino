game: game.o library.o
	g++ -o game game.o library.o -lncurses

game.o: game.cpp library.h
	g++ -c game.cpp -lncurses

library.o: library.cpp library.h
	g++ -c library.cpp -lncurses

clean:
	rm *.o main