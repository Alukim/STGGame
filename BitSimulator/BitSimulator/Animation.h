#include <SFML\Graphics.hpp>

class Animation
{
	sf::Texture spriteSheet;
	
	sf::Sprite sprite;
	
	std::vector<sf::IntRect> spriteRects;

	int currentFrame;

	int updateTime;

	sf::Clock timer;

	bool animate;

public:
	explicit Animation(const std::string &path, const sf::Vector2i &sheet_cut, const int frames, const float time_fix);

	void SetFrame(int frame);

	void AddSheetCut(sf::IntRect &rect);

	void Start();

	void Stop();
	
	sf::Sprite & GetFrame();
	

};


class CircleXplosion
{
private:
	sf::Vector2f centre;

};