#pragma once
#include <string>
#include <SFML\Graphics.hpp>
template <char letter>
class Bonus : public Sprite
{
	bool mod;

	int value;	// bonus value

	bool visible = true;

public:
	static int cap;

	static void CollectVoltBonus(Bonus<'V'> * voltBonus);
	static void CollectAmperBonus(Bonus<'A'> * amperBonus);

	Bonus<letter>(Texture & text, int val);

	bool isVisible();

	int GetBonus();
};

typedef Bonus<'A'> Amper;
typedef Bonus<'V'> Volt;


int Volt::cap = 500;


template<char letter>
inline void Bonus<letter>::CollectVoltBonus(Bonus<'V'> * voltBonus)
{
	voltBonus->visible = false;
	voltBonus->setScale(0.0, 0.0);
}

template<char letter>
inline bool Bonus<letter>::isVisible()
{
	return visible;
}

template<char letter>
inline int Bonus<letter>::GetBonus()
{
	return value;
}

template<char letter>
inline Bonus<letter>::Bonus(Texture & text, int val) :
	Sprite(text)
{
	mod = true;
	value = val;
}
