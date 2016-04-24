#include "BitTrack.h"

sf::Texture Track::texture = sf::Texture();


Track::Track(sf::RenderWindow *win,  float y)
{
	window = win;		// sets window pointer
	bitptr = NULL;		// sets bit pointer to null (no bit set on track)
	events = None;

	sf::Vector2u size = window->getSize();
	Timer.restart();

	h_offset = y;	// height which track begin with
	length = size.x;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, size.x, texture.getSize().y));
	sprite.setPosition(sf::Vector2f(0, h_offset));
}

void Track::Attach(Bit * ptr)
{
	bitptr = ptr;
	sf::FloatRect pos = sprite.getGlobalBounds();
	value = bitptr->GetState();
	bitptr->SetPosition((pos.width * 0.5F), pos.top + pos.height/2);
}

void Track::SetTexture(std::string &path)
{
	texture.loadFromFile(path);
	texture.setRepeated(true);
}

void Track::Detach()
{
	bitptr = NULL;
	value = false;
}

GameObject *Track::Update(float off)
{
		sf::FloatRect rect;
		GameObject *temp = 0;
		events = TrackEvents::No_Bit;
		draw_list.remove_if([](GameObject* x) { return (x->GetLayout().left + x->GetLayout().width < 0); });
		if(Timer.getElapsedTime().asMicroseconds() > Tick)
		{ 
			for (auto elem : draw_list)
			{
				elem->Move(-off, 0);
				rect = elem->GetLayout();

				if (rect.left + rect.width < 0)
				{
					draw_list.remove(elem);
					break;
				}
				// checking only if bit is on the track
				if (bitptr)
				{
					bitptr->Update();
					// checks for interaction of bit and track element
					events = TrackEvents::None;
					sf::FloatRect fl = bitptr->GetLayout();
					if (Intersect(fl, rect))
					{
						if (Volt *v = dynamic_cast<Volt *>(elem))
						{
							if (v->isVisible())
								events = TrackEvents::VBonusHit;
						}
						else if (dynamic_cast<Amper *>(elem))
							events = TrackEvents::ABonusHit;

						else if (dynamic_cast<LogicElem *>(elem))
							events = TrackEvents::Elem_Entered;
						temp = elem;
					}
				}
			}
			Timer.restart();
		}
		return temp;
}

void Track::AddElem(GameObject *new_elem)
{

	sf::FloatRect pos = sprite.getGlobalBounds();

	new_elem->SetPosition(pos.width, pos.top);

	draw_list.push_back(new_elem);
}

GameObject * Track::GetElem()
{
	return (*draw_list.begin());
}

void Track::Draw()
{
	if (value)
		sprite.setColor(sf::Color(0,150,0));
	else
		sprite.setColor(sf::Color(150,0,0));
	window->draw(sprite);

	if (bitptr)		
		bitptr->Draw();

	for (auto temp : draw_list)
	{
		temp->Draw();
	}

}

Bit::Bit(sf::RenderWindow *& render_target, std::string & path)
	: GameObject(render_target, path, sf::Color(255,0,255))
{
	Collecting = false;
	Entering = false;
	Leaving = false;
	State = false;
	Locked = false;
	sf::FloatRect rect = sprite.getGlobalBounds();
	sprite.setOrigin(Vector2f(rect.width / 2, rect.height / 2));
}

void Bit::ChangeState()
{
	if (State = !State)
		setColor(sf::Color::Green);
	else
		setColor(sf::Color::Cyan);
}

void Bit::SetState(bool state)
{
	if (State = state)	setColor(sf::Color::Green);
	else				setColor(sf::Color::Cyan);
}

bool Bit::GetState()
{
	return State;
}

void Bit::EnterGate(LogicElem * elem)
{
	if (prop != elem)
	{
		prop = elem;
		Entering = true;
		Locked = true;
	}
}

void Bit::LeaveGate()
{
	if (prop)
	{
		Leaving = true;
	}
}

bool Bit::Propagate()
{
	if (Entering)
	{
		bool x = prop->Propagate();
		prop = NULL;
		Entering = false;
		return x;
	}
}

void Bit::setCollectingState(bool state)
{
	Collecting = state;
}

bool Bit::isCollecting()
{
	return Collecting;
}

bool Bit::isLocked()
{
	return Locked;
}

bool Bit::Update()
{
	if (Timer.getElapsedTime().asMilliseconds() > Tick)
	{
		sf::Vector2f vec = sprite.getScale();
		if (Entering && vec.x > 0.1f)
		{
			sprite.setScale(sf::Vector2f(vec.x - 0.045f, vec.y - 0.045f));
		}
		else if (Leaving)
		{
			
			sprite.setScale(sf::Vector2f(vec.x + 60.0F / 1000, vec.y + 60.0F / 1000));
			if (vec.x >= 1)
			{
				Leaving = false;
				Locked = false;
				sprite.setScale(sf::Vector2f(1, 1));
			}
		}
		Timer.restart();
	}
	return false;
}

void Bit::Draw()
{
	if (sprite.getScale().x > 0.1f)
		window->draw(sprite);
}
