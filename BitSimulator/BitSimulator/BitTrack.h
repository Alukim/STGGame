#pragma once
#include "GameObject.h"
#include <SFML\Graphics.hpp>
#include "Gates.h"
#include <list>
class track
{
	sf::RenderWindow *window;
	sf::Sprite sprite;
	std::list <GameObject *> draw_list;
public:
	track(sf::RenderWindow *win, std::string path, int x, int y);

	void Update();
	void AddElem(GameObject *new_elem);
	void Draw();

};

class Elem
{
};