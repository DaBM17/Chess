//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "CurrentGame.hpp"
#include "GameInfo.h"
#include "../GraphicManager.h"
#include <iostream>
#include "Movement.hpp"
#include <fstream>

using namespace std;

CurrentGame::CurrentGame()
{

}

void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
    m_modeJoc = mode;
    m_board.LoadBoardFromFile(intitialBoardFile);
    if (m_modeJoc == GM_NORMAL)
    {
        m_nomFitxerMoviments = movementsFile;
    }
    else if (m_modeJoc == GM_REPLAY)
    {
        ifstream file(movementsFile);
        string posFrom, posTo;
        while (file >> posFrom >> posTo) {
            Movement move;
            move.stringToMoviment(posFrom);
            move.stringToMoviment(posTo);
            move.setPosFrom(posFrom);
            move.setPosTo(posTo);
            m_moviments.afegeix(move);
        }
    }
}

void CurrentGame::end()
{
    if (m_modeJoc == GM_NORMAL)
    {
        escriureMovimentsFitxer(m_nomFitxerMoviments);
    }
}

void CurrentGame::escriureMovimentsFitxer(const string& nomFitxer)
{
    fstream fitxerMoviments;
    fitxerMoviments.open(nomFitxer, std::fstream::out);

    if (fitxerMoviments.fail())
    {
        cerr << "Error: " << strerror(errno);
    }

    while (!m_moviments.esBuida())
    {
        Movement actual = m_moviments.getPrimer();
        string movimentActualString = actual.movimentToString();
        fitxerMoviments << movimentActualString << endl;
        m_moviments.treu();
    }

    fitxerMoviments.close();
}

void CurrentGame::mostrarPosicionsValides(vector<ChessPosition> vec)
{
    if (vec.size() != 0)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            cout << vec[i] << endl;
            GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + (vec[i].getPosX() * CELL_W), CELL_INIT_Y + (vec[i].getPosY() * CELL_H));
        }
    }
}

void CurrentGame::afegirMoviment(ChessPosition posFrom, ChessPosition posTo)
{
    Movement move;

    move.setPosFrom(posFrom);
    move.setPosTo(posTo);

    m_moviments.afegeix(move);
}

void CurrentGame::canviDeJugador()
{
    if (m_jugadorActual == CPC_Black)
    {
        m_jugadorActual = CPC_White;
    }
    else
    {
        if (m_jugadorActual == CPC_White)
        {
            m_jugadorActual = CPC_Black;
        }
    }

    m_estaSeleccionada = false;
    m_pecaSeleccionada.setType(CPT_EMPTY);
    m_pecaSeleccionada.setColor(CPC_NONE);
    m_movimentsValids.clear();
}

void CurrentGame::mostrarMissatge()
{
    int posTextX = CELL_INIT_X;
    int posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;

    if (m_guanyador == CPC_NONE)
    {
        std::string msg = "Juagdor actual: " + colorToString(m_jugadorActual);
        GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 0.8, msg);
    }
    else
    {
        std::string msg = "Ha guanyat el jugador " + colorToString(m_guanyador);
        GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 0.8, msg);
        
    }

    if (m_modeJoc == GM_NORMAL)
    {
        std::string msg = "Mode de Joc: Normal";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, CELL_INIT_Y + (CELL_H * NUM_ROWS) + 100, 0.8, msg);
    }
    else if (m_modeJoc == GM_REPLAY)
    {
        std::string msg = "Mode de Joc: Replay";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, CELL_INIT_Y + (CELL_H * NUM_ROWS) + 100, 0.8, msg);
    }
}

