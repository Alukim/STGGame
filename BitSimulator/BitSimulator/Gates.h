#pragma once
#include "GameObject.h"
#include <string>
#include <iostream>
#include <math.h>


// ====================================================== LOGIC ELEM BASE CLASS =====================================================
class LogicElem : public GameObject
{
protected:
	bool * _input;
	int inputs_count;
public:

	//> Default constructor
	//> initializes inputs number
	LogicElem(sf::RenderWindow *winref, std::string path, int q_inputs) : GameObject(winref, path, sf::Color(255, 0, 255)), inputs_count(q_inputs)
	{
		_input = new bool[inputs_count];
	}

	//> Pure virtual function used to simulate gate work
	virtual bool Propagate() = 0;

	virtual ~LogicElem()
	{
		delete _input;
	}

};



// ======================================================== NOR GATE CLASS ========================================================
template <int inputs>
class NORGate : public LogicElem
{
public:
	NORGate<inputs>(sf::RenderWindow * window, std::string path) : LogicElem(window, path, inputs)
	{
	}
	bool Propagate() override;
};
template<int inputs>
inline bool NORGate<inputs>::Propagate()
{
	for (int i = 0; i < inputs_count; i++)
	{
		if (_input[i]) { std::cout << "Propagation on gate: FALSE"; return false; }
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
	NANDGate<inputs>(sf::RenderWindow *window, std::string path) : LogicElem(window, path, inputs)
	{
	}

	bool Propagate() override;
};


template<int inputs>
inline bool NANDGate<inputs>::Propagate()
{
	for (int i = 0; i < inputs; i++)
	{
		if (!_input[i]) { std::cout << "Propagation on gate: TRUE"; return true; }
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
	XORGate<inputs>(sf::RenderWindow *window, std::string path) : LogicElem(window, path, inputs)
	{
	}

	bool Propagate() override;
};



template<int inputs>
inline bool XORGate<inputs>::Propagate()
{
	std::cout << "Hello, this code better should work" << std::endl;
	bool result = false;
	for (int i = 0; i < inputs_count; i++)
	{
		if (_input[i]) result = !result;

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

	bool Propagate() override;
};

typedef ORGate<2> OR2;
typedef ORGate<3> OR3;


template<int inputs>
inline bool ORGate<inputs>::Propagate()
{
	for (int i = 0; i < inputs_count; i++)
	{
		if (_input[i]) return true;
	}

	return false;
}


// ================================================== AND GATE CLASS ============================================================
template <int inputs>
class ANDGate : public LogicElem
{
public:
	ANDGate<inputs>(sf::RenderWindow *win, std::string path) : LogicElem(win, path,2)
	{
	}

	bool Propagate() override;

};

typedef ANDGate<2> AND2;
typedef ANDGate<3> AND3;



template<int inputs>
inline bool ANDGate<inputs>::Propagate()
{
	for (int i = 0; i < inputs_count; i++)
	{
		if (!_input[i]) return false;
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
	Multiplexer<address_inputs>(sf::RenderWindow *window, std::string path) : LogicElem(window, path, (int)std::pow(2, address_inputs))
	{
		_input = new bool[inputs_count];
		for (int i = 0; i < inputs_count; i++)
			_input[i] = false;
		
		add_input = new bool[address_inputs];
		for (int i = 0; i < address_inputs; i++)
			add_input[i] = false;
	}
	bool Propagate();
};

typedef Multiplexer<2> Multiplexer4;
typedef Multiplexer<1> Multiplexer2;

template<int address_inputs>
inline bool Multiplexer<address_inputs>::Propagate()
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

	if (_input[address])
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
	bool Propagate() override;
	FlipD(sf::RenderWindow *window, std::string path);
	~FlipD();
};


template<int input>
inline FlipD<input>::FlipD(sf::RenderWindow *window, std::string path) : LogicElem(window, path, 2)
{
}

template<int input>
inline bool FlipD<input>::Propagate()
{
		if (_input[1])
			return _input[0] == output;
		
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
	FlipJK(sf::RenderWindow *window, std::string path);
	~FlipJK();
};

template<int input>
inline FlipJK<input>::FlipJK(sf::RenderWindow *window, std::string path) : LogicElem(window, path, 3)
{
}

template<int input>
inline FlipJK<input>::~FlipJK()
{
}

template<int input>
inline bool FlipJK<input>::Propagate() 
{
	bool temp = false;
	if (_input[1])
	{
		if (!_input[0] && !_input[2])
			temp = output;
		else if ((!_input[0] && _input[2]) || (_input[0] && !_input[2]))
			temp = _input[0];

		else if (_input[0] && _input[2])
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
	FlipT(sf::RenderWindow *window, std::string path);
	~FlipT();
};


template<int input>
inline bool FlipT<input>::Propagate()
{
	bool temp;
	if (_input[0])
	{
		temp = !output;
	}
	else
	{
		temp = output;
	}
	if (_input[1])
	{
		temp == output ? return true : return false;
	}
	else
	{
		//End Game 
		return false;
	}
}

template<int input>
inline FlipT<input>::FlipT(sf::RenderWindow * window, std::string path) : LogicElem(window, path, 2)
{
}
