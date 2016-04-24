#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>-
#include <stdio.h>
#include <Windows.h>
#include "Gates.h"
#include "Game.h"
#include "Utilities.h"
#include "GUI.h"
#include "Bonus.h"
#include "BitTrack.h"
#include "Game.h"

int main(int argc, char **argv)
{
	Game Game;
	Game.Play();
	return EXIT_SUCCESS;
}