#include "Utilities.h"
bool Intersect(FloatRect &elem1, Vector2i &elem2)
{
	if ((elem2.x >= elem1.left)
		&& (elem2.x <= elem1.left + elem1.width)
		&& (elem2.y >= elem1.top)
		&& (elem2.y <= elem1.top + elem1.height))
		return true;
	else
		return false;
}

bool Intersect(IntRect &elem1, IntRect &elem2)
{
	return elem1.intersects(elem2);
}
void ChangeColor(sf::Image * ptr, sf::Color col1, sf::Color col2)
{
	Vector2u dim = ptr->getSize();

	for (int posx = 0; posx < dim.x; posx++)
	{
		for (int posy = 0; posy < dim.y; posy++)
		{
			if (ptr->getPixel(posx, posy) == col1)
				ptr->setPixel(posx, posy, col2);
		}
	}
}
