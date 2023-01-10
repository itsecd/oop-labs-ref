#include <gtest/gtest.h>

#include <chess/chess.h>

using namespace chess;



static bool operator==(Piece lhs, Piece rhs) {
    return
        lhs.get_type() == rhs.get_type() &&
        lhs.get_orientation() == rhs.get_orientation() &&
        lhs.is_white() == rhs.is_white();
}



TEST(BoardTests, WhiteGoesFirst) {
    BoardBuilder board_builder(nullptr);
    reset_to_initial(board_builder);
    auto board = board_builder.build();

    for (int col = 0; col < BOARD_SIZE; ++col) {
        ASSERT_ANY_THROW(board.move(Point(1, col), Point(2, col)));
    }

    board.move(Point(BOARD_SIZE - 2, 0), Point(BOARD_SIZE - 3, 0));
    ASSERT_TRUE(board[Point(BOARD_SIZE - 2, 0)] == Piece());
}



TEST(BoardTests, BishopCanPass) {
    BoardBuilder board_builder(nullptr);
    const auto bishop = Piece::create_bishop(true);
    board_builder[Point(0, 0)] = bishop;
    board_builder[Point(2, 2)] = Piece::create_rook(false);
    auto board = board_builder.build();

    board.move(Point(0, 0), Point(2, 2));
    ASSERT_TRUE(board[Point(0, 0)] == Piece());
    ASSERT_TRUE(board[Point(2, 2)] == bishop);
}

TEST(BoardTests, BishopCanNotPass) {
    BoardBuilder board_builder(nullptr);
    const auto bishop = Piece::create_bishop(true);
    const auto rook = Piece::create_rook(false);
    board_builder[Point(0, 0)] = Piece::create_bishop(true);
    board_builder[Point(1, 1)] = Piece::create_knight(false);
    board_builder[Point(2, 2)] = rook;
    auto board = board_builder.build();

    ASSERT_ANY_THROW(board.move(Point(0, 0), Point(2, 2)));
    ASSERT_TRUE(board[Point(0, 0)] == bishop);
    ASSERT_TRUE(board[Point(2, 2)] == rook);
}



TEST(BoardTests, KnightCanPass) {
    BoardBuilder board_builder(nullptr);
    const auto knight = Piece::create_knight(true);
    const auto rook = Piece::create_rook(false);
    board_builder[Point(0, 0)] = knight;
    board_builder[Point(0, 1)] = Piece::create_bishop(true);
    board_builder[Point(0, 2)] = Piece::create_bishop(true);
    board_builder[Point(1, 0)] = Piece::create_pawn(true, Point(1, 0));
    board_builder[Point(1, 1)] = Piece::create_pawn(true, Point(1, 0));
    board_builder[Point(1, 2)] = rook;
    auto board = board_builder.build();

    board.move(Point(0, 0), Point(1, 2));
    ASSERT_TRUE(board[Point(0, 0)] == Piece());
    ASSERT_TRUE(board[Point(1, 2)] == knight);
}
