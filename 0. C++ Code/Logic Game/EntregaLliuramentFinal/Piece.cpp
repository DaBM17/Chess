//
//  Piece.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "Piece.hpp"
#include <string>
#include <iostream>
#include "../GraphicManager.h"

using namespace std;

void Piece::setType(ChessPieceType type)
{
    m_type = type;
}

void Piece::setColor(ChessPieceColor color)
{
    m_color = color;
}

ChessPieceType Piece::getType() const
{
    return m_type;
}

ChessPieceColor Piece::getColor() const
{
    return m_color;
}

string Piece::toString() const
{
    string ret;
    switch (m_color) {
    case CPC_Black:
        ret = "b";
        break;
    case CPC_White:
        ret = "w";
        break;
    case CPC_NONE:
        ret = "_";
        break;
    }
    switch (m_type) {
    case CPT_King:
        ret += "R";
        break;
    case CPT_Queen:
        ret += "D";
        break;
    case CPT_Rook:
        ret += "T";
        break;
    case CPT_Bishop:
        ret += "A";
        break;
    case CPT_Knight:
        ret += "C";
        break;
    case CPT_Pawn:
        ret += "P";
        break;
    case CPT_EMPTY:
        ret += "_";
        break;
    }
    return ret;
}

Piece::Piece(ChessPieceType type, ChessPieceColor color)
{
    m_type = type;
    m_color = color;
}

Piece::Piece()
{

}

void Piece::render(int posX, int posY)
{
    switch (m_type)
    {
    case CPT_King:
        if (m_color == CPC_Black)
        {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
        }
        else
        {
            if (m_color == CPC_White)
            {
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
            }
        }
        break;
    case CPT_Queen:
        if (m_color == CPC_Black)
        {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
        }
        else
        {
            if (m_color == CPC_White)
            {
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
            }
        }
        break;
    case CPT_Rook:
        if (m_color == CPC_Black)
        {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
        }
        else
        {
            if (m_color == CPC_White)
            {
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
            }
        }
        break;
    case CPT_Bishop:
        if (m_color == CPC_Black)
        {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
        }
        else
        {
            if (m_color == CPC_White)
            {
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
            }
        }
        break;
    case CPT_Knight:
        if (m_color == CPC_Black)
        {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
        }
        else
        {
            if (m_color == CPC_White)
            {
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
            }
        }
        break;
    case CPT_Pawn:
        if (m_color == CPC_Black)
        {
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
        }
        else
        {
            if (m_color == CPC_White)
            {
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
            }
        }
        break;
    default:
        break;
    }
}