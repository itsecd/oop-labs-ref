#include <chess/chess.h>

#include <stdexcept>

using namespace chess;
using namespace std;

Piece* BoardBuilder::operator[](Point p) const {
    return _board[p];
}

void BoardBuilder::set_piece(Point p, unique_ptr<Piece> piece) {
    if (!is_point_on_board(p)) {
        throw invalid_argument("BoardBuilder::set_piece: Point is out of range.");
    }

    _board._pieces[p.row][p.col] = move(piece);
}

Board BoardBuilder::build() const {
    return _board;
}



void chess::reset_to_empty(BoardBuilder& board_builder) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board_builder.set_piece(Point(i, j), nullptr);
        }
    }
}

void chess::reset_to_initial(BoardBuilder& board_builder) {
    const auto top_color = false;
    const auto bottom_color = !top_color;

    reset_to_empty(board_builder);

    using namespace pieces;

    board_builder.set_piece(Point(0, 0), make_unique<Rook>(top_color));
    board_builder.set_piece(Point(0, 1), make_unique<Knight>(top_color));
    board_builder.set_piece(Point(0, 2), make_unique<Bishop>(top_color));
    board_builder.set_piece(Point(0, 3), make_unique<Queen>(top_color));
    board_builder.set_piece(Point(0, 4), make_unique<King>(top_color));
    board_builder.set_piece(Point(0, 5), make_unique<Bishop>(top_color));
    board_builder.set_piece(Point(0, 6), make_unique<Knight>(top_color));
    board_builder.set_piece(Point(0, 7), make_unique<Rook>(top_color));

    for (int col = 0; col < BOARD_SIZE; ++col) {
        board_builder.set_piece(Point(1, col), make_unique<Pawn>(top_color, Point(1, 0)));
        board_builder.set_piece(Point(BOARD_SIZE - 2, col), make_unique<Pawn>(bottom_color, Point(-1, 0)));
    }

    board_builder.set_piece(Point(BOARD_SIZE - 1, 0), make_unique<Rook>(bottom_color));
    board_builder.set_piece(Point(BOARD_SIZE - 1, 1), make_unique<Knight>(bottom_color));
    board_builder.set_piece(Point(BOARD_SIZE - 1, 2), make_unique<Bishop>(bottom_color));
    board_builder.set_piece(Point(BOARD_SIZE - 1, 3), make_unique<Queen>(bottom_color));
    board_builder.set_piece(Point(BOARD_SIZE - 1, 4), make_unique<King>(bottom_color));
    board_builder.set_piece(Point(BOARD_SIZE - 1, 5), make_unique<Bishop>(bottom_color));
    board_builder.set_piece(Point(BOARD_SIZE - 1, 6), make_unique<Knight>(bottom_color));
    board_builder.set_piece(Point(BOARD_SIZE - 1, 7), make_unique<Rook>(bottom_color));
}
