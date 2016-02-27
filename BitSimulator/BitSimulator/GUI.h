#pragma once
#include <SFML\Graphics.hpp>


// class used for drawing meters filled with spectrum's colors
class Buffer
{

protected:
	sf::RenderWindow * window;
	int load;
	int capacity;

	short int flashcounter;
	// entire buffer 
	sf::IntRect dim;
	sf::RectangleShape layout;
	
	// flow
	sf::RectangleShape fill;
	sf::IntRect flowdim;
	
	bool alerted;
	virtual void Refactor() = 0;
public:

	//> constructor
	Buffer(int cap, int x, int y, int w, int h);
	
	//> sets if there is an alert when meter is full
	void SetAlert(bool state);

	//> returns current fullfilment
	int GetFullfillment();

	//> adds /a value to the load
	//> returns true if buffer is overloaded
	bool Load(int value);

	//> draws buffer onto screen
	virtual void Draw();
};


class VerticalBuffer : public Buffer
{
public:
	void Refactor() override;
};


//class HorizontalBuffer : public Buffer
//{
//};


class InfoGiver
{
	sf::RectangleShape black_back;
	sf::Sprite * text_tab;
public:
	InfoGiver(int x, int y, int w, int h);
};