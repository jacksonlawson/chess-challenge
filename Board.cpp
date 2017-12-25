
#include <Board.hpp>
#include <Pawn.hpp>
#include <Rook.hpp>
#include <Bishop.hpp>
#include <King.hpp>

namespace chess_console
{
void Board::reset()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			m_boardArr[i][j].reset();
		}
	}

	//m_activeWhites.clear();
	m_deadWhites.clear();
	//m_activeBlacks.clear();
	m_deadBlacks.clear();

	m_history.clear();

	initialize();
}

void Board::initialize()
{
	/// initiating pawns for white and black
	for (char i = 0; i < 8; ++i)
	{
		Piece::Ptr p = std::make_shared<Pawn>(this, Piece::PlayerColor::pcWhite, BoardPosition {(char)1, (char)i});
		m_boardArr[1][i] = p;
		m_liveWhites.push_back(p);

		p = std::make_shared<Pawn>(this, Piece::PlayerColor::pcBlack, BoardPosition {(char)6, (char)i});
		m_boardArr[6][i] = p;
		m_liveBlacks.push_back(p);
	}

	std::vector<char> rookcolpos = {0, 7};
	for (auto iter = rookcolpos.begin(); iter != rookcolpos.end(); ++iter)
	{
		Piece::Ptr rook = std::make_shared<Rook>(this, Piece::PlayerColor::pcWhite, BoardPosition {0, *iter});
		m_boardArr[0][*iter] = rook;
		m_liveWhites.push_back(rook);
	}

	for (auto iter = rookcolpos.begin(); iter != rookcolpos.end(); ++iter)
	{
		Piece::Ptr rook = std::make_shared<Rook>(this, Piece::PlayerColor::pcBlack, BoardPosition {7, *iter});
		m_boardArr[7][*iter] = rook;
		m_liveBlacks.push_back(rook);
	}

	std::vector<char> bishopcolpos = {2, 5};
	for (auto iter = bishopcolpos.begin(); iter != bishopcolpos.end(); ++iter)
	{
		Piece::Ptr bishop = std::make_shared<Bishop>(this, Piece::PlayerColor::pcWhite, BoardPosition {0, *iter});
		m_boardArr[0][*iter] = bishop;
		m_liveWhites.push_back(bishop);
	}

	for (auto iter = bishopcolpos.begin(); iter != bishopcolpos.end(); ++iter)
	{
		Piece::Ptr bishop = std::make_shared<Bishop>(this, Piece::PlayerColor::pcBlack, BoardPosition {7, *iter});
		m_boardArr[7][*iter] = bishop;
		m_liveBlacks.push_back(bishop);
	}

	Piece::Ptr king = std::make_shared<King>(this, Piece::PlayerColor::pcWhite, BoardPosition {0, 4});
	m_boardArr[0][4] = king;
	m_liveWhites.push_back(king);

	m_whiteKing = king;

	king = std::make_shared<King>(this, Piece::PlayerColor::pcBlack, BoardPosition {7, 4});
	m_boardArr[7][4] = king;
	m_liveBlacks.push_back(king);

	m_blackKing = king;
}

std::string Board::tostring()
{
	std::stringstream ss;

	for (int i = 0; i < 28; ++i)
	{
		ss << "-";
	}

	ss << std::endl;

	for (int i = 7; i >= 0; --i)
	{
		ss << i+1 << "|";
		for (int j = 0; j < 8; ++j)
		{
			auto p = m_boardArr[i][j];
			if (p)
			{
				ss << p->tostring() << " ";
			}
			else
			{
				ss << ".. ";
			}
		}
		ss << "|";

		auto displayDeadlist = [&ss](auto deadlist)
		{
			for (auto p : deadlist)
				ss << p->tostring() << " ";
		};

		if (i == 7)
		{
			displayDeadlist(m_deadWhites);
		}

		if (i == 0)
		{
			displayDeadlist(m_deadBlacks);
		}

		ss << std::endl;
	}

	for (int i = 0; i < 28; ++i)
	{
		ss << "-";
	}

	ss << std::endl << "  ";
	for (int i = 0; i < 8; ++i)
	{
		ss << static_cast<char>('A' + i) << "  ";
	}

	ss << std::endl;

	return ss.str();
}

void Board::print(bool piswhitesmove, bool pischeck)
{
	std::cout << tostring() << std::endl
			<< "In check: " << (pischeck ? 'Y' : 'N' ) << std::endl //<< m_check
			<< "Move: " << (piswhitesmove ? 'W' : 'B') << std::endl;
}

