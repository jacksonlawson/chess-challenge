
#ifndef __KING_HPP__
#define __KING_HPP__

#include <Piece.hpp>

namespace chess_console
{

class King : public Piece
{
public:
	static PieceType const type = PieceType::ptKing;

	King(Board *pbrdptr, PlayerColor pplayer, BoardPosition pposition)
		: Piece(pbrdptr, pplayer, pposition, Piece::PieceType::ptKing)
	{ }

	bool isValidMove(const BoardPosition pposition)
	{
		const BoardPosition cpos = getCurrentPosition();
		if (cpos == pposition)
		{
			return false;
		}

		int const ROWDIFF = std::abs(pposition.row - cpos.row);
		int const COLDIFF = std::abs(pposition.column - cpos.column);
		if ((ROWDIFF == 1 && COLDIFF == 0) ||
			(ROWDIFF == 0 && COLDIFF == 1) ||
			(ROWDIFF == 1 && COLDIFF == 1))
		{
			return true;
		}

		return false;
	}

	bool amIUnderCheck()
	{
		return amIUnderCheck(getCurrentPosition());
	}

	bool amIUnderCheck(const BoardPosition newpos)
	{
		//auto printThreatRelation = [this](auto p)
		//{
		//	std::cout << "Check to [" << tostring()
		//		<< "] By [" << p->tostring() << "]" << std::endl;
		//};

		auto verifyPath = [this](auto p, auto ppos, auto cpos, auto rowdiff, auto coldiff)
		{
			bool isthreat { true };

			for (auto stpos = cpos.add(rowdiff, coldiff);
					!(stpos == ppos);
					stpos = stpos.add(rowdiff, coldiff))
			{
				if (getBoard()->getPieceAt(stpos))
				{
					isthreat = false;
					break;
				}
			}

			if (isthreat)
			{
				std::cout << "++CHECK [" << p->tostring()
					<< " -> " << tostring() << "]++" << std::endl;
				//printThreatRelation(p);
			}

			return isthreat;
		};

		auto cpos = newpos;

		int fwddir = 1;
        if (getPlayerColor() == Piece::PlayerColor::pcBlack)
        {
        	fwddir = -1;
        }

        bool isKingUnderCheck { false };

		for (auto p : getBoard()->getAllLiveEnemyPieces(getPlayerColor()))
		{
			switch(p->getType())
			{
				case Piece::PieceType::ptPawn:
				{
					auto ppos = p->getCurrentPosition();
					if ((ppos.row - cpos.row) * fwddir == 1)
					{
						// Possible threat
						if (std::abs(ppos.column - cpos.column) == 1)
						{
							std::cout << "++CHECK [" << p->tostring()
								<< " -> " << tostring() << "]++" << std::endl;
							//printThreatRelation(p);
							isKingUnderCheck = true;
						}
					}
				}
				break;

				case Piece::PieceType::ptBishop:
				{
					auto ppos = p->getCurrentPosition();
					int rowdiff = ppos.row - cpos.row;
					int coldiff = ppos.column - cpos.column;

					if (std::abs(rowdiff) - std::abs(coldiff) == 0)
					{
						// Bishop could be threat and we need to check the path
						// from king to bishop for any protectors / obstacles

						rowdiff /= std::abs(rowdiff);
						coldiff /= std::abs(coldiff);

						if (verifyPath(p, ppos, cpos, rowdiff, coldiff))
							isKingUnderCheck = true;
					}
				}
				break;

				case Piece::PieceType::ptRook:
				{
					auto ppos = p->getCurrentPosition();
					int rowdiff = ppos.row - cpos.row;
					int coldiff = ppos.column - cpos.column;

					if (rowdiff != 0 && coldiff != 0)
						break;

					// Rook could be threat and we need to check the path
					// from king to bishop for any protectors / obstacles
					rowdiff /= (rowdiff != 0 ? std::abs(rowdiff) : 1);
					coldiff /= (coldiff != 0 ? std::abs(coldiff) : 1);

					if (verifyPath(p, ppos, cpos, rowdiff, coldiff))
						isKingUnderCheck = true;

					break;
				}
			}
		}

		return isKingUnderCheck;

/*		int const dir[][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1} };

		auto cpos = getCurrentPosition();

        // eliminate enemy pawn proximity and eliminate path which are covered
        // by protected pieces.
        int fwddir = 1;
        if (getPlayerColor() == Piece::PlayerColor::pcBlack)
        {
        	fwddir = -1;
        }

        int const enemypawncheck[][2] = ( {fwddir, fwddir}, {fwddir, -fwddir}, {0, 0} };

		for (int i = 0; enemypawncheck[i][0] !=0; ++i)
		{
			auto p = getBoard()->getPieceAt(cpos.add(fwdir, 0));

		    if (p && p.getPlayerColor() != getPlayerColor())
		    {
		    	return true;
		    }
		}

		// check 1st half of direction
		for (int i = 0; i < 8; ++i)
		{
			// Iterate from current position until it reach a piece
			// or end of board.
			int const VEND =  - cpos.row;
			int const HEND =  - cpos.column;
			auto cpos = getCurrentPosition();

			for (auto newpos = cpos.add(dir[i][0], dir[i[1]);
					newpos.isValid();
					newpos = newpos.add(dir[i][0], dir[i[1]))
			{
				auto p = getBoard()->getPieceAt(newpos);
				if (p)
				{
					if (getPlayerColor() == p->getPlayerColor())
					{
						break;
					}
				}
			}
		}

		return false;
		*/
	}

	std::string tostring() override
	{
		return getPlayerColorStr() + "K";
	}
};
}

#endif
