#include <SFML/Graphics.hpp>
#include <cmath>


int main()
{
	const float fps = 1000 / 60;
	const float ups = 1000 / 100;
	sf::RenderWindow window(sf::VideoMode(1920,1080, 32), "BitSimulator");
	sf::Clock RenderClock;
	sf::Clock UpdateClock;
	sf::Event ev;
	while (window.isOpen())
	{
		// Events handler section
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();

			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			
		}
		

		// Update section
		if (UpdateClock.getElapsedTime().asMilliseconds() > ups)
		{
			//
			// updating object here
			//
		}
		// Drawing section
		if (RenderClock.getElapsedTime().asMilliseconds() > fps)
		{	
			window.clear();
			//
			// Drawing objects here
			//
			window.display();
			RenderClock.restart();
		}

	} 
	return 0;
}