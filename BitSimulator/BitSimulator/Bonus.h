#pragma once
#include <string>
#include <SFML\Graphics.hpp>
template <char letter>
class Bonus
{
	std::string let;
	sf::CircleShape shape;
	int value;
	
public:
	static int cap;
	Bonus<letter>(int val);
};

typedef Bonus<'A'> Amper;
typedef Bonus<'V'> Volt;

