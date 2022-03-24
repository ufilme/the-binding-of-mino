game: game.o library.o class.o
	g++ -o game game.o library.o class.o -lncurses

game.o: game.cpp library.h
	g++ -c game.cpp -lncurses

library.o: library.cpp library.h
	g++ -c library.cpp -lncurses

class.o: class.cpp class.h
	g++ -c class.cpp -lncurses

clean:
	rm *.o game