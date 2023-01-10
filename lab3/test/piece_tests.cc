#include <gtest/gtest.h>

#include <chess/chess.h>

using namespace chess;
using namespace chess::pieces;
using namespace std;

static constexpr int CHECK_RADIUS = 2;
static constexpr int CHECK_SIZE = 2 * CHECK_RADIUS + 1;

static bool check(
    const Piece& piece,
    const bool expected_captures[CHECK_SIZE][CHECK_SIZE],
    const bool expected_moves[CHECK_SIZE][CHECK_SIZE])
{
    for (int row = 0; row < CHECK_SIZE; ++row) {
        for (int col = 0; col < CHECK_SIZE; ++col) {
            Point p(row - CHECK_RADIUS, col - CHECK_RADIUS);
            if (expected_captures[row][col] != piece.can_move(p, true) ||
                expected_moves[row][col] != piece.can_move(p, false)) {
                return false;
            }
        }
    }

    return true;
}

TEST(PieceTests, King) {
    const King king(true);
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
    const Queen queen(true);
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
    const Rook rook(true);
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
    const Bishop bishop(true);
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
    const Knight knight(true);
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
    const Pawn pawn(true, Point(-1, 0));
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
    const Pawn pawn(true, Point(+1, 0));
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
