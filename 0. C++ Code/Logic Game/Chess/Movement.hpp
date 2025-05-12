#pragma once
#include "ChessPosition.hpp"

class Movement
{
public:
	Movement() {  }
	string movimentToString();
	void stringToMoviment(const string& moviment);
	ChessPosition getPosFrom() { return m_positionFrom; }
	ChessPosition getPosTo() { return m_positionTo; }
	void setPosFrom(ChessPosition posFrom) { m_positionFrom = posFrom; }
	void setPosTo(ChessPosition posTo) { m_positionTo = posTo; }
private:
	ChessPosition m_positionFrom;
	ChessPosition m_positionTo;
};