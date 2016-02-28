#pragma once
#include <string>
#include <SFML\Graphics.hpp>
template <char letter>
class Bonus
{
	std::string let;
	sf::CircleShape shape;
	int value;
	sf::Text text;

	sf::RenderWindow *window;
	
public:
	static int cap;
	Bonus<letter>(sf::RenderWindow *win, sf::Font *font, int val);

	void Draw();
};

typedef Bonus<'A'> Amper;
typedef Bonus<'V'> Volt;


int Volt::cap = 500;


template<char letter>
inline Bonus<letter>::Bonus(sf::RenderWindow *win, sf::Font *font, int val)
{
	window = win;

	let = letter;

	float res = (float)val / cap;

	if (val > cap)
		val = cap;

	shape.setRadius(res * 100);
	shape.setPosition(100, 100);
	if (res < 0.2f)
		shape.setFillColor(sf::Color::Red);
	else if (res < 0.5f)
		shape.setFillColor(sf::Color::Yellow);
	else
		shape.setFillColor(sf::Color::Green);

	text.setString(sf::String(let));
	text.setFont(*font);
	text.setColor(sf::Color::Green);

	sf::FloatRect shapedim = shape.getGlobalBounds();
	int textsize = text.getCharacterSize();

	if (shapedim.width < textsize)
	{
		float res_width = (float)(shapedim.width / textsize);
		float res_height = (float)(shapedim.height / textsize);

		text.setScale(sf::Vector2f(res_width, res_height));
	}
	
	sf::FloatRect textdim = text.getGlobalBounds();

	text.setPosition(shapedim.left + (int)shapedim.width/ 2 -(int)textdim.width / 2,
		shapedim.top + (int)shapedim.height/ 2 - (int)textdim.height / 2);



}

template<char letter>
inline void Bonus<letter>::Draw()
{
	window->draw(shape);
	window->draw(text);
}