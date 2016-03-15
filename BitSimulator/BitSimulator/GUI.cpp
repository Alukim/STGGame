#include "GUI.h"
#include "Utilities.h"



Battery::Battery(sf::RenderWindow * window, int l, int c, std::string path, int xpos, int ypos)
{
	prevheight = 1000;
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

	Refactor();
}



void Battery::Refactor()
{
	sf::Vector2u dim = batimg.getSize(); // dimensions of image

	sf::Color prob; // keeps tempoporary colour of pixel

	float res = (float)load / cap; // fullfillment ratio


	sf::Color fill;	// colour which the battery will be filled with


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
	
	if (load < cap && (load + load_inc) >= cap)
	{
		load = cap;
		Refactor();
		change = true;
	}
	else if(load + load_inc < cap)
	{
		load += load_inc;
		Refactor();
		change = true;
	}	
}

void Battery::Dissipate(int load_dnc)
{
	change = true;

	if (load > 0 && (load - load_dnc) < 0)
	{
		load -= load_dnc;
		load = 0;
		Refactor();
	}
	else if (load == 0)
	{
		change = false;
	}
	else
	{
		load -= load_dnc;
		Refactor();
	}
}

void Battery::Draw()
{

	if (waver == 31) waver = 0;
	if (waver == 0 || waver == 16)	change = true;
	if (change)
	{
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

sf::Vector2f Points_class::set_position()
{
	int pos_x, pos_y;

	sf::Vector2u curr_mode = ref->getSize();
	int screen_x = curr_mode.x;
	int screen_y = curr_mode.y;

	int x = (15 * text.getCharacterSize()) / 25;

	pos_x = screen_x - (7 * x /*Points:*/ + 7 * x /*ilosc pkt*/);
	pos_y = screen_y / 100;


	return sf::Vector2f(pos_x, pos_y);
}

Points_class::Points_class(sf::RenderWindow * window, sf::Font * font_)
{
	this->ref = window;
	this->points = 0;
	this->change = true;
	font = font_;

	text.setFont(*font);
	text.setPosition(set_position());
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

ParticleSystem::ParticleSystem(unsigned int count) :
	m_particles(count),
	m_vertices(sf::Points, count),
	m_lifetime(sf::seconds(3)),
	m_emitter(0, 0)
{
}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

void ParticleSystem::update(sf::Time elapsed)
{
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// update the position of the corresponding vertex
		m_vertices[i].position += p.velocity * elapsed.asSeconds();

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
		m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}

void ParticleSystem::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	target.draw(m_vertices, states);
}