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
	for (auto it = textVector.rbegin(); it != textVector.rend(); ++it)
	{
		textRect = (*it)->getGlobalBounds();
		(*it)->setPosition(textRect.left, border - textRect.height);
		border -= (textRect.height + 10);
	}
}

void Menu::addText(string newText, int size)
{
	String temp(newText);
	Text * text = new Text(temp, *fontPointer, size);

	TextList.push_back(text);

	FloatRect textRect = text->getGlobalBounds();
	Vector2u windowSize = window->getSize();
	text->setPosition((windowSize.x / 2.0f) - (textRect.width / 2.0f), 0);

	int border = windowSize.y / 2.0f + 20;
	for (auto it = TextList.rbegin(); it != TextList.rend(); ++it)
	{
		textRect = (*it)->getGlobalBounds();
		(*it)->setPosition(textRect.left, border - textRect.height);
		border -= (textRect.height + 50);
	}
}

void Menu::addImage(Image* title)
{
	titleImage = new Image();
	titleImage = title;
	texture.loadFromImage(*title);
	sprite = new Sprite();
	sprite->setTexture(texture);
	sprite->scale(0.7f, 0.7f);

	FloatRect spriteRect = sprite->getGlobalBounds();
	Vector2u windowSize = window->getSize();

	sprite->setPosition((windowSize.x / 2.0f) - (spriteRect.width / 2.0f), 100);

}

void Menu::changeText(string newtext)
{
	String temp(newtext);
	Text * text = new Text(temp, *fontPointer, 60);

	CounterList.push_back(text);

	FloatRect textRect = text->getGlobalBounds();
	Vector2u windowSize = window->getSize();
	text->setPosition((windowSize.x / 2.0f) - (textRect.width / 2.0f), (windowSize.y / 2.0f) - (textRect.height/2.0f));
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
	background = new Background();
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
		background->Update();
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
	clicked = false;
	return -1;
}

void Menu::DrawCounter()
{
	window->clear();
	for(auto text : CounterList)
	{
		window->draw(*text);
		window->display();
		sleep(milliseconds(1000));
		window->clear();
	}
}

void Menu::Draw()
{
	window->draw(*background);
	if (titleImage != nullptr)
	{
		window->draw(*sprite);
	}
	for (auto text : textVector)
	{
		window->draw(*text);
	}
	for (auto text : TextList)
	{
		window->draw(*text);
	}
	window->display();
}