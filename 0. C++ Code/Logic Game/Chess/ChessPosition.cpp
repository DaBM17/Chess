//
//  ChessPosition.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "ChessPosition.hpp"
#include "GameInfo.h"
#include <ostream>

/* Coordinate system:
    Y (rows)
  . ^
  . |  ***Black***
  4 |
  3 |
  2 |
  1 |  ***White***
 (0,0)----------> X (cols)
      a b c ...
*/

ChessPosition::ChessPosition()
{
    m_posX = 0;
    m_posY = 0;
}

void ChessPosition::setPosX(int pos_x)
{
    m_posX = pos_x;
}

void ChessPosition::setPosY(int pos_y)
{
    m_posY = pos_y;
}

int ChessPosition::getPosX() const
{
    return m_posX;
}

int ChessPosition::getPosY() const
{
    return m_posY;
}


string ChessPosition::PosToString()
{
    char pos1, pos2;
    /*
    * Les posicions a la classe venen guardades com enters, en aquest cas el que fem es passarla a string amb el format següent:
    * Lletra --> Coordenada a l'eix X
    * Número --> Coordenada a l'eix Y
    * Exemple: X=2 i Y=3, en string seria b3*/
    
    switch (m_posX)
    {
    case 0:
        pos1 = 'a';
        break;
    case 1:
        pos1 = 'b';
        break;
    case 2:
        pos1 = 'c';
        break;
    case 3:
        pos1 = 'd';
        break;
    case 4:
        pos1 = 'e';
        break;
    case 5:
        pos1 = 'f';
        break;
    case 6:
        pos1 = 'g';
        break;
    case 7:
        pos1 = 'h';
        break;
    }

    switch (m_posY)
    {
    case 0:
        pos2 = '1';
        break;
    case 1:
        pos2 = '2';
        break;
    case 2:
        pos2 = '3';
        break;
    case 3:
        pos2 = '4';
        break;
    case 4:
        pos2 = '5';
        break;
    case 5:
        pos2 = '6';
        break;
    case 6:
        pos2 = '7';
        break;
    case 7:
        pos2 = '8';
        break;
    }

    string posFinal;

    posFinal.push_back(pos1);
    posFinal.push_back(pos2);

    return posFinal;
}

void ChessPosition::StringToPos(const string& pos)
{
   /*
    * Amb aquest mètode fem que una posició codificada com string passi a ser dos números enters que representin les coordenades X i Y
    * Tractem el string que es passa com paràmetre com si fos un array de caràcters i segons la lletra (primer caràcter) que tinguem la X tindrà un valor
    * La coordenada Y serà un número per lo que serà el mateix tant en string com en enter
   */
    
    
    switch (pos[0])
    {
    case 'a':
        m_posX = 0;
        break;
    case 'b':
        m_posX = 1;
        break;
    case 'c':
        m_posX = 2;
        break;
    case 'd':
        m_posX = 3;
        break;
    case 'e':
        m_posX = 4;
        break;
    case 'f':
        m_posX = 5;
        break;
    case 'g':
        m_posX = 6;
        break;
    case 'h':
        m_posX = 7;
        break;
    }

    switch (pos[1])
    {
    case '1':
        m_posY = 0;
        break;
    case '2':
        m_posY = 1;
        break;
    case '3':
        m_posY = 2;
        break;
    case '4':
        m_posY = 3;
        break;
    case '5':
        m_posY = 4;
        break;
    case '6':
        m_posY = 5;
        break;
    case '7':
        m_posY = 6;
        break;
    case '8':
        m_posY = 7;
        break;
    }
}

bool ChessPosition::operator==(const ChessPosition& pos) const
{
    return ((m_posX == pos.m_posX) && (m_posY == pos.m_posY));
}

ChessPosition::ChessPosition(const string& pos)
{
    StringToPos(pos);
}

ostream& operator<<(ostream& output, ChessPosition& cp)
{
    string stringPosition;
    stringPosition = cp.PosToString();
    output << stringPosition;
    return output;
}
