#pragma once
#include "SFML\Graphics.hpp"
#include <string>
using namespace sf;

class GameObject
{
protected:
	sf::RenderWindow *window; //> pointer to a window object is asigned
	sf::IntRect rect; //> rectangle of texture layout
	sf::RectangleShape shape; //> representation of the object
public:
	//> default constructor
	GameObject() {}

	//> constructor
	//> /a text is a pointer to created texture in file
	//> /a adjust - flag informs about resizing the picture to texture size
	GameObject(RenderWindow *win, Texture *text, int x = 0, int y = 0, bool adjust = true, int width = 0, int height = 0);

	//> constructor
	//> /a path - string containing path to the texture
	GameObject(RenderWindow *win, std::string path,sf::Color transmask = sf::Color::Transparent, unsigned int x = 0, unsigned int y = 0 );

	//> sets position and modifies intmask of object
	void SetPosition(int x, int y);

	//> resizes the object to given /a width and /a height
	void Resize(unsigned int width, unsigned int height);

	//> scales the object dimensions by
	//> /a prct_x in width 
	//> /a prct_y in height
	void Scale(float prct_x, float prct_y);

	//> moves an object by
	//> /a x in x-axis
	//> /a y in y-axis
	virtual void Move(int x, int y);

	//> sets an origin of sprite
	//> /a x in x-axis
	//> /a y in y-axis;
	void SetOrigin(float x, float y);

	//> returns current dimensions of an object
	IntRect GetLayout() const;

	void operator = (GameObject &ref);

	//> draws the object into render context
	virtual void Draw();

	virtual ~GameObject();
};


