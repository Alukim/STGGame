#include "GameObject.h"
#include <iostream>
using namespace sf;

void GameObj::SetPosition(int x, int y)
{
	rect.left = x;
	rect.top = y;
	shape.setPosition(x, y);
}

void GameObj::Resize(unsigned int width, unsigned int height)
{
	rect.width = width;
	rect.height = height;
}

void GameObj::Scale(float prct_x, float prct_y)
{
	rect.width *= (prct_x / 100);
	rect.height *= (prct_y / 100);
	shape.setSize(sf::Vector2f(rect.width, rect.height));
}


void GameObj::Move(int x, int y)
{
	rect.left += x;
	rect.top += y;
}

IntRect GameObj::GetLayout() const
{
	return rect;
}

void GameObj::operator=(GameObj & ref)
{
	window = ref.window;
	shape = ref.shape;
	rect = ref.rect;
	shape.setTexture(ref.shape.getTexture(), true);
}

GameObj::GameObj(RenderWindow *win, Texture *text, int x, int y, bool adjust, int width, int height)
{
	if ((window = win) == NULL)
	{
		std::cerr << ("Could not find refered window. Exiting... ");
		throw NULL;
	}
	if (adjust)
	{
		rect.left = x;
		rect.top = y;
		rect.width = shape.getTexture()->getSize().x;
		rect.height = shape.getTexture()->getSize().y;
	}
	else
	{
		rect.left = x;
		rect.top = y;
		rect.width = width;
		rect.height = height;
	}
	shape.setSize(Vector2f(rect.width, rect.height));
	shape.setPosition(Vector2f(rect.left, rect.top));
}

GameObj::GameObj(RenderWindow *win, std::string path, unsigned int x, unsigned int y)
{
	sf::Texture temp;
	if (!(window = win))
	{
		std::cerr << ("Could not create a window reference. Exiting...");
		throw NULL;
	}
	if (!temp.loadFromFile(path))
	{
		std::cerr << ("Game files seem to be missing. Try reinstalling your game.");
		throw NULL;
	}

	shape.setTexture(&temp, true);
	rect.left = x;
	rect.top = y;
	rect.width = shape.getTexture()->getSize().x;
	rect.height = shape.getTexture()->getSize().y;

	shape.setPosition(Vector2f(rect.left, rect.top));
	shape.setSize(Vector2f(rect.width, rect.height));
}


void GameObj::Draw(void) const
{
	window->draw(shape);
}


GameObj::~GameObj()
{
}
