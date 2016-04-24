#pragma once
#include "SFML\Graphics.hpp"
#include "BitTrack.h"
#include "GUI.h"
class Game
{
private:
	void MoveUp();
	void MoveDown();

	void GrabBonus();

	void Update();

	void Draw();

	void Pause();
	void Unpause();

	// Graphic vars
	const sf::Int32 fps = 1000 / 30;
	const sf::Int32 ups = 1000 / 90;
	const int FPS = 300;

	sf::RenderWindow * Window;
	sf::Event events;
	sf::Font Font;

	sf::Clock RenderClock;
	sf::Clock UpdateClock;
	
	bool Fail;
	
	//game-logic vars
	
	bool Perfect;
	bool ElemEntered;			//> if ElemEntered - animation is shown
	long long int counter;		//> counts how many pixels the player reched

	Bit *bit;					//> bit

	
	Track *Tracks[6];			//> list of tracks
	int size = 6;					//> number of tracks
	int index;					//> number of track the bit is on

	float offset;
	

								
	// GUI elements
	Score *Points;				//> Scoring feature
	Battery *volts;				//> volt load
	Battery *amps;				//> amper load

public:
	Game();

	void Play();
	
};