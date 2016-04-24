#pragma once
#include <SFML\Graphics.hpp>
#include <stdlib.h>

// class used for drawing meters filled with spectrum's colors
class Battery
{
	sf::RenderWindow *ref;	//> pointer to window battery will be drawn in
	int diff;				//> var that indicates the difference between the actual buffer and drawn buffer

	int load;				//> battery's load
	int cap;				//> battery's capacity
	int waver;				//> special counter to provide flashing when battery is full
	int prevheight;			//> counter to determine the diff in colouring procces
	bool change;			//> defines if sprite needs to be updated before drawing

	sf::Image batimg;		//> variable where battery's texture is updated
	sf::Texture battxt;		//> battery's texture
	sf::Sprite batsprite;	//>	battery's sprite
	
	
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
	int Dissipate(int load_dnc);
		
	//> Draws the sprite onto screen
	void Draw();
};

class Score
{
private:
	bool render;

	int q_points;

	sf::RenderWindow *window;

	sf::Font *font;

	sf::Text t_score;

	sf::Text t_points;

public:
	Score(sf::RenderWindow *window_context, sf::Font *font);
	void Add(int inc);
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

