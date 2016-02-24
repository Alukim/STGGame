#include <SFML/Graphics.hpp>
#include "Gates.h"

int main(int argc, char **argv)
{
	XOR2 hehe;
	hehe.SetCustomInput(0, 1);
	hehe.SetCustomInput(1, 1);
	hehe.Propagate();
	const float fps = 1000 / 60;
	const float ups = 1000 / 100;
	sf::RenderWindow window(sf::VideoMode(1920,1080, 32), "BitSimulator", sf::Style::Default);
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
	return EXIT_SUCCESS;
}