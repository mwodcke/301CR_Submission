#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Bullet.h"
#include "Enemies.h"
#include "Analytics.h"

// Global variables for window size
#define WIDTH 1600
#define HEIGHT 900
#define BULLET_WIDTH 30
#define BULLET_HEIGHT 10

using namespace std;

int main()
{
	int deathCheck = 0;
	int enemyPlaces = 5;
	const float statWindowWidth = WIDTH * 0.8;
	const float statWindowHeight = HEIGHT * 0.8;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Clock Clock;

	// Font load settings
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	//////////////////////////////////////////////////////////////
	//															//
	// Text initialisation - Set to black for permanent text	//
	//															//
	//////////////////////////////////////////////////////////////

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setStyle(sf::Text::Bold);

	//////////////////////////////////////////////////////////////

	vector<Enemies*> EnemyList;	// List all current enemies
	EnemyList.resize(5);
	vector<Bullet*> BulletList; // List all current bullets

	// Array for enemy spawns on y-axis and if that spot is currently available
	float enemyPos[5][2] = {
			{ HEIGHT * 0.1, false },
			{ HEIGHT * 0.3, false },
			{ HEIGHT * 0.5, false },
			{ HEIGHT * 0.7, false },
			{ HEIGHT * 0.9, false }
	};

	//////////////////////////////////////////////////////////////
	//															//
	// Analytics initialisation									//
	//															//
	//////////////////////////////////////////////////////////////

	Analytics* statBox;
	Analytics stats(3, 3, 0, 0, 0, 0, 0.0f);
	Analytics statText("Current Lives: ", "Maximum Lives: ", "Score: ", "Bullets Shot : ", "Bullets Hit: ", "Enemies Killed: ", "Hit Percentage: ");

	//////////////////////////////////////////////////////////////
	//															//
	// Window Text Location Initialisation						//
	//															//
	//////////////////////////////////////////////////////////////

	float screenTextPos[3] = { 0.02, 0.2, 0.35 };

	float windowTextPos[4][2] = {
			{ 0.2, 0.2 },
			{ 0.2, 0.8 },
			{ 0.6, 0.2 },
			{ 0.6, 0.8 },
	};

	//////////////////////////////////////////////////////////////

	// Name of Window, FPS Cap = 60
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "301CR Game", sf::Style::Default);
	window.setFramerateLimit(60);

	//////////////////////////////////////////////////////////////
	//															//
	// Player character initialisation							//
	//															//
	//////////////////////////////////////////////////////////////

	Player* player = new Player();
	player->draw(HEIGHT);

	//////////////////////////////////////////////////////////////

	// Events whilst game is running
	while (window.isOpen())
	{
		//////////////////////////////////////////////////////////////
		//															//
		// Analytics Window Text Initialisation						//
		//															//
		//////////////////////////////////////////////////////////////

		// Screen Stats
		ostringstream scoreText, livesText, maxLivesText;
		scoreText << statText.currScore << stats.playerScore;
		livesText << statText.lives << stats.playerLives;
		maxLivesText << statText.maximumLives << stats.playerMaxLives;

		sf::Text score, currentLives, maximumLives;

		string screenStats[3] = { scoreText.str(), livesText.str(), maxLivesText.str() };
		sf::Text screenText[3] = { score, currentLives, maximumLives };

		// Stats Window Stats
		ostringstream bulletCountString, bulletHitString, enemiesKilledString, percentString;
		bulletCountString << statText.bulletCount << stats.playerShots;
		bulletHitString << statText.currHits << stats.shotsHit;
		enemiesKilledString << statText.kills << stats.enemiesKilled;
		percentString << statText.percent << stats.hitPercentage;

		sf::Text bulletCount, bulletHit, enemiesKilled, percent;

		string windowStats[4] = { bulletCountString.str(), bulletHitString.str(), enemiesKilledString.str(), percentString.str() };
		sf::Text windowText[4] = { bulletCount, bulletHit, enemiesKilled, percent };

		//////////////////////////////////////////////////////////////

		sf::Event event;
		while (window.pollEvent(event))
		{	
			switch (event.type)
			{
				// Closing Window
				case sf::Event::Closed:
					window.close();
					break;

				// Bullet Generation
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Space)
					{
						Bullet* bullets = new Bullet();
						bullets->initialDraw(player->player, true);
						window.draw(bullets->bullet);
						stats.addBulletCount();
						BulletList.push_back(bullets);
					}
					break;

				default:
					break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player->player.getPosition().y >= 90)
			player->player.move(0, -5); 

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player->player.getPosition().y <= (HEIGHT - 110))
			player->player.move(0, 5);

		window.clear(sf::Color::White);
		
		window.draw(player->player);

		//////////////////////////////////////////////////////////////
		//															//
		// Constant Stats (Score, Lives)							//
		//															//
		//////////////////////////////////////////////////////////////

		for (int i = 0; i < 3; i++)
		{
			screenText[i] = text;
			screenText[i].setString(screenStats[i]);
			screenText[i].setFillColor(sf::Color::Black);
			screenText[i].setPosition(WIDTH * screenTextPos[i], HEIGHT * 0.02);
			window.draw(screenText[i]);
		}

		//////////////////////////////////////////////////////////////
		//															//
		// Stat Text Setup - Makes text in window white not black	//
		//															//
		//////////////////////////////////////////////////////////////

		for (int x = 0; x < 4; x++)
		{
			windowText[x] = text;
			windowText[x].setString(windowStats[x]);
			windowText[x].setFillColor(sf::Color::White);
		}

		//////////////////////////////////////////////////////////////
		//															//
		// Initial Enemy Placement									//
		//															//
		// If spaces are available, spawn enemies					//
		//															//
		//////////////////////////////////////////////////////////////

		int sizeCheck = EnemyList.size();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			cout << "Vector size: " << sizeCheck << "\n";
			cout << "Death Counter: " << deathCheck << "\n";
		}
 
		//if (sizeCheck /*+ deathCheck)*/ < 6)
		//{
		//	cout << "Test Render \n";
		//}
		for (int i = 0; i < 5 - deathCheck ; i++)
		{
			sf::CircleShape enemyAvatar(50.0f);
			Enemies* enemy = new Enemies(enemyAvatar);
			EnemyList[i] = enemy;
			//enemy = EnemyList.at(i);
			enemy->draw(WIDTH, HEIGHT, i);
			window.draw(enemy->enemy);
		}

		for (int e = 0; e < 5 - deathCheck; e++)
		{
			bool shot = EnemyList.at(e)->shoot(Clock);

			if (shot == true)
			{
				cout << "Hit \n";
				Bullet* botBullets = new Bullet();
				botBullets->initialDraw(EnemyList.at(e)->enemy, false);
				window.draw(botBullets->bullet);
				BulletList.push_back(botBullets);
			}
		}

		//////////////////////////////////////////////////////////////
		//															//
		// Bullet Traversal											//
		//															//
		//////////////////////////////////////////////////////////////

		for (int a = 0; a < BulletList.size(); a++)
		{
			if (BulletList.at(a)->bulletAlive == true)
			{
				bool hit; // Determines if target is hit

				// If bullet could hit the player
				if (BulletList.at(a)->bullet.getPosition().x <= 60 && BulletList.at(a)->bullet.getPosition().x >= 10)
				{
					hit = BulletList.at(a)->collision(BulletList.at(a)->bullet, player->player);

					if (hit == true)
						if (stats.playerLives > 0)
							stats.playerLives--;
				}

				// If bullet could hit the enemies
				if (BulletList.at(a)->bullet.getPosition().x >= WIDTH - 160 && BulletList.at(a)->bullet.getPosition().x <= WIDTH - 100)
				{
					for (int j = 0; j < EnemyList.size(); j++)
					{
						hit = BulletList.at(a)->collision(BulletList.at(a)->bullet, EnemyList.at(j)->enemy);
						if (hit == true)
						{
							std::cout << "Removed Enemy " << j << std::endl;
							EnemyList.erase(EnemyList.begin() + j);
							BulletList.erase(BulletList.begin() + a);
							deathCheck++;
							stats.addPlayerScore();
							stats.addDeathCount();
							stats.addHitCount();
						}
					}
				}

				// Only draw the bullet's when true
				BulletList.at(a)->bulletMove(BulletList.at(a)->bullet.getPosition(), WIDTH);
				window.draw(BulletList.at(a)->bullet);
			}

			// Erase bullet from run time when false
			if (BulletList.at(a)->bulletAlive == false)
				BulletList.erase(BulletList.begin() + a);
		}

		//////////////////////////////////////////////////////////////
		//															//
		// Stat Window Generation									//
		//															//
		//////////////////////////////////////////////////////////////

		if (stats.playerShots > 0)
			stats.hitPercentage = (stats.shotsHit / stats.playerShots) * 100;
		else
			stats.hitPercentage = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		{
			//statBox->windowDraw(WIDTH, HEIGHT);
			sf::RectangleShape statWindow(sf::Vector2f(statWindowWidth, statWindowHeight));
			statWindow.setFillColor(sf::Color::Blue);
			statWindow.setOutlineThickness(5);
			statWindow.setOutlineColor(sf::Color::Black);
			statWindow.setPosition(WIDTH * 0.1, HEIGHT * 0.1);

			window.draw(statWindow);
			//window.draw(statBox->statWindow);
			
			for (int y = 0; y < 4; y++)
			{
				windowText[y].setPosition(statWindow.getPosition().x + (statWindowWidth * windowTextPos[y][0]), statWindow.getPosition().y + (statWindowHeight * windowTextPos[y][1]));
				window.draw(windowText[y]);
			}
		}
			
		window.display();
	}

	return 0;
};