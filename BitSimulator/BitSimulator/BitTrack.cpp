#include "BitTrack.h"

sf::Texture *Track::texture = new sf::Texture;
sf::RenderWindow *Track::window = 0;
int Track::trackHeight = 0;

Bit::Bit(Texture &text) : Sprite(text)
{
	FloatRect rect = getLocalBounds();
	setOrigin(Vector2f(rect.width / 2, rect.height / 2));
	Locked = false;
	Moved = false;
	Entering = false;
	Leaving = false;
	value = true;
	startedEntering = false;
	state = Event::None;
}

void Bit::setHeight(const int level)
{
	Vector2f vec = getPosition();
	setPosition(vec.x, level);
}

void Bit::getBack()
{
	currentHeight = previousHeight;
	FloatRect bitRect = getGlobalBounds();
	setPosition(bitRect.left, previousHeight);
}

void Bit::attachToTrack(Track * track)
{
	currTrack = track;
	Vector2f temp = getPosition();
	setPosition(temp.x, track->level);
	track->setValue(this->value);
}


int Bit::Update()
{
	if (value)
		setColor(Color::Red);
	else 
		setColor(Color::Blue);
	
	Vector2f scale = getScale();
	if (Entering) 
	{
		if (scale.x >= 0.1)
		{
			setScale(scale.x - 0.03, scale.x - 0.03);
			if (startedEntering)
				startedEntering = false;
			else
				state = Event::None;
		}
		else
		{
			setScale(0.00, 0.00);
			Entering = false;
			Leaving = true;
			
			if (propagateObject->Propagate())
				state = Event::CorrectPropagation;

			else state = Event::IncorrectPropagation;

			attachToTrack(propagateObject->OutputTrack());
		}
	}
	else if (Leaving) 
	{
		if (scale.x < 1.0)
		{
			setScale(scale.x + 0.03, scale.x + 0.03);
			state = Event::None;
		}
		else 
		{
			setScale(1.0, 1.0);
			Leaving = false;
			state = Event::ElemLeft;
		}
	}
	return false;
}

bool Bit::hasMoved()
{
	return Moved;
}

bool Bit::isLocked()
{
	return Locked;
}

bool Bit::isEntering()
{
	return Entering;
}

bool Bit::isLeaving()
{
	return Leaving;
}

bool Bit::isCollecting()
{
	return Collecting;
}

bool Bit::Value()
{
	return value;
}

void Bit::changeValue()
{
	value = !value;
	currTrack->setValue(value);
}

void Bit::EnterLogicElem(LogicElem * object)
{
	propagateObject = object;
	Entering = true;
	startedEntering = true;
	state = ElemEntered;
}



void Track::Cut(Track * track)
{
	track->end = true;
}

Track * Track::startNewTrack(int height, int level, bool mod, bool value)
{
	return new Track(height, mod, value, 1100);
}

bool Track::getValue(void) const
{
	return val;
}

Track::Track(int lvl, bool alter, bool value, int border_left)
{
	dims.b_left = border_left;
	dims.b_right = window->getSize().x + 50;
	mod = alter;
	val = value;
	level = lvl;
	sprite.setTexture(*texture);
	sprite.setTextureRect(IntRect(0, 0, dims.b_left - dims.b_right, trackHeight));
	sprite.setOrigin(0, trackHeight / 2);
	sprite.setPosition((float)border_left, level);
}

void Track::SetTexture(std::string & path)
{
	texture->loadFromFile(path);
	texture->setSmooth(true);
	texture->setRepeated(true);
	trackHeight = texture->getSize().y;
}

void Track::SetWindowPointer(RenderWindow * render)
{
	window = render;
}

bool Track::canBitAttach(Bit * bitPointer)
{
	FloatRect bitRect = bitPointer->getGlobalBounds();
	return bitRect.left > dims.b_left && bitRect.left + bitRect.width < dims.b_right;
}

void Track::Update(float offset)
{
	if (end)
	{
		dims.b_left -= offset;
		dims.b_right -= offset;
	}
	else
		dims.b_left -= offset;
	if (val)
		sprite.setColor(Color::Red);
	else
		sprite.setColor(Color::Yellow);

	sprite.setTextureRect(IntRect(0, 0, dims.b_right - dims.b_left, trackHeight));
	sprite.move(-offset, 0);
}

void Track::setValue(const bool & value)
{
	val = value;
}

bool Track::toDelete()
{
	return dims.b_right < 0;
}

void LevelManager::ReadLevel(int levelNumber)
{
	string temp("Level");
	temp += levelNumber;
	temp = temp + ".txt";
}
