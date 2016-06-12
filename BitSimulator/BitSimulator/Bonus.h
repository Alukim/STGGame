#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
class Bonus : public Sprite
{
	bool mod;

	unsigned int value;	// bonus value

	bool visible;

public:
	Bonus(Texture *texture, int startValue);

	static void CollectBonus(Bonus * bonus);

	bool isVisible();

	unsigned int GetBonus();
};
