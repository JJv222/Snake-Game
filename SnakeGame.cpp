#include "SnakeGame.h"
#include "SnakeBodyBlock.h"
SnakeGame::SnakeGame(sf::Vector2f WindowSize)
{
	window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(WindowSize.x), static_cast<unsigned int>(WindowSize.y)), "Snake the game by JJ222");
	RefreshLimit = 60;
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
	PointSprite.setTextureRect(sf::IntRect (0, 192, 64, 64)); // Pieces former , each piece is 64x64,total 254x308 , 33x39 px thickness
	PointSprite.setPosition(300, 300);
	//Snake
	SnakeHead.setTexture(PiecesImage);
	SnakeHead.setTextureRect(sf::IntRect (256, 0, 64, 64));
	SnakeHead.setPosition(64, 64);
	SnakeHead.FirstMove = true;
	SnakeHead.directions.push_back('d');
	SnakeHead.nextdirections.push_back('d');
	SnakeBody.push_back(&SnakeHead);
	HeadLastDirection= 'd';

	//border
	Ground.setSize(sf::Vector2f(1200, 900)); //set background size
	sf::Color Groundcolor(240, 214, 171);
	Ground.setFillColor(Groundcolor);

	BorderImage.loadFromFile("Textures/borderFinal.png");
	BorderSprite.setTexture(BorderImage);
	//Inivisivle map barier
	Background.setSize(sf::Vector2f(813, 568));
	Background.move(30, 40);
}
void SnakeGame::CreateTexts() {
	Mainfont.loadFromFile("Textures/arial.ttf");
	PointsText.setFont(Mainfont);
	PointsText.setCharacterSize(24);
	PointsText.setFillColor(sf::Color::White);
	PointsText.setPosition(10, 10);
}
void SnakeGame::HeadChangeDirection(sf::Event* event) {
	if (event->type == sf::Event::KeyPressed) {
		switch (event->key.code)
		{
		case sf::Keyboard::Up: {
			if (HeadLastDirection != 's') {
				SnakeHead.nextdirections.pop_back();
				SnakeHead.nextdirections.push_back('w');
			}
			break; }
		case sf::Keyboard::Right: {
			if (HeadLastDirection != 'a') {
				SnakeHead.nextdirections.pop_back();
				SnakeHead.nextdirections.push_back('d');
			}
			break; }
		case sf::Keyboard::Left: {
			if (HeadLastDirection != 'd') {
				SnakeHead.nextdirections.pop_back();
				SnakeHead.nextdirections.push_back('a');
			}
			break; }
		case sf::Keyboard::Down: {
			if (HeadLastDirection != 'w') {
				SnakeHead.nextdirections.pop_back();
				SnakeHead.nextdirections.push_back('s');
			}
			break; }
		default:
			break;
		}
	}
}
void SnakeGame::SnakeDirectionChange() {
	for (unsigned int j = 1; j < SnakeBody.size(); j++) {
		if (!SnakeBody[j]->FirstMove) {
			int deltaX = abs(int(SnakeBody[j]->getPosition().x - SnakeBody[SnakeBody.size() - 2]->getPosition().x));
			int deltaY = abs(int(SnakeBody[j]->getPosition().y - SnakeBody[SnakeBody.size() - 2]->getPosition().y));
			if (deltaX == 64  || deltaY == 64) {
				SnakeBody[j]->FirstMove = true;
			}
		}
		if (SnakeBody[j]->RotationPoints.size() > 1 && SnakeBody[j]->RotationPoints[1] == SnakeBody[j]->getPosition() ) {

			SnakeBody[j]->directions[1] = SnakeBody[j]->nextdirections[1]; //change direction
			SnakeBody[j]->RotationPoints.erase(SnakeBody[j]->RotationPoints.begin() + 1); //delete first rotation point
			SnakeBody[j]->nextdirections.erase(SnakeBody[j]->nextdirections.begin()+1); //delete first next direction

			if ((j + 1) < SnakeBody.size()) {
				SnakeBody[j + 1]->nextdirections.push_back(SnakeBody[j]->directions[1]);
				SnakeBody[j + 1]->RotationPoints.push_back(SnakeBody[j]->getPosition());
			}
		}

	}
}
void SnakeGame::SnakeMoving() {
	
	sf::Vector2f LastPosition = SnakeBody[SnakeBody.size() - 1]->getPosition();
	//move snake body on the map
	int deltaX = abs(int(SnakeHead.getPosition().x)) % 64;
	int deltaY = abs(int(SnakeHead.getPosition().y)) % 64;
	if (deltaY == 0 && deltaX == 0) {
		if (SnakeBody.size() > 1) {
			if (SnakeHead.directions[1] != SnakeHead.nextdirections[1]) {
				//change direction of snake head
				SnakeBody[1]->nextdirections.push_back(SnakeHead.nextdirections[1]);
				SnakeBody[1]->RotationPoints.push_back(SnakeHead.getPosition());
				
			}
		}
		SnakeHead.directions[1] = SnakeHead.nextdirections[1];
	}
	HeadLastDirection = SnakeHead.directions[1];
	for (int i = 0; i < SnakeBody.size(); i++) {
		if (SnakeBody[i]->FirstMove) {
			if (SnakeBody[i]->directions[1] == 'w') SnakeBody[i]->move(0, -64);
			else if (SnakeBody[i]->directions[1] == 'a') SnakeBody[i]->move(-64, 0);
			else if (SnakeBody[i]->directions[1] == 's') SnakeBody[i]->move(0, 64);
			else if (SnakeBody[i]->directions[1] == 'd') SnakeBody[i]->move(64, 0);
		}
	}
	//eat point
	if (SnakeHead.getGlobalBounds().intersects(PointSprite.getGlobalBounds())) {
		SnakeBodyBlock* newBlock = new SnakeBodyBlock();
		newBlock->setTexture(PiecesImage);
		newBlock->setTextureRect(sf::IntRect(64, 0, 64, 64));
		newBlock->setPosition(LastPosition);

		newBlock->directions.push_back(SnakeBody[SnakeBody.size() - 1]->directions[1]);
		SnakeBody.push_back(newBlock);

		//Create new point on the map

		sf::FloatRect bounds(64.0f, 64.0f, 768.0f - 64.0f, 512.0f - 64.0f);// Define the bounds for the new point

		bool isPointOnSnake = false;
		do {
			isPointOnSnake = false;

			// Generate random multiples of 64 for x and y within the defined bounds
			float x = static_cast<float>((rand() % static_cast<int>(bounds.width / 64)) * 64) + bounds.left;
			float y = static_cast<float>((rand() % static_cast<int>(bounds.height / 64)) * 64) + bounds.top;

			PointSprite.setPosition(x, y);

			// Check if the point is on the snake or outside the game area
			for (auto i = SnakeBody.begin(); i != SnakeBody.end(); i++) {
				if (PointSprite.getGlobalBounds().intersects((*i)->getGlobalBounds())) {
					isPointOnSnake = true;
					break; // No need to continue checking
				}
			}
		} while (isPointOnSnake);

	}
}
void SnakeGame::SnakeTextureUpdate() {
	//update snake texture
	switch (SnakeHead.directions[1])
	{
	case 'w':
		SnakeHead.setTextureRect(sf::IntRect(192, 0, 64, 64));
		break;
	case 'a':
		SnakeHead.setTextureRect(sf::IntRect(192, 64, 64, 64));
		break;
	case 'd':
		SnakeHead.setTextureRect(sf::IntRect(256, 0, 64, 64));
		break;
	case 's':
		SnakeHead.setTextureRect(sf::IntRect(256, 64, 64, 64));
		break;
	default:
		break;
	}
	for (int j = 1; j < SnakeBody.size(); j++) {
		if (j <SnakeBody.size()-1 && SnakeBody[j]->RotationPoints.size() >1 && SnakeBody[j]->RotationPoints[1] == SnakeBody[j]->getPosition()) {
			if (SnakeBody[j]->nextdirections[1] == 'a' && SnakeBody[j]->directions[1] == 'w')SnakeBody[j]->setTextureRect(sf::IntRect(128, 0, 64, 64));
			if (SnakeBody[j]->nextdirections[1] == 'd' && SnakeBody[j]->directions[1] == 'w')SnakeBody[j]->setTextureRect(sf::IntRect(0, 0, 64, 64));

			if (SnakeBody[j]->nextdirections[1] == 'a' && SnakeBody[j]->directions[1] == 's')SnakeBody[j]->setTextureRect(sf::IntRect(128, 128, 64, 64));
			if (SnakeBody[j]->nextdirections[1] == 'd' && SnakeBody[j]->directions[1] == 's')SnakeBody[j]->setTextureRect(sf::IntRect(0, 64, 64, 64));

			if (SnakeBody[j]->nextdirections[1] == 'w' && SnakeBody[j]->directions[1] == 'a')SnakeBody[j]->setTextureRect(sf::IntRect(0, 64, 64, 64));
			if (SnakeBody[j]->nextdirections[1] == 's' && SnakeBody[j]->directions[1] == 'a')SnakeBody[j]->setTextureRect(sf::IntRect(0, 0, 64, 64));

			if (SnakeBody[j]->nextdirections[1] == 'w' && SnakeBody[j]->directions[1] == 'd')SnakeBody[j]->setTextureRect(sf::IntRect(128, 128, 64, 64));
			if (SnakeBody[j]->nextdirections[1] == 's' && SnakeBody[j]->directions[1] == 'd')SnakeBody[j]->setTextureRect(sf::IntRect(128, 0, 64, 64));
		}
		else if(j < SnakeBody.size() - 1){
			if (SnakeBody[j]->directions[1] == 'w' || SnakeBody[j]->directions[1] == 's')SnakeBody[j]->setTextureRect(sf::IntRect(128, 64, 64, 64));
			if (SnakeBody[j]->directions[1] == 'a' || SnakeBody[j]->directions[1] == 'd') SnakeBody[j]->setTextureRect(sf::IntRect(64, 0, 64, 64));
		}
		else{
			if (SnakeBody[j]->RotationPoints.size() > 1 && SnakeBody[j]->RotationPoints[1] == SnakeBody[j]->getPosition()) {
				if (SnakeBody[j]->nextdirections[1] == 'w')SnakeBody[j]->setTextureRect(sf::IntRect(192, 128, 64, 64));
				if (SnakeBody[j]->nextdirections[1] == 'a') SnakeBody[j]->setTextureRect(sf::IntRect(192, 192, 64, 64));
				if (SnakeBody[j]->nextdirections[1] == 's')SnakeBody[j]->setTextureRect(sf::IntRect(256, 192, 64, 64));
				if (SnakeBody[j]->nextdirections[1] == 'd') SnakeBody[j]->setTextureRect(sf::IntRect(256, 128, 64, 64));
			}
			else {
				if (SnakeBody[j]->directions[1] == 'w')SnakeBody[j]->setTextureRect(sf::IntRect(192, 128, 64, 64));
				if (SnakeBody[j]->directions[1] == 'a') SnakeBody[j]->setTextureRect(sf::IntRect(192, 192, 64, 64));
				if (SnakeBody[j]->directions[1] == 's')SnakeBody[j]->setTextureRect(sf::IntRect(256, 192, 64, 64));
				if (SnakeBody[j]->directions[1] == 'd') SnakeBody[j]->setTextureRect(sf::IntRect(256, 128, 64, 64));
			}
		}
	}
}
bool SnakeGame::SnakeCollision() {
	// Kolizje miêdzy segmentami wê¿a
	sf::FloatRect backgroundBounds = Background.getGlobalBounds();
	for (auto i : SnakeBody) {
		sf::FloatRect snakeBounds = i->getGlobalBounds();
		for (auto j : SnakeBody) {
			if (i != j && i->getGlobalBounds().intersects(j->getGlobalBounds())) {
				return true; // Kolizja miêdzy segmentami wê¿a
			}
		}
		if ((snakeBounds.left < backgroundBounds.left) || (snakeBounds.left + snakeBounds.width > backgroundBounds.left + backgroundBounds.width) || (snakeBounds.top < backgroundBounds.top) || (snakeBounds.top + snakeBounds.height > backgroundBounds.top + backgroundBounds.height)) {
			return true;  //Kolizje z bokami t³a (ramk¹)
		}
	}
	// Brak kolizji
	return false;
}

bool SnakeGame::Display()
{

	unsigned int timer = 0;
	while (window->isOpen())
	{
		sf::Event event;
		if (timer == 3500000) {
			if (SnakeCollision()) return false; //check collision
			SnakeMoving(); //move snake
			SnakeTextureUpdate(); //update snake texture
		}
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window->close();
				return false;
			}
			HeadChangeDirection(&event);//game logic and update

		}
		if (timer == 3500000) {
			SnakeDirectionChange();		//move snake 

			window->clear();		//draw
			window->draw(Ground);
			for (int i = 1; i < SnakeBody.size(); i++) {
				window->draw(*SnakeBody[i]);
			}
			window->draw(SnakeHead);
			window->draw(PointSprite);
			window->draw(BorderSprite);
			window->display();
		}
		if(timer==3500000)timer = 0;
		timer++;
	}
	return 0;
}