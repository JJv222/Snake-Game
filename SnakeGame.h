#pragma once
#include "Menu.h"
#include "SnakeBodyBlock.h"
class SnakeGame
{
private:
	sf::RenderWindow* window;
	sf::Font Mainfont;
	sf::Text PointsText;
	char HeadLastDirection;

	sf::Texture PiecesImage;
	sf::Texture BorderImage;
	sf::Sprite BorderSprite; //745x594 px
	sf::Sprite PointSprite;
	sf::RectangleShape Background;
	sf::RectangleShape Ground;
	SnakeBodyBlock SnakeHead, SnakeMidle, SnakeTail;
	std::vector <SnakeBodyBlock*> SnakeBody, SnakeBodyBuffer;
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
	bool SnakeCollision();
};

