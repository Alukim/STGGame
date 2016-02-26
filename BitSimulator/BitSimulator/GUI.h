#pragma once
#include <SFML\Graphics.hpp>

// class used for drawing meters filled with spectrum's colors
class Meter
{
	int fullfillment;
	int capacity;
	sf::IntRect dim;
public:

	//> sets alert
	void SetAlert(bool state);
};
