#pragma once
#include "Menu.h"
#include "SnakeBodyBlock.h"
class SnakeGame
{
private:
	sf::RenderWindow* window;
	sf::Font Mainfont;
	sf::Text PointsText;

	sf::Texture PiecesImage;
	sf::Sprite PointSprite;
	SnakeBodyBlock SnakeHead;

	std::vector <SnakeBodyBlock> SnakeBody;

	void CreatePieces();
	void CreateTexts();

public:

	SnakeGame(sf::Vector2f);
	~SnakeGame();
	bool Display();
	void SnakeMoving(sf::Event* event);
};