bool CurrentGame::updateAndRenderNormal(int mousePosX, int mousePosY, bool mouseStatus)
{
    int posX, posY;
    bool jocFinalitzat = false;
    m_modeJoc = GM_NORMAL;

    if ((mouseStatus) && (mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) &&
        (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) &&
        (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
    {
        posX = (mousePosX - CELL_INIT_X) / CELL_W;
        posY = (mousePosY - CELL_INIT_Y) / CELL_H;

        //PECA CLICADA
        ChessPosition position;
        position.setPosX(posX);
        position.setPosY(posY);
        m_board.ObtenirPeca(position);
        if (m_board.ObtenirPeca(position).getColor() == m_jugadorActual)
        {
            m_pecaSeleccionada = m_board.ObtenirPeca(position);
            m_pecaSeleccionadaPosicio = position;
            m_estaSeleccionada = true;
            m_movimentsValids = m_board.GetValidMoves(position);
        }
        else
        {
            if (m_estaSeleccionada)
            {
                if (movimentValid(position))
                {
                    if (m_board.ObtenirPeca(position).getType() == CPT_King)
                    {
                        m_guanyador = m_jugadorActual;
                        jocFinalitzat = true;
                    }
                    //m_pecaSeleccionadaPosicio --> posFrom, position --> posTo
                    Movement movimentRealitzat;
                    movimentRealitzat.setPosFrom(m_pecaSeleccionadaPosicio);
                    movimentRealitzat.setPosTo(position);
                    m_moviments.afegeix(movimentRealitzat);
                    m_board.MovePiece(m_pecaSeleccionadaPosicio, position);
                    canviDeJugador();
                }
            }
        }
    }

    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    m_board.render();
    mostrarPosicionsValides(m_movimentsValids);
    mostrarMissatge();

    return jocFinalitzat;
}

bool CurrentGame::updateAndRenderReplay(int mousePosX, int mousePosY, bool mouseStatus)
{
    bool jocFinalitzat = false;
    int sleep = clock();
    bool aux = true;

    if ((mouseStatus) && (mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) &&
        (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) &&
        (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
    {
        if (sleep > time + 200) {
            if (!m_moviments.esBuida())
            {
                Movement move;
                move = m_moviments.getPrimer();
                m_board.MovePiece(move.getPosFrom(), move.getPosTo());
                m_moviments.treu();
            }
            else
            {
                std::string msg = "No es poden fer mes moviments" + colorToString(m_guanyador);
                GraphicManager::getInstance()->drawFont(FONT_RED_30, CELL_INIT_X, CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60, 0.8, msg);
                jocFinalitzat = true;
                aux = false;
            }
            time = clock();
        }
    }

    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    m_board.render();
    mostrarPosicionsValides(m_movimentsValids);
    if (aux) mostrarMissatge();

    return jocFinalitzat;
}

bool CurrentGame::movimentValid(ChessPosition position)
{
    bool trobat = false;
    int i = 0;

    while ((!trobat) && (i < m_movimentsValids.size()))
    {
        if (m_movimentsValids[i] == position)
        {
            trobat = true;
        }
        else
        {
            i++;
        }
    }

    return trobat;
}

string CurrentGame::colorToString(ChessPieceColor color)
{
    string colorRetorn;

    if (color == CPC_Black)
    {
        colorRetorn = "Negres";
    }
    else if (color == CPC_White)
    {
        colorRetorn = "Blanques";
    }

    return colorRetorn;
}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus, int modeJoc)
{
    bool retorn = false;
    if (modeJoc == 1) //MODE JOC NORMAL
    {
        retorn = updateAndRenderNormal(mousePosX, mousePosY, mouseStatus);
    }
    else if (modeJoc == 2) //MODE REPLAY
    {
        retorn = updateAndRenderReplay(mousePosX, mousePosY, mouseStatus);
    }
    return retorn;
}

#if 0
bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus) 
{
    
    //TODO 1: Interactuar amb la crida per dibuixar gràfics (sprites).
    // 	      Dibuixar a pantalla el gràfic amb el tauler buit.
    //--------------------------------------------------------------
    int posX = 0;
    int posY = 7;
    ChessPosition cPosFrom, cPosTo;
    Piece pecaSeleccionada;
    bool pecaClicada = false;
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    /*
        if ((!mouseStatus) && (mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) &&
            (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) &&
            (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
            GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE,
                CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
    */

    m_board.render();

    int posTextX = CELL_INIT_X;
    int posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;
    std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 0.8, msg);
   
    if ((mouseStatus) && (mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) && (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) && (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
    {
        posX = (mousePosX - CELL_INIT_X) / CELL_W;
        cout << posX << endl;
        posY = (mousePosY - CELL_INIT_Y) / CELL_H;
        cout << posY << endl;
        cPosFrom.setPosX(posX);
        cPosFrom.setPosY(posY);
        m_board.GetValidMoves(cPosFrom);
        cout << "TAMANY: " << m_board.GetValidMoves(cPosFrom).size() << endl;
        if (m_board.GetPieceTypeAtPos(cPosFrom) != CPT_EMPTY)
        {
            pecaClicada = true;
            cout << "CASELLA OCUPADA" << endl;
            pecaSeleccionada = m_board.ObtenirPeca(cPosFrom);
        }
        mostrarPosicionsValides(m_board.GetValidMoves(cPosFrom));
    }

    if (pecaClicada)
    {
        if ((mouseStatus) && (mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) && (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) && (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
        {
            cout << "PECA CLICADA" << endl;
            cPosTo.setPosX((mousePosX - CELL_INIT_X) / CELL_W);
            cPosTo.setPosY((mousePosY - CELL_INIT_Y) / CELL_H);
            m_board.MovePiece(cPosFrom, cPosTo);
        }
    }

    //TODO 1.1 Afegir l'include de GraphicManager --> #include "../GraphicManager.h"
    //TODO 1.2 Fer la crida de dibuixar un sprite --> GraphicManager::getInstance()->drawSprite(image, posX, posY);
    //	    Per començar podem cridar el drawSprite amb els params --> (IMAGE_BOARD,0,0)



    /*
    //TODO 1.3: Dibuixar a pantalla el gràfic amb el tauler i un peó blanc a la posició (0,0) de la pantalla
    if ((mouseStatus) && (mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) &&
        (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) &&
        (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
    {
        
        //GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
    }

    int posTextX = CELL_INIT_X;
    int posTextY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;

    std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY, 0.8, msg);*/
    //TODO 1.3: Dibuixar a pantalla el gràfic amb el tauler i un peó blanc a la casella (0,0) del tauler
 



    //TODO 1.4: Dibuixar a pantalla el gràfic amb el tauler i un peó blanc a la casella (posX, posY) del tauler
 
 




    //TODO 2: Interacció amb el mouse
    //------------------------------------------
    // TODO 2.1: Dibuixar el peó a sobre del tauler només si estem pressionant el botó esquerre del mouse
    //          Si no l'estem pressionant només s'ha de dibuixar el tauler sense el peó

 




    // TODO 2.2 Dibuixar el peó a sobre del tauler només si estem pressionant el botó esquerre del mouse dins dels límits del tauler
    //          Si no l'estem pressionant o l'estem pressionant fora dels límits del tauler només s'ha de dibuixar el tauler sense el peó





    // TODO 2.3 Dibuixar el peó a sobre del tauler només si estem pressionant el botó esquerre del mouse dins dels límits del tauler
    //          S'ha de dibuixar el peó a la casella sobre la que estem clicant amb el ratolí
    //          Si no l'estem pressionant o l'estem pressionant fora dels límits del tauler només s'ha de dibuixar el tauler sense el peó
 





    //TODO 3: Imprimir text per pantalla
    //------------------------------------------
    // TODO 3.1: Imprimir les coordenades de la posició actual del ratolí a sota del tauler







    //TODO 4: Mostrar l’estat inicial del joc amb totes les peces col·locades a la seva posició inicial
    //------------------------------------------
 

    //m_board.render();

    return false;

}
#endif
