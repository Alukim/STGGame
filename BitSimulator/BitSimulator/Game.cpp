#include "Game.h"
#include <Windows.h>
#include <string>

Game::Game()
{
	status = END;

	if (!Font.loadFromFile("comic.ttf"))
	{
		MessageBox(NULL, "Font not found!", "ERROR", NULL);
		return;
	}
	Window = new sf::RenderWindow(sf::VideoMode(1920, 1080, 32), "BitSimulator", sf::Style::Fullscreen);
	status = MENU;
}

void Game::runGame()
{
	while (status != END)
	{
		switch (status)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::GAME:
			//
			break;
		}
	}
}

void Game::menu()
{
	sf::Text title("BitSimulator", Font, 100);
	title.setStyle(sf::Text::Bold);

	title.setPosition(1920 / 2 - title.getGlobalBounds().width / 2, 40);

	const int ile = 2; //ile elementów masz w MENU

	sf::Text tekst[ile];

	std::string str[] = { "Play","Exit" };
	for (int i = 0;i<ile;i++)
	{
		tekst[i].setFont(Font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(1920 / 2 - tekst[i].getGlobalBounds().width / 2, 500 + i * 120);
	}

	while (status == MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(/*mo¿emy tutaj podaæ okno*/));
		sf::Event event;

		while (Window->pollEvent(event))
		{
			//Wciœniêcie ESC lub przycisk X
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape)
				status = END;

			//klikniêcie EXIT
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				status = END;
			}
		}
		for (int i = 0;i<ile;i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(sf::Color::Cyan);
			else tekst[i].setColor(sf::Color::White);

			Window->clear();

			Window->draw(title);
			for (int i = 0;i<ile;i++)
				Window->draw(tekst[i]);

			Window->display();
	}
}

Game::~Game()
{
}
