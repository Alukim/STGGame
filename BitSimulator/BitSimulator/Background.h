#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
using namespace sf;
using namespace std;


const int BLOCKX = 16;
const int BLOCKY = 16;
struct dispersionUnit
{
	Vector2i dispCentre;
	unsigned int dispRange;
	unsigned int redispRange;
	Color dispersionColor;
};

const int WIDTH = 64;
const int HEIGHT = 48;
class Background : public Sprite
{
	const int dispTime;

	Clock updateTimer;
	Clock newDispersionTimer;

	list<dispersionUnit> dispVector;

	VertexArray arrayVector[WIDTH][HEIGHT];

	Color backgroundColor;

	RenderTexture texture;
public:
	Background();

	void Update();
};