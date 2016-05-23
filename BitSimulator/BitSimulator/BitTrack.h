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

	bool getValue(void) const;

	Sprite sprite;
	
	track_dim dims;

	Track(int level, bool mod, bool value, int border_left);
	
	static void SetTexture(std::string & path);

	static void SetWindowPointer(RenderWindow * render);

	bool canBitAttach(Bit * bitPointer);

	void setLevel(int lvl);

	void Update(float offset);

	void setValue(const bool & value);

	bool toDelete();

	void Cut();
};


class Bit : public Sprite
{
	
	Clock timer;
	const int Tick = 20;
	int previousHeight;
	int currentHeight;
	bool value;
	bool Moved;
	bool Locked;
	bool Entering;
	bool Leaving;
	bool Collecting;
	LogicElem * propagateObject;

public:
	
	bool Visible;

	Bit(Texture & text);

	void setHeight(const int level);

	void getBack();

	void attachToTrack(Track * track);

	int Update();

	bool & hasMoved();

	bool & isLocked();

	bool & isEntering();

	bool & isLeaving();

	bool & isCollecting();

	bool & Value();
	
	void changeValue(); 
	
	void EnterLogicElem(LogicElem * object);
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