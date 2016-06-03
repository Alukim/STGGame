#pragma once
#include "SFML\Graphics.hpp"
#include "BitTrack.h"
#include "GUI.h"
#define TRACK_AMOUNT 8
class Game
{
private:

	const int FPS = 300;
	const int UPS = 1000 / 120;
	RenderWindow * Window;
	Font * bellfort;
	Event events;

	Texture AND2Texture;
	Texture BitTexture;

	RectangleShape fader;
	//game-logic vars
	float offset;						//> how fast the map moves

	Bit *bit;							//> bit

	std::vector<Sprite *> elems;		//> logic elems + bonuses

	std::list<Track *> trackMap[8];		//> tracks

	bool moveUp, moveDown;
	int FadetoBlack;
	// GUI elements
	
	Score *Points;						//> Scoring feature

	Battery *volts;						//> volt load

	Battery *amps;						//> amper load

	Clock updateTimer;

	long long int pixelCounter = 0;

	int levelHeights[TRACK_AMOUNT] = { 250, 295, 340, 385, 430, 475, 520, 565 };

private:

	inline bool Update();

	inline void IncrementPixelCounter();

	inline void Draw();

	void AddLogicElem(LogicElem * newObject, int trackNumber, int inputCount);

	void AddBonus(Sprite * newBonus);

public:

	Game(RenderWindow * renderTarget, Font * font);

	void Play();

};