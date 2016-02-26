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
	void menu();
	void GameOver();
private:
	sf::Font Font;
	float FPS;
	float UPS;
	sf::Clock *RenderClock;
	sf::Clock *UpdateClock;
	sf::RenderWindow *Window;
};

