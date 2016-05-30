#pragma once
#include <SFML\Graphics.hpp>
#include "Gates.h"
#include "Bonus.h"
#include "GUI.h"
#include "Utilities.h"
#include <list>
#include <fstream>

using namespace std;


const std::string txtpath	 = "Resource/Textures/";
const std::string mscpath	 = "Resource/Music/";
const std::string fntpath	 = "Resource/Fonts/";

class Bit;


struct track_dim
{
	float b_left;
	float b_right;
};


class Track
{
	bool mod;
	bool val;

	bool end = false;
	
	static Texture *texture;
	static RenderWindow * window;
	
public:
	
	static int trackHeight;
	int level;
	
	Track(int level, bool mod, bool value, int border_left);
	
	static void Cut(Track * track);
	
	static Track * startNewTrack(int height, int level, bool mod, bool value);
	
	bool getValue(void) const;

	Sprite sprite;
	
	track_dim dims;

	
	
	static void SetTexture(std::string & path);

	static void SetWindowPointer(RenderWindow * render);

	bool canBitAttach(Bit * bitPointer);

	void Update(float offset);

	void setValue(const bool & value);

	bool toDelete();
};


class Bit : public Sprite
{
	int state;
	Clock timer;
	const int Tick = 20;
	int previousHeight;
	int currentHeight;
	bool startedEntering;
	bool value;
	bool Moved;
	bool Locked;
	bool Entering;
	bool Leaving;
	bool Collecting;
	LogicElem * propagateObject;
	Track * currTrack;

public:
	
	enum Event
	{
		None					= 0x00,
		ElemEntered				= 0x01,
		BonusIntersection		= 0x02,
		CorrectPropagation		= 0x03,
		IncorrectPropagation	= 0x04,
		ElemLeft				= 0x05
	};

	Bit(Texture & text);

	void setHeight(const int level);

	void getBack();

	int Update();

	bool hasMoved();

	bool isLocked();

	bool isEntering();

	bool isLeaving();

	bool isCollecting();

	bool Value();
	
	void changeValue(); 
	
	void EnterLogicElem(LogicElem * object);
	
	void attachToTrack(Track * track);
};


struct ElemScript {
	int startingPixel;
	int elemType;
	int inputAmount;
};

class LevelManager {
private:
	std::list <ElemScript> elems;
public:
	LevelManager()
	{
	}

	void ReadLevel(int levelNumber);


};