#include "Background.h"

Background::Background() : dispTime(10), backgroundColor(Color(102, 102, 102)), Sprite()
{
	texture.create(1024, 768);
	backgroundColor = Color(102, 102, 102);
	for (unsigned i = 0; i < WIDTH; ++i)
	{
		for (unsigned j = 0; j < HEIGHT; ++j)
		{
			arrayVector[i][j] = VertexArray(PrimitiveType::Triangles, 4);
			arrayVector[i][j][0].position = Vector2f(i * BLOCKX, j * BLOCKY);
			arrayVector[i][j][1].position = Vector2f(i * BLOCKX + BLOCKX, j * BLOCKY);
			arrayVector[i][j][2].position = Vector2f(i * BLOCKX + BLOCKX, j * BLOCKY + BLOCKY);
			arrayVector[i][j][3].position = Vector2f(i * BLOCKX, j * BLOCKY + BLOCKY);

			for (unsigned k = 0; k < 4; k++)
			{
				arrayVector[i][j][k].color = backgroundColor;
			}
		}
	}
	setTexture(texture.getTexture());
	newDispersionTimer.restart();
}

void Background::Update()
{
	if (newDispersionTimer.getElapsedTime().asSeconds() > 0.8f)
	{
		newDispersionTimer.restart();
		dispersionUnit temp;
		int x = 0, y = 0;
		x = rand() % (WIDTH - 22) + 11;
		y = rand() % (HEIGHT - 22) + 11;

		temp.dispCentre = Vector2i(x, y);
		temp.dispersionColor = Color(rand() % 255, rand() % 255, rand() % 255);
		temp.dispRange = 0;
		temp.redispRange = 0;
		dispVector.push_back(temp);
	}

	if (updateTimer.getElapsedTime().asMilliseconds() > 60)
	{
		updateTimer.restart();
		list<dispersionUnit>::iterator it = dispVector.begin();
		for (it; it != dispVector.end(); ++it)
		{
			if (++(it->dispRange) < 10)
			{
				for (unsigned i = it->dispCentre.x - it->dispRange; i <= it->dispCentre.x + it->dispRange; ++i)
					for (unsigned k = 0; k < 4; ++k)
					{
						arrayVector[i][it->dispCentre.y - it->dispRange][k].color = it->dispersionColor;
						arrayVector[i][it->dispCentre.y + it->dispRange][k].color = it->dispersionColor;
					}
				for (unsigned i = it->dispCentre.y - it->dispRange; i <= it->dispCentre.y + it->dispRange; ++i)
					for (unsigned k = 0; k < 4; ++k)
					{
						arrayVector[it->dispCentre.x - it->dispRange][i][k].color = it->dispersionColor;
						arrayVector[it->dispCentre.x + it->dispRange][i][k].color = it->dispersionColor;
					}
			}
			if (it->dispRange > 6)
			{
				++(it->redispRange);
				for (unsigned i = it->dispCentre.x - it->redispRange; i <= it->dispCentre.x + it->redispRange; ++i)
					for (unsigned k = 0; k < 4; ++k)
					{
						arrayVector[i][it->dispCentre.y - it->redispRange][k].color = backgroundColor;
						arrayVector[i][it->dispCentre.y + it->redispRange][k].color = backgroundColor;
					}
				for (unsigned i = it->dispCentre.y - it->redispRange; i <= it->dispCentre.y + it->redispRange; ++i)
					for (unsigned k = 0; k < 4; ++k)
					{
						arrayVector[it->dispCentre.x - it->redispRange][i][k].color = backgroundColor;
						arrayVector[it->dispCentre.x + it->redispRange][i][k].color = backgroundColor;
					}
			}
		}
	}
	dispVector.remove_if([](dispersionUnit & unit) {return unit.redispRange >= 10; });
	texture.clear();
	for (unsigned i = 0; i < WIDTH; ++i)
	{
		for (unsigned j = 0; j < HEIGHT; ++j)
		{
			texture.draw(arrayVector[i][j]);
		}
	}
	texture.display();
	setTexture(texture.getTexture());
}
