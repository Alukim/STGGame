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
	width = (int)sprite.getGlobalBounds().width;
}

void Track::Attach(GameObject * ptr)
{
	bitptr = ptr;
	sf::FloatRect pos = sprite.getGlobalBounds();

	bitptr->SetPosition((int)(pos.width * 0.03f), (int)pos.top);
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
		(*it)->Move(-3, 0);
	}
	sprite.move(sf::Vector2f(-2, 0));
	if (offset.x > width)
		offset.x = 0;

	if (bitptr && draw_list.size() != 0)
	{
		Volt *ptr0 = 0;
		if (ptr0 = dynamic_cast<Volt*>(*draw_list.begin()))
		{
			if (Intersect(bitptr->GetLayout(), ptr0->GetLayout()))
				return VBonusHit;
		}
		else
		{
			Amper *ptr1 = 0;
			if (ptr1 = dynamic_cast<Amper*>(*draw_list.begin()))
			{
				if (Intersect(bitptr->GetLayout(), ptr1->GetLayout()))
					return ABonusHit;
			}
			else
			{
			}
		}
	}
	return 0;
}

void Track::AddElem(GameObject * new_elem)
{

	sf::FloatRect pos = sprite.getGlobalBounds();

	new_elem->SetPosition(1200/*pos.left + pos.width*/, (int)pos.top);

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
	sprite.setPosition(sf::Vector2f(width - offset.x+1, offset.y));
	window->draw(sprite);

	if (bitptr)		bitptr->Draw();


	std::list<GameObject *>::iterator it = draw_list.begin();
	for (it; it != draw_list.end(); it++)
	{
		(*it)->Draw();
	}
}

Tracklist::Tracklist(sf::RenderWindow *window)
{
	size = 5;
	track_num = 0;
	list = new Track*[size];

	bit = new GameObject(window, txtpath + "bit.png", sf::Color(255, 0, 255));

	counter = 0;
	AddTrack(new Track(window, txtpath + "track.png", 0, 200), 0);
	AddTrack(new Track(window, txtpath + "track.png", 50, 285), 1);
	AddTrack(new Track(window, txtpath + "track.png", 115, 370), 2);
	AddTrack(new Track(window, txtpath + "track.png", 200, 455), 3);
	AddTrack(new Track(window, txtpath + "track.png", 0, 540), 4);

	list[0]->Attach(bit);

	volts = new Battery(window, 0, 5000, txtpath + "Baterry/bat.png");
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
	int temp = 0;
	for (int i = 0; i < size; i++)
	{
		if (list[i])
		{
			switch (list[i]->Update())
			{
				// loading battery with bonus volt amount
			case Events::VBonusHit:
				temp = ((Volt *)list[i])->GetBonus();
				volts->Load(temp);
				(list[i]->draw_list).pop_front();
				break;

				// loading battery with bonus amper amount
			case Events::ABonusHit:
				((Amper *)list[i]->GetElem())->GetBonus();
				list[i]->draw_list.pop_front();
				break;

				// bit annihilation - gets to nearest checkpoint or ends the run
			case Events::Bit_Annihillated:
				break;

				// logic element entered
			case Events::Elem_Entered:
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
		list[track_num + 1]->Attach(temp);
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

