//
//  CurrentGame.hpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#ifndef CurrentGame_hpp
#define CurrentGame_hpp

#include <stdio.h>
#include <string>
#include <time.h>
#include "GameInfo.h"
#include "Chessboard.hpp"
#include "QueueMovements.hpp"

using namespace std;

class CurrentGame {

public:
    CurrentGame();
    void init(GameMode mode, const string& intitialBoardFile, const string& movementsFile);
	bool updateAndRender(int mousePosX, int mousePosY, bool mouseStatus, int modeJoc);
    void end();
    void mostrarPosicionsValides(vector<ChessPosition> vec);
    void afegirMoviment(ChessPosition posFrom, ChessPosition posTo);
private:
    void canviDeJugador();
    void escriureMovimentsFitxer(const string& nomFitxer);
    void mostrarMissatge();
    bool updateAndRenderNormal(int mousePosX, int mousePosY, bool mouseStatus);
    bool updateAndRenderReplay(int mousePosX, int mousePosY, bool mouseStatus);
    bool movimentValid(ChessPosition position);
    string colorToString(ChessPieceColor color);
    string m_nomFitxerMoviments;
    Chessboard m_board;
    Piece m_pecaSeleccionada;
    ChessPosition m_pecaSeleccionadaPosicio;
    bool m_estaSeleccionada = false;
    GameMode m_modeJoc;
    ChessPieceColor m_jugadorActual = CPC_White;
    ChessPieceColor m_guanyador = CPC_NONE;
    VecOfPositions m_movimentsValids;
    QueueMovements m_moviments;
    int time = 0;
};

#endif /* CurrentGame_hpp */
