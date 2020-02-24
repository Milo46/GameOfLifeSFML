#include "game.h"

void Game::frameDelay()
{
	sf::Time time = this->dtClock.getElapsedTime(); // Pobranie czasu z timer'a
	while (time.asMilliseconds() <= this->delay) { //Sprawdzenie pobranego czasu w milisekundach
		time = this->dtClock.getElapsedTime(); //Jezeli = false, to przytrzymaj program do momentu uzyskania lub przekroczenia 'this->delay'
	}
	this->dtClock.restart(); //Restart timer'a
}

void Game::update()
{
	//Sfml'owe wydarzenia
	this->updateSfEvents();

	//Ustawienie obecnej pozycji myszki w oknie
	this->mousePos = sf::Mouse::getPosition(*this->window);

	//Zaktualizowanie mapy komorek
	this->cellsmap.update(this->isEvolving, mousePos, this->isMouseLeftClicked);

	//Zaktualizowanie przyciskow
	this->buttons["btnStopResume"].update(this->window->mapPixelToCoords(this->mousePos), this->isMouseLeftClicked);
	this->buttons["btnGenerate"].update(this->window->mapPixelToCoords(this->mousePos), this->isMouseLeftClicked);
	this->buttons["btnClear"].update(this->window->mapPixelToCoords(this->mousePos), this->isMouseLeftClicked);
	this->buttons["btnExit"].update(this->window->mapPixelToCoords(this->mousePos), this->isMouseLeftClicked);

	//Jezeli przycisk od zatrzymywania i wznawiania generowanie kolejnych generacji zostanie wcisniety
	if (this->buttons["btnStopResume"].isPressed())
	{
		//Jezeli teraz jest w trakcie generowania
		if (this->isEvolving == true)
		{
			//Zatrzymaj generowanie i zmien tekst przycisku
			this->buttons["btnStopResume"].changeText("Resume");
			this->isEvolving = false;
		}
		else //W innym wypadku
		{
			//Zrob to samo co w 35 lini, ale na odwrot
			this->buttons["btnStopResume"].changeText("Pause");
			this->isEvolving = true;
		}
	}

	//Jezeli przycisk od generowania nowego poczatku symulacji zostanie wcisniety
	if (this->buttons["btnGenerate"].isPressed())
	{
		//Wygeneruj nowa mape komorek oraz automatycznie zatrzymaj generowanie generacji
		this->cellsmap = CellsMap(sf::Vector2f(10.f, 10.f), sf::Vector2f(this->renderRectangle.getSize().x / 10.f, this->renderRectangle.getSize().y / 10.f), 20);
		this->buttons["btnStopResume"].changeText("Resume");
		this->isEvolving = false;
	}

	//Jezeli przycisk od czyszczenia mapy komorek zostanie wcisniety
	if (this->buttons["btnClear"].isPressed())
	{
		//Wyczysc mape komorek i zatrzymaj generowanie generacji
		this->cellsmap.clear();
		this->buttons["btnStopResume"].changeText("Resume");
		this->isEvolving = false;
	}

	//Jezeli przycisk od wychodzenia zostanie wcisniety
	if (this->buttons["btnExit"].isPressed())
	{
		//To wyjdz z aplikacji
		this->isRunning = false;
	}
}

void Game::updateSfEvents()
{
	//Ustawienie domyslnej wartosci
	this->isMouseLeftClicked = false;

	//Sprawdzenie wystepowania sfml'wych wydarzen
	while (this->window->pollEvent(this->sfEventHandler))
	{
		//Jezeli okno zostanie zamkniete
		if (this->sfEventHandler.type == sf::Event::Closed)
		{
			//Zakoncz dzialanie aplikacji
			this->isRunning = false;
		}

		//Jezeli przycisk myszy zostanie wcisniety
		if (this->sfEventHandler.type == sf::Event::MouseButtonPressed)
		{
			//Jezeli to byl lewy przycisk
			if (this->sfEventHandler.mouseButton.button == sf::Mouse::Left)
			{
				this->isMouseLeftClicked = true;
			}
		}
	}
}

