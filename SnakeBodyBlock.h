#pragma once
#include "Menu.h"
struct  SnakeBodyBlock : public sf::Sprite
{
	char direction, nextdirection;
	bool rotation;
	bool FirstMove;
	sf::Vector2f RotationPoint;

	SnakeBodyBlock() {
		rotation = 0;
		direction = ' ';
		nextdirection = ' ';
		FirstMove = false;
	}
	void setDirection(char dir) {
		direction = dir;
	}
};

