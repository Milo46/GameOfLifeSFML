#include "Button.h"

ButtonColors::ButtonColors()
{
    this->idle = sf::Color();
    this->hover = sf::Color();
    this->active = sf::Color();
}

ButtonColors::ButtonColors(const sf::Color& idle, const sf::Color& hover, const sf::Color& active)
{
    this->idle = idle;
    this->hover = hover;
    this->active = active;
}

Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size, sf::Font* font, const std::string& text, const ButtonColors& buttonColors)
    :Textbox(pos, size, font, text, buttonColors.idle)
{
	this->buttonState = BTN_IDLE;

	this->buttonColors = buttonColors;
}

Button::~Button()
{

}

bool Button::isPressed()
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}

void Button::changeText(const std::string& text)
{
    this->setText(text);
}

void Button::update(const sf::Vector2f& mousePos, const bool& isMouseLeftClicked)
{
	//Aktualizuje stan przycisku

	//Domyslny stan przycisku
	this->buttonState = BTN_IDLE;

	//Jezeli myszka znajduje sie na przycisku
	if (this->getShape().getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Jezeli zostal wcisniety
		if (isMouseLeftClicked == true)
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	//Zmiana kolor w zaleznosci od stanu
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->setFillColor(this->buttonColors.idle);
		break;

	case BTN_HOVER:
		this->setFillColor(this->buttonColors.hover);
		break;

	case BTN_ACTIVE:
		this->setFillColor(this->buttonColors.active);
		break;
	}
}
