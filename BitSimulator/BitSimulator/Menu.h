#pragma once
#include "SFML\Graphics.hpp"
#include <list>

using namespace sf;
class Menu
{
	//> window where menu context is rendered
	sf::RenderWindow *window;

	//> color RGB for normal rendering
	sf::Color normalview;

	//> color RGB to show mouse hovering
	sf::Color hoverview;


	//> borders of menu elements
	sf::IntRect _oprt_size;

	//> number of current option
	int current;

	//> total options number
	int _opts; // ilosc wszystkich opcji

			   //> options list
	std::list<Text> opts;

	//> pointer to font
	Font *f;

	//> Background to be rendered while polling menu
	sf::RectangleShape title;

public:
	//> default constructor
	Menu(sf::RenderWindow *render, Font *fp);

	//> adds new option
	//> /a name - text representing option on the screen
	//> /a font - loaded option font
	void AddNewOption(std::string path);

	//> Sets operational height and width of menu
	//> Elements of menu cannot cross given borders of width and height
	//> By default width and height is set to 800 and 600
	void SetBounds(int xpos, int ypos, int w, int h);

	//> Sets colors of normal and hovering view
	//> if given colours are exactly the same, menu is not modyfying textures
	void SetColors(sf::Color ncolor, sf::Color hcolor);

	//> Sets background of the menu
	void SetBackground(std::string path);
	void SetBackground(sf::Texture *t);
	//> Updates the menu every frame
	//> Switches between options, changes colors and control menu events
	//> Returns number of option choosen by clicking LMB or pressing Enter
	int Update(sf::Event &ev);

	//> Draws menu content on the screen
	void Draw();

	~Menu();
};
