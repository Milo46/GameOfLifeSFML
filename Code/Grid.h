//Klasa siatki, dajaca mozliwosc wyswietlenia siatki na danym obszarze

#ifndef GRID_H
#define GRID_H

#include "CellsMap.h"

class Grid
{
private:
	sf::Vector2f rectSize; //Rozmiar jednej komorki
	sf::Vector2f gridSize; //Rozmiar calej siatki

public:
	Grid(sf::Vector2f rectSize = sf::Vector2f(10, 10), sf::Vector2f gridSize = sf::Vector2f(0, 0));
	virtual ~Grid();

	void render(sf::RenderWindow* window, sf::Color linesColor);
};

#endif