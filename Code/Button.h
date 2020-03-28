//Klasa przycisku

#ifndef BUTTON_H
#define BUTTON_H

#include "Textbox.h"

//Stany przycisku
enum ButtonStates {
	BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE
};

//Struktura przechowujaca kolory dla danego stanu przycisku
struct ButtonColors
{
	sf::Color idle, hover, active;

	ButtonColors();

	ButtonColors(const sf::Color& idle, const sf::Color& hover, const sf::Color& active);
};

class Button : public Textbox
{
private:
	short unsigned buttonState; //Stan przycisku

	ButtonColors buttonColors;

public:
	Button(const sf::Vector2f& pos = sf::Vector2f(), const sf::Vector2f& size = sf::Vector2f(), sf::Font* font = NULL,
        const std::string& text = "", const ButtonColors& buttonColors = ButtonColors());
	virtual ~Button();

	bool isPressed(); //Zwraca prawde, jezeli zostal klikniety

	void changeText(const std::string& text);

	void update(const sf::Vector2f& mousePos, const bool& isMouseLeftClicked);
};

#endif
