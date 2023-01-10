#include <gtest/gtest.h>

#include <chess/chess.h>

using namespace chess;

static constexpr int CHECK_RADIUS = 2;
static constexpr int CHECK_SIZE = 2 * CHECK_RADIUS + 1;

static bool check(
    const Piece* piece,
    const bool expected_captures[CHECK_SIZE][CHECK_SIZE],
    const bool expected_moves[CHECK_SIZE][CHECK_SIZE])
{
    for (int row = 0; row < CHECK_SIZE; ++row) {
        for (int col = 0; col < CHECK_SIZE; ++col) {
            Point p(row - CHECK_RADIUS, col - CHECK_RADIUS);
            if (expected_captures[row][col] != can_move(piece, p, true) ||
                expected_moves[row][col] != can_move(piece, p, false)) {
                return false;
            }
        }
    }

    return true;
}

TEST(PieceTests, King) {
    const Piece* king = Piece::create_king(true);
    const bool expected[][CHECK_SIZE] = {
        { false, false, false, false, false },
        { false,  true,  true,  true, false },
        { false,  true, false,  true, false },
        { false,  true,  true,  true, false },
        { false, false, false, false, false }
    };

    EXPECT_TRUE(check(king, expected, expected));
}

TEST(PieceTests, Queen) {
    const Piece* queen = Piece::create_queen(true);
    const bool expected[][CHECK_SIZE] = {
        {  true, false,  true, false,  true },
        { false,  true,  true,  true, false },
        {  true,  true, false,  true,  true },
        { false,  true,  true,  true, false },
        {  true, false,  true, false,  true }
    };

    EXPECT_TRUE(check(queen, expected, expected));
}

TEST(PieceTests, Rook) {
    const Piece* rook = Piece::create_rook(true);
    const bool expected[][CHECK_SIZE] = {
        { false, false,  true, false, false },
        { false, false,  true, false, false },
        {  true,  true, false,  true,  true },
        { false, false,  true, false, false },
        { false, false,  true, false, false }
    };

    EXPECT_TRUE(check(rook, expected, expected));
}

TEST(PieceTests, Bishop) {
    const Piece* bishop = Piece::create_bishop(true);
    const bool expected[][CHECK_SIZE] = {
        {  true, false, false, false,  true },
        { false,  true, false,  true, false },
        { false, false, false, false, false },
        { false,  true, false,  true, false },
        {  true, false, false, false,  true }
    };

    EXPECT_TRUE(check(bishop, expected, expected));
}

TEST(PieceTests, Knight) {
    const Piece* knight = Piece::create_knight(true);
    const bool expected[][CHECK_SIZE] = {
        { false,  true, false,  true, false },
        {  true, false, false, false,  true },
        { false, false, false, false, false },
        {  true, false, false, false,  true },
        { false,  true, false,  true, false }
    };

    EXPECT_TRUE(check(knight, expected, expected));
}

TEST(PieceTests, PawnUp) {
    const Piece* pawn = Piece::create_pawn(true, Point(-1, 0));
    const bool expected_captures[][CHECK_SIZE] = {
        { false, false, false, false, false },
        { false,  true, false,  true, false },
        { false, false, false, false, false },
        { false, false, false, false, false },
        { false, false, false, false, false }
    };
    const bool expected_moves[][CHECK_SIZE] = {
        { false, false, false, false, false },
        { false, false,  true, false, false },
        { false, false, false, false, false },
        { false, false, false, false, false },
        { false, false, false, false, false }
    };

    EXPECT_TRUE(check(pawn, expected_captures, expected_moves));
}

TEST(PieceTests, PawnDown) {
    const Piece* pawn = Piece::create_pawn(true, Point(+1, 0));
    const bool expected_captures[][2 * CHECK_RADIUS + 1] = {
        { false, false, false, false, false },
        { false, false, false, false, false },
        { false, false, false, false, false },
        { false,  true, false,  true, false },
        { false, false, false, false, false }
    };
    const bool expected_moves[][2 * CHECK_RADIUS + 1] = {
        { false, false, false, false, false },
        { false, false, false, false, false },
        { false, false, false, false, false },
        { false, false,  true, false, false },
        { false, false, false, false, false }
    };

    EXPECT_TRUE(check(pawn, expected_captures, expected_moves));
}
