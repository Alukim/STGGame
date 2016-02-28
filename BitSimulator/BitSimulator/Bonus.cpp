#include "Bonus.h"


template<char letter>
inline Bonus<letter>::Bonus(int val)
{
	letter = let;

	float res = (float)val / cap;

	if (val > cap)
		val = cap;

	shape.setRadius(res * 30.0f);

	if (res < 0.2f)
		shape.setFillColor(sf::Color::Red);
	else if (res < 0.5f)
		shape.setFillColor(sf::Color::Yellow);
	else
		shape.setFillColor(sf::Color::Green);
}