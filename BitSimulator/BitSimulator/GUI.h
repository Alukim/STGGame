#pragma once
#include <SFML\Graphics.hpp>


// class used for drawing meters filled with spectrum's colors
class Battery
{
	sf::RenderWindow *ref;	//> pointer to window battery will be drawn in

	int load;				//> battery's load
	int cap;				//> battery's capacity
	int waver;				//> special counter to provide flashing when battery is full
	int prevheight;			//> counter to determine the diff in colouring procces
	bool change;			//> defines if sprite needs to be updated before drawing

	sf::Sprite batsprite;	//>	battery's sprite
	sf::Sprite lightsprite; //> lightning's sprite

	sf::Image batimg;		//> variable where batimg updates take place
	sf::Image lightimg;		//> variable where lightning updates take place

	void Refactor();		//> update method

public:

	//> Default constructor
	Battery()
	{
	}

	//> Constructor
	//> Creates Battery image with loading utility
	//> /a window - pointer to window battery will be drawn in
	//> /a l - load the battery starts with
	//> /a c - capacity of battery
	//> /a path - path of the image
	//> Sets object coords to /a xpos and /a ypos;
	Battery(sf::RenderWindow *window, int l, int c, std::string path, int xpos=0, int ypos=0);


	
	//> Adds the /a load_inc to load value
	void Load(int load_inc);
		
	//> decrements load value by /a load_dnc
	void Dissipate(int load_dnc);
		
	//> Draws the sprite onto screen
	void Draw();
};

class Points_class
{
	int points;
	sf::Font * font;
	sf::RenderWindow * ref;
	sf::Text  text;
	std::string s;
	bool change;
	sf::Vector2f set_position();

public:

	Points_class(sf::RenderWindow * window, sf::Font * font_);
	void Update(int inc);
	void Draw();
};

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
private:

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;

public:

	ParticleSystem(unsigned int count);
	void setEmitter(sf::Vector2f position);
	void update(sf::Time elapsed);

private:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

};

