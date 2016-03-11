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
	const int fps = 1000 / 100;
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
	Battery bat(window, 200, 5000, "Resource/Textures/Baterry/bat.png");

	AND2 martha(window, "Resource/Textures/Gates/And.png");
	track m(window, "Resource/Textures/track.png", 0, 200);

	m.AddElem(&martha);
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

	GameObject *bit = new GameObject(window, "Resource/Textures/bit.png", sf::Color(255, 0, 255));

	Music.setVolume(50);
	Music.setLoop(true);
	Music.play();
	Music.stop();
	Volt bon(window, "Resource/Textures/gwiazda.png", 400);

	m.AddElem(&bon);
	m.Attach(bit);

	Points_class points(window, &Font);
	while (window->isOpen())
	{

		// Update section
		if (UpdateClock.getElapsedTime().asMilliseconds() > ups)
		{
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				bat.Load(500);
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				bat.Dissipate(50);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
				points.Update(400);
			}

			//
			// updating object here
			//
			m.Update();
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
		}

		// Drawing section
		if (RenderClock.getElapsedTime().asMilliseconds() > fps)
		{
			frames++;
			window->clear();
			bat.Draw();
			bon.Draw();
			points.Draw();
			m.Draw();
			//
			// Drawing objects here
			//
			window->display();
			RenderClock.restart();
		}

		if (fpsCounter.getElapsedTime().asSeconds() > 1.0f)
		{
			std::cout << frames << std::endl;
			frames = 0;
			fpsCounter.restart();
		}
		//sf::sleep(sf::milliseconds(1));
	}
	return EXIT_SUCCESS;
}