#include "CellsMap.h"

void CellsMap::generate(int livingCellSpawningChance)
{
	//Jezeli lcsc == 0
	if (livingCellSpawningChance == 0)
	{
		this->clear();
	}
	else
	{
		for (int i = 0; i < this->size.y; i++)
		{
			for (int j = 0; j < this->size.x; j++)
			{
				this->cellsData[i][j] = randint(1, 100) <= livingCellSpawningChance ? Living : Dead;
			}
		}
	}
}

CellsMap::CellsMap(sf::Vector2f rectSize, sf::Vector2f cellsDataSize, int lcsc)
{
	//Ustawienie ilosci komorek (x, y)
	this->size = cellsDataSize;

	//Stworzenie dwu wymiarowej tablicy na wskaznikach
	this->cellsData = new CellType*[this->size.y];
	for (int i = 0; i < this->size.y; i++)
	{
		this->cellsData[i] = new CellType[this->size.x];
	}

	//Wygenerowanie mapy
	this->generate(lcsc);

	//Ustawienie wzorca
	this->rect = sf::RectangleShape(rectSize);
	this->rect.setFillColor(sf::Color::Yellow);
}

CellsMap::~CellsMap()
{

}

void CellsMap::loadFromFile(const std::string& filePath)
{
	std::fstream file(filePath, std::ios_base::in);

	for (int i = 0; i < this->size.y; i++)
	{
		for (int j = 0; j < this->size.x; j++)
		{
			int temp;
			file >> temp;

			this->cellsData[i][j] = temp == 0 ? Dead : Living;
		}
	}

	file.close();
}

void CellsMap::clear()
{
	//Ustawienie wszystkich komorek na martwe
	for (int i = 0; i < this->size.y; i++)
	{
		for (int j = 0; j < this->size.x; j++)
		{
			this->cellsData[i][j] = Dead;
		}
	}
}

void CellsMap::update(bool isEvolving, const sf::Vector2i& mousePos, bool isMouseLeftClicked)
{
	//Jezeli trzeba wygenerowac kolejne pokolenie
	if (isEvolving == true)
	{
		//Generowanie nastepnego pokolenia do tymczasowej tablicy oraz przepisanie jej
		CellType** _temp;
		_temp = new CellType * [this->size.y];
		for (int i = 0; i < this->size.y; i++)
		{
			_temp[i] = new CellType[this->size.x];
			for (int j = 0; j < this->size.x; j++)
			{
				int result = 0;
				if (i > 0)
				{
					if (this->cellsData[i - 1][j] == Living) result++;
					if (j > 0 && this->cellsData[i - 1][j - 1] == Living) result++;
					if (j < this->size.x - 1 && this->cellsData[i - 1][j + 1] == Living) result++;
				}
				if (j > 0 && this->cellsData[i][j - 1] == Living) result++;
				if (j < this->size.x - 1 && this->cellsData[i][j + 1] == Living) result++;
				if (i < this->size.y - 1)
				{
					if (j > 0 && this->cellsData[i + 1][j - 1] == Living) result++;
					if (this->cellsData[i + 1][j] == Living) result++;
					if (j < this->size.x - 1 && this->cellsData[i + 1][j + 1] == Living) result++;
				}

				_temp[i][j] = this->cellsData[i][j];

				//Standart 23/3
				if (this->cellsData[i][j] == Living && !(result == 2 || result == 3))
					_temp[i][j] = Dead;
				if (this->cellsData[i][j] == Dead && (result == 3))
					_temp[i][j] = Living;
			}
		}

		for (int i = 0; i < this->size.y; i++)
		{
			for (int j = 0; j < this->size.x; j++)
			{
				this->cellsData[i][j] = _temp[i][j];
			}
		}
	}
	//Jezeli lewy przycisk myszy zostal wcisniety oraz nie trwa generowanie kolejnych pokolen
	if (isMouseLeftClicked == true && isEvolving == false)
	{
		//Ustal ktora komorka zostala wcisnieta i zamien jej stan na przeciwny
		//Mozna w ten sposob myszka wprowadzac wlasne struktury
		for (int i = 0; i < this->size.y; i++)
		{
			for (int j = 0; j < this->size.x; j++)
			{
				if (mousePos.x >= this->rect.getSize().x * j && mousePos.x < this->rect.getSize().x * (j + 1) &&
					mousePos.y >= this->rect.getSize().y * i && mousePos.y < this->rect.getSize().y * (i + 1))
				{
					if (this->cellsData[i][j] == Living) this->cellsData[i][j] = Dead;
					else this->cellsData[i][j] = Living;
				}
			}
		}
	}
}

void CellsMap::render(sf::RenderWindow* window)
{
	//Wyswietlenie komorek
	for (int i = 0; i < this->size.y; i++)
	{
		for (int j = 0; j < this->size.x; j++)
		{
			if (this->cellsData[i][j] == Living)
			{
				this->rect.setPosition(sf::Vector2f(j * this->rect.getSize().x, i * this->rect.getSize().y));
				window->draw(this->rect);
			}
		}
	}
}