#include "Game.h"

inline void Game::MoveUp()
{
	if (!bit->isLocked()) {
		if (bit_level != 0) {
			for (int i = bit_level - 1; i >= 0; i--) {
				for (auto track : trackMap[i]) {
					if (track->canBitAttach(bit)) {
						prev_bit_level = bit_level;
						bit_level = i;
						bit->setHeight(levelHeights[i]);
						return;
					}
				}
			}
		}
	}
}

inline void Game::MoveDown()
{
	// if bit is not entering or leaving a gate - free to move
	if (!bit->isLocked()) { 
		// if bit is not on the last track (nothing to check)
		if (bit_level != TRACK_AMOUNT - 1) {
			// search through the tracks below the current one to transfer bit there
			for (int i = bit_level + 1; i < TRACK_AMOUNT; i++) {
				// search through every piece of the track on given level
				for (auto track : trackMap[i]) {
					// checks if dims of bit are encloses in track dims
					if (track->canBitAttach(bit)) {
						prev_bit_level = bit_level;
						bit_level = i;
						bit->setHeight(levelHeights[i]);
						track->setValue(bit->Value());
						// if bit moved - get out of function
						return;
					}
				}
			}
		}
	}
}

inline void Game::Update()
{
	// 1. sprawdz czy bit nie wpierdolil sie na element przy moveup/movedown
	if (updateTimer.getElapsedTime().asMilliseconds() >= UPS) {
		updateTimer.restart();
		bool track_collision = false;
		bit->Update();
		for (auto &trackList : trackMap)
		{
			for (auto &track : trackList)
				track->Update(offset);
		}

		for (auto &elem : elems)
		{
			FloatRect floatRect = elem->getGlobalBounds();
			FloatRect bitRect = bit->getGlobalBounds();
			if (LogicElem * temp = dynamic_cast<LogicElem *>(elem))
			{
				if (bitRect.intersects(floatRect))
				{
					if (bit->hasMoved()) {
						bit->getBack();
					}
					else if (!bit->isEntering())
					{
						bit->EnterLogicElem(temp);
					}
				}
			}
			else
			{
				if (bit->isCollecting())
				{
					// dodawanie voltów
					if (Volt * temp = dynamic_cast<Volt*>(elem))
						Points->Add(temp->GetBonus());

					// dodawanie amperów
					else
						Points->Add(dynamic_cast<Amper*>(elem)->GetBonus());
				}
			}
			elem->move(-offset, 0);
		}
		if (pixelCounter)
			IncrementPixelCounter();
		
		// dodawanie nowych elementów do listy
	}
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

	if (bit->Visible)
		Window->draw(*bit);
}

void Game::AddLogicElem(LogicElem * newObject, int trackNumber, int inputCount)
{
	newObject->setPosition(1024, levelHeights[trackNumber] - Track::trackHeight / 2);
	elems.push_back(newObject);

	if (inputCount == 2) 
	{
		trackMap[trackNumber].back()->Cut();
		trackMap[trackNumber + 1].back()->Cut();
		trackMap[trackNumber + 1].push_back(new Track(levelHeights[trackNumber + 1], true, true, 1024));
		trackMap[trackNumber + 2].back()->Cut();
	}
	else 
	{
		trackMap[trackNumber].back()->Cut();
		trackMap[trackNumber + 1].back()->Cut();
		trackMap[trackNumber + 2].back()->Cut();
		trackMap[trackNumber + 3].back()->Cut();
		trackMap[trackNumber + 4].back()->Cut();
	}

}

void Game::StartTrack(int level, bool mod, bool value)
{
	trackMap[level].push_back(new Track(levelHeights[level], mod, value, 1024));
}

Game::Game()
{
	Fail = false;
	tim.restart();
	updateTimer.restart();
	Window = new sf::RenderWindow(sf::VideoMode(1024, 768, 32), "BitSimulator", sf::Style::Default);

	if (!Font.loadFromFile(fntpath + "bellfort.otf"))
		Fail = true;

	volts = new Battery(Window, 2500, 5000, txtpath + "bat1.png");
	Points = new Score(Window, &Font);


	Track::SetTexture(txtpath + "track.png");
	Track::SetWindowPointer(Window);
	trackMap[0].push_back(new Track(levelHeights[0], true, false, 0));
	trackMap[1].push_back(new Track(levelHeights[1], true, false, 0));
	trackMap[2].push_back(new Track(levelHeights[2], true, false, 0));
	trackMap[3].push_back(new Track(levelHeights[3], true, false, 0));
	trackMap[4].push_back(new Track(levelHeights[4], true, false, 200));
	trackMap[5].push_back(new Track(levelHeights[5], true, false, 200));
	trackMap[6].push_back(new Track(levelHeights[6], true, false, 200));
	trackMap[7].push_back(new Track(levelHeights[7], true, false, 200));

	

	Image temp;
	temp.loadFromFile(txtpath + "Gates/And.png");
	temp.createMaskFromColor(Color(255, 0, 255));
	AND2Texture.loadFromImage(temp);
	AddLogicElem(new AND2(AND2Texture), 2, 2);
	AddLogicElem(new AND2(AND2Texture), 5, 2);

	temp.loadFromFile(txtpath + "bit.png");
	temp.createMaskFromColor(Color(255, 0, 255));

	BitTexture.loadFromImage(temp);
	bit = new Bit(BitTexture);

	bit->setPosition(100, levelHeights[prev_bit_level = bit_level = 3]);
	offset = 1.4;
}

void Game::Play()
{
	while (Window->isOpen()) {
		while (Window->pollEvent(events)) {
			if (events.type == Event::KeyPressed && 
				(events.key.code == Keyboard::Up || events.key.code == Keyboard::W))
				MoveUp();

			else if (events.type == Event::KeyPressed && 
				(events.key.code == Keyboard::Down || events.key.code == Keyboard::S))
				MoveDown();

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
			else if (events.type == Event::KeyPressed && events.key.code == Keyboard::Right) {
				offset = 3.0;
			}
			else if (events.type == Event::KeyReleased && events.key.code == Keyboard::Right) {
				offset = 1.4;
			}
			else if (events.type == Event::Closed)
				Window->close();

			else if (events.type == Event::KeyPressed && events.key.code == Keyboard::Escape)
				Window->close();
		}
		++cont;
		if (tim.getElapsedTime().asSeconds() > 1) {
			std::cout << cont << std::endl;
			cont = 0;
			tim.restart();
		}

		Update();
		Window->clear(Color::Blue);
		Draw();
		Window->display();
	}
}


