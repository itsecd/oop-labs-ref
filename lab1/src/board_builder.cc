#include <stdexcept>

#include <chess/chess.h>

using namespace chess;
using namespace std;
//
//const auto top_color = Color::Black;
//const auto bottom_color = Color::White;
//const auto top_orientation = Square(1, 0);
//const auto bottom_orientation = Square(-1, 0);
//
//_board[0][0] = Piece(Type::Rook, top_color, top_orientation);
//_board[0][1] = Piece(Type::Knight, top_color, top_orientation);
//_board[0][2] = Piece(Type::Bishop, top_color, top_orientation);
//_board[0][3] = Piece(Type::Queen, top_color, top_orientation);
//_board[0][4] = Piece(Type::King, top_color, top_orientation);
//_board[0][5] = Piece(Type::Bishop, top_color, top_orientation);
//_board[0][6] = Piece(Type::Knight, top_color, top_orientation);
//_board[0][7] = Piece(Type::Rook, top_color, top_orientation);
//
//_board[BOARD_SIZE - 1][0] = Piece(Type::Rook, bottom_color, bottom_orientation);
//_board[BOARD_SIZE - 1][1] = Piece(Type::Knight, bottom_color, bottom_orientation);
//_board[BOARD_SIZE - 1][2] = Piece(Type::Bishop, bottom_color, bottom_orientation);
//_board[BOARD_SIZE - 1][3] = Piece(Type::Queen, bottom_color, bottom_orientation);
//_board[BOARD_SIZE - 1][4] = Piece(Type::King, bottom_color, bottom_orientation);
//_board[BOARD_SIZE - 1][5] = Piece(Type::Bishop, bottom_color, bottom_orientation);
//_board[BOARD_SIZE - 1][6] = Piece(Type::Knight, bottom_color, bottom_orientation);
//_board[BOARD_SIZE - 1][7] = Piece(Type::Rook, bottom_color, bottom_orientation);
//
//for (int col = 0; col < BOARD_SIZE; ++col) {
//    _board[1][col] = Piece(Type::Pawn, top_color, top_orientation);
//    _board[BOARD_SIZE - 2][col] = Piece(Type::Pawn, bottom_color, bottom_orientation);
//}