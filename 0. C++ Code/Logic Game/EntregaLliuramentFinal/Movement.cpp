#include "Movement.hpp"
#include <sstream>

string Movement::movimentToString()
{
	string posFrom = m_positionFrom.PosToString();
	string posTo = m_positionTo.PosToString();
	string moviment = posFrom + " " + posTo;
	return moviment;
}

void Movement::stringToMoviment(const string& moviment)
{
	string stringPosFrom, stringPosTo;
	stringstream movimentStream(moviment);
	movimentStream >> stringPosFrom >> stringPosTo;
}
