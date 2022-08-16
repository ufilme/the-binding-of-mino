main: main.o GameManager.o
	g++ -o main main.o GameManager.o -lncurses

main.o: main.cpp includes/GameManager.hpp
	g++ -Wall -c main.cpp -lncurses

GameManager.o: includes/GameManager.cpp includes/Entity.hpp includes/Map.hpp
	g++ -Wall -c includes/GameManager.cpp -lncurses

Entity.o: includes/Entity.cpp includes/Entity.hpp
	g++ -Wall -c includes/Entity.cpp -lncurses
	
Map.o: includes/Map.cpp includes/Map.hpp
	g++ -Wall -c includes/Map.cpp -lncurses

Artifact.o: includes/Artifact.cpp includes/Artifact.hpp
	g++ -Wall -c includes/Artifact.cpp -lncurses

Enemy.o: includes/Enemy.cpp includes/Enemy.hpp
	g++ -Wall -c includes/Enemy.cpp -lncurses

clean:
	rm *.o main