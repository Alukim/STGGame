#include "BitTrack.h"

sf::Texture Track::texture = sf::Texture();


Track::Track(sf::RenderWindow *win,  float y)
{
	window = win;		// sets window pointer
	bitptr = NULL;		// sets bit pointer to null (no bit set on track)
	
	sf::Vector2u size = window->getSize();

	h_offset = y;	// height which track begin with
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, size.x, texture.getSize().y));
	sprite.setPosition(sf::Vector2f(0, h_offset));
}

void Track::Attach(GameObject * ptr)
{
	bitptr = ptr;
	sf::FloatRect pos = sprite.getGlobalBounds();

	bitptr->SetPosition((int)(pos.width * 0.03f), (int)pos.top);
}

void Track::SetTexture(std::string &path)
{
	
	texture.loadFromFile(path);
	texture.setRepeated(true);
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

	for (it; it != draw_list.end(); it++) 
	{
		(*it)->Move(-1, 0);
	}

	if (bitptr && draw_list.size() != 0) {

		GameObject *tempptr = *draw_list.begin();

		// checks for interaction of bit and track element
		if (Intersect(bitptr->GetLayout(), tempptr->GetLayout()))
		{
			// first element is volt bonus, returns BonusHit event
			if (typeid(Volt) == typeid(*tempptr))				return Events::VBonusHit;

			// first element is amper bonus, returns BonusHit event
			else if (typeid(Amper) == typeid(*tempptr))			return Events::ABonusHit;

			// first element is 2-inputs NAND, returns Elem_Entered event
			else if (typeid(LogicElem<2>) == typeid(*tempptr)
				|| typeid(LogicElem<3>) == typeid(*tempptr))	return Events::Elem_Entered;
		}
	}
	return Events::None;  // no event occured
}

void Track::AddElem(GameObject * new_elem)
{

	sf::FloatRect pos = sprite.getGlobalBounds();

	new_elem->SetPosition(pos.width, (int)pos.top);

	draw_list.push_back(new_elem);
}

GameObject * Track::GetElem()
{
	return (*draw_list.begin());
}

void Track::Draw()
{
	window->draw(sprite);

	if (bitptr)		bitptr->Draw();

	std::list<GameObject *>::iterator it = draw_list.begin();

	for (it; it != draw_list.end(); it++)	
		(*it)->Draw();

}

Tracklist::Tracklist(sf::RenderWindow *window)
{
	size = 5;
	track_num = 0;
	bitstate = true;

	Track::SetTexture(txtpath + "track.png");

	bit = new GameObject(window, txtpath + "bit.png", sf::Color(255, 0, 255));
	
	counter = 0;
	AddTrack(new Track(window, 200), 0);
	AddTrack(new Track(window, 285), 1);
	AddTrack(new Track(window, 370), 2);
	AddTrack(new Track(window, 455), 3);
	AddTrack(new Track(window, 540), 4);

	list[0]->Attach(bit);

	volts = new Battery(window, 5000, 10000, txtpath + "Baterry/bat.png");
}

void Tracklist::AddTrack(Track * track, int pos)
{
	list[pos] = track;
}

void Tracklist::AddElem(GameObject * new_elem, int track)
{
	list[track]->AddElem(new_elem);
}

void Tracklist::ChangeBitState()
{
	bitstate = !bitstate;
}

void Tracklist::Update()
{
	for (int i = 0; i < size; i++) {
		if (list[i])
		{

			switch (list[i]->Update())
			{
				// loading battery with bonus volt amount
			case Events::VBonusHit: {
				int temp = (dynamic_cast<Volt *>(list[i]->GetElem()))->GetBonus();
				volts->Load(temp);
				(list[i]->draw_list).pop_front();
			}
			break;
			// loading battery with bonus amper amount
			case Events::ABonusHit: 
			{
				int temp = (dynamic_cast<Amper *>(list[i]->GetElem()))->GetBonus();
				amps->Load(temp);
				list[i]->draw_list.pop_front();
			}
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
	//volts->Dissipate(1);
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

