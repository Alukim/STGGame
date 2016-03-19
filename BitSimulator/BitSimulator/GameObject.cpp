#include "GameObject.h"
#include <iostream>
using namespace sf;

void GameObject::SetPosition(int x, int y)
{
	rect.left = x;
	rect.top = y;
	shape.setPosition(x, y);
}

void GameObject::Resize(unsigned int width, unsigned int height)
{
	rect.width = width;
	rect.height = height;
}

void GameObject::Scale(float prct_x, float prct_y)
{
	rect.width *= (prct_x / 100);
	rect.height *= (prct_y / 100);
	shape.setSize(sf::Vector2f(rect.width, rect.height));
}


void GameObject::Move(int x, int y)
{
	rect.left += x;
	rect.top += y;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
}

void GameObject::SetOrigin(float x, float y)
{
	shape.setOrigin(sf::Vector2f(x, y));
}

IntRect GameObject::GetLayout() const
{
	return rect;
}

void GameObject::operator=(GameObject & ref)
{
	window = ref.window;
	shape = ref.shape;
	rect = ref.rect;
	shape.setTexture(ref.shape.getTexture(), true);
}

GameObject::GameObject(RenderWindow *win, Texture *text, int x, int y, bool adjust, int width, int height)
{
	if ((window = win) == NULL)
	{
		std::cerr << ("Could not find refered window. Exiting... ") << std::endl;
		throw NULL;
	}
	if (!text)
	{
		std::cerr << "Texture passed is NULL!" << std::endl;
		throw NULL;
	}
	else
		shape.setTexture(text);
	
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

GameObject::GameObject(RenderWindow *win, std::string &path,  sf::Color transmask, unsigned int x, unsigned int y)
{
	sf::Image img;
	sf::Texture *temp = new sf::Texture;
	if (!(window = win))
	{
		std::cerr << ("Could not create a window reference. Exiting...");
		throw NULL;
	}
	if (!(img.loadFromFile(path)))
	{
		std::cerr << ("Game files seem to be missing. Try reinstalling your game.");
		throw NULL;
	}
	if (transmask != sf::Color::Transparent)
		img.createMaskFromColor(transmask);
	
	temp->loadFromImage(img);
	temp->setSmooth(true);

	shape.setTexture(temp, true);
	rect.left = x;
	rect.top = y;
	rect.width = shape.getTexture()->getSize().x;
	rect.height = shape.getTexture()->getSize().y;

	shape.setPosition(Vector2f(rect.left, rect.top));
	shape.setSize(Vector2f(rect.width, rect.height));
}


void GameObject::Draw(void)
{
	window->draw(shape);
}


GameObject::~GameObject()
{
}
