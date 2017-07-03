#pragma once

#include "Player.h"

#include <iostream>
#include <SFML\Graphics.hpp>

class Bullet
{
public:
	bool bulletAlive, playerShot;
	int bulletWidth = 30;
	int bulletHeight = 10;

	sf::RectangleShape bullet;

	Bullet();
	Bullet(bool bulletAlive, bool playerShot);

	bool collision(sf::RectangleShape position, sf::CircleShape entity);
	sf::Vector2f bulletMove(sf::Vector2f position, float screen);
	void draw(sf::Vector2f position);
	void initialDraw(sf::CircleShape origin, bool playerShot);

	~Bullet();
};

