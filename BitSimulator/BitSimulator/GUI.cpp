#include "GUI.h"
#include "Utilities.h"


InfoGiver::InfoGiver(int x, int y, int w, int h) :text_tab(NULL)
{
	black_back.setPosition(x, y);
	black_back.setSize(sf::Vector2f(w, h));
	black_back.setFillColor(sf::Color::Black);
}

void Battery::Refactor()
{
	sf::Vector2u dim = img.getSize(); // dimensions of image

	sf::Color prob; // keeps tempoporary colour of pixel

	float res = (float)load / cap; // fullfillment ratio


	sf::Color fill;	// colour battery will be filled with


	// estimating fill colour
	if (res < 0.15f)		fill = sf::Color::Red;
	else if (res < 0.4f)	fill = sf::Color(255, 165, 0);
	else if (res < 0.7f)	fill = sf::Color::Yellow;
	else					fill = sf::Color::Green;


	// height the coulouring begin with
	int href = (int)((1 - res) * dim.y);

	// colouring loop
	for (int posx = 0; posx < dim.x; posx++)
	{
		for (int posy = 0; posy < dim.y; posy++)
		{
			prob = img.getPixel(posx, posy);

			if (posy < href) // colours the transparent section of battery
			{

				if (prob != sf::Color(254, 0, 0) && prob != sf::Color::Black && prob != sf::Color(200, 200, 200, 0))
					img.setPixel(posx, posy, sf::Color::Transparent);
			}
			else // colours fill section of battery
			{

				if (prob != sf::Color(254, 0, 0) && prob != sf::Color::Black && prob != sf::Color(200, 200, 200, 0))
					img.setPixel(posx, posy, fill);
			}
		}
	}
	sf::Texture * _ptr = new sf::Texture;
	_ptr->loadFromImage(img);

	sprite.setTexture(*_ptr);
}

Battery::Battery(sf::RenderWindow * window, int l, int c, std::string path)
{
	change = true;
	waver = 0;
	ref = window;
	load = l;
	cap = c;

	img.loadFromFile(path);
	img.createMaskFromColor(sf::Color(200, 200, 200));


	sf::Texture * ptr = new sf::Texture;
	ptr->loadFromImage(img);

	sprite.setTexture(*ptr);

	sprite.setPosition(sf::Vector2f(100, 100));
}

void Battery::Load(int load_inc)
{
	change = true;
	load += load_inc;
	if (load >= cap)
		load = cap;
	else
		waver = 0;
}

void Battery::Dissipate(int load_dnc)
{
	change = true;
	load -= load_dnc;
	if (load < 0)
		load = 0;
}

void Battery::Draw()
{
	
	if (waver == 31) waver = 0;
	if (waver == 0 || waver == 16)	change = true;
	if (change)
	{
		Refactor();

		sf::Vector2u dim = img.getSize();
		if (load == cap)
		{
			if (waver < 15)
			{
				for (int posx = 0; posx < dim.x; posx++)
				{
					for (int posy = 0; posy < dim.y; posy++)
					{
						sf::Color temp = img.getPixel(posx, posy);
						if (temp == sf::Color::Black)
							img.setPixel(posx, posy, sf::Color(254, 0, 0));
					}
				}
			}
			else if (waver < 30)
			{
				for (int posx = 0; posx < dim.x; posx++)
				{
					for (int posy = 0; posy < dim.y; posy++)
					{
						if (img.getPixel(posx, posy) == sf::Color(254, 0, 0))
							img.setPixel(posx, posy, sf::Color::Black);
					}
				}
			}
		}
		else	ChangeColor(&img, sf::Color(254, 0, 0), sf::Color::Black);

		sf::Texture *ptr = new sf::Texture;
		ptr->loadFromImage(img);
		sprite.setTexture(*ptr);
	}
	waver++;
	ref->draw(sprite);
	change = false;
}