BoardPosition Board::translateInput(std::string pin)
{
	if (pin.length() > 2
		|| (pin[0] < 'A' && pin[0] > 'H')
		|| (pin[0] < 'a' && pin[0] > 'h')
		|| (pin[1] < '1' && pin[1] > '8'))
	{
		std::cout << "Invalid input position: " << pin << std::endl;
		return BoardPosition {};
	}

	auto row = static_cast<char>((pin[1] - '1'));
	auto col = static_cast<char>((std::toupper(pin[0]) - 'A'));

	return BoardPosition {row, col};
}

Piece::Ptr Board::validateUserInput(std::string const & pin, bool piswhitesmove)
{

//		std::cout << "DBG" << row << ":" << col << std::endl;
	auto pos = translateInput(pin);

	if (false == pos.isvalid())
		return nullptr;

	auto p = m_boardArr[pos.row][pos.column];
	if (!p)
	{
		std::cout << "No piece on the specified position: " << pin << std::endl;
		return nullptr;
	}

	if (piswhitesmove)
	{
		if (Piece::PlayerColor::pcWhite != p->getPlayerColor())
		{
			std::cout << "It's WHITE's move" << std::endl;
			return nullptr;
		}
	}
	else
	{
		if (Piece::PlayerColor::pcBlack != p->getPlayerColor())
		{
			std::cout << "It's BLACK's move" << std::endl;
			return nullptr;
		}
	}

	return p;
}

void Board::loop()
{
	bool whitesmove {true};
	bool ischeck {false};

	while(true)
	{
		print(whitesmove, ischeck);

		std::string from;
		std::string to;

		std::cout << "Enter piece to move: ";
		std::cin >> from;

		auto p = validateUserInput(from, whitesmove);
		if (!p)
			continue;

		std::cout << "Enter target position: ";
		std::cin >> to;

		auto newpos = translateInput(to);
		if (!newpos.isvalid())
		{
			//std::cout << " HUH UNEXPECTED ~~" << std::endl;
			continue;
		}

		if (!p->isValidMove(newpos))
			continue;

		if (movePiece(p, newpos))
		{
			ischeck = whitesmove ? m_isBlackUnderCheck : m_isWhiteUnderCheck;
			whitesmove = !whitesmove;
		}
	}
}

bool Board::movePiece(Piece::Ptr p, BoardPosition newpos)
{
	auto cpos = p->getCurrentPosition();
	auto deadpiece = m_boardArr[newpos.row][newpos.column];

	if (p->getType() == Piece::PieceType::ptPawn)
	{
		if (std::abs(cpos.row - newpos.row) == 2)
			m_lastPawnDoubleStep = p;
		else
			m_lastPawnDoubleStep.reset();
	}
	else
		m_lastPawnDoubleStep.reset();

	if (deadpiece)
	{
		if (deadpiece->getPlayerColor() == Piece::PlayerColor::pcWhite)
		{
			m_liveWhites.erase(std::find(m_liveWhites.begin(), m_liveWhites.end(), deadpiece));
			m_deadWhites.push_back(deadpiece);
		}
		else
		{
			m_liveBlacks.erase(std::find(m_liveBlacks.begin(), m_liveBlacks.end(), deadpiece));
			m_deadBlacks.push_back(deadpiece);
		}
	}

	m_boardArr[newpos.row][newpos.column] = p;
	m_boardArr[cpos.row][cpos.column].reset();
	p->makeMove(newpos);

	m_isWhiteUnderCheck = std::dynamic_pointer_cast<King>(m_whiteKing)->amIUnderCheck();
	m_isBlackUnderCheck = std::dynamic_pointer_cast<King>(m_blackKing)->amIUnderCheck();

	auto rollback = [this, cpos, newpos](auto p, auto deadpiece, auto livelist, auto deadlist)
	{
		std::cout << ">>> You can't make this move your king is under check." << std::endl;
		m_boardArr[cpos.row][cpos.column] = p;
		m_boardArr[newpos.row][newpos.column] = deadpiece;
		p->makeMove(cpos);

		if (deadpiece)
		{
			deadpiece->makeMove(newpos);
			livelist.push_back(deadpiece);
			deadlist.erase(std::find(deadlist.begin(), deadlist.end(), deadpiece));
		}

		return true;
	};

	bool isRollback { false };

	if (p->getPlayerColor() == Piece::PlayerColor::pcWhite && m_isWhiteUnderCheck)
		isRollback = rollback(p, deadpiece, m_liveBlacks, m_deadBlacks);

	if (p->getPlayerColor() == Piece::PlayerColor::pcBlack && m_isBlackUnderCheck)
		isRollback = rollback(p, deadpiece, m_liveWhites, m_deadWhites);

	if (isRollback == false)
		m_history.push_back({cpos, newpos, p, deadpiece});

	return !isRollback;
}
}
