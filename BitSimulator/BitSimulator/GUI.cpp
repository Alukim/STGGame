#include "GUI.h"
#include "Utilities.h"



Battery::Battery(sf::RenderWindow * window, int l, int c, std::string path, int xpos, int ypos)
{
	change = true;
	waver = 0;
	ref = window;
	load = l;
	cap = c;

	batimg.loadFromFile(path);
	batimg.createMaskFromColor(sf::Color(200, 200, 200));

	sf::Texture * battxt = new sf::Texture;
	battxt->loadFromImage(batimg);

	batsprite.setTexture(*battxt);
	batsprite.setPosition(sf::Vector2f(xpos, ypos));

	lightimg.loadFromFile("Resource/Textures/Baterry/piorun2.png");
	lightimg.createMaskFromColor(sf::Color(255, 0, 255));

	sf::Texture *lighttxt = new sf::Texture;
	lighttxt->loadFromImage(lightimg);
	lightsprite.setTexture(*lighttxt);

	sf::FloatRect temp = batsprite.getGlobalBounds();
	lightsprite.setPosition(sf::Vector2f(xpos, ypos));

	batsprite.setScale(sf::Vector2f(0.5f, 0.5f));
	lightsprite.setScale(sf::Vector2f(0.5f, 0.5f));
}



void Battery::Refactor()
{
	sf::Vector2u dim = batimg.getSize(); // dimensions of image

	sf::Color prob; // keeps tempoporary colour of pixel

	float res = (float)load / cap; // fullfillment ratio


	sf::Color fill;	// colour battery will be filled with


					// estimating fill colour
	if (res < 0.3f)		fill = sf::Color::Red;
	else if (res < 0.6f)	fill = sf::Color(255, 165, 0);
	else if (res < 0.8f)	fill = sf::Color::Yellow;
	else					fill = sf::Color::Green;


	// height the coulouring begin with
	int href = (int)((1 - res) * dim.y);

	// colouring loop
	for (int posx = 0; posx < dim.x; posx++)
	{
		for (int posy = 0; posy < dim.y; posy++)
		{
			prob = batimg.getPixel(posx, posy);

			if (posy < href) // colours the transparent section of battery
			{

				if (prob != sf::Color(254, 0, 0) && prob != sf::Color::Black && prob != sf::Color(200, 200, 200, 0))
					batimg.setPixel(posx, posy, sf::Color::Transparent);
			}
			else // colours fill section of battery
			{

				if (prob != sf::Color(254, 0, 0) && prob != sf::Color::Black && prob != sf::Color(200, 200, 200, 0))
					batimg.setPixel(posx, posy, fill);
			}
		}
	}
	sf::Texture * _ptr = new sf::Texture;
	_ptr->loadFromImage(batimg);

	batsprite.setTexture(*_ptr);
}

void Battery::Load(int load_inc)
{
	change = true;
	load += load_inc;
	if (load >= cap)
	{
		load = cap;
		change = false;
	}
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

		sf::Vector2u dim = batimg.getSize();
		if (load == cap)
		{
			if (waver < 15)
			{
				ChangeColor(&batimg, sf::Color::Black, sf::Color(254, 0, 0));
				ChangeColor(&lightimg, sf::Color::Black, sf::Color(254, 0, 0));
			}

			else if (waver < 30)
			{
				ChangeColor(&batimg, sf::Color(254, 0, 0), sf::Color::Black);
				ChangeColor(&lightimg, sf::Color(254, 0, 0), sf::Color::Black);
			}

		}
		else
		{
			ChangeColor(&batimg, sf::Color(254, 0, 0), sf::Color::Black);
			ChangeColor(&lightimg, sf::Color(254, 0, 0), sf::Color::Black);
		}

		sf::Texture *batptr = new sf::Texture;
		batptr->loadFromImage(batimg);
		batptr->setSmooth(true);
		batsprite.setTexture(*batptr);

		sf::Texture *lightptr = new sf::Texture;
		lightptr->loadFromImage(lightimg);
		lightptr->setSmooth(true);
		lightsprite.setTexture(*lightptr);
	}
	waver++;
	ref->draw(batsprite);
	ref->draw(lightsprite);
	change = false;
}

Points_class::Points_class(sf::RenderWindow * window, sf::Font * font_, int posx, int posy)
{
	this->ref = window;
	this->points = 0;
	this->change = true;

	font = font_;
	//sf::Text * text = new sf::Text;

	text.setFont(*font);
	text.setPosition(posx, posy);
	text.setColor(sf::Color(255, 0, 0));


}

void Points_class::Update(int inc)
{
	points += inc;
	change = true;
}

void Points_class::Draw()
{
	
	if (change)
	{
		s = "Points: " + std::to_string(points);
		text.setString(s);
	}
	ref->draw(text);
	change = false;
}
