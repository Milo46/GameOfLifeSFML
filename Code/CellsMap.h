//Klasa mapy komorek

#ifndef CELLSMAP_H
#define CELLSMAP_H

#include "RandomGenerator.h"
#include "Button.h"
#include <fstream>

//Typ wyliczeniowy pozwalajacy zidentyfikowac stan komorki
enum CellType {
	Dead = 0, Living = 1
};

class CellsMap
{
private:
	CellType** cellsData; //Wskaznik na wskazniki, uzylem tego jako dwuwymiarowej tablicy
	sf::Vector2f size; //Ilosc komorek w dwoch y (x, y)

	sf::RectangleShape rect; //Wzorcowy kwadrat, ktory bedzie wyswietlany dla kazdej zywej komorki

	//lcsc = livingSellSpawningChance
	void generate(int lcsc); //Funkcja generujaca poczatek symulacji

public:
	//Rozmiar jednej komorki, ilosc komorek, szansa na pojawienie sie komorki w danym polu
	CellsMap(sf::Vector2f rectSize = sf::Vector2f(0, 0), sf::Vector2f cellsDataSize = sf::Vector2f(0, 0), int lcsc = 50);
	virtual ~CellsMap();

	void loadFromFile(const std::string& filePath); //Funkcja ladujaca mape z pliku (obecnie nie uzywana)

	void clear(); //Funkcja czyszczaca mape

	void update(bool isEvolving, const sf::Vector2i& mousePos, bool isMouseLeftClicked);
	void render(sf::RenderWindow* window);
};

#endif