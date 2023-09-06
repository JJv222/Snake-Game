#pragma once
#include "Menu.h"
struct  SnakeBodyBlock : public sf::Sprite
{
	std::vector<char> directions;
	std::vector<char> nextdirections;
	bool FirstMove;
	std::vector <sf::Vector2f> RotationPoints;

	SnakeBodyBlock() {
		FirstMove = false;
		directions.push_back('k');
		nextdirections.push_back('k');
		RotationPoints.push_back(sf::Vector2f(-50, -50));

	}
	virtual ~SnakeBodyBlock() {
		directions.clear();
		nextdirections.clear();
		RotationPoints.clear();
	}
};

