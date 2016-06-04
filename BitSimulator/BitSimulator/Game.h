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

	RectangleShape fader;				// game-over screen effect
	
	//game-logic vars
	float offset;						//> how fast the map moves

	Bit *bit;							//> bit

	vector<Sprite *> elems;		//> logic elems + bonuses

	list<Track *> trackMap[8];		//> tracks

	bool moveUp, moveDown;
	bool collect;
	int FadetoBlack;


	// GUI elements
	Score *Points;						//> Scoring feature

	Battery *volts;						//> volt load

	Battery *amps;						//> amper load

	Texture AND2Texture;
	Texture BitTexture;
	Texture VoltBonusTexture;
	Texture AmperBonusTexture;

	Clock updateTimer;

	long long int pixelCounter = 0;

	int levelHeights[TRACK_AMOUNT] = { 250, 295, 340, 385, 430, 475, 520, 565 };

private:

	inline bool Update();

	inline void IncrementPixelCounter();

	inline void Draw();

	void AddLogicElem(LogicElem * newObject, int trackNumber, int inputCount);

	void AddBonus(Sprite * newBonus, unsigned int trackNumber);

public:

	Game(RenderWindow * renderTarget, Font * font);

	void Play();

};

double coverPercentage(FloatRect &elem1, FloatRect &elem2);