#pragma once
#include "GameObject.h"
#include <SFML\Graphics.hpp>
#include "Gates.h"
#include "Bonus.h"
#include "GUI.h"
#include "Utilities.h"
#include <list>


const std::string txtpath	 = "Resource/Textures/";
const std::string mscpath	 = "Resource/Music/";
const std::string fntpath	 = "Resource/Fonts/";

enum TrackEvents
{
	None					=		0x10,
	VBonusHit				=		0x01,
	ABonusHit				=		0x02,
	Elem_Entered			=		0x03,
	Bit_Annihillated		=		0x05,
	CheckpointReached		=		0x06,
	Run_Off_Fuel			=		0x07,
	No_Bit					=		0x08
};

class Bit;

class Track
{
private:
	
	sf::RenderWindow *window;			//> pointer to window the track will be drawn in
	sf::Sprite sprite;					//> sprite of track
	std::list <GameObject *> draw_list;	//> list of elements placed on track
	Bit *bitptr;						//> pointer to bit on track, if there is not any, pointer is null
	
	sf::Clock Timer;

	const int Tick = 50;
	float length;						//> length of track
	float h_offset;						//> height offset of the track	

	static sf::Texture texture;

	bool Perfect = false;
	bool value = false;
public:
	
	TrackEvents events = None;

	//> constructor
	Track(sf::RenderWindow *win, float y);


	//> Attaches a bit to the track
	//> /a ptr - pointer to bit object
	void Attach(Bit *ptr);

	//> Detaches a bit from the track
	//> Returns pointer to detached bit
	void Detach();
	
	static void SetTexture(std::string &path);


	//> Updates the whole track(objects within included)
	GameObject *Update(float off);


	//> Adds an elemement to the track
	//> /a new_elem - pointer to new element object
	void AddElem(GameObject *new_elem);


	GameObject * GetElem();


	//> Draws whole track
	void Draw();
};


class Bit : public GameObject
{
	bool Collecting;
	bool Entering;
	bool Leaving;
	bool Locked;
	bool State;

	LogicElem * prop = NULL;
	

	sf::Clock Timer;
	const int Tick = 350;
public:
	Bit(sf::RenderWindow *&render_target, std::string &path);
	
	void ChangeState();
	void SetState(bool state);
	bool GetState();

	void EnterGate(LogicElem* elem);
	void LeaveGate();
	bool Propagate();

	void setCollectingState(bool state);

	bool isCollecting();

	bool isLocked();

	bool Update();

	void Draw();
};