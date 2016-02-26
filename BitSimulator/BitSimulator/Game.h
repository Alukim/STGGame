#pragma once
#include "SFML\Graphics.hpp"
class Game
{
public:
	Game();
	~Game();
	void runGame();
protected:
	enum GameState {MENU,GAME_OVER,GAME,END} status; //Lista wyliczeniowa statusu gry
	sf::RenderWindow *window;
private:
	sf::Font Font;

	void menu();
};

