#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <Windows.h>
#include "Gates.h"
#include "Game.h"
#include "Utilities.h"
#include "GUI.h"
#include "Bonus.h"
int main(int argc, char **argv)
{
	const float fps = 1000 / 60;
	const float ups = 1000 / 100;
	sf::RenderWindow window(sf::VideoMode(1000, 800, 32), "BitSimulator", sf::Style::Default);
	sf::Clock RenderClock;
	sf::Clock UpdateClock;
	sf::Event ev;
	sf::Font Font;
	sf::Font Font2;
	sf::Music Music;
	Battery bat(&window, 200, 5000, "Resource/Textures/Baterry/bat.png");

	if (!Music.openFromFile("Resource/Music/Menu.ogg"))
	{
		MessageBox(NULL, "Music not found", "Error", NULL);
		return 0;
	}

	if (!Font.loadFromFile("Resource/Fonts/comic.ttf"))
	{
		MessageBox(NULL, "Font not found", "Error", NULL);
		return 0;
	}
	if (!Font2.loadFromFile("Resource/Fonts/comic.ttf"))
	{
		MessageBox(NULL, "Font2 not found", "Error", NULL);
		return 0;
	}
	Music.setVolume(50);
	Music.setLoop(true);
	Music.play();
	Music.stop();
	Volt bon(&window, &Font, 400);
	Points_class points(&window, &Font2, 700, 0);
	while (window.isOpen())
	{
		// iookoko
		// Events handler section
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::RAlt)
			{
				std::cout << "sunder" << std::endl;
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
				points.Update(10);
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
			bon.Draw();
			points.Draw();
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