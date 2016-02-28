#pragma once
#include <SFML\Graphics.hpp>


// class used for drawing meters filled with spectrum's colors
class Battery
{
	
	int load;				//> battery's load
	int cap;				//> battery's capacity
	sf::Sprite batsprite;	//>	battery's sprite
	sf::Sprite lightsprite;

	sf::RenderWindow *ref;	//> pointer to window battery will be drawn in

	bool change;			//> defines if sprite needs to be updated before drawing

	sf::Image img;			//> variable where updates take place
	int waver;				//> special counter to provide flashing when battery is full
	void Refactor();		//> update method

public:

	//> Constructor
	//> Creates Battery image with loading utility
	//> /a window - pointer to window battery will be drawn in
	//> /a l - load the battery starts with
	//> /a c - capacity of battery
	//> /a path - path of the image
	//> Sets object coords to /a xpos and /a ypos;
	Battery(sf::RenderWindow *window, int l, int c, std::string path, int xpos=0, int ypos=0);


	
	//> Adds the /a load_inc to load value
	void Load(int load_inc);
		
	//> decrements load value by /a load_dnc
	void Dissipate(int load_dnc);
		
	//> Draws the sprite onto screen
	void Draw();
};
