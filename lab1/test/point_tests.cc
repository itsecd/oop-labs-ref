#include <gtest/gtest.h>

#include <chess/chess.h>

using namespace chess;

TEST(PointTests, IsPointOnBoard) {
    EXPECT_TRUE(is_point_on_board(Point(0, 0)));
    EXPECT_TRUE(is_point_on_board(Point(0, 7)));
    EXPECT_TRUE(is_point_on_board(Point(7, 0)));
    EXPECT_TRUE(is_point_on_board(Point(7, 7)));

    EXPECT_FALSE(is_point_on_board(Point(-1, 0)));
    EXPECT_FALSE(is_point_on_board(Point(+8, 0)));
    EXPECT_FALSE(is_point_on_board(Point(0, -1)));
    EXPECT_FALSE(is_point_on_board(Point(0, +8)));
}
