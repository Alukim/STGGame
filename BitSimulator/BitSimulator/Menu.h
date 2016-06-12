#pragma once
#include <SFML\Graphics.hpp>
#include <list>
#include <string>
#include "Background.h"
using namespace sf;
using namespace std;
class Menu
{
	RenderWindow * window;
	Font * fontPointer;
	list<Text *> textVector;
	list<Text*> TextList;
	Color hoverColor;
	Color defaultColor;

	Event events;

	bool clicked;

	Image * titleImage = nullptr;
	Texture texture;
	Sprite * sprite;

	Background * background;

	int optionUpdate();
public:
	Menu()
	{
	}

	Menu(RenderWindow * renderTarget, Font * font);

	static enum Colours{Hover = 0x01, Default = 0x02};

	void setFont(Font * font);
	void addOption(string newOption);
	void addText(string newText, int size);
	void addImage(Image * title);
	void changeText(string text);

	void setColor(Color color, Colours flag);
	
	int pollMenu();
	void Draw();
	~Menu()
	{
		for (auto elem : textVector)
			delete elem;
	
		for (auto elem : TextList)
			delete elem;

		delete background;
		delete sprite;
	}
};