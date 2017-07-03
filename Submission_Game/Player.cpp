#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::draw(float screenHeight)
{
	player.setRadius(50.0f);
	player.setFillColor(sf::Color::Blue);
	player.setPosition(10, (screenHeight / 2));
}