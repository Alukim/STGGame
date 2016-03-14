#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "GameObject.h"
template <char letter>
class Bonus : public GameObject
{
	bool mod;
	int value;					// bonus value

public:
	static int cap;
	Bonus<letter>(sf::RenderWindow *win, std::string path, int val);

	void Draw() override;
	int GetBonus();
};

typedef Bonus<'A'> Amper;
typedef Bonus<'V'> Volt;


int Volt::cap = 500;



template<char letter>
inline void Bonus<letter>::Draw()
{
	shape.rotate(0.5f);
	sf::Vector2f scale = shape.getScale();

	if (scale.x < 0.2f)		mod = false;
	else if (scale.x >= 1.0f) mod = true;

	if (mod)
	{
		scale.x -= 0.01f; 
		scale.y -= 0.01f;
	}
	else
	{
		scale.x += 0.01f; 
		scale.y += 0.01f;
	}
	shape.setScale(sf::Vector2f(scale.x, scale.y));

	sf::IntRect pos = GetLayout();
	shape.setPosition(sf::Vector2f(pos.left, pos.top + pos.height/2));
	window->draw(shape);
}

template<char letter>
inline int Bonus<letter>::GetBonus()
{
	return value;
}

template<char letter>
inline Bonus<letter>::Bonus(sf::RenderWindow * win, std::string path, int val) : GameObject(win, path, sf::Color::Black)
{
	mod = true;
	value = val;
	window = win;
	shape.setScale(sf::Vector2f(1.0f, 1.0f));
	sf::FloatRect pos = shape.getLocalBounds();
	shape.setOrigin(pos.left + pos.width / 2, pos.top + pos.height / 2);
}
