#pragma once
#include <SFML\Graphics.hpp>
#include <stdlib.h>

using namespace sf;

const std::string txtpath = "Resource/Textures/";
const std::string mscpath = "Resource/Music/";
const std::string fntpath = "Resource/Fonts/";

// class used for drawing meters filled with spectrum's colors
class Battery
{
	RenderWindow *renderTarget;	//> pointer to window battery will be drawn in

	int load;					//> battery's load
	int cap;					//> battery's capacity
	Vector2u batSize;


	Texture texture;
	Sprite batSprite;			//>	battery's sprite
	RectangleShape filling;		//> battery's filling
	Color fillColor;

public:

	//> Default constructor
	Battery()
	{
	}

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

class Score
{
private:
	bool render;

	int q_points;

	sf::RenderWindow *window;

	sf::Font *font;

	sf::Text t_score;

	sf::Text t_points;

public:
	Score(sf::RenderWindow *window_context, sf::Font *font);
	void Add(int inc);
	void Draw();
};