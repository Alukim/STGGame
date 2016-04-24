#include "Game.h"

void Game::MoveUp()
{
	if (index != 0 && !bit->isLocked())
	{
		Tracks[index]->Detach();
		Tracks[--index]->Attach(bit);
	}
}

void Game::MoveDown()
{
	if (index != size - 1 && !bit->isLocked())
	{
		Tracks[index]->Detach();
		Tracks[++index]->Attach(bit);
	}
}

void Game::Update()
{
	GameObject *coll = 0; // pointer to colliding item
	
	for (auto track : Tracks)
	{
		coll = track->Update(offset);
		switch (track->events)
		{
		case VBonusHit:

			if (bit->isCollecting())
			{
				double cover = 0;
				if ((cover = CoverBonus(bit->GetLayout(), coll->GetLayout())) > 0)
				{
					volts->Load(cover * (dynamic_cast<Volt *>(coll)->GetBonus()));
					Points->Add(cover * 300);
					if (cover > 0.9f)
						Perfect = true;
				}
			}
			break;
		case ABonusHit:
			if (bit->isCollecting())
			{
				double cover = 0;
				if (cover = CoverPercentage(bit->GetLayout(), coll->GetLayout()) > 0)
				{
					amps->Load(cover*(dynamic_cast<Amper *>(coll)->GetBonus()));

					if (cover > 0.9f)		Perfect = true;
				}
			}
			break;
		case Elem_Entered:
			bit->EnterGate(dynamic_cast<LogicElem*>(coll));
			break;

		case Bit_Annihillated:
			break;
		case CheckpointReached:
			break;
		case Run_Off_Fuel:
			// goes to endgame screen
			break;

		case None:
			if (bit->isLocked())
			{				
				bit->LeaveGate();
				if (bit->Propagate())
					Points->Add(1);
				else
				{
					// koniec gry
				}
			}
			break;
		}
	}
}

void Game::Draw()
{
	Points->Draw();
	for (int i = 0; i < size; i++)
		Tracks[i]->Draw();
	bit->Draw();
	volts->Draw();
}

Game::Game()
{
	Fail = false;

	Window = new sf::RenderWindow(sf::VideoMode(1024, 768, 32), "BitSimulator", sf::Style::Default);
	Window->setFramerateLimit(FPS);
	if (!Font.loadFromFile(fntpath + "bellfort.otf"))
		Fail = true;

	volts = new Battery(Window, 2500, 5000, txtpath + "bat1.png");
	Points = new Score(Window, &Font);

	bit = new Bit(Window, txtpath + "bit.png");
	bit->SetState(true);

	ElemEntered = false;
	Track::SetTexture(txtpath + "track.png");

	Tracks[0] = new Track(Window, 200);
	Tracks[1] = new Track(Window, 280);
	Tracks[2] = new Track(Window, 360);
	Tracks[3] = new Track(Window, 440);
	Tracks[4] = new Track(Window, 520);
	Tracks[5] = new Track(Window, 600);

	Tracks[index = 2]->Attach(bit);

	offset = 0.5f;
}

void Game::Play()
{
	//Tracks[0]->AddElem(new AND2(Window, txtpath + "Gates/And.png"));
	Tracks[0]->AddElem(new Volt(Window, txtpath + "VBonus.png", 200));
	while (Window->isOpen())
	{
		while (Window->pollEvent(events))
		{
			if (events.type == sf::Event::KeyPressed
				&& (events.key.code == sf::Keyboard::Up || events.key.code == sf::Keyboard::W))
			{
				MoveUp();
			}
			else if (events.type == sf::Event::KeyPressed
				&& (events.key.code == sf::Keyboard::Down || events.key.code == sf::Keyboard::S))
			{
				MoveDown();
			}

			else if (events.type == sf::Event::KeyPressed
				&& events.key.code == sf::Keyboard::Space)
			{
				bit->ChangeState();
			}

			else if (events.type == sf::Event::KeyPressed
				&& events.key.code == sf::Keyboard::LControl)
			{
				bit->setCollectingState(true);
			}
			else if (events.type == sf::Event::KeyReleased
				&& events.key.code == sf::Keyboard::LControl)
			{
				bit->setCollectingState(false);
			}
			else if (events.type == sf::Event::KeyPressed && events.key.code == sf::Keyboard::Right)
			{
				if (!bit->isLocked())
					offset = 2.0f;
			}

			else if (events.type == sf::Event::KeyReleased && events.key.code == sf::Keyboard::Right)
			{
				offset = 0.8f;
			}
			else if (events.type == sf::Event::Closed)			Window->close();

			else if (events.type == sf::Event::KeyPressed
				&& events.key.code == sf::Keyboard::Escape)		Window->close();
		}

		Update();

		Window->clear();
		Draw();
		Window->display();
	}
}


