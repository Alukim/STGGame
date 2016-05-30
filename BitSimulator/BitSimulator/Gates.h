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
	for (int i = 0; i < inputs_count; i++)
	{
		if (inputPointers[i]->getValue()) { std::cout << "Propagation on gate: FALSE"; return false; }
	}
	std::cout << "Propagation on gate: TRUE";
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
	for (int i = 0; i < inputs; i++)
	{
		if (!inputPointers[i]->getValue()) { std::cout << "Propagation on gate: TRUE"; return true; }
	}
	std::cout << "Propagation on gate: FALSE";
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
	std::cout << "Hello, this code better should work" << std::endl;
	bool result = false;
	for (int i = 0; i < inputs_count; i++)
	{
		if (inputPointers[i]->getValue()) result = !result;

	}
	std::cout << "Propagation on gate: " << result << std::endl;
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
	for (int i = 0; i < inputs_count; i++)
	{
		if (inputPointers[i]->getValue()) return true;
	}

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
	for (int i = 0; i < inputs_count; i++)
	{
		if (!inputPointers[i]->getValue()) return false;
	}
	return true;
}


// ===================================================== LOGIC ELEM CLASS ===========================================================


template <int address_inputs>
class Multiplexer : public LogicElem
{
	bool strob;
	bool *add_input;

public : 
	Multiplexer<address_inputs>(std::string & path) : LogicElem(path, (int)std::pow(2, address_inputs))
	{
		inputPointers = new Track * [inputs_count];
		
		add_input = new bool[address_inputs];
		for (int i = 0; i < address_inputs; i++)
			add_input[i] = false;
	}
	bool Propagate(void);
};

typedef Multiplexer<2> Multiplexer4;
typedef Multiplexer<1> Multiplexer2;

template<int address_inputs>
inline bool Multiplexer<address_inputs>::Propagate(void)
{
	int address = 0;

	// getting number of input
	for (int i = 0; i < address_inputs; i++)
	{
		if (add_input[i])
		{
			address += (int)pow(2, i);
		}
	}

	if (inputPointers[address]->getValue())
		return true;
	
	else return false;
}
// -------------------------------------------Flip-Flop D Class------------------------------------
template <int input>
class FlipD : public LogicElem
{
private:
	bool output;
public:
	bool Propagate(void) override;
	FlipD(sf::RenderWindow * window, std::string & path);
	~FlipD(void);
};


template<int input>
inline FlipD<input>::FlipD(sf::RenderWindow * window, std::string & path) : LogicElem(window, path, 2)
{
}

template<int input>
inline bool FlipD<input>::Propagate(void)
{
		if (inputPointers[1]->getValue())
			return (input[0]->getValue() == output);
		
		else return false; //End Game
}



// -------------------------------------------Flip-Flop JK Class------------------------------------

template <int input>
class FlipJK : public LogicElem
{
private:
	bool output;
public:
	bool Propagate() override; // _input[0] == J && _input[2] == K
	FlipJK(Texture & text);
	~FlipJK(void);
};

template<int input>
inline FlipJK<input>::FlipJK(Texture & text) : LogicElem(text, 3)
{
}

template<int input>
inline FlipJK<input>::~FlipJK(void)
{
}

template<int input>
inline bool FlipJK<input>::Propagate(void)
{
	bool temp = false;
	if (inputPointers[1]->getValue())
	{
		if (!inputPointers[0]->getValue() && !inputPointers[2]->getValue())
			temp = output;
		else if ((!inputPointers[0]->getValue() && inputPointers[2]->getValue())
			|| (inputPointers[0]->getValue() && !inputPointers[2]->getValue()))
			temp = inputPointers[0]->getValue();

		else if (inputPointers[0]->getValue() && inputPointers[2]->getValue())
			temp = !output;

		return temp == output;
	}
	else return false;
}

// -------------------------------------------Flip-Flop T Class------------------------------------

template<int input>
class FlipT : public LogicElem
{
private:
	bool output;
public:
	bool Propagate() override; //_input[0] == T;
	FlipT(Texture & text);
	~FlipT(void);
};


template<int input>
inline bool FlipT<input>::Propagate(void)
{
	bool temp;
	if (inputPointers[0]->getValue())
	{
		temp = !output;
	}
	else
	{
		temp = output;
	}
	if (inputPointers[1]->getValue())
	{
		temp == output ? return true : return false;
	}
	else
	{
		return false;
	}
}

template<int input>
inline FlipT<input>::FlipT(Texture & text) : LogicElem(text, 2)
{
}
