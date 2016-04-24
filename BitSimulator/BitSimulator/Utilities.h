#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
bool Intersect(FloatRect &elem1, Vector2i &elem2);
bool Intersect(FloatRect &elem1, FloatRect &elem2);
void ChangeColor(sf::Image *ptr, sf::Color col1, sf::Color col2);
double CoverBonus(sf::FloatRect elem1, sf::FloatRect elem2);
double CoverPercentage(sf::FloatRect elem1, sf::FloatRect elem2);
