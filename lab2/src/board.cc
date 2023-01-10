#include <chess/chess.h>

#include <cassert>
#include <stdexcept>
#include <utility>

using namespace chess;
using namespace std;



Board::Board() :
    _can_continue(true),
    _is_white_turn(true)
{
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            _pieces[row][col] = nullptr;
        }
    }
}

Board::Board(const Board& board) :
    _can_continue(board._can_continue),
    _is_white_turn(board._is_white_turn)
{
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            const auto piece = board[Point(row, col)];
            _pieces[row][col] = piece ? piece->clone() : nullptr;
        }
    }
}

Piece* Board::operator[](Point p) const {
    if (!is_point_on_board(p)) {
        throw invalid_argument("Board::operator[]: Point is out of range.");
    }

    return _pieces[p.row][p.col];
}

bool Board::can_continue() const {
    return _can_continue;
}

bool Board::is_white_turn() const {
    return _is_white_turn;
}

Board& Board::operator=(const Board& board) {
    Board copy(board);
    copy.swap(*this);
    return *this;
}

void Board::move(Point src, Point dst) {
    if (!_can_continue) {
        throw logic_error("Board::move: No more moves can be made.");
    }

    const auto src_piece = (*this)[src];
    if (src_piece == nullptr || src_piece->is_white() != _is_white_turn) {
        throw logic_error("Board::move: Invalid src.");
    }

    const auto dst_piece = (*this)[dst];

    if (dst_piece != nullptr &&
        dst_piece->is_white() == _is_white_turn) {
        throw logic_error("Board::move: Invalid dst.");
    }

    if (!can_pass(*this, src, dst)) {
        throw logic_error("Board::move: No way to pass from src to dst.");
    }

    const auto is_invalid_turn =
        dst_piece == nullptr && !can_move(src_piece, dst - src, false) ||
        dst_piece != nullptr && (dst_piece->is_white() == _is_white_turn || !can_move(src_piece, dst - src, true));

    if (is_invalid_turn) {
        throw logic_error("Board::move: Invalid turn.");
    }

    if (dst_piece != nullptr && dst_piece->get_type() == Type::King) {
        _can_continue = false;
    }

    delete (*this)[dst];
    _pieces[dst.row][dst.col] = (*this)[src];
    _pieces[src.row][src.col] = nullptr;

    _is_white_turn = !_is_white_turn;
}

void Board::swap(Board& board) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            std::swap(_pieces[row][col], board._pieces[row][col]);
        }
    }
    std::swap(_can_continue, board._can_continue);
    std::swap(_is_white_turn, board._is_white_turn);
}

Board::~Board() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            delete _pieces[row][col];
            _pieces[row][col] = nullptr;
        }
    }
}



bool chess::can_pass(const Board& board, const Point src, const Point dst) {
    const auto src_piece = board[src];

    if (src_piece == nullptr) {
        throw logic_error("No piece in src.");
    }

    const auto move_vector = dst - src;
    const auto n = abs(move_vector.row);

    // Special case for knight
    if (n != abs(move_vector.col)) {
        return true;
    }

    const auto step = move_vector / n;
    auto position = src + step;
    while (position != dst) {
        if (board[position] != nullptr) {
            return false;
        }
        position += step;
    }

    return true;
}
