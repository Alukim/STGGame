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

enum Events
{
	None					=		0x00,
	VBonusHit				=		0x01,
	ABonusHit				=		0x02,
	Elem_Entered			=		0x03,
	Bit_Annihillated		=		0x05,
	CheckpointReached		=		0x06,
	Run_Off_Fuel			=		0x07,
	Bit_Inv_Collision		=		0x08
};


class Tracklist;

class Track
{
private:
	
	sf::RenderWindow *window;			//> pointer to window the track will be drawn in
	sf::Sprite sprite;					//> sprite of track
	std::list <GameObject *> draw_list;	//> list of elements placed on track
	GameObject *bitptr;					//> pointer to bit on track, if there is not any, pointer is null
	
	float length;						//> length of track
	float h_offset;						//> height offset of the track
	
	static sf::Texture texture;
public:
	friend Tracklist;

	

	//> construcor
	Track(sf::RenderWindow *win, float y);


	//> Attaches a bit to the track
	//> /a ptr - pointer to bit object
	void Attach(GameObject *ptr);

	static void SetTexture(std::string &path);

	//> Detaches a bit from the track
	//> Returns pointer to detached bit
	GameObject* Detach();


	//> Updates the whole track(objects within included)
	int Update();


	//> Adds an elemement to the track
	//> /a new_elem - pointer to new element object
	void AddElem(GameObject *new_elem);


	GameObject * GetElem();


	//> Draws whole track
	void Draw();
};


class Tracklist
{

private:
	int size;				//> contains max quantity of tracks
	int track_num;			//> track number in list order, where bit is attached
	long long int counter;

	bool bitstate;

	GameObject *bit;		//> pointer to bit
	Track *list[5];			//> list of tracks

	Battery *volts;			//> volt load
	Battery *amps;			//> amper load

public:

	Tracklist(sf::RenderWindow * window);
	void AddTrack(Track *track, int pos);
	void AddElem(GameObject *new_elem, int track);
	void ChangeBitState();
	void Update();
	void BitUp();
	void BitDown();
	void Draw();
};