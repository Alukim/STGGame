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