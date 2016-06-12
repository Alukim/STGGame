#include "Game.h"

Game::Game(RenderWindow * renderTarget, Font * font)
{
	Window = renderTarget;
	bellfort = font;

	volts = new Battery(Window, 2500, 5000, txtpath + "bat1.png");
	Points = new Score(Window, bellfort);
	background = new Background();

	Track::SetTexture(txtpath + "track.png");
	Track::SetWindowPointer(Window);

	// creating tracks
	trackMap[0].push_back(new Track(levelHeights[0], 0, true, false, 0));
	trackMap[1].push_back(new Track(levelHeights[1], 1, true, false, 0));
	trackMap[2].push_back(new Track(levelHeights[2], 2, true, false, 0));
	trackMap[3].push_back(new Track(levelHeights[3], 3, true, false, 0));
	trackMap[4].push_back(new Track(levelHeights[4], 4, true, false, 200));
	trackMap[5].push_back(new Track(levelHeights[5], 5, true, false, 200));
	trackMap[6].push_back(new Track(levelHeights[6], 6, true, false, 200));
	trackMap[7].push_back(new Track(levelHeights[7], 7, true, false, 200));

	Image temp;
	temp.loadFromFile(txtpath + "Gates/Nowe/AND.png");
	temp.createMaskFromColor(Color(255, 0, 255));
	AND2Texture.loadFromImage(temp);

	temp.loadFromFile(txtpath + "VBonus.png");
	temp.createMaskFromColor(Color(255, 0, 255));
	VoltBonusTexture.loadFromImage(temp);

	AddLogicElem(new AND2(AND2Texture), 2, 2);
	AddLogicElem(new AND2(AND2Texture), 5, 2);

	AddBonus(new Bonus(&VoltBonusTexture, 500), 1);
	temp.loadFromFile(txtpath + "bit.png");
	temp.createMaskFromColor(Color(255, 0, 255));

	BitTexture.loadFromImage(temp);
	bit = new Bit(BitTexture);

	bit->setPosition(275, 0);
	bit->attachToTrack(trackMap[3].front());
	offset = 1.6;

	moveUp = moveDown = collect = false;
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
			switch (events.type)
			{
			case Event::KeyPressed:
				switch (events.key.code)
				{
				case Keyboard::Up:
				case Keyboard::W:
					moveUp = !(moveDown = false);
					break;
				case Keyboard::Down:
				case Keyboard::S:
					moveDown = !(moveUp = false);
					break;
				case Keyboard::Space:
					bit->changeValue();
					break;
				case Keyboard::LControl:
					collect = true;
					break;
				case Keyboard::Right:
				case Keyboard::D:
					offset = 3.5;
					break;
				}
				break;
			case Event::KeyReleased:
				switch (events.key.code)
				{
				case Keyboard::Right:
					offset = 2.0;
					break;
				case Keyboard::LControl:
					collect = false;
					break;
				}
				break;
			case Event::Closed:
				Window->close();
				break;
			}
		}
		if (Update())
			return;
		background->Update();
		Window->draw(*background);
		Draw();
		Window->display();
	}
}

void Game::LoadLevel(std::string path)
{
	fstream file(path);
	if (!file)
		throw exception("Couldn't open game files. Try reinstalling the game");

	ElemScript elem;
	int type;
	while (!file.eof())
	{
		file >> type;
		switch (type)
		{
			//end level pixel get
		case 0:
			file >> elem.pixelCount;
			elem.beginTrack = 0;
			elem.bonus = 0;
			elem.inputCount = 0;
			break;
			// bramka logiczna
		case 1:
			file >> elem.pixelCount;
			//file >> 
			break;
		}
		elem.elemType = type;

	}
}

inline bool Game::Update()
{
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
			if (done == false)
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
			if (done == false)
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
			if (bitRect.intersects(elemRect))		 // if there is a collision (bit with logic elem)
			{
				if (LogicElem * pointer = dynamic_cast<LogicElem *>(elem))	// if elem is LogicElem type (gate element)
				{
					if (!bit->isLocked())			// if bit is entering or leaving another element (pragmatic if)
					{
						if (moveUp || moveDown)		// if bit changed track
							bit->getBack();
						else						// bit is free and can get into the logic elem
							bit->EnterLogicElem(pointer);
					}
				}

				else	// if elem is Bonus element
				{
					Bonus * bonusPointer = dynamic_cast<Bonus *>(elem);
					if (collect)	// if bit is collecting (CTRL pressed) then check on collisions
					{
						double coeff = coverPercentage(bonusPointer->getGlobalBounds(), bitRect);
						Points->Add(coeff * bonusPointer->GetBonus());
						volts->Load(bonusPointer->GetBonus());
						Bonus::CollectBonus(bonusPointer);
						collect = false; // stop collecting
					}
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
		volts->Dissipate(1);
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

void Game::AddBonus(Sprite * newBonus, unsigned int trackNumber)
{
	newBonus->setPosition(1024, levelHeights[trackNumber] - Track::trackHeight / 2);
	elems.push_back(newBonus);
}


double coverPercentage(FloatRect &elem1, FloatRect &elem2)
{
	double area1 = 0.0, area2 = 0.0;
	area1 = elem1.width * elem1.height;
	area2 = elem2.width * elem2.height;

	double x = 0.0, y = 0.0;
	double area3 = 0.0;

	if (elem1.left > elem2.left)
		x = elem2.left + elem2.width - elem1.left;
	else
		x = elem1.left + elem1.width - elem2.left;

	if (elem1.top > elem2.top)
		y = elem2.top + elem2.height - elem1.top;
	else
		y = elem1.top + elem1.height - elem2.top;

	if (x < 0 || y < 0)
		return 0.0;
	else
	{
		area3 = x * y;
		return (area3 / area1);
	}
}

