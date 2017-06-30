#include <SFML/Graphics.hpp>

// Global variables for window size
#define WIDTH 1600
#define HEIGHT 900

int main()
{
	// Name of Window at top, frame rate locked to max of 60
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "301CR Game", sf::Style::Default);
	window.setFramerateLimit(60);

	// Define player character and position
	sf::CircleShape shape(50.f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(10, (HEIGHT / 2));

	// While the window is open, draw the circle to the screen
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{	
			switch (event.type)
			{
				// Closing Window
				case sf::Event::Closed:
					window.close();
					break;

				// Key Pressed
				case sf::Event::KeyPressed:
					// Used to shoot at enemies
					if (event.key.code == sf::Keyboard::Space)
					{

					}
					break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && shape.getPosition().y >= 10)
			shape.move(0, -5); 

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && shape.getPosition().y <= (HEIGHT - 110))
			shape.move(0, 5);

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
};