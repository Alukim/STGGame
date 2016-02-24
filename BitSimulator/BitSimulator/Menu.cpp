#include "Menu.h"
Menu::Menu(sf::RenderWindow *render, Font *fp)
{
	window = render;
	f = fp;
	current = 0;
	_opts = 0;
	_oprt_size.left = 0;
	_oprt_size.top = 0;
	_oprt_size.width = render->getSize().x;
	_oprt_size.height = render->getSize().y;
}

void Menu::AddNewOption(std::string n)
{
	Text temp(String(n), *f, 100);
	temp.setColor(normalview);
	opts.push_back(temp);
	_opts++;
	int i = 0;
	std::list<Text>::iterator titer = opts.begin();
	for (titer; titer != opts.end(); titer++)
	{
		FloatRect frtemp = titer->getGlobalBounds();
		titer->setPosition(sf::Vector2f((_oprt_size.width - frtemp.width) / 2, _oprt_size.height * i / _opts));
		i++;
	}
}

void Menu::SetBounds(int xpos, int ypos, int w, int h)
{
	_oprt_size.left = xpos;
	_oprt_size.top = ypos;
	_oprt_size.width = w;
	_oprt_size.height = h;
}


void Menu::SetColors(sf::Color ncolor, sf::Color hcolor)
{
	hoverview = hcolor;
	normalview = ncolor;
}

int Menu::Update(sf::Event &ev)
{
	int i = 0;
	std::list<Text>::iterator titer = opts.begin();
	if (normalview == hoverview)
	{
		for (titer; titer != opts.end(); titer++)
			titer->setColor(normalview);
		titer->setColor(hoverview);
	}
	titer = opts.begin();
	if (ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::Up)
		{
			if (current > 0)
				current--;
		}
		else if (ev.key.code == sf::Keyboard::Down)
		{
			if (current < _opts - 1)
				current++;

		}
		else if (ev.key.code == sf::Keyboard::Return)
			return current;
	}
	else if (ev.type == sf::Event::MouseMoved)
	{
		for (titer; titer != opts.end(); titer++)
		{
			sf::Vector2i mouse = sf::Mouse::getPosition(*window);
			sf::FloatRect fl = titer->getGlobalBounds();
			titer->setColor(normalview);

			if (Intersect(fl, mouse)) // if mouse hovers on an option
				current = i; // set new hovered option

			i++;
		}
	}
	else if (ev.type == sf::Event::MouseButtonPressed)
	{
		if (ev.mouseButton.button == sf::Mouse::Left)
			return current;
	}
	return -1;
}

void Menu::Draw()
{
	int i = 0;
	std::list<Text>::iterator titer = opts.begin();
	for (titer; titer != opts.end(); titer++)
	{
		if (i != current)
			titer->setColor(normalview);
		else
			titer->setColor(hoverview);

		window->draw(*titer);
		i++;
	}
}
Menu::~Menu()
{
	opts.clear();
}
