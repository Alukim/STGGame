#include "BitTrack.h"

Track::Track(sf::RenderWindow * win, std::string path, int x, int y)
{
	window = win;
	offset.x = x;
	offset.y = y;

	sf::Texture *text = new sf::Texture;

	text->loadFromFile(path);
	text->setSmooth(true);

	bitptr = NULL;

	sprite.setTexture(*text);
	sprite.setPosition(sf::Vector2f(x, y));
	width = sprite.getGlobalBounds().width;
}

void Track::Attach(GameObject * ptr)
{
	bitptr = ptr;
	sf::FloatRect pos = sprite.getGlobalBounds();

	bitptr->SetPosition(pos.width * 0.03, pos.top);
}

GameObject* Track::Detach()
{
	GameObject *get = bitptr;
	bitptr = NULL;
	return get;
}

int Track::Update()
{
	std::list<GameObject *>::iterator it = draw_list.begin();
	offset.x += 2;
	for (it; it != draw_list.end(); it++)
	{
		(*it)->Move(-4, 0);
	}
	sprite.move(sf::Vector2f(-2, 0));
	if (offset.x > width)
		offset.x = 0;

	if (bitptr)
	{
		Volt *ptr0 = 0;
		if (draw_list.size() != 0)
		{
			if (ptr0 = dynamic_cast<Volt*>(*draw_list.begin()))
			{
				if (Intersect(bitptr->GetLayout(), ptr0->GetLayout()))
				{
					//draw_list.pop_front();
					std::cout << "Volt bonus hit" << std::endl;
					return VBonusHit;
				}
			}
			else
			{
				Amper *ptr1 = 0;
				if (ptr1 = dynamic_cast<Amper*>(*draw_list.begin()))
				{
					if (Intersect(bitptr->GetLayout(), ptr1->GetLayout()))
					{
						draw_list.pop_front();
						std::cout << "Amper bonus hit" << std::endl;
						return ABonusHit;
					}
				}
				else
				{

				}
			}
		}
	}
}

void Track::AddElem(GameObject * new_elem)
{

	sf::FloatRect pos = sprite.getGlobalBounds();

	new_elem->SetPosition(1200/*pos.left + pos.width*/, pos.top);

	draw_list.push_back(new_elem);
}

GameObject * Track::GetElem()
{
	return (*draw_list.begin());
}

void Track::Draw()
{
	sprite.setPosition(sf::Vector2f(-offset.x, offset.y));
	window->draw(sprite);
	sprite.setPosition(sf::Vector2f(width - offset.x, offset.y));
	window->draw(sprite);

	if (bitptr)
		bitptr->Draw();

	std::list<GameObject *>::iterator it = draw_list.begin();
	for (it; it != draw_list.end(); it++)
	{
		(*it)->Draw();
	}
}

Tracklist::Tracklist(sf::RenderWindow *window, GameObject * bitptr) : bit(bitptr)
{
	size = 5;
	track_num = 0;
	list = new Track*[size];

	AddTrack(new Track(window, textpath + "track.png", 0, 200), 0);
	AddTrack(new Track(window, textpath + "track.png", -50, 285), 1);
	AddTrack(new Track(window, textpath + "track.png", 0, 370), 2);
	AddTrack(new Track(window, textpath + "track.png", 0, 455), 3);
	AddTrack(new Track(window, textpath + "track.png", 0, 540), 4);

	list[0]->Attach(bitptr);

	volts = new Battery(window, 0, 5000, textpath + "Baterry/bat.png");
	amps = new Battery(window, 0, 5000, textpath + "Battery/bat.png");

}

void Tracklist::AddTrack(Track * track, int pos)
{
	list[pos] = track;
}

void Tracklist::AddElem(GameObject * new_elem, int track)
{
	list[track]->AddElem(new_elem);
}

void Tracklist::Update()
{
	for (int i = 0; i < size; i++)
	{
		if (list[i])
		{
			switch (list[i]->Update())
			{
			case Events::VBonusHit:
				volts->Load(((Volt *)list[i]->GetElem())->GetBonus());
				list[i]->draw_list.pop_front();
				break;

			case Events::ABonusHit:
				((Amper *)list[i]->GetElem())->GetBonus();
				list[i]->draw_list.pop_front();
				break;
			}
		}
	}
}

void Tracklist::BitUp()
{
	if (track_num != 0)
	{
		GameObject *temp = list[track_num]->Detach();
		list[track_num - 1]->Attach(temp);
		track_num--;
	}
}

void Tracklist::BitDown()
{
	if (track_num != 4)
	{
		GameObject * temp = list[track_num]->Detach();
		list[track_num+1]->Attach(temp);
		track_num++;
	}
}

void Tracklist::Draw()
{
	for (int i = 0; i < size; i++)
	{
		if (list[i])
			list[i]->Draw();
	}
	volts->Draw();
}

