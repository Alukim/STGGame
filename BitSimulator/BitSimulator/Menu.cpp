#include "Menu.h"

void Menu::addOption(string newOption)
{
	String temp(newOption);
	Text * newText = new Text(temp, *fontPointer, 40);

	textVector.push_back(newText);

	FloatRect textRect = newText->getGlobalBounds();
	Vector2u windowSize = window->getSize();
	newText->setPosition(windowSize.x - (textRect.width+10), 0);

	int border = windowSize.y - 10;
	for (auto it = textVector.rbegin(); it != textVector.rend(); it++)
	{
		textRect = (*it)->getGlobalBounds();
		(*it)->setPosition(textRect.left, border - textRect.height);
		border -= (textRect.height + 10);
	}
}

void Menu::setFont(Font * font)
{
	fontPointer = font;
	hoverColor = Color::Red;
	defaultColor = Color::White;
}

Menu::Menu(RenderWindow * renderTarget, Font * font)
{
	window = renderTarget;
	fontPointer = font;
	hoverColor = Color::Red;
	defaultColor = Color::White;
}

int Menu::pollMenu()
{
	int result = 0;
	while (window->isOpen())
	{
		while (window->pollEvent(events))
		{
			if (events.type == Event::Closed)
				window->close();

			else if (events.type == Event::MouseButtonPressed && events.mouseButton.button == Mouse::Left)
				clicked = true;
		}

		result = optionUpdate();

		if (result != -1)
			return result;
		Draw();
	}
	return -1;
}


void Menu::setColor(Color color, Colours flag)
{
	if (flag & Colours::Hover)
		hoverColor = color;

	if (flag & Colours::Default)
		defaultColor = color;
}
int Menu::optionUpdate()
{
	int optionIndex = 0;
	FloatRect textRect;
	Vector2f mousePos;

	for (auto text : textVector)
	{
		textRect = text->getGlobalBounds();
		mousePos = Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
		if (textRect.contains(mousePos))
		{
			if (clicked)
				return optionIndex;
			else
				text->setColor(hoverColor);
		}
		else
			text->setColor(defaultColor);

		++optionIndex;
	}
	return -1;
}

void Menu::Draw()
{
	window->clear();
	for (auto text : textVector)
	{
		window->draw(*text);
	}
	window->display();
}