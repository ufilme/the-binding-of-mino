main: main.o GameManager.o
	g++ -o main main.o GameManager.o 

main.o: main.cpp GameManager.hpp
	g++ -Wall -c main.cpp

GameManager.o: Entity.hpp Map.hpp
	g++ -Wall -c GameManager.cpp -lncurses

Entity.o: Entity.cpp Entity.hpp
	g++ -Wall -c Entity.cpp
	
Map.o: Map.cpp Map.hpp
	g++ -Wall -c Map.cpp

Artifact.o: Artifact.cpp Artifact.hpp
	g++ -Wall -c Artifact.cpp

Enemy.o: Enemy.cpp Enemy.hpp
	g++ -Wall -c Enemy.cpp

clean:
	rm *.o game