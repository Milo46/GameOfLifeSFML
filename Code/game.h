//Klasa gry, odowiadajaca za cala aplikacje

#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include <iostream>
#include <map>

class Game
{
private:
	const sf::Color BackGroundColor; //Stala przechowujaca kolor tla w rgb

	bool isRunning; //True - aplikacja dziala, false - aplikacja zatrzymana / wylaczona
	bool isEvolving; //True - trzeba generowac kolejne generacje komorek, false - nie trzeba

	sf::RenderWindow* window; //Wskaznik na sfml'we okno
	sf::Event sfEventHandler; //Handler sfml'wych event'ow

	sf::Font font; //Czcionka

	sf::Clock dtClock; //Zegar potrzebny do pilnowania odstepow pomiedzy klatkami
	float delay; //Minimalna roznica (milisekundy) pomiedzy klatkami

	//Podzielilem okno aplikacji na dwie sekcje
	sf::RectangleShape renderRectangle; //Sekcja wyswietlania komorek
	sf::RectangleShape optionsRectangle; //Sekcja wyswietlania menu

	sf::Vector2i mousePos; //Zmienna potrzebna do przechowywania pozycji myszki w oknie
	std::map<std::string, Button> buttons; //Mapa przyciskow
	bool isMouseLeftClicked; //True - lewy przycisk myszy zostal kilkniety, false - nie zostal klikniety

	Grid grid; //Siatka
	CellsMap cellsmap; //Zmienna 'CellsMap' przechowujaca wszystkie niezbedne informacje na temat symulacji

	void frameDelay(); //Funkcja pilnujaca odstep pomiedzyklatkami
	void update(); //Funkcja aktualizujaca wszystkie procesy
	void updateSfEvents(); //Funkcja aktualizujaca i przechwytujaca sfml'we wydarzenia
	void render(); //Funkcja wyswietlajaca wszystkie obiekty w oknie

public:
	Game();
	virtual ~Game();

	void run(); //Funkcja startujaca aplikacje
};

#endif