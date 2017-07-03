#include "Enemies.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Enemies::Enemies(sf::CircleShape avatar)
{
	enemy = avatar;
}

Enemies::Enemies()
{
}


Enemies::~Enemies()
{
}

bool Enemies::shoot(sf::Clock time)
{
	gameTime = time.getElapsedTime();

	cout << "Bullet Gap: " << bulletGap.asSeconds() << endl;
	cout << "Current Game Time : " << gameTime.asSeconds() << endl;
	cout << "Previous Shot Time: " << previousShot.asSeconds() << endl;

	if (previousShot + bulletGap <= gameTime /*gameTime - previousShot >= bulletGap*/)
	{
		cout << "Reached\n";
		previousShot = gameTime;

		cout << "New Previous Shot Time: " << previousShot.asSeconds() << endl;
		cout << "New Game Time: " << gameTime.asSeconds() << endl;

		return previousShot, true;
	}
	else
		return false;
}

void Enemies::draw(int windowX, int windowY, int place)
{
	enemy.setFillColor(sf::Color::Red);
	enemy.setPosition(windowX - 150, windowY * (0.1 + (place * 0.18)));
}

