#pragma once
#include <string>
#include <SFML\Graphics.hpp>
template <char letter>
class Bonus : public Sprite
{
	bool mod;
	int value;					// bonus value
	bool Visible = true;
public:
	static int cap;
	Bonus<letter>(Texture & text, int val);
	bool isVisible();
	int GetBonus();
};

typedef Bonus<'A'> Amper;
typedef Bonus<'V'> Volt;


int Volt::cap = 500;


template<char letter>
inline bool Bonus<letter>::isVisible()
{
	return Visible;
}

template<char letter>
inline int Bonus<letter>::GetBonus()
{
	Visible = false;
	return value;
}

template<char letter>
inline Bonus<letter>::Bonus(Texture & text, int val) :
	Sprite(text)
{
	mod = true;
	value = val;
}
