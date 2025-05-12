//
//  Chessboard.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "Chessboard.hpp"
#include "ChessPosition.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Chessboard::Chessboard()
{
	int i, j;
	for (i = 0; i < NUM_COLS; i++)
	{
		for (j = 0; j < NUM_ROWS; j++)
		{
			m_board[i][j].setType(CPT_EMPTY);
			m_board[i][j].setColor(CPC_NONE);
		}
	}
}

void Chessboard::LoadBoardFromFile(const string& path)
{
	fstream file;
	//char separador, tipusFile[32], colorFile[32], posXfile[32], posYfile[32];
	char separador, tipusFile, colorFile;
	ChessPieceType tipus;
	ChessPieceColor color;
	ChessPosition cp;
	Piece piece;
	string stringPosition;

	file.open(path);

	if (!file.is_open())
	{
		cout << "no s'ha pogut obrir l'arxiu" << endl;
	}
	else
	{
		string line;
		while (getline(file, line))
		{
			stringstream streamLine(line);
			//LLECTURA DEL FITXER
			streamLine >> colorFile >> separador >> tipusFile >> stringPosition;
			//cout << stringPosition << endl;

			//PROVA
			//COLOR
			if (colorFile == '0')
			{
				color = CPC_White;
			}
			else
			{
				if (colorFile == '1')
				{
					color = CPC_Black;
				}
				else
				{
					color = CPC_NONE;
				}
			}

			//TIPUS
			switch (tipusFile)
			{
			case 'R':
				tipus = CPT_King;
				break;
			case 'D':
				tipus = CPT_Queen;
				break;
			case 'T':
				tipus = CPT_Rook;
				break;
			case 'A':
				tipus = CPT_Bishop;
				break;
			case 'C':
				tipus = CPT_Knight;
				break;
			case 'P':
				tipus = CPT_Pawn;
				break;
			default:
				tipus = CPT_EMPTY;
				break;
			}

			//POSICIÓ			
			cp.StringToPos(stringPosition);
			//TIPUS I COLOR DE LA PEÇA
			piece.setColor(color);
			piece.setType(tipus);
			ColocarPeca(cp, piece);
		}
	}

	file.close();
}

VecOfPositions Chessboard::GetValidMoves(const ChessPosition& pos) const
{
	Piece p = m_board[pos.getPosX()][pos.getPosY()];
	ChessPieceColor cpc = p.getColor();
	ChessPieceType cpt = p.getType();
	vector <ChessPosition> v_moves;

	switch (cpt)
	{
	case CPT_Bishop:
		v_moves = GetValidMovesBishop(pos);
		break;
	case CPT_King:
		v_moves = GetValidMovesKing(pos);
		break;
	case CPT_Knight:
		v_moves = GetValidMovesKnight(pos);
		break;
	case CPT_Pawn:
		v_moves = GetValidMovesPawn(pos);
		break;
	case CPT_Queen:
		v_moves = GetValidMovesQueen(pos);
		break;
	case CPT_Rook:
		v_moves = GetValidMovesRook(pos);
		break;
	default:
		break;
	}

	return v_moves;
}

bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)
{
	VecOfPositions possible = GetValidMoves(posFrom);
	for (int i = 0; i < possible.size(); ++i) {
		if (posTo.getPosX() == possible[i].getPosX() && posTo.getPosY() == possible[i].getPosY()) {
			m_board[posTo.getPosX()][posTo.getPosY()].setColor(m_board[posFrom.getPosX()][posFrom.getPosY()].getColor());
			m_board[posTo.getPosX()][posTo.getPosY()].setType(m_board[posFrom.getPosX()][posFrom.getPosY()].getType());
			m_board[posFrom.getPosX()][posFrom.getPosY()].setColor(CPC_NONE);
			m_board[posFrom.getPosX()][posFrom.getPosY()].setType(CPT_EMPTY);
			return true;
		}
	}
	return false;
}

string Chessboard::ToString() const
{
	string board = "";
	for (int i = 0; i < NUM_ROWS; ++i) {
		for (int j = 0; j < NUM_COLS; ++j) {
			board += m_board[j][i].toString();
			board += " ";
		}
		board += "\n";
	}
	return board;
}

//METODES PER OBTENIR MOVIMENTS VALIDS

