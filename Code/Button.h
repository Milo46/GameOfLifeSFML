//Klasa przycisku

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

//Stany przycisku
enum ButtonStates {
	BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE
};

//Struktura przechowujaca kolory dla danego stanu przycisku
struct ButtonColors
{
	sf::Color idle, hover, active;

	ButtonColors()
	{
		this->idle = sf::Color();
		this->hover = sf::Color();
		this->active = sf::Color();
	}

	ButtonColors(sf::Color idle, sf::Color hover, sf::Color active)
	{
		this->idle = idle;
		this->hover = hover;
		this->active = active;
	}
};

class Button
{
private:
	short unsigned buttonState; //Stan przycisku

	sf::RectangleShape shape; //Ksztalt
	sf::Font* font; //Wskaznik na czcionke
	sf::Text text; //Tekst

	ButtonColors buttonColors;

public:
	Button(sf::Vector2f pos = sf::Vector2f(), sf::Vector2f size = sf::Vector2f(), sf::Font* font = NULL, std::string text = "", ButtonColors buttonColors = ButtonColors());
	virtual ~Button();

	bool isPressed(); //Zwraca prawde, jezeli zostal klikniety

	void changeText(const std::string& text); //Funkcja zmieniajaca tekst

	void update(const sf::Vector2f& mousePos, bool isMouseLeftClicked);
	void render(sf::RenderWindow* window);
};

#endif