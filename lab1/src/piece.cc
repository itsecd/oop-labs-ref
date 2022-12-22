#include <chess/chess.h>

#include <cassert>
#include <cmath>

using namespace chess;
using namespace std;



Piece Piece::create_king(const bool is_white) {
    return Piece(Type::King, is_white, Point());
}

Piece Piece::create_queen(const bool is_white) {
    return Piece(Type::Queen, is_white, Point());
}

Piece Piece::create_rook(const bool is_white) {
    return Piece(Type::Rook, is_white, Point());
}

Piece Piece::create_bishop(const bool is_white) {
    return Piece(Type::Bishop, is_white, Point());
}

Piece Piece::create_knight(const bool is_white) {
    return Piece(Type::Knight, is_white, Point());
}

Piece Piece::create_pawn(const bool is_white, const Point orientation) {
    assert((orientation == Point(-1, 0) || orientation == Point(+1, 0)) && "Piece::create_pawn: Orientation is out of range.");

    return Piece(Type::Pawn, is_white, orientation);
}

Piece::Piece() :
    _type(Type::None),
    _is_white(false)
{ }

Piece::Piece(const Type type, const bool is_white, const Point orientation) :
    _type(type),
    _is_white(is_white),
    _orientation(orientation)
{ }

Type Piece::get_type() const {
    return _type;
}

bool Piece::is_white() const {
    return _is_white;
}

Point Piece::get_orientation() const {
    return _orientation;
}



bool chess::can_move(const Piece piece, const Point p, const bool is_capture) {
    if (p.row == 0 && p.col == 0) {
        return false;
    }

    switch (piece.get_type()) {
    case Type::None:
        return false;
    case Type::King:
        return abs(p.row) <= 1 && abs(p.col) <= 1;
    case Type::Queen:
        return p.row == 0 || p.col == 0 || abs(p.row) == abs(p.col);
    case Type::Rook:
        return p.row == 0 || p.col == 0;
    case Type::Bishop:
        return abs(p.row) == abs(p.col);
    case Type::Knight:
        return
            abs(p.row) == 1 && abs(p.col) == 2 ||
            abs(p.row) == 2 && abs(p.col) == 1;
    case Type::Pawn:
        if (is_capture) {
            return p.row == piece.get_orientation().row && (p.col == -1 || p.col == +1);
        }
        else {
            return p.row == piece.get_orientation().row && p.col == 0;
        }
    default:
        assert(false && "can_move: Piece type is out of range.");
        return false;
    }
}
