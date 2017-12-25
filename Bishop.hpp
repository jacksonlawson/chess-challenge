
#ifndef __BISHOP_HPP__
#define __BISHOP_HPP__

#include <Piece.hpp>

namespace chess_console
{

class Bishop : public Piece
{
public:
	static PieceType const type = PieceType::ptBishop;

	Bishop(Board *pbrdptr, PlayerColor pplayer, BoardPosition pposition)
		: Piece(pbrdptr, pplayer, pposition, Piece::PieceType::ptBishop)
	{

	}

	bool isValidMove(const BoardPosition pposition)
	{
		const BoardPosition cpos = getCurrentPosition();
		if (cpos == pposition)
			return false;

		int const ROWDIFF = pposition.row - cpos.row;
		int const COLDIFF = pposition.column - cpos.column;

		auto const diff = std::abs(ROWDIFF) - std::abs(COLDIFF);

		if (0 == diff)
		{
			auto p = getBoard()->getPieceAt(pposition.row, pposition.column);
			if (p)
			{
				if (p->getPlayerColor() == getPlayerColor())
				{
					std::cout << "Same color: " << pposition.tostring()
					<< " - " << cpos.tostring() << std::endl;
					return false;
				}
			}

			int rowstep = ROWDIFF < 0 ? -1 : 1;
			int colstep = COLDIFF < 0 ? -1 : 1;

			int const COUNT = std::abs(ROWDIFF);

			if (getPlayerColor() == Piece::PlayerColor::pcBlack)
			{
				rowstep = -rowstep;
				colstep = -colstep;
			}

			for (int i = 1; i < COUNT; ++i)
			{
				auto newpos = cpos.add(i * rowstep, i * colstep);
				p = getBoard()->getPieceAt(newpos);

				if (p)
				{
					std::cout << "Target position : " << pposition.tostring()
					<< " unreachable as there is piece at: " << newpos.tostring()
					<< std::endl;
					return false;
				}
			}

			return true;
		}

		return false;
	}

	std::string tostring() override
	{
		return getPlayerColorStr() + "B";
	}
};
}

#endif
