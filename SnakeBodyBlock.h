#pragma once
#include "Menu.h"
struct  SnakeBodyBlock : public sf::Sprite
{
	short int rotation;
	char direction;

	SnakeBodyBlock() {
		rotation = 0;
		direction = ' ';
	}
	void Rotate() {
		if (direction == 'w') {
			this->setRotation(0);
		}
		else if (direction == 'a') {
			this->setRotation(90);
		}
		else if (direction == 's') {
			this->setRotation(270);
		}
		else if (direction == 'd') {
			this->setRotation(300);
		}
	}
};

