#include "Bullet.h"

Bullet::Bullet(bool exist, bool shot)
{
	bulletAlive = exist;
	playerShot = shot;
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

bool Bullet::collision(sf::RectangleShape pos, sf::CircleShape entity)
{
	// If the width of the bullet at or past the left side of the enemy || at or before the right side of the enemy
	if (pos.getPosition().x + pos.getSize().x >= entity.getPosition().x && pos.getPosition().x <= entity.getPosition().x + entity.getRadius())
	{
		// And the height is at or below top side of enemy || at of above bottom side of enemy
		if (pos.getPosition().y + pos.getSize().y >= entity.getPosition().y && pos.getPosition().y <= entity.getPosition().y + entity.getRadius())
			std::cout << "Collision Detected" << std::endl;
			return true;
	}

	//return false;
}

//////////////////////////////////////////////////////////////////////////////////
//																				//
// Bullet Movement																//
//																				//
// If the bullet has been shot by the player and is still on screen, move right //
// If bullet is shot by enemy, move left										//
// If bullet goes off screen, destroy it										//
//																				//
//////////////////////////////////////////////////////////////////////////////////

sf::Vector2f Bullet::bulletMove(sf::Vector2f pos, float screenWidth)
{	
	if (pos.x < screenWidth && pos.x > -50)
	{
		if (playerShot == true)
			bullet.setPosition(pos.x + 5, pos.y);
		else
			bullet.setPosition(pos.x - 5, pos.y);
		//std::cout << "New X Pos: " << pos.x << std::endl;

		return pos;
	}
}
void Bullet::draw(sf::Vector2f pos)
{
	bullet.setPosition(pos.x, pos.y);
}

void Bullet::initialDraw(sf::CircleShape origin, bool player)
{
	bullet.setSize(sf::Vector2f(bulletWidth, bulletHeight));
	bullet.setFillColor(sf::Color::Black);

	bulletAlive = true;

	if (player == true)
	{
		playerShot = true;
		bullet.setPosition(origin.getPosition().x + (origin.getRadius() * 2) + 5, origin.getPosition().y + origin.getRadius() - (bulletHeight / 2));
	}
	else
	{
		playerShot = false;
		bullet.setPosition(origin.getPosition().x - ((origin.getRadius() * 2)), origin.getPosition().y + origin.getRadius() - (bulletHeight / 2));
	}
}