#include "SnakeGame.h"
#include "SnakeBodyBlock.h"
SnakeGame::SnakeGame(sf::Vector2f WindowSize)
{
	window = new sf::RenderWindow(sf::VideoMode(WindowSize.x, WindowSize.y), "Snake the game by JJ222");
	RefreshLimit = 200;
	CreatePieces();
	CreateTexts();
}

SnakeGame::~SnakeGame()
{
	delete window;
	SnakeBody.clear();
	for (SnakeBodyBlock* i : SnakeBody) {
		delete i;
	}
}

void SnakeGame::CreatePieces() {
	
		//Points 
	PiecesImage.loadFromFile("Textures/snakeTexture.png");
	PointSprite.setTexture(PiecesImage);
	PointSprite.setTextureRect(sf::IntRect (0, 192, 64, 64)); // Pieces former , each piece is 64x64,total 254x308
	PointSprite.setPosition(300, 300);
	//Snake
	SnakeHead.setTexture(PiecesImage);
	SnakeHead.setTextureRect(sf::IntRect (256, 0, 64, 64));
	SnakeHead.setPosition(0, 0);
	SnakeHead.FirstMove = true;
	SnakeBody.push_back(&SnakeHead);



}
void SnakeGame::CreateTexts() {
	Mainfont.loadFromFile("Textures/arial.ttf");
	PointsText.setFont(Mainfont);
	PointsText.setCharacterSize(24);
	PointsText.setFillColor(sf::Color::White);
	PointsText.setPosition(10, 10);
}
void SnakeGame::HeadChangeDirection(sf::Event* event) {
	if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Up) {
		SnakeHead.direction = 'w';
	}
	else if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Right) {
		SnakeHead.direction = 'd';
	}
	else if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Left) {
		SnakeHead.direction = 'a';
	}
	else if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Down) {
		SnakeHead.direction = 's';
	}

}
void SnakeGame::SnakeDirectionChange() {
	for (int j = 1; j <= SnakeBody.size() - 1; j++) {
		if (!SnakeBody[j]->FirstMove) {
			int deltaX = abs(int(SnakeBody[j]->getPosition().x - SnakeBody[SnakeBody.size() - 2]->getPosition().x));
			int deltaY = abs(int(SnakeBody[j]->getPosition().y - SnakeBody[SnakeBody.size() - 2]->getPosition().y));
			std::cout << deltaX << " " << deltaY << std::endl;
			if (deltaX == 64  || deltaY == 64) {
				SnakeBody[j]->FirstMove = true;
				std::cout << " wtf " ;
			}
		}
		if (j == 1) {

			if (SnakeBody[0]->nextdirection != SnakeBody[0]->direction) {
				SnakeBody[0]->nextdirection = SnakeBody[0]->direction;

				SnakeBody[1]->nextdirection = SnakeBody[0]->direction;
				SnakeBody[1]->RotationPoint = SnakeBody[0]->getPosition();
			}
		}
		if ( SnakeBody[j]->RotationPoint == SnakeBody[j]->getPosition()) {
			SnakeBody[j]->direction= SnakeBody[j]->nextdirection; 
			if ((j + 1) <= (SnakeBody.size() - 1)) {
				SnakeBody[j + 1]->nextdirection = SnakeBody[j]->direction;
				SnakeBody[j + 1]->RotationPoint = SnakeBody[j]->getPosition();
			}
		}
	}
}
void SnakeGame::SnakeMoving() {
	sf::Vector2f LastPosition = SnakeBody[SnakeBody.size() - 1]->getPosition();
	//move snake body on the map
	for (SnakeBodyBlock* i : SnakeBody) {
		if (i->FirstMove) {
			if (i->direction == 'w') i->move(0, -4);
			else if (i->direction == 'a') i->move(-4, 0);
			else if (i->direction == 's') i->move(0, 4);
			else if (i->direction == 'd') i->move(4, 0);
		}
	}
	//eat point

	if (SnakeHead.getGlobalBounds().intersects(PointSprite.getGlobalBounds())) {
		SnakeBodyBlock* newBlock = new SnakeBodyBlock();
		newBlock->setTexture(PiecesImage);
		newBlock->setTextureRect(sf::IntRect(64, 0, 64, 64));
		newBlock->setPosition(LastPosition);
		newBlock->direction = SnakeBody[SnakeBody.size() - 1]->direction;
		newBlock->nextdirection = SnakeBody[SnakeBody.size() - 1]->direction;
		newBlock->RotationPoint = LastPosition;
		SnakeBody.push_back(newBlock);

		bool isPointOnSnake = false;
		PointSprite.setPosition(rand() % 1000, rand() % 800);
		while (isPointOnSnake) {
			for (auto i = SnakeBody.begin(); i != SnakeBody.end(); i++) {
				if (PointSprite.getGlobalBounds().intersects((*i)->getGlobalBounds())) {
					PointSprite.setPosition(rand() % 1000, rand() % 800);
				}
			}
		}
	}
}
void SnakeGame::SnakeTextureUpdate() {
	//update snake texture
	for (SnakeBodyBlock* i : SnakeBody) {
		switch (i->direction)
		{
		case 'w':
			i->setTextureRect(sf::IntRect(192, 0, 64, 64));
			break;
		case 'a':
			i->setTextureRect(sf::IntRect(192, 64, 64, 64));
			break;
		case 'd':
			i->setTextureRect(sf::IntRect(256, 0, 64, 64));
			break;
		case 's':
			i->setTextureRect(sf::IntRect(256, 64, 64, 64));
			break;
		default:
			break;
		}
	}
}

bool SnakeGame::Display()
{
	sf::RectangleShape rect(sf::Vector2f(1200, 900)); //set background size
	rect.setFillColor(sf::Color::White); //set background color
	while (window->isOpen())
	{
		sf::Event event;
		SnakeMoving(); //move snake
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window->close();
				std::cout << "koniec gry ";
				return false;
			}
			HeadChangeDirection(&event);//game logic and update

		}
		SnakeTextureUpdate();		//update snake texture
		SnakeDirectionChange();		//move snake 

		window->clear();		//draw
		window->draw(rect);
		for (int i = 0; i < SnakeBody.size(); i++){
			window->draw(*SnakeBody[i]);
		}
		window->draw(PointSprite);
		window->display();

		sf::sleep(sf::milliseconds(20)); //set game speed
	}
	return 0;
}