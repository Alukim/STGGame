#include "Game.h"

Game::Game(RenderWindow * renderTarget, Font * font)
{
	Window = renderTarget;
	bellfort = font;

	volts = new Battery(Window, 2500, 5000, txtpath + "bat1.png");
	Points = new Score(Window, bellfort);


	Track::SetTexture(txtpath + "track.png");
	Track::SetWindowPointer(Window);
	trackMap[0].push_back(new Track(levelHeights[0], 0, true, false, 0));
	trackMap[1].push_back(new Track(levelHeights[1], 1, true, false, 0));
	trackMap[2].push_back(new Track(levelHeights[2], 2, true, false, 0));
	trackMap[3].push_back(new Track(levelHeights[3], 3, true, false, 0));
	trackMap[4].push_back(new Track(levelHeights[4], 4, true, false, 200));
	trackMap[5].push_back(new Track(levelHeights[5], 5, true, false, 200));
	trackMap[6].push_back(new Track(levelHeights[6], 6, true, false, 200));
	trackMap[7].push_back(new Track(levelHeights[7], 7, true, false, 200));

	Image temp;
	temp.loadFromFile(txtpath + "Gates/And2.png");
	temp.createMaskFromColor(Color(255, 0, 255));
	AND2Texture.loadFromImage(temp);
	AddLogicElem(new AND2(AND2Texture), 2, 2);
	AddLogicElem(new AND2(AND2Texture), 5, 2);

	temp.loadFromFile(txtpath + "bit.png");
	temp.createMaskFromColor(Color(255, 0, 255));

	BitTexture.loadFromImage(temp);
	bit = new Bit(BitTexture);

	bit->setPosition(275, 0);
	bit->attachToTrack(trackMap[3].front());
	offset = 1.6;

	moveUp = moveDown = false;
	FadetoBlack = 0;
	fader.setSize(Vector2f(1024, 768));
	fader.setFillColor(Color(0, 0, 0, 0));
}

void Game::Play()
{
	while (Window->isOpen())
	{
		while (Window->pollEvent(events))
		{
			if (events.type == Event::KeyPressed &&
				(events.key.code == Keyboard::Up || events.key.code == Keyboard::W))
				moveUp = !(moveDown = false);

			else if (events.type == Event::KeyPressed &&
				(events.key.code == Keyboard::Down || events.key.code == Keyboard::S))
				moveDown = !(moveUp = false);

			else if (events.type == Event::KeyPressed
				&& events.key.code == Keyboard::Space) {
				bit->changeValue();
			}
			else if (events.type == Event::KeyPressed
				&& events.key.code == Keyboard::LControl) {
			}
			else if (events.type == Event::KeyReleased
				&& events.key.code == Keyboard::LControl) {
			}
			else if (events.type == Event::KeyPressed && events.key.code == Keyboard::Right) 
				offset = 3.5;

			else if (events.type == Event::KeyReleased && events.key.code == Keyboard::Right)
				offset = 2.0;

			else if (events.type == Event::Closed)
				Window->close();
		}
		if (Update())
			return;
		Window->clear(Color::Blue);
		Draw();
		Window->display();
	}
}

inline bool Game::Update()
{
	// 1. sprawdz czy bit nie wpierdolil sie na element przy moveup/movedown
	if (updateTimer.getElapsedTime().asMilliseconds() >= UPS)
	{
		updateTimer.restart();
		if (moveUp)
		{
			int index = bit->getTrackIndex();
			bool done = false;
			if (!bit->isLocked())
			{
				while (--index >= 0 && !done)
				{
					for (auto &track : trackMap[index])
					{
						if (track->canBitAttach(bit))
						{
							bit->attachToTrack(track);
							done = true;
							break;
						}
					}
				}
			}
			// if bit didn't change track
			moveUp = false;
		}
		else if (moveDown)
		{
			int index = bit->getTrackIndex();
			bool done = false;
			if (!bit->isLocked())
			{
				while (++index < TRACK_AMOUNT && !done)
				{
					for (auto &track : trackMap[index])
						if (track->canBitAttach(bit))
						{
							bit->attachToTrack(track);
							done = true;
							break;
						}
				}
			}
			//if bit didn't change track
			moveDown = false;
		}
		switch (bit->Update())
		{
		case Bit::Event::ElemEntered:
			break;
		case Bit::Event::ElemLeft:
			break;
		case Bit::Event::IncorrectPropagation:
			FadetoBlack = 1;

			break;
		case Bit::Event::CorrectPropagation:
			Points->Add(5000);
			break;
		}
		FloatRect bitRect = bit->getGlobalBounds();
		for (auto elem : elems)
		{
			elem->move(-offset, 0);
			FloatRect elemRect = elem->getGlobalBounds();
			if (bitRect.intersects(elemRect))
			{
				// if elem is LogicElem type (gate element)
				if (LogicElem * pointer = dynamic_cast<LogicElem *>(elem))
				{
					if (!bit->isLocked())
					{
						// if bit changed track
						if (moveUp || moveDown)
							bit->getBack();
						// bit is free and can get into to logic elem
						else
							bit->EnterLogicElem(pointer);
					}
				}
				// if elem is Volt or Amper type (Bonus element)
				else
				{
					Volt * voltPointer = dynamic_cast<Volt *>(elem);
					if (voltPointer)
					{
						Points->Add(voltPointer->GetBonus());
						volts->Load(voltPointer->GetBonus());
					}
					// else - dodaj do baterii Amperów
				}
			}
		}
		// moves the tracks
		for (auto &trackList : trackMap)
		{
			for (auto &track : trackList)
				track->Update(offset);
		}
		moveUp = moveDown = false;
		
		
		if (FadetoBlack > 255) return true;	
		else if (FadetoBlack > 0)
		{
			++FadetoBlack;
			fader.setFillColor(Color(0, 0, 0, FadetoBlack));
		}
	}
	return false;
}

inline void Game::IncrementPixelCounter()
{
	++pixelCounter;
}

inline void Game::Draw()
{
	Points->Draw();
	volts->Draw();

	for (auto &tracklist : trackMap)
	{
		for (auto &elem : tracklist)
			Window->draw(elem->sprite);
	}
	for (auto &elem : elems)
		Window->draw(*elem);

	Window->draw(*bit);
	Window->draw(fader);
}

void Game::AddLogicElem(LogicElem * newObject, int trackNumber, int inputCount)
{
	newObject->setPosition(1024, levelHeights[trackNumber] - Track::trackHeight / 2);
	elems.push_back(newObject);
	Track * temp = nullptr;
	if (inputCount == 2)
	{
		// setting first input
		temp = trackMap[trackNumber].back();
		Track::Cut(temp);
		newObject->setInputTrack(0, temp);

		// ending track between 2 inputs
		Track::Cut(trackMap[trackNumber + 1].back());

		// setting second input
		temp = trackMap[trackNumber + 2].back();
		Track::Cut(temp);
		newObject->setInputTrack(1, temp);

		// setting output track
		temp = Track::startNewTrack(levelHeights[trackNumber + 1], trackNumber + 1, true, true);
		trackMap[trackNumber + 1].push_back(temp);
		newObject->setOutputTrack(temp);
	}
}





