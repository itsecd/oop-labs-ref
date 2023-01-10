#pragma once

namespace chess {

    constexpr int BOARD_SIZE = 8;



    struct Point {
    public:
        int row;
        int col;

        Point();
        Point(int row, int col);
    };

    bool operator==(Point lhs, Point rhs);

    bool operator!=(Point lhs, Point rhs);

    Point& operator/=(Point& lhs, int rhs);

    Point operator/(Point lhs, int rhs);

    Point& operator+=(Point& lhs, Point rhs);

    Point& operator-=(Point& lhs, Point rhs);

    Point operator+(Point lhs, Point rhs);

    Point operator-(Point lhs, Point rhs);

    bool is_point_on_board(Point p);



    enum class Type {
        None,
        King,
        Queen,
        Rook,
        Bishop,
        Knight,
        Pawn
    };



    class Piece {
    private:
        Type _type;
        bool _is_white;
        Point _orientation;

        Piece(Type type, bool is_white, Point orientation);

    public:
        static Piece create_king(bool is_white);
        static Piece create_queen(bool is_white);
        static Piece create_rook(bool is_white);
        static Piece create_bishop(bool is_white);
        static Piece create_knight(bool is_white);
        static Piece create_pawn(bool is_white, Point orientation);

        Piece();

        Type get_type() const;
        bool is_white() const;
        Point get_orientation() const;
    };

    bool can_move(Piece piece, Point p, bool is_capture);



    class Board {
    private:
        Piece _pieces[BOARD_SIZE][BOARD_SIZE];
        bool _can_continue;
        bool _is_white_turn;

        Board();

    public:
        friend class BoardBuilder;

        Piece operator[](Point p) const;
        bool can_continue() const;
        bool is_white_turn() const;

        void move(Point src, Point dst);
    };

    bool can_pass(const Board& board, Point src, Point dst);



    class BoardBuilder {
        Board _board;

    public:
        Piece operator[](Point p) const;

        Piece& operator[](Point p);

        Board build() const;
    };

    void reset_to_empty(BoardBuilder& board_builder);

    void reset_to_initial(BoardBuilder& board_builder);
}