void Game::render()
{
	this->window->clear(this->BackGroundColor); //Czyszczenie okna

	this->cellsmap.render(this->window); //Wyswietlenie komorek
	this->grid.render(this->window, sf::Color::Black); //Wyswietlenie siatki
	this->window->draw(this->optionsRectangle); //Wyswietlenie strefy menu

	//Narysowanie wszystkich przyciskow
	this->buttons["btnStopResume"].render(this->window);
	this->buttons["btnGenerate"].render(this->window);
	this->buttons["btnClear"].render(this->window);
	this->buttons["btnExit"].render(this->window);

	this->window->display(); //Wyswietlenie okna
}

//Troche tego wyszlo w konstruktorze
Game::Game()
	:BackGroundColor(sf::Color(61.f, 61.f, 59.f))
{
	this->isRunning = false;
	this->isEvolving = false;

	//Stworzenie i ustawienie sfml'wego okna
	this->window = new sf::RenderWindow(sf::VideoMode(960, 720), "Game of Life", sf::Style::Titlebar | sf::Style::Close);
	this->window->setKeyRepeatEnabled(false); //Blokowanie powtarzanego wejscia (klawisza, przycisku)
	//Potrzebne do sprawdzania pojedynczego wcisniecia

	//Ustawienie ikonki okna
	sf::Image icon;
	icon.loadFromFile("Glider.png");
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	//Zaladowanie czcionki
	this->font.loadFromFile("OpenSans-Bold.ttf");

	//Ustawienie sekcji wyswietlania komorek
	this->renderRectangle = sf::RectangleShape(sf::Vector2f(720.f, 720.f));
	this->renderRectangle.setPosition(sf::Vector2f(0.f, 0.f));

	//Ustawienie sekcji wyswietlania menu
	this->optionsRectangle = sf::RectangleShape(sf::Vector2f(240.f, 720.f));
	this->optionsRectangle.setPosition(sf::Vector2f(this->renderRectangle.getSize().x, 0.f));
	this->optionsRectangle.setFillColor(sf::Color(20.f, 20.f, 20.f));

	//Ustawienie pozycji, nie wiem czy jest to potrzebne, bo za doslownie chwile jest on aktualizowany w 'update()'
	this->mousePos = sf::Mouse::getPosition(*this->window);

	//Ustawienie struktury z kolorami przyciskow - Button.h 11 linijka
	ButtonColors bc_temp{sf::Color(40.f, 40.f, 40.f), sf::Color(100.f, 100.f, 100.f), sf::Color(160.f, 160.f, 160.f)};

	//Ustawienie wszystkich przysickow
	this->buttons["btnStopResume"] = Button(this->optionsRectangle.getPosition() + sf::Vector2f(20.f, 20.f), sf::Vector2f(200.f, 40.f), &this->font, "Resume", bc_temp);
	this->buttons["btnGenerate"] = Button(this->optionsRectangle.getPosition() + sf::Vector2f(20.f, 80.f), sf::Vector2f(200.f, 40.f), &this->font, "Generate", bc_temp);
	this->buttons["btnClear"] = Button(this->optionsRectangle.getPosition() + sf::Vector2f(20.f, 140.f), sf::Vector2f(200.f, 40.f), &this->font, "Clear", bc_temp);
	this->buttons["btnExit"] = Button(this->optionsRectangle.getPosition() + sf::Vector2f(20.f, 660.f), sf::Vector2f(200.f, 40.f), &this->font, "Exit", bc_temp);
	
	this->isMouseLeftClicked = false;

	//Ustawienie siatki
	this->grid = Grid(sf::Vector2f(10.f, 10.f), this->renderRectangle.getSize());
	
	//Ustawienie klasy komorek
	this->cellsmap = CellsMap(sf::Vector2f(10.f, 10.f), sf::Vector2f(this->renderRectangle.getSize().x / 10, this->renderRectangle.getSize().y / 10), 0);

	//Ustawienie minimalnego odstepu miedzy klatkami
	this->delay = 100.f;
}

Game::~Game()
{

}

void Game::run()
{
	this->isRunning = true; //Start aplikacji
	
	while (this->isRunning) //Wykonuj dopoki aplikacja dziala
	{
		this->update();
		this->render();
		this->frameDelay();
	}
	this->window->close(); //Zamknij okno
}