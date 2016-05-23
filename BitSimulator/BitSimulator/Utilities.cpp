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

bool Intersect(FloatRect &elem1, FloatRect &elem2)
{
	if ((elem1.left + elem1.width >= elem2.left) && (elem1.left < elem2.left + elem2.width) 
		&& (elem1.top + elem1.height >= elem2.top) && (elem1.top < elem2.top + elem2.height))
		return true;
	
	else return false;
}

void ChangeColor(sf::Image * ptr, sf::Color col1, sf::Color col2)
{
	Vector2u dim = ptr->getSize();

	for (unsigned posx = 0; posx < dim.x; posx++)
	{
		for (unsigned posy = 0; posy < dim.y; posy++)
		{
			if (ptr->getPixel(posx, posy) == col1)
				ptr->setPixel(posx, posy, col2);
		}
	}
}

double CoverBonus(sf::FloatRect elem1, sf::FloatRect elem2)
{
	if (elem1.left > elem2.left && elem1.left + elem1.width < elem2.left + elem2.width)
		return 1.0f;
	else
	{	
		double temp = elem2.left - elem1.left;
		temp = elem1.width - temp;
		temp /= elem2.width;
		return temp;
	}
}

double CoverPercentage(sf::FloatRect elem1, sf::FloatRect elem2)
{
		int area = (int)(elem1.width * elem1.height);

		int diff_x = (int)(elem1.left - elem2.left);

		if (diff_x < 0)
			diff_x =(int)(elem1.width + diff_x);

		else
			diff_x = (int)(elem2.width - diff_x);

		int diff_y = (int)(elem1.top - elem2.top);

		if (diff_y < 0)
			diff_y = (int)(elem1.height + diff_y);
		else
			diff_y = (int)(elem2.height - diff_y);
		
		double l = (double)(diff_x * diff_y) / area;
		return l;
}
