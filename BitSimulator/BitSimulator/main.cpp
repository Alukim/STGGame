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
	sf::RenderWindow window(sf::VideoMode(1920, 1080, 32), "BitSimulator", sf::Style::Fullscreen);
	sf::Clock RenderClock;
	sf::Clock UpdateClock;
	sf::Event ev;
	sf::Font Font;

	Battery bat(&window, 200, 5000, "bat.png");
	/*sf::Texture *texture = new sf::Texture;
	if ((texture->loadFromFile("Resource\Texture\Menu.jpg")))
	{
		MessageBox(NULL, "Texture not found", "Error", NULL);
		return 0;
	}
	if (!Font.loadFromFile("Resource\Fonts\Comic\comic.ttf"))
	{
		MessageBox(NULL, "Font not found", "Error", NULL);
		return 0;
	}
	sf::Sprite Background_menu(*texture);
	AND2 a(&window, "Resource\Gates\And.png");*/
	
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
				bat.Load(20);
			}
			else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				bat.Dissipate(30);
			}
			//
			// updating object here
			//
		}
		// Drawing section
		if (RenderClock.getElapsedTime().asMilliseconds() > fps)
		{
			window.clear(sf::Color::Blue);
			bat.Draw();
			//window.draw(Background_menu);
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