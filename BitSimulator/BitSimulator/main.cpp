#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Gates.h"
#include "Game.h"

int main(int argc, char **argv)
{
	Game *object = new Game();
	object->runGame();
	return EXIT_SUCCESS;
}