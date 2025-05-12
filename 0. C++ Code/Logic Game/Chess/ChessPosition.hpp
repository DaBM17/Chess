//
//  ChessPosition.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef ChessPosition_hpp
#define ChessPosition_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class ChessPosition
{
public:
    ChessPosition();
    void setPosX(int pos_x);
    void setPosY(int pos_y);
    int getPosX() const;
    int getPosY() const;
    //string PosToString(const ChessPosition& pos);
    string PosToString();
    void StringToPos(const string& pos);
    bool operator==(const ChessPosition& pos) const;
    ChessPosition(const string& pos);
private:
    int m_posX; //Column 0....7
    int m_posY; //Row 0....7
};


#endif

ostream& operator<<(ostream& output, ChessPosition& cp);

typedef vector<ChessPosition> VecOfPositions;
//vector<ChessPosition> VecOfPositions;