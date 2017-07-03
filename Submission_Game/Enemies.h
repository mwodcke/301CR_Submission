#pragma once

#include "Bullet.h"
#include "Analytics.h"

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Window.hpp>

class Enemies
{
public:
	sf::Time bulletGap = sf::seconds(3.0f);
	sf::Time gameTime;
	sf::Time previousShot;

	sf::Vector2f position;
	sf::CircleShape enemy;

	Enemies(sf::CircleShape playerAvatar);
	Enemies();

	bool shoot(sf::Clock clock);
	void draw(int windowX, int windowY, int place);

	~Enemies();
};

