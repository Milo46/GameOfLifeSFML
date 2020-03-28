//Game of Life - SFML
//Napisalem to, poniewaz zaciekawilem sie ta Gra w Zycie
//Moze na poczatku ta symulacja wydawala mi sie bezuzyteczna, ale sie przekonalem, ze moze byc uzyteczna :)
//Np. do wyznaczania liczb pierwszych

//Tylko dla Visual Studio, powoduje, ze konsola sie nie wyswietla
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "game.h"

#include "SFML/Graphics.hpp"

int main()
{
	//Stworzenie obiektu typu Game i zastartowanie gry
    Game game;
	game.run();

	return 0;
}
