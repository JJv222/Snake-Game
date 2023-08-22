#include "SnakeGame.h"
#include "SnakeBodyBlock.h"
SnakeGame::SnakeGame(sf::Vector2f WindowSize)
{
	window = new sf::RenderWindow(sf::VideoMode(WindowSize.x, WindowSize.y), "Chess the game");

	CreatePieces();
	CreateTexts();
}

SnakeGame::~SnakeGame()
{
	delete window;
}

void SnakeGame::CreatePieces() {
	
		//Points 
	PiecesImage.loadFromFile("Textures/snakeTexture.png");
	PointSprite.setTexture(PiecesImage);
	sf::IntRect subRect(0, 192, 64, 64); // Pieces former , each piece is 64x64,total 254x308
	PointSprite.setTextureRect(subRect);
	//Snake
	subRect.top = 0; subRect.left = 256;
	SnakeHead.setTexture(PiecesImage);
	SnakeHead.setTextureRect(subRect);
	SnakeHead.setPosition(200, 300);
	SnakeBody.push_back(SnakeHead);


}
void SnakeGame::CreateTexts() {
	Mainfont.loadFromFile("Textures/arial.ttf");
	PointsText.setFont(Mainfont);
	PointsText.setCharacterSize(24);
	PointsText.setFillColor(sf::Color::White);
	PointsText.setPosition(10, 10);
}
void SnakeGame::SnakeMoving(sf::Event* event) {
	if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Up) {
		//SnakeHead.move(0, -64); 
		SnakeHead.direction = 'w';
	}
	else if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Right) {
		//SnakeHead.move(64, 0); 
		SnakeHead.direction = 'd';
	}
	else if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Left) {
		//SnakeHead.move(-64, 0);
		SnakeHead.direction = 'a';
	}
	else if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Down) {
		//	SnakeHead.move(0, 64);
		SnakeHead.direction = 's';
	}

	//move snake body on the map

	for (SnakeBodyBlock i : SnakeBody) {
		if (i.direction == 'w') i.move(0, -64);
		else if (i.direction == 'a') i.move(-64, 0);
		else if (i.direction == 's') i.move(0, 64);
		else if (i.direction == 'd') i.move(64, 0);
	}
}
bool SnakeGame::Display()
{
	sf::RectangleShape rect(sf::Vector2f(1200, 900));
	rect.setFillColor(sf::Color::White);
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window->close();
				std::cout << "koniec gry ";
				return false;
			}
			//game logic and update
			SnakeMoving(&event);
		}

		//draw

		window->clear();
		window->draw(rect);
		window->draw(PointSprite);
		window->draw(SnakeHead);
		window->display();
	}
	return 0;
}