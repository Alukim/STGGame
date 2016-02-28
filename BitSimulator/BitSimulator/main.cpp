#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <Windows.h>
#include "Gates.h"
#include "Game.h"
#include "Utilities.h"
#include "GUI.h";

int main(int argc, char **argv)
{
	const float fps = 1000 / 60;
	const float ups = 1000 / 100;
	sf::RenderWindow window(sf::VideoMode(1000, 800, 32), "BitSimulator", sf::Style::Default);
	sf::Clock RenderClock;
	sf::Clock UpdateClock;
	sf::Event ev;
	sf::Font Font;

	Battery bat(&window, 200, 5000, "bat.png");
	
	if (!Font.loadFromFile("comic.ttf"))
	{
		MessageBox(NULL, "Font not found", "Error", NULL);
		return 0;
	}
	
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

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				bat.Load(50);
			}
			else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				bat.Dissipate(50);
			}
			//
			// updating object here
			//
		}



		// Drawing section
		if (RenderClock.getElapsedTime().asMilliseconds() > fps)
		{
			window.clear();
			bat.Draw();
			//
			// Drawing objects here
			//
			window.display();
			RenderClock.restart();
		}

		sf::sleep(sf::milliseconds(8));
	}
	return EXIT_SUCCESS;
}