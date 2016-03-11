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
	GameObject *bitptr;
public:
	track(sf::RenderWindow *win, std::string path, int x, int y);

	void Attach(GameObject *ptr);
	GameObject* Detach();
	void Update();
	void AddElem(GameObject *new_elem);
	void Draw();

};
