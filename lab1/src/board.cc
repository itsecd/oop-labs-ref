#include <cassert>
#include <stdexcept>

#include <chess/chess.h>

using namespace chess;
using namespace std;



Board::Board(PromotePawnCallback promote_pawn_callback) :
    _promote_pawn_callback(promote_pawn_callback),
    _can_continue(true),
    _is_white_turn(true)
{ }

Piece Board::operator[](Point p) const {
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

void Board::move(Point src, Point dst) {
    if (!_can_continue) {
        throw logic_error("Board::move: No more moves can be made.");
    }

    const auto src_piece = (*this)[src];
    if (src_piece.get_type() == Type::None || src_piece.is_white() != _is_white_turn) {
        throw logic_error("Board::move: Invalid src.");
    }

    const auto dst_piece = (*this)[dst];

    if (dst_piece.get_type() != Type::None &&
        dst_piece.is_white() == _is_white_turn) {
        throw logic_error("Board::move: Invalid dst.");
    }

    if (!can_pass(*this, src, dst)) {
        throw logic_error("Board::move: No way to pass from src to dst.");
    }

    const auto is_invalid_turn =
        dst_piece.get_type() == Type::None && !can_move(src_piece, dst - src, false) ||
        dst_piece.get_type() != Type::None && (dst_piece.is_white() == _is_white_turn || !can_move(src_piece, dst - src, true));

    if (is_invalid_turn) {
        throw logic_error("Board::move: Invalid turn.");
    }

    if (dst_piece.get_type() == Type::King) {
        _can_continue = false;
    }

    _pieces[dst.row][dst.col] = (*this)[src];
    _pieces[src.row][src.col] = Piece();

    // TODO: _promote_pawn_callback

    _is_white_turn = !_is_white_turn;
}



bool chess::can_pass(const Board& board, const Point src, const Point dst) {
    const auto src_piece = board[src];
    const auto dst_piece = board[dst];

    if (src_piece.get_type() == Type::None) {
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
        if (board[position].get_type() != Type::None) {
            return false;
        }
        position += step;
    }

    return true;
}