VecOfPositions Chessboard::GetValidMovesBishop(const ChessPosition& p) const
{
	vector<ChessPosition> v_moves;

	GenerarMovimentsValidsAmbDireccio(p, -1, 1, v_moves);
	GenerarMovimentsValidsAmbDireccio(p, -1, -1, v_moves);
	GenerarMovimentsValidsAmbDireccio(p, 1, 1, v_moves);
	GenerarMovimentsValidsAmbDireccio(p, 1, -1, v_moves);

	return v_moves;
}

VecOfPositions Chessboard::GetValidMovesPawn(const ChessPosition& p) const
{
	vector<ChessPosition> v_moves;

	movimentPawn(p, v_moves);

	return v_moves;
}

VecOfPositions Chessboard::GetValidMovesQueen(const ChessPosition& p) const
{
	vector<ChessPosition> v_moves;

	//DIAGONAL
	GenerarMovimentsValidsAmbDireccio(p, -1, +1, v_moves);
	GenerarMovimentsValidsAmbDireccio(p, -1, -1, v_moves);
	GenerarMovimentsValidsAmbDireccio(p, +1, +1, v_moves);
	GenerarMovimentsValidsAmbDireccio(p, +1, -1, v_moves);
	//VERTICAL
	GenerarMovimentsValidsAmbDireccio(p, 0, +1, v_moves);
	GenerarMovimentsValidsAmbDireccio(p, 0, -1, v_moves);
	//HORIZONTAL
	GenerarMovimentsValidsAmbDireccio(p, +1, 0, v_moves);
	GenerarMovimentsValidsAmbDireccio(p, -1, 0, v_moves);

	return v_moves;
}

VecOfPositions Chessboard::GetValidMovesKing(const ChessPosition& p) const
{
	vector<ChessPosition> v_moves;

	movimentKing(p, v_moves);

	return v_moves;
}

VecOfPositions Chessboard::GetValidMovesKnight(const ChessPosition& p) const
{
	vector<ChessPosition> v_moves;

	esquerraSuperiorKnight(p, v_moves);
	dretaSuperiorKnight(p, v_moves);
	esquerraInferiorKnight(p, v_moves);
	dretaInferiorKnight(p, v_moves);

	return v_moves;
}

VecOfPositions Chessboard::GetValidMovesRook(const ChessPosition& p) const
{
	vector<ChessPosition> v_moves;

	//VERTICAL
	GenerarMovimentsValidsAmbDireccio(p, 0, +1, v_moves);
	GenerarMovimentsValidsAmbDireccio(p, 0, -1, v_moves);
	//HORIZONTAL
	GenerarMovimentsValidsAmbDireccio(p, +1, 0, v_moves);
	GenerarMovimentsValidsAmbDireccio(p, -1, 0, v_moves);

	return v_moves;
}

void Chessboard::GenerarMovimentsValidsAmbDireccio(const ChessPosition& p, int dirX, int dirY, VecOfPositions& v) const
{ 
	Piece pieceToMove = m_board[p.getPosX()][p.getPosY()];
	ChessPosition posAux;
	bool continuar = true;

	int x = p.getPosX() + dirX, y = p.getPosY() + dirY;
	while (DinsTauler(x, y) && (continuar))
	{
		if ((m_board[x][y].getType() == CPT_EMPTY))
		{
			posAux.setPosX(x);
			posAux.setPosY(y);
			v.push_back(posAux);
			x += dirX;
			y += dirY;
		}
		else
		{
			if (m_board[x][y].getColor() != pieceToMove.getColor()) //COMPROVAR SI POT MENJAR UNA PEÇA
			{
				posAux.setPosX(x);
				posAux.setPosY(y);
				v.push_back(posAux);
			}
			continuar = false;
		}
	}
}

