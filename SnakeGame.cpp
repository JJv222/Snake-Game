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
	SnakeHead.directions.push_back('d');
	SnakeHead.nextdirections.push_back('d');
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
	if (event->type == sf::Event::KeyPressed) {
		switch (event->key.code)
		{
		case sf::Keyboard::Up: {
			SnakeHead.nextdirections.pop_back();
			SnakeHead.nextdirections.push_back('w');
			break; }
		case sf::Keyboard::Right: {
			SnakeHead.nextdirections.pop_back();
			SnakeHead.nextdirections.push_back('d');
			break; }
		case sf::Keyboard::Left: {
			SnakeHead.nextdirections.pop_back();
			SnakeHead.nextdirections.push_back('a');
			break; }
		case sf::Keyboard::Down: {
			SnakeHead.nextdirections.pop_back();
			SnakeHead.nextdirections.push_back('s');
			break; }
		default:
			break;
		}
	}
}
void SnakeGame::SnakeDirectionChange() {
	for (int j = 1; j < SnakeBody.size(); j++) {
		if (!SnakeBody[j]->FirstMove) {
			int deltaX = abs(int(SnakeBody[j]->getPosition().x - SnakeBody[SnakeBody.size() - 2]->getPosition().x));
			int deltaY = abs(int(SnakeBody[j]->getPosition().y - SnakeBody[SnakeBody.size() - 2]->getPosition().y));
			if (deltaX == 64  || deltaY == 64) {
				SnakeBody[j]->FirstMove = true;
			}
		}
	/*	if (j == 1) {
			if (SnakeBody[0]->nextdirections.front() != SnakeBody[0]->directions.front()) {
				SnakeBody[0]->directions.front() = SnakeBody[0]->nextdirections.front();

				SnakeBody[1]->nextdirections.push_back(SnakeBody[0]->directions.front());
				SnakeBody[1]->RotationPoints.push_back(SnakeBody[0]->getPosition());
			}
			
			
		} */
	//	std::cout <<"next dir: " << SnakeBody[1]->nextdirections.front() << " dir: " << SnakeBody[1]->directions.front() <<" pos : " << SnakeBody[1]->getPosition().x << "  " << SnakeBody[1]->getPosition().y << " Rotation:" << SnakeBody[1]->RotationPoints.front().x << "  " << SnakeBody[1]->RotationPoints.front().y << std::endl;
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
	for (int i = 0; i < SnakeBody.size(); i++) {
		if (i==0) {
			int deltaX = abs(int(SnakeHead.getPosition().x)) % 64;
			int deltaY = abs(int(SnakeHead.getPosition().y)) % 64;			
			if (deltaY == 0 && deltaX ==0) {
				if ( SnakeBody.size() > 1) {
					if ( SnakeHead.directions[1] != SnakeHead.nextdirections[1]) {
						SnakeBody[1]->nextdirections.push_back(SnakeHead.nextdirections[1]);
						SnakeBody[1]->RotationPoints.push_back(SnakeHead.getPosition());
					}
				}
				SnakeHead.directions[1] = SnakeHead.nextdirections[1];
			}
		}
		if (SnakeBody[i]->FirstMove) {
			if (SnakeBody[i]->directions[1] == 'w') SnakeBody[i]->move(0, -4);
			else if (SnakeBody[i]->directions[1] == 'a') SnakeBody[i]->move(-4, 0);
			else if (SnakeBody[i]->directions[1] == 's') SnakeBody[i]->move(0, 4);
			else if (SnakeBody[i]->directions[1] == 'd') SnakeBody[i]->move(4, 0);
		}
	}
	//eat point

	if (SnakeHead.getGlobalBounds().intersects(PointSprite.getGlobalBounds())) {
		std::cout << "POINT";
		SnakeBodyBlock* newBlock = new SnakeBodyBlock();
		newBlock->setTexture(PiecesImage);
		newBlock->setTextureRect(sf::IntRect(64, 0, 64, 64));
		newBlock->setPosition(LastPosition);

		newBlock->directions.push_back(SnakeBody[SnakeBody.size() - 1]->directions[1]);
		SnakeBody.push_back(newBlock);

	//Create new point on the map
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
		switch (i->directions[1])
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
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				window->close();
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