#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Gates.h"
#include "Game.h"

int main(int argc, char **argv)
{

	const float fps = 1000 / 60;
	const float ups = 1000 / 100;
	sf::RenderWindow window(sf::VideoMode(1920, 1080, 32), "BitSimulator", sf::Style::Fullscreen);
	sf::Clock RenderClock;
	sf::Clock UpdateClock;
	sf::Event ev;
	sf::Font Font;
	Font.loadFromFile("comic.ttf");
	AND2 a(&window, "And.png");
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
			a.Draw();
			//
			// Drawing objects here
			//
			window.display();
			RenderClock.restart();
		}

		sf::sleep(sf::milliseconds(8));
	}
}