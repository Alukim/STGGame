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
	Settings
};
int main(int argc, char **argv)
{
	RenderWindow Window(VideoMode(1024, 768), "BitSimulator", Style::Default);
	Window.setKeyRepeatEnabled(false);
	Font bellfort;
	if (!bellfort.loadFromFile(fntpath + "bellfort.otf"))
		Error("Couldn't load font file.");
	
	bool runApp = true;
	Menu * mainMenu = nullptr;
	Menu * lvlPicker = nullptr;
	Game * game = nullptr;
	try
	{
		lvlPicker = new Menu(&Window, &bellfort);
		mainMenu = new Menu(&Window, &bellfort);
		game = new Game(&Window, &bellfort);
	}
	catch (exception &e)
	{
		MessageBox(NULL, e.what(), "Error occured!", MB_ICONERROR | MB_OK);
	}
	mainMenu->addOption("New Game");
	mainMenu->addOption("Highscores");
	mainMenu->addOption("Exit");

	lvlPicker->addOption("Level 1");
	lvlPicker->addOption("Level 2");
	lvlPicker->addOption("Level 3");
	lvlPicker->addOption("Level 4");
	lvlPicker->addOption("Level 5");
	lvlPicker->addOption("Level 6");

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
			case 2: runApp = false;
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
		}
	}
	delete mainMenu;
	delete game;
	delete lvlPicker;
	return EXIT_SUCCESS;
}


// TO DO:
// napisaæ level managera
// napisaæ ranking
// przepuœciæ przez leak detectora
// zaladowac wszystkie brameczki