#pragma once
#include "SFML\Graphics.hpp"
class Game
{
public:
	Game();
	~Game();
	sf::RenderWindow *Window;
	void runGame();
protected:
	enum GameState {MENU,GAME_OVER,GAME,END} status; //Lista wyliczeniowa statusu gry
private:
	sf::Font Font;

	void menu();
};

