#include <chess/chess.h>

#include <cassert>
#include <cmath>
#include <stdexcept>

using namespace chess;
using namespace chess::pieces;
using namespace std;



Piece::Piece(const bool is_white) :
    _is_white(is_white)
{ }

bool Piece::is_white() const {
    return _is_white;
}



King::King(bool is_white) : Piece(is_white) { }

bool King::can_move(Point p, bool is_capture) const {
    (void)is_capture;

    if (p.row == 0 && p.col == 0) {
        return false;
    }

    return abs(p.row) <= 1 && abs(p.col) <= 1;
}

unique_ptr<Piece> King::clone() const {
    return make_unique<King>(this->is_white());
}



Queen::Queen(bool is_white) : Piece(is_white) { }

bool Queen::can_move(Point p, bool is_capture) const {
    (void)is_capture;

    if (p.row == 0 && p.col == 0) {
        return false;
    }

    return p.row == 0 || p.col == 0 || abs(p.row) == abs(p.col);
}

unique_ptr<Piece> Queen::clone() const {
    return make_unique<Queen>(this->is_white());
}



Rook::Rook(bool is_white) : Piece(is_white) { }

bool Rook::can_move(Point p, bool is_capture) const {
    (void)is_capture;

    if (p.row == 0 && p.col == 0) {
        return false;
    }

    return p.row == 0 || p.col == 0;
}

unique_ptr<Piece> Rook::clone() const {
    return make_unique<Rook>(this->is_white());
}



Bishop::Bishop(bool is_white) : Piece(is_white) { }

bool Bishop::can_move(Point p, bool is_capture) const {
    (void)is_capture;

    if (p.row == 0 && p.col == 0) {
        return false;
    }

    return abs(p.row) == abs(p.col);
}

unique_ptr<Piece> Bishop::clone() const {
    return make_unique<Bishop>(this->is_white());
}



Knight::Knight(bool is_white) : Piece(is_white) { }

bool Knight::can_move(Point p, bool is_capture) const {
    (void)is_capture;

    return
        abs(p.row) == 1 && abs(p.col) == 2 ||
        abs(p.row) == 2 && abs(p.col) == 1;
}

unique_ptr<Piece> Knight::clone() const {
    return make_unique<Knight>(this->is_white());
}



Pawn::Pawn(bool is_white, Point orientation) :
    Piece(is_white),
    _orientation(orientation)
{
    if (orientation != Point(-1, 0) && orientation != Point(+1, 0)) {
        throw logic_error("Pawn::Pawn: Orientation is out of range.");
    }
}

bool Pawn::can_move(Point p, bool is_capture) const {
    if (is_capture) {
        return p.row == _orientation.row && (p.col == -1 || p.col == +1);
    }
    else {
        return p.row == _orientation.row && p.col == 0;
    }
}

unique_ptr<Piece> Pawn::clone() const {
    return make_unique<Pawn>(this->is_white(), this->_orientation);
}
