#pragma once
#include <SFML\Graphics.hpp>
#include <list>
#include <string>
using namespace sf;
using namespace std;
class Menu
{
	RenderWindow * window;
	Font * fontPointer;
	list<Text *> textVector;
	Color hoverColor;
	Color defaultColor;

	Event events;

	bool clicked;

	int optionUpdate();
public:
	Menu()
	{
	}

	Menu(RenderWindow * renderTarget, Font * font);

	static enum Colours{Hover = 0x01, Default = 0x02};

	void setFont(Font * font);
	void addOption(string newOption);
	
	void setColor(Color color, Colours flag);
	
	int pollMenu();
	void Draw();
	~Menu()
	{
		for (auto elem : textVector)
			delete elem;
	}
};