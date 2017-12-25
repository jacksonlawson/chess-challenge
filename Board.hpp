
#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>

#include <Piece.hpp>

class King;

namespace chess_console
{

class Board
{
public:
	struct MoveRecord
	{
		BoardPosition from, to;
		Piece::Ptr piece;
		Piece::Ptr taken;

		MoveRecord(BoardPosition pfrom, BoardPosition pto,
			Piece::Ptr ppiece, Piece::Ptr ptaken)
			: from(pfrom), to(pto), piece(ppiece), taken(ptaken)
		{ }
	};
	typedef std::vector<MoveRecord> MoveHistoryT;
	typedef std::vector<Piece::Ptr> PieceVectorT;

	Board()
	{
		initialize();
	}

	void reset();
	void initialize();
	std::string tostring();
	void print(bool piswhitesmove, bool pischeck);
	BoardPosition translateInput(std::string pin);
	Piece::Ptr validateUserInput(std::string const & pin, bool piswhitesmove);
	void loop();
	bool movePiece(Piece::Ptr p, BoardPosition newpos);

	Piece::Ptr getPieceAt(BoardPosition const & bp)
	{
		return getPieceAt(bp.row, bp.column);
	}

	Piece::Ptr getPieceAt(char const & prow, char const & pcol)
	{
		return m_boardArr[(int)prow][(int)pcol];
	}

	Piece::Ptr getLastPawnDoubleStep() const
	{
		return m_lastPawnDoubleStep;
	}

	const PieceVectorT & getAllLiveEnemyPieces(Piece::PlayerColor pc) const
	{
		if (pc == Piece::PlayerColor::pcWhite)
			return m_liveBlacks;

		return m_liveWhites;
	}

	const PieceVectorT & getAllLivePieces(Piece::PlayerColor pc) const
	{
		if (pc == Piece::PlayerColor::pcWhite)
			return m_liveWhites;

		return m_liveBlacks;
	}

private:
	Piece::Ptr m_boardArr[8][8];

	Piece::Ptr m_blackKing, m_whiteKing;

	PieceVectorT m_liveWhites;
	PieceVectorT m_liveBlacks;

	PieceVectorT m_deadWhites;
	PieceVectorT m_deadBlacks;

	MoveHistoryT m_history;

	Piece::Ptr m_lastPawnDoubleStep;

	bool m_isBlackUnderCheck, m_isWhiteUnderCheck;
};

}

#endif
