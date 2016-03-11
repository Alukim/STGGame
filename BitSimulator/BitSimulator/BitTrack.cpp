#include "BitTrack.h"

track::track(sf::RenderWindow * win, std::string path, int x, int y)
{
	window = win;
	offset.x = x;
	offset.y = y;

	sf::Texture *text = new sf::Texture;

	text->loadFromFile(path);
	text->setSmooth(true);
	
	bitptr = NULL;

	sprite.setTexture(*text);
	sprite.setPosition(sf::Vector2f(x, y));
	width = sprite.getGlobalBounds().width;
}

void track::Attach(GameObject * ptr)
{
	bitptr = ptr;
	sf::FloatRect pos = sprite.getGlobalBounds();

	bitptr->SetPosition(pos.width * 0.03, pos.top);
}

GameObject* track::Detach()
{
	GameObject *get = bitptr;
	bitptr = NULL;
	return get;
}

void track::Update()
{
	std::list<GameObject *>::iterator it = draw_list.begin();
	offset.x += 2;
	for (it; it != draw_list.end(); it++)
	{
		(*it)->Move(-1, 0);
	}
	sprite.move(sf::Vector2f(-2, 0));
	if (offset.x > width)
		offset.x = 0;
}

void track::AddElem(GameObject * new_elem)
{
	
	sf::FloatRect pos = sprite.getGlobalBounds();
	
	new_elem->SetPosition(1200/*pos.left + pos.width*/, pos.top);

	draw_list.push_back(new_elem);
}

void track::Draw()
{
	sprite.setPosition(sf::Vector2f(-offset.x, offset.y));
	window->draw(sprite);
	sprite.setPosition(sf::Vector2f(width - offset.x, offset.y));
	window->draw(sprite);

	if (bitptr)
		bitptr->Draw();

	std::list<GameObject *>::iterator it = draw_list.begin();
	for (it; it != draw_list.end(); it++)
	{
		(*it)->Draw();
	}
}
