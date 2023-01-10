#include <gtest/gtest.h>

#include <chess/chess.h>

using namespace chess;
using namespace chess::pieces;
using namespace std;



TEST(BoardTests, WhiteGoesFirst) {
    BoardBuilder board_builder;
    reset_to_initial(board_builder);
    auto board = board_builder.build();

    for (int col = 0; col < BOARD_SIZE; ++col) {
        ASSERT_ANY_THROW(board.move(Point(1, col), Point(2, col)));
    }

    board.move(Point(BOARD_SIZE - 2, 0), Point(BOARD_SIZE - 3, 0));
    ASSERT_TRUE(board[Point(BOARD_SIZE - 2, 0)] == nullptr);
}



TEST(BoardTests, BishopCanPass) {
    BoardBuilder board_builder;
    board_builder.set_piece(Point(0, 0), make_unique<Bishop>(true));
    board_builder.set_piece(Point(2, 2), make_unique<Rook>(false));
    auto board = board_builder.build();

    board.move(Point(0, 0), Point(2, 2));
    ASSERT_TRUE(board[Point(0, 0)] == nullptr);
    ASSERT_TRUE(dynamic_cast<Bishop*>(board[Point(2, 2)]) != nullptr);
}

TEST(BoardTests, BishopCanNotPass) {
    BoardBuilder board_builder;
    board_builder.set_piece(Point(0, 0), make_unique<Bishop>(true));
    board_builder.set_piece(Point(1, 1), make_unique<Knight>(true));
    board_builder.set_piece(Point(2, 2), make_unique<Rook>(false));
    auto board = board_builder.build();

    ASSERT_ANY_THROW(board.move(Point(0, 0), Point(2, 2)));
    ASSERT_TRUE(dynamic_cast<Bishop*>(board[Point(0, 0)]) != nullptr);
    ASSERT_TRUE(dynamic_cast<Rook*>(board[Point(2, 2)]) != nullptr);
}



TEST(BoardTests, KnightCanPass) {
    BoardBuilder board_builder;
    board_builder.set_piece(Point(0, 0), make_unique<Knight>(true));
    board_builder.set_piece(Point(0, 1), make_unique<Bishop>(true));
    board_builder.set_piece(Point(0, 2), make_unique<Bishop>(true));
    board_builder.set_piece(Point(1, 0), make_unique<Pawn>(true, Point(1, 0)));
    board_builder.set_piece(Point(1, 1), make_unique<Pawn>(true, Point(1, 0)));
    board_builder.set_piece(Point(1, 2), make_unique<Rook>(false));
    auto board = board_builder.build();

    board.move(Point(0, 0), Point(1, 2));
    ASSERT_TRUE(board[Point(0, 0)] == nullptr);
    ASSERT_TRUE(dynamic_cast<Knight*>(board[Point(1, 2)]) != nullptr);
}
