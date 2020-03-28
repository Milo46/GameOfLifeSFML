#include "Grid.h"

Grid::Grid(const sf::Vector2f& rectSize, const sf::Vector2f& gridSize, const sf::Color& linesColor)
{
	this->rectSize = rectSize;
	this->gridSize = gridSize;
	this->linesColor = linesColor;
}

Grid::~Grid()
{

}

void Grid::render(sf::RenderWindow* window)
{
	//Wyswietlanie siatki za pomoca linii

	for (int i = 0; i <= (this->gridSize.y / this->rectSize.y) + 1; i++)
	{
		sf::VertexArray line(sf::Lines, 2);
		line[0].position = sf::Vector2f(0, this->rectSize.y * i);
		line[1].position = sf::Vector2f(this->gridSize.x, this->rectSize.y * i);

		line[0].color = this->linesColor;
		line[1].color = this->linesColor;

		window->draw(line);
	}
	for (int i = 0; i <= (this->gridSize.x / this->rectSize.x) + 1; i++)
	{
		sf::VertexArray line(sf::Lines, 2);
		line[0].position = sf::Vector2f(this->rectSize.x * i, 0);
		line[1].position = sf::Vector2f(this->rectSize.x * i, this->gridSize.y);

		line[0].color = this->linesColor;
		line[1].color = this->linesColor;

		window->draw(line);
	}
}
