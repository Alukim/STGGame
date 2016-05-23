#pragma once
#include "SFML\Graphics.hpp"
#include "BitTrack.h"
#include "GUI.h"
#define TRACK_AMOUNT 8
class Game
{
private:
	inline void MoveUp();
	
	inline void MoveDown();

	inline void Update();

	inline void IncrementPixelCounter();

	inline void Draw();

	void AddLogicElem(LogicElem * newObject, int trackNumber, int inputCount);

	void AddBonus(Sprite * newBonus);

	void StartTrack(int level, bool mod, bool value );

	// Graphic vars
	const int FPS = 300;
	const int UPS = 1000 / 120;
	RenderWindow * Window;
	Event events;
	Font Font;
	bool Fail;
	
	Texture AND2Texture;
	Texture BitTexture;

	//game-logic vars
	float offset;							//> how fast the map moves
	
	long long int counter;					//> counts how many pixels the player reached
	
	int bit_level;							//> track that the bit is on
	
	int prev_bit_level;
	

	bool movedUp = false;

	bool movedDown = false;

	
	Bit *bit;							//> bit
	
	std::vector<Sprite *> elems;	//> logic elems + bonuses
	
	std::list<Track *> trackMap[8];		//> tracks
	
	int levelHeights[TRACK_AMOUNT]= { 250, 295, 340, 385, 430, 475, 520, 565};
								
	// GUI elements
	Score *Points;						//> Scoring feature
	
	Battery *volts;						//> volt load
	
	Battery *amps;						//> amper load

	
	
	Clock updateTimer;					
	
	long long int pixelCounter = 0;
	
	int cont=0;

	Clock tim;
public:

	Game();

	void Play();
	
};