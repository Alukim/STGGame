#pragma once
#include "SFML\Graphics.hpp"
class Game
{
public:
	Game();
	~Game();
	void runGame();
protected:
	enum GameState {MENU,GAME_OVER,GAME,END}; //Lista wyliczeniowa statusu gry
	GameState status;
	sf::RenderWindow Window(sf::VideoMode(1920, 1080, 32), sf::Style::Fullscreen);
private:
	sf::Font Font;

	void menu();
};

