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
	
	sf::Clock RenderClock;
	sf::Clock UpdateClock;
	sf::Clock fpsCounter;
	fpsCounter.restart();
	int frames = 0;

	sf::Event ev;
	sf::Font Font;
	sf::Music Music;
	
	GameObject *bit = new GameObject(window, textpath + "bit.png", sf::Color(255, 0, 255));
	Volt bon(window, textpath + "gwiazda.png", 400);

	AND2 martha(window, textpath + "Gates/And.png");
	Tracklist map(window, bit);

	map.AddElem(&bon, 0);

	if (!Music.openFromFile(musicpath + "Menu.ogg"))
	{
		MessageBox(NULL, "Music not found", "Error", NULL);
		return 0;
	}

	if (!Font.loadFromFile(fontpath + "comic.ttf"))
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

			// BEGIN UPDATE SECTION

			// END OF UPDATE SECTION
			
			map.Update();
			UpdateClock.restart();
		}

		// Events handler section
		while (window->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window->close();

			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				window->close();
			}
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Down)
			{
				map.BitDown();
			}
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Up)
			{
				map.BitUp();
			}
		}

		// Drawing section
		if (RenderClock.getElapsedTime().asMilliseconds() > fps)
		{
			//
			// Drawing objects here
			//

			frames++;
			window->clear();
			points.Draw();
			map.Draw();
			window->display();
			RenderClock.restart();
		}

		if (fpsCounter.getElapsedTime().asSeconds() > 1.0f)
		{
			std::cout << frames << std::endl;
			frames = 0;
			fpsCounter.restart();
		}
		sf::sleep(sf::milliseconds(2));
	}
	return EXIT_SUCCESS;
}