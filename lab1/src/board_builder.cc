#include <stdexcept>

#include <chess/chess.h>

using namespace chess;
using namespace std;

Piece BoardBuilder::operator[](Point p) const {
    return _board[p];
}

Piece& BoardBuilder::operator[](Point p) {
    if (!is_point_on_board(p)) {
        throw invalid_argument("BoardBuilder::operator[]: Point is out of range.");
    }

    return _board._pieces[p.row][p.col];
}

Board BoardBuilder::build() const {
    return _board;
}



void chess::reset_to_empty(BoardBuilder& board_builder) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board_builder[Point(i, j)] = Piece();
        }
    }
}

void chess::reset_to_initial(BoardBuilder& board_builder) {
    const auto top_color = false;
    const auto bottom_color = !top_color;

    board_builder[Point(0, 0)] = Piece::create_rook(top_color);
    board_builder[Point(0, 1)] = Piece::create_knight(top_color);
    board_builder[Point(0, 2)] = Piece::create_bishop(top_color);
    board_builder[Point(0, 3)] = Piece::create_queen(top_color);
    board_builder[Point(0, 4)] = Piece::create_king(top_color);
    board_builder[Point(0, 5)] = Piece::create_bishop(top_color);
    board_builder[Point(0, 6)] = Piece::create_knight(top_color);
    board_builder[Point(0, 7)] = Piece::create_rook(top_color);

    for (int col = 0; col < BOARD_SIZE; ++col) {
        board_builder[Point(1, col)] = Piece::create_pawn(top_color, Point(1, 0));
        board_builder[Point(BOARD_SIZE - 2, col)] = Piece::create_pawn(bottom_color, Point(-1, 0));
    }

    board_builder[Point(BOARD_SIZE - 1, 0)] = Piece::create_rook(bottom_color);
    board_builder[Point(BOARD_SIZE - 1, 1)] = Piece::create_knight(bottom_color);
    board_builder[Point(BOARD_SIZE - 1, 2)] = Piece::create_bishop(bottom_color);
    board_builder[Point(BOARD_SIZE - 1, 3)] = Piece::create_queen(bottom_color);
    board_builder[Point(BOARD_SIZE - 1, 4)] = Piece::create_king(bottom_color);
    board_builder[Point(BOARD_SIZE - 1, 5)] = Piece::create_bishop(bottom_color);
    board_builder[Point(BOARD_SIZE - 1, 6)] = Piece::create_knight(bottom_color);
    board_builder[Point(BOARD_SIZE - 1, 7)] = Piece::create_rook(bottom_color);
}
