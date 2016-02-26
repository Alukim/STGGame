#pragma once
#include <SFML\Graphics.hpp>

// class used for drawing meters filled with spectrum's colors
class Buffer
{
	int load;
	int capacity;
	sf::IntRect dim;
public:

	//> sets if there is an alert when meter is full
	void SetAlert(bool state);

	//> returns current fullfilment
	int GetFullfillment();

	//> adds /a value to the load
	bool Load(int value);

	//> draws buffer onto screen
	void Draw();
};
