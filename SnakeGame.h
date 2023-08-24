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
	SnakeBodyBlock SnakeHead, SnakeMidle, SnakeTail;
	std::vector <SnakeBodyBlock*> SnakeBody;
	unsigned short int RefreshLimit;

	void CreatePieces();
	void CreateTexts();

public:

	SnakeGame(sf::Vector2f WindowSize);
	~SnakeGame();
	bool Display();
	void HeadChangeDirection(sf::Event* event);
	void SnakeMoving();
	void SnakeDirectionChange();
	void SnakeTextureUpdate();
};

