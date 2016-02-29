#pragma once
#include <string>
#include <SFML\Graphics.hpp>
template <char letter>
class Bonus
{
	sf::RenderWindow *window;	// window pointer bonus will be drawn in
						
	sf::Sprite sprite;			// sprite of bonus
	sf::Text text;				// letter of bonus

	bool factor;

	int value;					// bonus value
	
public:
	static int cap;
	Bonus<letter>(sf::RenderWindow *win, sf::Font *font, int val);

	void Draw();
};

typedef Bonus<'A'> Amper;
typedef Bonus<'V'> Volt;


int Volt::cap = 500;

	

template<char letter>
inline void Bonus<letter>::Draw()
{
	sprite.setPosition(500, 500);
	sprite.rotate(1.0f);

	const sf::Vector2f scale = sprite.getScale();
	
	if (scale.x < 0.6f)		factor = false;
	else if(scale.x > 1.0f)	factor = true;

	if (factor)	sprite.setScale(scale.x - 0.01f, scale.y - 0.01f);
	else sprite.setScale(scale.x + 0.01f, scale.y + 0.01f);

	window->draw(sprite);
	window->draw(text);
}

template<char letter>
inline Bonus<letter>::Bonus(sf::RenderWindow * win, sf::Font * font, int val)
{
	
	text.setFont(*font);
	text.setString(sf::String(letter));
	text.setColor(sf::Color::Magenta);

	sf::Texture *temp = new sf::Texture;
	temp->loadFromFile("Resource/Textures/gwiazda.png");
	temp->setSmooth(true);
	sprite.setTexture(*temp);
	
	sf::FloatRect frect = sprite.getGlobalBounds();
	sprite.setOrigin(frect.left + frect.width / 2, frect.top + frect.height / 2);


	value = val;
	window = win;
	factor = true;
}
