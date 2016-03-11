#pragma once
#include "GameObject.h"
#include <SFML\Graphics.hpp>
#include "Gates.h"
#include <list>
class track
{
	int width;							//> width of track
	sf::RenderWindow *window;			//> pointer to window the track will be drawn in
	sf::Sprite sprite;					//> sprite of track
	std::list <GameObject *> draw_list;	//> list of elements placed on track
	GameObject *bitptr;					//> pointer to bit on track, if there is not any, pointer is null
	sf::Vector2i offset;				//> offset of the track
	
public:
	
	//> construcor
	track(sf::RenderWindow *win, std::string path, int x, int y);

	//> Attaches a bit to the track
	//> /a ptr - pointer to bit object
	void Attach(GameObject *ptr);

	//> Detaches a bit from the track
	//> Returns pointer to detached bit
	GameObject* Detach();

	//> Updates the whole track(objects within included)
	void Update();

	//> Adds an elemement to the track
	//> /a new_elem - pointer to new element object
	void AddElem(GameObject *new_elem);

	//> Draws whole track
	void Draw();
};
