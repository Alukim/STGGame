#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <math.h>

using namespace sf;

class Track;

// ====================================================== LOGIC ELEM BASE CLASS =====================================================
class LogicElem : public Sprite
{
protected:
	Track ** inputPointers;
	Track * outputPointer;
	int inputs_count;
public:

	//> Default constructor
	//> initializes inputs number
	LogicElem(Texture & text, int q_inputs) : Sprite(text), inputs_count(q_inputs)
	{
		inputPointers = new Track*[inputs_count];
		outputPointer = NULL;
	}

	//> Pure virtual function used to simulate gate work
	virtual bool Propagate(void) = 0;

	void LogicElem::setInputTrack(int input, Track * Pointer)
	{
		inputPointers[input] = Pointer;
	}

	void LogicElem::setOutputTrack(Track * Pointer)
	{
		outputPointer = Pointer;
	}

	Track * OutputTrack();

	virtual ~LogicElem(void)
	{
		delete inputPointers;
	}

};



// ======================================================== NOR GATE CLASS ========================================================
template <int inputs>
class NORGate : public LogicElem
{
public:
	NORGate<inputs>(Texture & text) : LogicElem(inputs)
	{
	}
	bool Propagate(void) override;
};
template<int inputs>
inline bool NORGate<inputs>::Propagate(void)
{
	for (unsigned i = 0; i < inputs_count; ++i)
		if (inputPointers[i]->getValue()) { std::cout << "Propagation on gate: FALSE"; return false; }
	return true;
}


typedef NORGate<2> NOR2;
typedef NORGate<3> NOR3;





// ======================================================== NAND GATE CLASS ========================================================
template <int inputs>
class NANDGate : public LogicElem
{
public:
	NANDGate<inputs>(Texture & text) : LogicElem(text, inputs)
	{
	}

	bool Propagate(void) override;
};


template<int inputs>
inline bool NANDGate<inputs>::Propagate(void)
{
	for (unsigned i = 0; i < inputs; ++i)
		if (!inputPointers[i]->getValue()) { std::cout << "Propagation on gate: TRUE"; return true; }
	return false;
}
typedef NANDGate<2> NAND2;
typedef NANDGate<3> NAND3;


// ================================================== XOR GATE CLASS ===========================================================
template <int inputs>
class XORGate : public LogicElem
{
public:
	XORGate<inputs>(sf::RenderWindow * window, std::string & path) : LogicElem(window, path, inputs)
	{
	}

	bool Propagate(void) override;
};



template<int inputs>
inline bool XORGate<inputs>::Propagate(void)
{
	bool result = false;
	for (unsigned i = 0; i < inputs_count; ++i)
		if (inputPointers[i]->getValue()) result = !result;

	return result;
}

typedef XORGate<2> XOR2;
typedef XORGate<3> XOR3;







// ===================================================== OR GATE CLASS =============================================================
template <int inputs>
class ORGate : public LogicElem
{
public:
	ORGate<inputs>(sf::RenderWindow *window, std::string path) : LogicElem(window, path, inputs)
	{
	}

	bool Propagate(void) override;
};

typedef ORGate<2> OR2;
typedef ORGate<3> OR3;


template<int inputs>
inline bool ORGate<inputs>::Propagate(void)
{
	for (unsigned i = 0; i < inputs_count; ++i)
		if (inputPointers[i]->getValue()) return true;

	return false;
}


// ================================================== AND GATE CLASS ============================================================
template <int inputs>
class ANDGate : public LogicElem
{
public:
	ANDGate<inputs>(Texture & text) : LogicElem(text, inputs)
	{
	}

	bool Propagate(void) override;

};

typedef ANDGate<2> AND2;
typedef ANDGate<3> AND3;



template<int inputs>
inline bool ANDGate<inputs>::Propagate(void)
{
	for (unsigned i = 0; i < inputs_count; ++i)
		if (!inputPointers[i]->getValue()) return false;
	return true;
}