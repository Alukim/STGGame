#pragma once
#include "GameObject.h"
#include <string>
#include <iostream>


// ====================================================== LOGIC ELEM BASE CLASS =====================================================
template <int inputs>
class LogicElem: public GameObject
{
protected:
	bool _input[inputs] = { 0 };
	int inputs_count;
public:
	
	
	LogicElem() : inputs_count(inputs)
	{
	}

	virtual bool Propagate() = 0;
	void SetCustomInput(int index_in, bool digit);
	void Burn();
	void Update();

};



// ======================================================== NOR GATE CLASS ========================================================
template <int inputs>
class NORGate : public LogicElem<inputs>
{
public:
	bool Propagate() override;

};
template<int inputs>
inline bool NORGate<inputs>::Propagate()
{
	std::cout << "Hello, this code better should work" << std::endl;
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
	bool result = true;
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



