#include "GUI.h"

Battery::Battery(sf::RenderWindow * window, int l, int c, std::string path, int xpos, int ypos)
{
	renderTarget = window;
	load = 0;
	cap = c;
	Image temp;
	temp.loadFromFile(txtpath + "battery.png");
	temp.createMaskFromColor(Color(255, 0, 255));

	texture.loadFromImage(temp);
	texture.setSmooth(true);
	batSize = texture.getSize();

	filling.setSize(Vector2f(0,0));
	filling.setPosition(16, 16);
	batSprite.setTexture(texture, true);
	batSprite.setPosition(16, 16);
	Load(l);
}

void Battery::Load(int load_inc)
{

	if (load < cap && (load + load_inc) >= cap)
		load = cap;

	else if (load + load_inc < cap)
		load += load_inc;

	float coeff = (float)load / (float)cap;
	
	if (coeff < 0.3f)
		fillColor = Color::Red;
	else if (coeff < 0.7)
		fillColor = Color::Yellow;
	else
		fillColor = Color::Green;
	
	filling.setSize(Vector2f(coeff * batSize.x, batSize.y));
	filling.setFillColor(fillColor);
}

void Battery::Dissipate(int load_dnc)
{
	if (load > 0 && (load - load_dnc) < 0)
		load = 0;

	else if (load - load_dnc > 0)
		load -= load_dnc;

	float coeff = (float)load / (float)cap;

	if (coeff < 0.3f)
		fillColor = Color::Red;
	else if (coeff < 0.7)
		fillColor = Color::Yellow;
	else
		fillColor = Color::Green;

	filling.setSize(Vector2f(coeff * batSize.x, batSize.y));
	filling.setFillColor(fillColor);
}

void Battery::Draw()
{
	renderTarget->draw(filling);
	renderTarget->draw(batSprite);
}

Score::Score(sf::RenderWindow * window_context, sf::Font * font): 
	t_score(sf::Text("Score:", *font, 50)), 
	t_points(sf::Text("999999", *font, 50))
{
	window = window_context;
	this->font = font;

	sf::FloatRect temp1 = t_points.getGlobalBounds();
	t_points.setOrigin(sf::Vector2f(temp1.left + temp1.width+10, 0));
	sf::Vector2u w_size = window_context->getSize();
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
