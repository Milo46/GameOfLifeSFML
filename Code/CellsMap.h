//Klasa mapy komorek

#ifndef CELLSMAP_H
#define CELLSMAP_H

#include "RandomGenerator.h"
#include "Button.h"
#include <fstream>

#include <iostream>

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

	float delay;
	float storagedDt;

public:
	//Rozmiar jednej komorki, ilosc komorek, szansa na pojawienie sie komorki w danym polu
	CellsMap(const sf::Vector2f& rectSize = sf::Vector2f(0, 0), const sf::Vector2f& cellsDataSize = sf::Vector2f(0, 0), const float& delay = 100.f, const int& lcsc = 20, const std::string& mapfile = "");
	virtual ~CellsMap();

	void loadFromFile(const std::string& filePath); //Funkcja ladujaca mape z pliku (obecnie nie uzywana)

	//lcsc = livingSellSpawningChance
	void generate(const int& lcsc = 20); //Funkcja generujaca poczatek symulacji
	void clear(); //Funkcja czyszczaca mape

	void update(const bool& isEvolving, const sf::Vector2i& mousePos, const bool& isMouseLeftClicked, const float& dt);
	void render(sf::RenderWindow* window);
};

#endif
