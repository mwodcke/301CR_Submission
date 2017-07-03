#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;

class Analytics
{
public:

	//////////////////////////////////////////////////////////////
	//															//
	// Store info on:											//
	//															//
	// Strings:													//
	//															//
	// Current Bullet Counter									//
	//															//
	// Ints:													//
	//															//
	// Current Player Lives										//
	// Max Player Lives											//
	// Shots player has made this game							//
	// How many shots have hit the enemies						//
	// Player's score for this game								//
	// # of enemies player has killed							//
	//															//
	// Floats:													//
	//															//
	// The percentage rate of hits player makes					//
	//															//
	//////////////////////////////////////////////////////////////

	sf::RectangleShape statWindow;

	string lives, maximumLives, currScore, bulletCount, currHits, kills, percent;

	int playerLives, playerMaxLives, playerScore, playerShots, shotsHit, enemiesKilled;
	float hitPercentage;

	Analytics(int currLives, int maxLives, int score, int currShots, int hits, int enemyKills, float hitPer);
	Analytics(string lives, string maximumLives, string currScore, string bulletText, string currHts, string kills, string percent);
	Analytics();

	void playerDeath();
	int getBulletCount();
	void addHitCount();
	void addDeathCount();
	void addBulletCount();
	void addPlayerScore();
	void checkShotPercent();
	void windowDraw(float width, float height);

	~Analytics();
};

