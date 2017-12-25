
#ifndef __ROOK_HPP__
#define __ROOK_HPP__

#include <Piece.hpp>


namespace chess_console
{

class Rook : public Piece
{
public:
	static PieceType const type = PieceType::ptRook;

	Rook(Board *pbrdptr, PlayerColor pplayer, BoardPosition pposition)
		: Piece(pbrdptr, pplayer, pposition, Piece::PieceType::ptRook)
	{

	}

	bool isValidMove(const BoardPosition pposition)
	{
		const BoardPosition cpos = getCurrentPosition();
		if (cpos == pposition)
			return false;

		auto lmbexp = [this](auto & p) {
			if (p)
			{
				if (p->getPlayerColor() == getPlayerColor())
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			return true;
		};

		auto p = getBoard()->getPieceAt(pposition.row, pposition.column);
		if (lmbexp(p) == false)
		{
			return false;
		}

		// Check for obstacles like a piece of same color is in the path / target
		// piece of opposite color is in between target and current position.
		// If target position has opposite color piece take it out of active list.
		if (cpos.row == pposition.row)
		{
//			std::cout << "Inside the ROOK same row move" << std::endl;
			int const COLDIFF = pposition.column - cpos.column;
			int const sign = COLDIFF > 0 ? 1 : -1;
			for (int i = 1; i < std::abs(COLDIFF) + 1; ++i)
			{
				auto p = getBoard()->getPieceAt(cpos.row, cpos.column + (i * sign));
				if (lmbexp(p) == false)
				{
					std::cout << "Invalid move for ROOK column wise" << std::endl;
					return false;
				}
			}
			return true;
		}

		if (cpos.column == pposition.column)
		{
			int const ROWDIFF = pposition.row - cpos.row;
			int const sign = ROWDIFF > 0 ? 1 : -1;
			for (int i = 1; i < std::abs(ROWDIFF) + 1; ++i)
			{
				auto p = getBoard()->getPieceAt(cpos.row + (i * sign), cpos.column);
				if (lmbexp(p) == false)
				{
					std::cerr << "Invalid move for ROOK row wise" << std::endl;
					return false;
				}
			}
			return true;
		}
		return false;
	}

	std::string tostring() override
	{
		return getPlayerColorStr() + "R";
	}
};
}

#endif
