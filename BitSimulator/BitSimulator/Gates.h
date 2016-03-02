#pragma once
#include "GameObject.h"
#include <string>
#include <iostream>
#include <math.h>


// ====================================================== LOGIC ELEM BASE CLASS =====================================================
template <int inputs>
class LogicElem : public GameObject
{
protected:
	bool * _input;
	int inputs_count;
public:

	//> Default constructor
	//> initializes inputs number
	LogicElem(sf::RenderWindow *winref, std::string path) : GameObject(winref, path, sf::Color(200, 200, 200)), inputs_count(inputs)
	{
	}

	//> Pure virtual function used to simulate gate work
	virtual bool Propagate() = 0;


	//> Changes input digit on given track
	//> /a index_in	- index of track
	//> /a digit - digit value to be replaced
	void SetCustomInput(int index_in, bool digit);
	void Burn();
	void Update();

};



// ======================================================== NOR GATE CLASS ========================================================
template <int inputs>
class NORGate : public LogicElem<inputs>
{
	
public:
	NORGate<inputs>(sf::RenderWindow * window, std::string path) : GameObject(window, path)
	{
		inputs_count = inputs;
		_input = new bool[inputs_count];
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
typedef NORGate<4> NOR4;
typedef NORGate<8> NOR8;





// ======================================================== NAND GATE CLASS ========================================================
template <int inputs>
class NANDGate : public LogicElem<inputs>
{
public:
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
typedef NANDGate<4> NAND4;
typedef NANDGate<8> NAND8;




// ================================================== XOR GATE CLASS ===========================================================
template <int inputs>
class XORGate : public LogicElem<inputs>
{
public:
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
typedef XORGate<4> XOR4;
typedef XORGate<8> XOR8;







// ===================================================== OR GATE CLASS =============================================================
template <int inputs>
class ORGate : public LogicElem<inputs>
{
public:
	bool Propagate() override;
};

typedef ORGate<2> OR2;
typedef ORGate<3> OR3;
typedef ORGate<4> OR4;
typedef ORGate<8> OR8;


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
class ANDGate : public LogicElem<inputs>
{
public:
	ANDGate<inputs>(sf::RenderWindow *win, std::string path) : LogicElem(win, path)
	{
	}

	bool Propagate() override;

};

typedef ANDGate<2> AND2;
typedef ANDGate<3> AND3;
typedef ANDGate<4> AND4;
typedef ANDGate<8> AND8;



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
template<int inputs>
inline void LogicElem<inputs>::SetCustomInput(int index_in, bool digit)
{
	if (index_in > inputs)
		throw "Out of scope";
	else
		_input[index_in] = digit;
}


template<int inputs>
inline void LogicElem<inputs>::Burn()
{
	// runs animation of overheating gate
}

template<int inputs>
inline void LogicElem<inputs>::Update()
{
	// updates logic
}

template <int address_inputs>
class Multiplexer : public LogicElem<address_inputs>
{
	bool strob;
	bool *add_input;

public : 
	Multiplexer<address_inputs>(sf::RenderWindow *window, std::string path) : LogicElem(window, path)
	{
		inputs_count = (int)pow(2, address_inputs);
		_input = new bool[inputs_count];
		for (int i = 0; i < inputs_count; i++)
			_input[i] = false;
		
		add_input = new bool[address_inputs];
		for (int i = 0; i < address_inputs; i++)
			add_input[i] = false;
	}
	bool Propagate();
};

typedef Multiplexer<4> Multiplexer16;
typedef Multiplexer<3> Multiplexer8;
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

	if (_input[i])
		return true;
	
	else return false;
}
// -------------------------------------------Flip-Flop Class------------------------------------
template <int input>
class FlipD : public LogicElem<input>
{
private:
	bool output;
public:
	bool Propagate() override;
	FlipD();
	~FlipD();
};

template<int input>
inline FlipD<input>::FlipD() : LogicElem<2>
{
}

template<int input>
inline bool FlipD<input>::Propagate()
{
		if (_input[1])
		{
			_input[0] == output ? return true : return false;
		}
		else
		{
			//End Game 
			return false;
		}
}


template <int input>
class FlipJK : public LogicElem<input>
{
private:
	bool output;
public:
	bool Propagate() override;
	FlipJK();
	~FlipJK();
};

template<int input>
inline FlipJK<input>::FlipJK() : LogicElem<3>
{}

template<int input>
inline bool FlipJK<input>::Propagate()
{
	if (_input[1])
	{
		if (_input[0] && _input[])
		{

		}
	}
	else
	{
		//End Game 
		return false;
	}
}

template<int input>
class FlipT : public LogicElem<input>
{
private:
	bool output;
public:
	bool Propagate() override;
	FlipT();
	~FlipT();
};

template<int input>
inline FlipT<input>::FlipT() : LogicElem<2>
{}

template<int input>
inline bool FlipT<input>::Propagate()
{
	if (_input[1])
	{
		if (_input[0] && _input[])
		{

		}
	}
	else
	{
		//End Game 
		return false;
	}
}