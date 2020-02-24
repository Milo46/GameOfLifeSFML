 #include "Button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::Font* font, std::string text, ButtonColors buttonColors)
{
	//Ustawienie wszystkich zmiennych

	this->shape = sf::RectangleShape(size);
	this->shape.setPosition(pos);

	this->buttonState = BTN_IDLE;

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);

	//Uzylem dwa razy wiekszej czcionki, a potem zmniejszylem skale, aby uzyskac ostrzejszy tekst
	this->text.setCharacterSize(26);
	this->text.setScale(sf::Vector2f(0.5f, 0.5f));

	//Miej wiecej wysrodkowanie tekstu na przycisku
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->buttonColors = buttonColors;

	this->shape.setFillColor(this->buttonColors.idle);

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
	//Zmienia i centruje tekst
	this->text.setString(text);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);
}

void Button::update(const sf::Vector2f& mousePos, bool isMouseLeftClicked)
{
	//Aktualizuje stan przycisku

	//Domyslny stan przycisku
	this->buttonState = BTN_IDLE;

	//Jezeli myszka znajduje sie na przycisku
	if (this->shape.getGlobalBounds().contains(mousePos))
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
		this->shape.setFillColor(this->buttonColors.idle);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->buttonColors.hover);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->buttonColors.active);
		break;
	}
}

void Button::render(sf::RenderWindow* window)
{
	window->draw(this->shape);
	window->draw(this->text);
}
