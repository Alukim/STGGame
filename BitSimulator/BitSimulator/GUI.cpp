#include "GUI.h"
#include "Utilities.h"



Battery::Battery(sf::RenderWindow * window, int l, int c, std::string path, int xpos, int ypos)
{
	change = true;
	waver = 0;
	ref = window;
	load = l;
	cap = c;
	diff = 0;

	batimg.loadFromFile(path);
	batimg.createMaskFromColor(sf::Color(255, 0, 255));
	prevheight = batimg.getSize().y;

	battxt.loadFromImage(batimg);
	battxt.setSmooth(true);
	
	batsprite.setTexture(battxt);
	batsprite.setPosition(sf::Vector2f(xpos, ypos));

	Refactor();
}



void Battery::Refactor()
{
	static sf::Color prev_col = sf::Color::Black;
	sf::Vector2u dim = batimg.getSize(); // dimensions of image

	sf::Color prob; // keeps tempoporary colour of pixel

	float res = (float)load / cap; // fullfillment ratio


	sf::Color fill;	// colour which the battery will be filled with

	// estimating fill colour
	if (res < 0.3f)			fill = sf::Color::Red;
	else if (res < 0.6f)	fill = sf::Color(255, 165, 0);
	else if (res < 0.8f)	fill = sf::Color::Yellow;
	else					fill = sf::Color::Blue;

	// height the coulouring begin with (downwards)
	int href = (int)((1 - res) * dim.y);

	// colouring loops
	if (href != prevheight) {
		if (href > prevheight) {
			for (int posx = 0; posx < dim.x; posx++) {

				// gets pixel from (posx, posy) position and colours it to the transparent one
				for (int posy = prevheight; posy < href; posy++) {
					prob = batimg.getPixel(posx, posy);
					if (prob != sf::Color::Black && prob != sf::Color(210, 154, 46))
						batimg.setPixel(posx, posy, sf::Color::Transparent);
				}
			}
		}
		else {
			int end;
			// if colour has changed, whole colour section needs to be redrawn
			if (prev_col != fill) end = dim.y;
			else	end = prevheight;

			for (int posx = 0; posx < dim.x; posx++) {
				// gets pixel from (posx, posy) position and colours it to the fill colour one
				for (int posy = href; posy < end; posy++) {
					prob = batimg.getPixel(posx, posy);
					if (prob != sf::Color::Black && prob != sf::Color(210, 154,46))
						batimg.setPixel(posx, posy, fill);
				}
			}
		}
		// updates the texture, battery ready to be drawn
		prevheight = href;
		battxt.update(batimg);
	}
}

void Battery::Load(int load_inc)
{
	diff += load_inc;

	if (load < cap && (load + load_inc) >= cap)
		load = cap;

	else if (load + load_inc < cap)
		load += load_inc;

	if (diff > 15) {
		Refactor();
		diff = 0;
	}
}

int Battery::Dissipate(int load_dnc)
{
	diff -= load_dnc;
	if (load > 0 && (load - load_dnc) < 0)
		load = 0;

	else if (load - load_dnc > 0)
		load -= load_dnc;

	if (diff < -15)
	{
		Refactor();
		diff = 0;
	}
	return load;
}

void Battery::Draw()
{
	ref->draw(batsprite);
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

Score::Score(sf::RenderWindow * window_context, sf::Font * font): 
	t_score(sf::Text("Score:", *font, 50)), 
	t_points(sf::Text("999999", *font, 50))
{
	window = window_context;
	this->font = font;

	sf::FloatRect temp1 = t_points.getGlobalBounds();
	t_points.setOrigin(sf::Vector2f(temp1.left + temp1.width+10, 0));
	Vector2u w_size = window_context->getSize();
	t_points.setPosition(sf::Vector2f(w_size.x-20, 0));

	sf::FloatRect temp2 = t_score.getGlobalBounds();
	t_score.setOrigin(sf::Vector2f(temp2.left + temp2.width + 10, 0));
	t_score.setPosition(sf::Vector2f(w_size.x - temp1.width - 30, 0));
	t_points.setString("0");
	
}

void Score::Add(int inc)
{
	q_points += inc;
	t_points.setString(std::to_string(q_points));
}

void Score::Draw()
{
	window->draw(t_score);
	window->draw(t_points);
}
