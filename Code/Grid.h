//Klasa siatki, dajaca mozliwosc wyswietlenia siatki na danym obszarze

#ifndef GRID_H
#define GRID_H

#include "CellsMap.h"

class Grid
{
private:
	sf::Vector2f rectSize; //Rozmiar jednej komorki
	sf::Vector2f gridSize; //Rozmiar calej siatki
	sf::Color linesColor;

public:
	Grid(const sf::Vector2f& rectSize = sf::Vector2f(10, 10), const sf::Vector2f& gridSize = sf::Vector2f(0, 0), const sf::Color& linesColor = sf::Color::Black);
	virtual ~Grid();

	void render(sf::RenderWindow* window);
};

#endif