void Chessboard::movimentPawn(const ChessPosition& p, VecOfPositions& v) const
{
	ChessPosition posAux;
	Piece piece = m_board[p.getPosX()][p.getPosY()];
	bool continuar = true;

	if (piece.getColor() == CPC_Black) //PEO NEGRE
	{
		if (p.getPosY() == 6) //FILA PEONS NEGRES
		{
			if (m_board[p.getPosX()][p.getPosY() - 1].getType() == CPT_EMPTY)
			{
				posAux.setPosX(p.getPosX());
				posAux.setPosY(p.getPosY() - 1);
				v.push_back(posAux);
				if ((m_board[p.getPosX()][p.getPosY() - 2].getType() == CPT_EMPTY))
				{
					posAux.setPosX(p.getPosX());
					posAux.setPosY(p.getPosY() - 2);
					v.push_back(posAux);
				}
			}
		}
		else
		{
			if (DinsTauler(p.getPosX(), p.getPosY() - 1))
			{
				if (m_board[p.getPosX()][p.getPosY() - 1].getType() == CPT_EMPTY)
				{
					posAux.setPosX(p.getPosX());
					posAux.setPosY(p.getPosY() - 1);
					v.push_back(posAux);
				}
			}
		}

		if (DinsTauler(p.getPosX() - 1, p.getPosY() - 1))
		{
			if (m_board[p.getPosX() - 1][p.getPosY() - 1].getColor() != piece.getColor() && m_board[p.getPosX() - 1][p.getPosY() - 1].getColor() != CPC_NONE)
			{
				posAux.setPosX(p.getPosX() - 1);
				posAux.setPosY(p.getPosY() - 1);
				v.push_back(posAux);
			}
		}

		if (DinsTauler(p.getPosX() + 1, p.getPosY() - 1))
		{
			if (m_board[p.getPosX() + 1][p.getPosY() - 1].getColor() != piece.getColor() && m_board[p.getPosX() + 1][p.getPosY() - 1].getColor() != CPC_NONE)
			{
				posAux.setPosX(p.getPosX() + 1);
				posAux.setPosY(p.getPosY() - 1);
				v.push_back(posAux);
			}
		}
	}
	else //PEO BLANC
	{
		if (p.getPosY() == 1)
		{
			if (m_board[p.getPosX()][p.getPosY() + 1].getType() == CPT_EMPTY)
			{
				posAux.setPosX(p.getPosX());
				posAux.setPosY(p.getPosY() + 1);
				v.push_back(posAux);
				if ((m_board[p.getPosX()][p.getPosY() + 2].getType() == CPT_EMPTY))
				{
					posAux.setPosX(p.getPosX());
					posAux.setPosY(p.getPosY() + 2);
					v.push_back(posAux);
				}
			}
		}
		else
		{
			if (DinsTauler(p.getPosX(), p.getPosY() + 1))
			{
				if (m_board[p.getPosX()][p.getPosY() + 1].getType() == CPT_EMPTY)
				{
					posAux.setPosX(p.getPosX());
					posAux.setPosY(p.getPosY() + 1);
					v.push_back(posAux);
				}
			}
		}

		if (DinsTauler(p.getPosX() - 1, p.getPosY() + 1))
		{
			if (m_board[p.getPosX() - 1][p.getPosY() + 1].getColor() != piece.getColor() && m_board[p.getPosX() - 1][p.getPosY() + 1].getColor() != CPC_NONE)
			{
				posAux.setPosX(p.getPosX() - 1);
				posAux.setPosY(p.getPosY() + 1);
				v.push_back(posAux);
			}
		}

		if (DinsTauler(p.getPosX() + 1, p.getPosY() + 1))
		{
			if (m_board[p.getPosX() + 1][p.getPosY() + 1].getColor() != piece.getColor() && m_board[p.getPosX() + 1][p.getPosY() + 1].getColor() != CPC_NONE)
			{
				posAux.setPosX(p.getPosX() + 1);
				posAux.setPosY(p.getPosY() + 1);
				v.push_back(posAux);
			}
		}
	}
}

