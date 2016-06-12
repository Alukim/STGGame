#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>-
#include <stdio.h>
#include <Windows.h>
#include "Gates.h"
#include "Game.h"
#include "GUI.h"
#include "Bonus.h"
#include "BitTrack.h"
#include "Menu.h"
#include <string>
#include <sstream>

void Error(string errorText)
{
	errorText = errorText + " The game will exit now.";
	MessageBox(NULL, errorText.c_str(), "Error occured!", MB_ICONERROR | MB_OK);
}

enum AppStates
{
	mainMenu,
	LevelPicker,
	Play,
	EndGameScreen,
	Highscores,
	AuthorScreen,
	Settings,
	Counter
};
int main(int argc, char **argv)
{
	bool runApp = true;
	srand(time(NULL));

	Font bellfort;
	if (!bellfort.loadFromFile(fntpath + "bellfort.otf"))
	{
		Error("Couldn't load font file.");
		runApp = false;
	}

	Image * title = new Image();
	if (!title->loadFromFile(txtpath + "title.png"))
	{
		Error("Couldn't load title image.");
		runApp = false;
	}
	vector<Music*> musicList;

	for (int i = 0; i < 8; ++i)
	{
		musicList.push_back(new Music());
		ostringstream ss;
		ss << i;
		string str = ss.str();
		if (!musicList[i]->openFromFile(txtpath + "../Music/Music" + str + ".ogg"))
		{
			Error("Couldn't load music file");
			runApp = false;
			break;
		}
	}
	

	RenderWindow Window(VideoMode(1024, 768), "BitSimulator", Style::Default);
	Window.setKeyRepeatEnabled(false);
	
	Menu * mainMenu = nullptr;
	Menu * lvlPicker = nullptr;
	Menu * Authors = nullptr;
	Menu * Counter = nullptr;

	Game * game = nullptr;
	try
	{
		lvlPicker = new Menu(&Window, &bellfort);
		mainMenu = new Menu(&Window, &bellfort);
		Authors = new Menu(&Window, &bellfort);
		Counter = new Menu(&Window, &bellfort);
		game = new Game(&Window, &bellfort);
	}
	catch (exception &e)
	{
		MessageBox(NULL, e.what(), "Error occured!", MB_ICONERROR | MB_OK);
	}
	mainMenu->addImage(title);
	mainMenu->addOption("New Game");
	mainMenu->addOption("Highscores");
	mainMenu->addOption("Authors");
	mainMenu->addOption("Exit");

	lvlPicker->addOption("Level 1");
	lvlPicker->addOption("Level 2");
	lvlPicker->addOption("Level 3");
	lvlPicker->addOption("Level 4");
	lvlPicker->addOption("Level 5");
	lvlPicker->addOption("Level 6");

	Authors->addOption("Back to menu             ");
	Authors->addText("Authors:", 120);
	Authors->addText(" ", 120);
	Authors->addText("Aleksander Krawiec", 70);
	Authors->addText("Bartosz Kowalski", 70);

	int numberofmusic = (rand() % 8) + 1;
	musicList[numberofmusic]->setVolume(30);
	musicList[numberofmusic]->setLoop(true);
	musicList[numberofmusic]->play();

	int levelPicked = 0;
	AppStates state = AppStates::mainMenu;
	while (runApp)
	{
		switch (state)
		{
		case AppStates::mainMenu:
			switch (mainMenu->pollMenu())
			{
			case -1: runApp = false;
				break;
			case 0: state = AppStates::LevelPicker;
				break;
			case 1: state = AppStates::Highscores;
				break;
			case 2: state = AppStates::AuthorScreen;
				break;
			case 3: runApp = false;
				break;
			}
			break;
		case AppStates::LevelPicker:
			levelPicked = lvlPicker->pollMenu();
			if (levelPicked == -1)
				runApp = false;
			else
			{
				// za³¹cz level
				state = AppStates::Play;
			}
			break;
		case AppStates::Play:
			game->Play();
			state = AppStates::EndGameScreen;
			break;
		case AppStates::EndGameScreen:
			runApp = false;
			break;
		case AppStates::Highscores:
			break;
		case::AppStates::Settings:
			break;
		case::AppStates::AuthorScreen:
			if (Authors->pollMenu() == 0)
				state = AppStates::mainMenu;
			break;
		}
	}
	delete mainMenu;
	delete game;
	delete lvlPicker;
	delete Authors;
	delete Counter;
	return EXIT_SUCCESS;
}


// TO DO:
// napisaæ level managera
// napisaæ ranking
// przepuœciæ przez leak detectora
// zaladowac wszystkie brameczki