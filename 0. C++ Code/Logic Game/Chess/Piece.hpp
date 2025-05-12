//
//  Piece.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "GameInfo.h"
using namespace std;

typedef enum {
    CPT_King,
    CPT_Queen,
    CPT_Rook,
    CPT_Bishop,
    CPT_Knight,
    CPT_Pawn,
    CPT_EMPTY
} ChessPieceType;

typedef enum {
    CPC_Black,
    CPC_White,
    CPC_NONE
} ChessPieceColor;

class Piece {

public:
    void setType(ChessPieceType type);
    void setColor(ChessPieceColor color);
    ChessPieceType getType() const;
    ChessPieceColor getColor() const;
    string toString() const;
    Piece(ChessPieceType type, ChessPieceColor color)/* : m_type(type), m_color(color)*/;
    Piece();
    void render(int posX, int posY);
private:
    ChessPieceType  m_type;
    ChessPieceColor m_color;
};


#endif /* Piece_hpp */