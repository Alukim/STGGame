#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;
class Rank
{
	RenderWindow * window;
	Font * fontPointer;

	vector<Text *> textArray;
	vector<int> pointArray;

public:
	Rank(RenderWindow * renderTarget, Font * font, string rankPath);

	void tryAddNewRank(string nickName, int points);
};