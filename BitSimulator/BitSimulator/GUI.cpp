#include "GUI.h"

Buffer::Buffer(int cap, int x, int y, int w, int h)
{
	load = 0;
	capacity = cap;
	dim.left = x;
	dim.top = y;
	dim.width = w;
	dim.height = h;

	flashcounter = 0;
	flowdim.left = dim.left + 5;
	flowdim.width = dim.width - 10;

}

void Buffer::SetAlert(bool state)
{
	alerted = state;
}


int Buffer::GetFullfillment()
{
	return load;
}

bool Buffer::Load(int value)
{
	load += value;
	return (load > capacity);
}

void Buffer::Draw()
{

	if (alerted)
	{
		if (flashcounter < 30)
			layout.setFillColor(sf::Color::Red);
		else if (flashcounter < 60)
			layout.setFillColor(sf::Color::Black);
		else
			flashcounter = 0;
	}

	window->draw(layout);
	window->draw(fill);
}

void VerticalBuffer::Refactor()
{
	float res = load / capacity;
	if (res < 0.15f)
		fill.setFillColor(sf::Color(255, 0, 0));

	else if (res < 0.3f)
		fill.setFillColor(sf::Color(205, 85, 0));

	else if (res < 0.45f)
		fill.setFillColor(sf::Color(255, 165, 0));

	else if (res < 0.6f)
		fill.setFillColor(sf::Color(255, 255, 0));

	else if (res < 0.75f)
		fill.setFillColor(sf::Color(159, 251, 136));

	else if (res < 1.0f)
		fill.setFillColor(sf::Color(0, 255, 0));


	flowdim.height = res * dim.height;
	flowdim.top = dim.top + dim.height - flowdim.height -5;
}


InfoGiver::InfoGiver(int x, int y, int w, int h) :text_tab(NULL)
{
	black_back.setPosition(x, y);
	black_back.setSize(sf::Vector2f(w, h));
	black_back.setFillColor(sf::Color::Black);
}
