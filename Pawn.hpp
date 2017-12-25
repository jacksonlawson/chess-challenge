
#include <Piece.hpp>

#ifndef __PAWN_HPP__
#define __PAWN_HPP__

namespace chess_console
{
class Pawn : public Piece
{
public:
	Pawn(Board *pbrdptr, PlayerColor pplayer, BoardPosition pposition)
		: Piece(pbrdptr, pplayer, pposition, Piece::PieceType::ptPawn)
		 , m_firstMove(false)
	{ }

	bool isValidMove(BoardPosition pposition)
	{
		//generateValidMovesFromCurrentPosition();
		//std::cout << "DBG: " << pposition.tostring() << std::endl;
		BoardPosition cpos = getCurrentPosition();
		char trow {1}, tcol {1};
		if (getPlayerColor() == PlayerColor::pcBlack)
			trow = tcol = -1;

		/*auto isForwardMove = [=](auto nextpos, auto oldpos)
		{
			return nextpos.row - oldpos.row > 0 && nextpos.column - oldpos.column > 0;
		};

		char trow {1}, tcol {1};
		if (getPlayerColor() == PlayerColor::pcBlack
				&& !isForwardMove(cpos, pposition))
		{
			return false;
		}
		else if (!isForwardMove(pposition, cpos))
			return false;
*/
		auto p = getBoard()->getPieceAt(pposition.row, pposition.column);
		if (p)
		{
			if (p->getPlayerColor() != getPlayerColor())
			{
				if (pposition.column - cpos.column == tcol &&
				 	pposition.row - cpos.row == trow)
				{
					return true;
				}
			}
			return false;
		}

		// Check for cross move even when no pawn or piece to kill
		// as 1st double step opens this move.
		auto pawn = getBoard()->getLastPawnDoubleStep();
		if (pawn)
		{
			std::cout << "Inside cross move" << std::endl;
			auto pawnpo = pawn->getCurrentPosition();
			auto crosspos = pawnpo.add(trow, 0);

			if (pposition == crosspos)
				return true;

			std::cout << crosspos.tostring() << " / " << pposition.tostring() << std::endl;
		}

		auto forwardpos = cpos.add(trow, 0);
		if (forwardpos == pposition)
		{
			return true;
		}

		if (!m_firstMove)
		{
			forwardpos = cpos.add(trow * 2, 0); // 2 step up for 1st move
			if (forwardpos == pposition)
				return true;
		}

		return false;
	}

	std::string tostring()
	{
		return getPlayerColorStr() + "P";
	}

private:
	bool m_firstMove;
	BoardPosition m_validPositions[4];
};
}
#endif
