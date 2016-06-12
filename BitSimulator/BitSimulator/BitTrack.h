#pragma once
#include <SFML\Graphics.hpp>
#include "Gates.h"
#include "Bonus.h"
#include "GUI.h"
#include <list>
#include <fstream>

using namespace std;

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

	int height;

	int level;

public:
	
	Track(int height, int level, bool mod, bool value, int border_left);
	
	bool getValue(void) const;

	Sprite sprite;
	
	track_dim dims;

	static void Cut(Track * track);
	
	static Track * startNewTrack(int height, int level, bool mod, bool value);
	
	static void SetTexture(std::string & path);

	static void DestroyTexture();

	static void SetWindowPointer(RenderWindow * render);

	bool canBitAttach(Bit * bitPointer);

	void Update(float offset);

	void setValue(const bool & value);

	bool toDelete();
};


class Bit : public Sprite
{
	int state;
	
	bool startedEntering;
	
	bool value;
	
	bool Entering;
	
	bool Leaving;
	
	bool Collecting;
	
	LogicElem * propagateObject;
	
	Track * currTrack;

	Track * prevTrack;

	int propagateTime;

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

	int Update();

	bool isLocked();

	bool Value();

	int getTrackIndex();
	
	void changeValue(); 
	
	void EnterLogicElem(LogicElem * object);
	
	void attachToTrack(Track * track);

	void getBack();

	~Bit()
	{
	}
};