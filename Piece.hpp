
#ifndef __PIECE_HPP__
#define __PIECE_HPP__

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <sstream>

namespace chess_console
{
class Board;

struct BoardPosition
{
	char row, column;

	BoardPosition() : row(-1), column(-1)
	{ }

	BoardPosition(char prow, char pcol) : row(prow), column(pcol)
	{ }

	bool operator == (const BoardPosition & val) const
	{
		return row == val.row && column == val.column;
	}

	BoardPosition add(const char prow, const char pcol) const
	{
		return BoardPosition { static_cast<char>(row + prow),
							   static_cast<char>(column + pcol) };
	}

	bool isvalid()
	{
		return (row >= 0 && row < 8 && column >= 0 && column < 8);
	}

	std::string tostring() const
	{
		std::stringstream ss;
		ss << "[" << (int)row << ":" << (int)column << "]";
		return ss.str();
	}
};


class Piece
{
public:
	enum class PlayerColor : int
	{
		pcWhite,
		pcBlack
	};

	enum class PieceType : int
	{
		ptPawn,
		ptBishop,
		ptRook,
		ptKing,
		ptKnight,
		ptQueen
	};

	typedef std::shared_ptr<Piece> Ptr;

	Piece(Board *pbrdptr, PlayerColor pplayer, BoardPosition pposition,
			PieceType ppt)
		: m_brdptr(pbrdptr), m_player(pplayer), m_position(pposition),
		  m_type(ppt)
	{ }

	BoardPosition getCurrentPosition() const { return m_position; }
	PlayerColor getPlayerColor() const { return m_player; }
	std::string getPlayerColorStr() const
	{
		if (PlayerColor::pcWhite == m_player)
			return "W";
		return "B";
	}

	virtual bool isValidMove(BoardPosition pposition) = 0;
	virtual std::string tostring() = 0;

	void makeMove(BoardPosition pposition)
	{
		m_position = pposition;
	}

	Board *getBoard() const { return m_brdptr; }

	PieceType getType() const { return m_type; }

private:
	PlayerColor m_player;
	BoardPosition m_position;
	Board *m_brdptr;
	PieceType m_type;
};
}

#endif
