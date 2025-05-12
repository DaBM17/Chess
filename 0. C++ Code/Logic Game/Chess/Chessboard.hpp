//
//  Chessboard.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef Chessboard_hpp
#define Chessboard_hpp

#include <stdio.h>
#include "Piece.hpp"
#include "GameInfo.h"
#include "ChessPosition.hpp"



class Chessboard
{
public:
    Chessboard();    
    void LoadBoardFromFile(const string& path);
    VecOfPositions GetValidMoves (const ChessPosition& pos) const;
    bool MovePiece (const ChessPosition& posFrom, const ChessPosition& posTo);
    string ToString () const;
    VecOfPositions GetValidMovesBishop(const ChessPosition& p) const;
    VecOfPositions GetValidMovesPawn(const ChessPosition& p) const;
    VecOfPositions GetValidMovesQueen(const ChessPosition& p) const;
    VecOfPositions GetValidMovesKing(const ChessPosition& p) const;
    VecOfPositions GetValidMovesKnight(const ChessPosition& p) const;
    VecOfPositions GetValidMovesRook(const ChessPosition& p) const;
    void ColocarPeca(const ChessPosition& cp, const Piece& p);
    Piece ObtenirPeca(const ChessPosition& cp);
    bool DinsTauler(int x, int y) const;
    void render();

    //COMPROVA QUE LA POSICIO NO ESTIGUI OCUPADA PER UNA FITXA DEL MATEIX COLOR I ESTIGUI DINS DEL TAULER
    bool PotMoure(ChessPosition cp, int x, int y) const; 
    ChessPieceColor GetPieceColorAtPos(const ChessPosition& pos) const;
    ChessPieceType GetPieceTypeAtPos(const ChessPosition& pos) const;
private:
    Piece m_board[NUM_COLS][NUM_ROWS];
    void GenerarMovimentsValidsAmbDireccio(const ChessPosition& p, int dirX, int dirY, VecOfPositions& v) const;
    void esquerraSuperiorKnight(const ChessPosition& p, VecOfPositions& v) const;
    void dretaSuperiorKnight(const ChessPosition& p, VecOfPositions& v) const;
    void esquerraInferiorKnight(const ChessPosition& p, VecOfPositions& v) const;
    void dretaInferiorKnight(const ChessPosition& p, VecOfPositions& v) const;
    void movimentPawn(const ChessPosition& p, VecOfPositions& v) const;
    void movimentKing(const ChessPosition& p, VecOfPositions& v) const;
};


#endif /* Chessboard_hpp */
