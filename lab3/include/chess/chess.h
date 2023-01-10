#pragma once

#include <array>
#include <memory>

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
        Queen,
        Rook,
        Bishop,
        Knight,
        Pawn
    };



    class Piece {
    private:
        bool _is_white;

    protected:
        Piece(bool is_white);

    public:
        virtual bool can_move(Point p, bool is_capture) const = 0;
        virtual std::unique_ptr<Piece> clone() const = 0;
        bool is_white() const;

        virtual ~Piece() = default;
    };

    using PiecePtr = std::unique_ptr<Piece>;



    namespace pieces {

        class King : public Piece {
        public:
            King(bool is_white);

            bool can_move(Point p, bool is_capture) const override;
            PiecePtr clone() const override;
        };

        class Queen : public Piece {
        public:
            Queen(bool is_white);

            bool can_move(Point p, bool is_capture) const override;
            PiecePtr clone() const override;
        };

        class Rook : public Piece {
        public:
            Rook(bool is_white);

            bool can_move(Point p, bool is_capture) const override;
            PiecePtr clone() const override;
        };

        class Bishop : public Piece {
        public:
            Bishop(bool is_white);

            bool can_move(Point p, bool is_capture) const override;
            PiecePtr clone() const override;
        };

        class Knight : public Piece {
        public:
            Knight(bool is_white);

            bool can_move(Point p, bool is_capture) const override;
            PiecePtr clone() const override;
        };

        class Pawn : public Piece {
            Point _orientation;

        public:
            Pawn(bool is_white, Point orientation);

            bool can_move(Point p, bool is_capture) const override;
            PiecePtr clone() const override;
        };

    }



    class Board {
    private:
        std::array<std::array<PiecePtr, BOARD_SIZE>, BOARD_SIZE> _pieces;
        bool _can_continue;
        bool _is_white_turn;

        Board();

    public:
        friend class BoardBuilder;

        Board(const Board& board);

        Piece* operator[](Point p) const;
        bool can_continue() const;
        bool is_white_turn() const;

        Board& operator=(const Board& board);
        void move(Point src, Point dst);
        void swap(Board& board);
    };

    bool can_pass(const Board& board, Point src, Point dst);



    class BoardBuilder {
        Board _board;

    public:
        Piece* operator[](Point p) const;

        void set_piece(Point p, std::unique_ptr<Piece> piece);

        Board build() const;
    };

    void reset_to_empty(BoardBuilder& board_builder);

    void reset_to_initial(BoardBuilder& board_builder);
}
