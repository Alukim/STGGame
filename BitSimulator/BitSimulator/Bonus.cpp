#include "Bonus.h"

Bonus::Bonus(Texture * texture, int startValue) : Sprite(*texture)
{
	value = startValue;
	visible = true;
}

void Bonus::CollectBonus(Bonus * bonus)
{
	bonus->visible = false;
	bonus->setScale(0.0, 0.0);
}

bool Bonus::isVisible()
{
	return visible;
}

unsigned int Bonus::GetBonus()
{
	return value;
}

