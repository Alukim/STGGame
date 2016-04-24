#include "GameObject.h"
#include <iostream>
using namespace sf;

void GameObject::SetPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void GameObject::Scale(float prct_x, float prct_y)
{
	sprite.scale(sf::Vector2f(prct_x, prct_y));
}


void GameObject::Move(float x, float y)
{
	sprite.move(sf::Vector2f(x, y));
}

void GameObject::SetOrigin(float x, float y)
{
	sprite.setOrigin(sf::Vector2f(x, y));
}

void GameObject::setColor(const sf::Color &colour)
{
	sprite.setColor(colour);
}

FloatRect &GameObject::GetLayout()
{
	return sprite.getGlobalBounds();
}

void GameObject::operator=(GameObject & ref)
{
	window = ref.window;
	sprite = ref.sprite;
	sprite.setTexture(*ref.sprite.getTexture(), true);
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
		sprite.setTexture(*text);
	
	sprite.setPosition(Vector2f(x, y));
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
	sprite.setTexture(*temp, true);

	sprite.setPosition(Vector2f(x, y));
}


void GameObject::Draw(void)
{
	window->draw(sprite);
}

GameObject::operator sf::Sprite() const
{
	return sprite;
}

GameObject::~GameObject()
{
}
