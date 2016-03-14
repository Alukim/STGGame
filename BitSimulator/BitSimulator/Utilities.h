#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
bool Intersect(FloatRect &elem1, Vector2i &elem2);
bool Intersect(IntRect &elem1, IntRect &elem2);
void ChangeColor(sf::Image *ptr, sf::Color col1, sf::Color col2);
