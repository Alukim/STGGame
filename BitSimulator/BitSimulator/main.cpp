#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <Windows.h>
#include "Gates.h"
#include "Game.h"
#include "Utilities.h"
#include "GUI.h"
#include "Bonus.h"
#include "BitTrack.h"

int main(int argc, char **argv)
{
	const int fps = 1000 / 200;
	const int ups = 1000 / 100;

	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1200, 800, 32), "BitSimulator", sf::Style::Default);
	
	window->setVerticalSyncEnabled(true);

	sf::Clock RenderClock;
	sf::Clock UpdateClock;
	sf::Clock fpsCounter;
	fpsCounter.restart();
	int frames = 0;

	sf::Event ev;
	sf::Font Font;
	sf::Music Music;
	
	Tracklist map(window);

	map.AddElem(new Volt(window, txtpath + "gwiazda.png", 400), 0);
	map.AddElem(new AND2(window, txtpath + "Gates/And.png"), 3);
	if (!Music.openFromFile(mscpath + "Menu.ogg"))
	{
		MessageBox(NULL, "Music not found", "Error", NULL);
		return 0;
	}

	if (!Font.loadFromFile(fntpath + "comic.ttf"))
	{
		MessageBox(NULL, "Font not found", "Error", NULL);
		return 0;
	}

	Music.setVolume(50);
	Music.setLoop(true);
	Music.play();
	Music.stop();

	Points_class points(window, &Font);
	while (window->isOpen())
	{
		// Update section
		if (UpdateClock.getElapsedTime().asMilliseconds() > ups)
		{
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
			}
			
			map.Update();
			UpdateClock.restart();
		}

		// Events handler section
		while (window->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)				window->close();

			else if (ev.type == sf::Event::KeyPressed 
				&& ev.key.code == sf::Keyboard::Escape)		window->close();

			else if (ev.type == sf::Event::KeyPressed
				&& (ev.key.code == sf::Keyboard::Down
				||ev.key.code == sf::Keyboard::S))			map.BitDown();
			
			else if (ev.type == sf::Event::KeyPressed 
				&& (ev.key.code == sf::Keyboard::Up
				|| ev.key.code == sf::Keyboard::W))			map.BitUp();
		}

		// Drawing section
		if (RenderClock.getElapsedTime().asMilliseconds() > fps)
		{
			window->clear(sf::Color::Blue);
			//points.Draw();
			map.Draw();
			window->display();
			RenderClock.restart();

		}
		sf::sleep(sf::milliseconds(2));
	}
	return EXIT_SUCCESS;
}