#include "Analytics.h"

Analytics::Analytics(int currLives, int maxLives, int score, int currShots, int hits, int enemyKills, float hitPer)
{
	playerLives = currLives;
	playerMaxLives = currLives;
	playerScore = score;
	playerShots = currShots;
	shotsHit = hits;
	enemiesKilled = enemyKills;
	hitPercentage = hitPer;
}

Analytics::Analytics(string playLives, string playMaxLives, string playScore, string bulletText, string bulletHits, string playKills, string hitPercent)
{
	lives = playLives;
	maximumLives = playMaxLives;
	currScore = playScore;
	bulletCount = bulletText;
	currHits = bulletHits;
	kills = playKills;
	percent = hitPercent;
}

Analytics::Analytics()
{
}


Analytics::~Analytics()
{
}

void Analytics::playerDeath()
{
	playerLives--;
}

int Analytics::getBulletCount()
{
	return playerShots;
}

void Analytics::addHitCount()
{
	shotsHit++;
}

void Analytics::addDeathCount()
{
	enemiesKilled++;
}

void Analytics::addBulletCount()
{
	playerShots++;
}

void Analytics::addPlayerScore()
{
	playerScore += 100;
}

void Analytics::checkShotPercent()
{
	hitPercentage = shotsHit / playerShots;
}

//void windowDraw(float width, float height)
//{
//	statWindow.setSize(sf::Vector2f(width * 0.8, height * 0.8));
//	statWindow.setFillColor(sf::Color::Blue);
//	statWindow.setOutlineThickness(5);
//	statWindow.setOutlineColor(sf::Color::Black);
//	statWindow.setPosition(width * 0.1, height * 0.1);
//}
