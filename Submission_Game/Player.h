#pragma once

#include <SFML\/Graphics.hpp>

class Player
{
public:
	sf::CircleShape player;

	Player();

	void draw(float screen);

	~Player();
};

