#include "Animation.h"


Animation::Animation(const std::string & path, const sf::Vector2i & sheet_cut, const int frames, const float time_fix)
{
	spriteSheet.loadFromFile(path);
	currentFrame = 0;
	animate = false;
	timer.restart();
	updateTime = time_fix;
}

void Animation::SetFrame(int frame)
{
	if (frame > 0 && frame < spriteRects.size())
	{
		sprite.setTextureRect(spriteRects[frame]);
		timer.restart();
	}
}

void Animation::AddSheetCut(sf::IntRect &rect)
{
	spriteRects.push_back(rect);
}

void Animation::Start()
{
	animate = true;
	timer.restart();
}

void Animation::Stop()
{
	animate = false;
}

sf::Sprite & Animation::GetFrame()
{
	if (timer.getElapsedTime().asSeconds() > updateTime)
	{
		if (currentFrame == spriteRects.size())
			currentFrame = 0;
		sprite.setTextureRect(spriteRects[currentFrame]); // takes new frame
		++currentFrame;
		timer.restart();
	}
	return sprite;
}
