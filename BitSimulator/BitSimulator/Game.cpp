#include "Game.h"
#include <Windows.h>
#include <string>

Game::Game()
{
	FPS = 1000/60;
	UPS = 1000/100;
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
		case GameState::GAME_OVER:
			GameOver();
			break;
		}
	}
}
void Game::GameOver()
{
	sf::Text title("GAME OVER", Font, 100);
	title.setStyle(sf::Text::Bold);

	title.setPosition((Window->getSize().x / 2) - (title.getGlobalBounds().width / 2), Window->getSize().y / 7);

	const int ile = 2; //ile element�w masz w GAME_OVER

	sf::Text tekst[ile];

	std::string str[] = { "Retry","Menu" };
	for (int i = 0;i < ile;i++)
	{
		tekst[i].setFont(Font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition((Window->getSize().x / 2) - (tekst[i].getGlobalBounds().width / 2), (Window->getSize().y / 2) - (tekst[i].getGlobalBounds().height / 2 * -4 * i));
	}

	while (status == MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(*Window));
		sf::Event event;

		while (Window->pollEvent(event))
		{
			//Wci�ni�cie X
			if (event.type == sf::Event::Closed)
			{
				status = END;
			}

			//klikni�cie Retry
			else if (tekst[1].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				status = GAME;
			}

			//klikni�cie Menu
			else if (tekst[2].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				status == MENU;
			}
		}
		for (int i = 0;i < ile;i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(sf::Color::Cyan);
			else tekst[i].setColor(sf::Color::White);

			Window->clear();

			Window->draw(title);
			for (int i = 0;i < ile;i++)
				Window->draw(tekst[i]);

			Window->display();
	}
}

void Game::menu()
{
	sf::Text title("BitSimulator", Font, 100);
	title.setStyle(sf::Text::Bold);

	title.setPosition((Window->getSize().x / 2) - (title.getGlobalBounds().width / 2), Window->getSize().y / 9);

	const int ile = 2; //ile element�w masz w MENU

	sf::Text tekst[ile];

	std::string str[] = { "Play","Exit" };
	for (int i = 0;i<ile;i++)
	{
		tekst[i].setFont(Font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition((Window->getSize().x / 2) - (tekst[i].getGlobalBounds().width / 2), (Window->getSize().y / 2) - (tekst[i].getGlobalBounds().height / 2 * -4 * i));
	}

	while (status == MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(*Window));
		sf::Event event;

		while (Window->pollEvent(event))
		{
			//Wci�ni�cie ESC lub przycisk X
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape)
			{
				status = END;
			}

			//klikni�cie EXIT
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				status = END;
			}

			//Wci�niecie G
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
			{
				status = GAME_OVER;
			}
		}
		for (int i = 0;i < ile;i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(sf::Color::Cyan);
			else tekst[i].setColor(sf::Color::White);

			Window->clear();

			Window->draw(title);
			for (int i = 0;i < ile;i++)
				Window->draw(tekst[i]);

			Window->display();
	}
}



Game::~Game()
{
}