void Chessboard::esquerraSuperiorKnight(const ChessPosition& p, VecOfPositions& v) const
{
	ChessPosition posAux;
	int x = p.getPosX(), y = p.getPosY(), novaX, novaY;
	Piece pieceAux = m_board[x][y];

	novaX = x - 2;
	novaY = y - 1;
	if (PotMoure(p, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}
	novaX = x - 1;
	novaY = y - 2;
	if (PotMoure(p, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}
}

void Chessboard::dretaSuperiorKnight(const ChessPosition& p, VecOfPositions& v) const
{
	ChessPosition posAux;
	int x = p.getPosX(), y = p.getPosY(), novaX, novaY;
	Piece pieceAux = m_board[x][y];

	novaX = x + 1;
	novaY = y - 2;
	if (PotMoure(p, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}
	novaX = x + 2;
	novaY = y - 1;
	if (PotMoure(p, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}
}

void Chessboard::esquerraInferiorKnight(const ChessPosition& p, VecOfPositions& v) const
{
	ChessPosition posAux;
	int x = p.getPosX(), y = p.getPosY(), novaX, novaY;
	Piece pieceAux = m_board[x][y];

	novaX = x - 2;
	novaY = y + 1;
	if (PotMoure(p, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}
	novaX = x - 1;
	novaY = y + 2;
	if (PotMoure(p, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}
}

void Chessboard::dretaInferiorKnight(const ChessPosition& p, VecOfPositions& v) const
{
	ChessPosition posAux;
	int x = p.getPosX(), y = p.getPosY(), novaX, novaY;
	Piece pieceAux = m_board[x][y];

	novaX = x + 1;
	novaY = y + 2;
	if (PotMoure(p, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}
	novaX = x + 2;
	novaY = y + 1;
	if (PotMoure(p, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}
}

void Chessboard::movimentKing(const ChessPosition& position, VecOfPositions& v) const
{
	ChessPosition posAux;
	int x = position.getPosX(), y = position.getPosY(), novaX, novaY;
	Piece piece = m_board[x][y];
	bool continuar = true;

	//CANTONADA ESQUERRA SUPERIOR
	novaX = x - 1;
	novaY = y + 1;
	if (PotMoure(position, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}

	//SUPERIOR
	novaX = x;
	novaY = y + 1;
	if (PotMoure(position, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}

	//CANTONADA DRETA SUPERIOR
	novaX = x + 1;
	novaY = y + 1;	
	if (PotMoure(position, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}

	//ESQUERRA
	novaX = x - 1;
	novaY = y;
	if (PotMoure(position, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}

	//DRETA
	novaX = x + 1;
	novaY = y;
	if (PotMoure(position, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}

	//CANTONADA ESQUERRA INFERIOR
	novaX = x - 1;
	novaY = y - 1;	
	if (PotMoure(position, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}

	//INFERIOR
	novaX = x;
	novaY = y - 1;	
	if (PotMoure(position, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}

	//CANTONADA DRETA INFERIOR
	novaX = x + 1;
	novaY = y - 1;	
	if (PotMoure(position, novaX, novaY))
	{
		posAux.setPosX(novaX);
		posAux.setPosY(novaY);
		v.push_back(posAux);
	}
}

//METODES AUXILIARS

void Chessboard::ColocarPeca(const ChessPosition& cp, const Piece& p)
{
	m_board[cp.getPosX()][cp.getPosY()].setColor(p.getColor());
	m_board[cp.getPosX()][cp.getPosY()].setType(p.getType());
}

Piece Chessboard::ObtenirPeca(const ChessPosition& cp)
{
	Piece pieceAux = m_board[cp.getPosX()][cp.getPosY()];
	return pieceAux;
}

bool Chessboard::DinsTauler(int x, int y) const
{
	if ((x >= 0) && (x <= 7) && (y >= 0) && (y <= 7))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Chessboard::render()
{
	int i, j;

	for (i = 0; i < NUM_COLS; i++)
	{
		for (j = 0; j < NUM_ROWS; j++)
		{
			m_board[i][j].render(i, j);
		}
	}
}

bool Chessboard::PotMoure(ChessPosition cp, int x, int y) const
{
	ChessPieceColor cpc = m_board[cp.getPosX()][cp.getPosY()].getColor();
	ChessPieceType cpt = m_board[cp.getPosX()][cp.getPosY()].getType();
	if (DinsTauler(x, y))
	{
		if ((m_board[x][y].getType() == CPT_EMPTY) || (m_board[x][y].getColor() != cpc))
		{
			return true;
		}
	}
	return false;
}

ChessPieceColor Chessboard::GetPieceColorAtPos(const ChessPosition& pos) const
{
	Piece piece;
	ChessPieceColor cpc;
	piece = m_board[pos.getPosX()][pos.getPosY()];
	cpc = piece.getColor();
	return cpc;
}

ChessPieceType Chessboard::GetPieceTypeAtPos(const ChessPosition& pos) const
{
	Piece piece;
	ChessPieceType cpt;
	piece = m_board[pos.getPosX()][pos.getPosY()];
	cpt = piece.getType();
	return cpt;
}
