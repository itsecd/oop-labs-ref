#include <chess/chess.h>

using namespace chess;



Point::Point() :
    row(0),
    col(0)
{ }

Point::Point(const int row, const int col) :
    row(row),
    col(col)
{ }

bool chess::operator==(const Point lhs, const Point rhs) {
    return
        lhs.row == rhs.row &&
        lhs.col == rhs.col;
}

bool chess::operator!=(const Point lhs, const Point rhs) {
    return !(lhs == rhs);
}

Point& chess::operator/=(Point& lhs, int rhs) {
    lhs.row /= rhs;
    lhs.col /= rhs;

    return lhs;
}

Point chess::operator/(Point lhs, const int rhs) {
    lhs /= rhs;

    return lhs;
}

Point& chess::operator+=(Point& lhs, const Point rhs) {
    lhs.row += rhs.row;
    lhs.col += rhs.col;

    return lhs;
}

Point& chess::operator-=(Point& lhs, const Point rhs) {
    lhs.row -= rhs.row;
    lhs.col -= rhs.col;

    return lhs;
}

Point chess::operator+(Point lhs, const Point rhs) {
    lhs += rhs;

    return lhs;
}

Point chess::operator-(Point lhs, const Point rhs) {
    lhs -= rhs;
    return lhs;
}



bool chess::is_point_on_board(const Point p) {
    return
        0 <= p.row && p.row < BOARD_SIZE &&
        0 <= p.col && p.col < BOARD_SIZE;
}
