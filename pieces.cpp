#include "./utility/models/piece.cpp"
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

class Piece {
    private: 
        Player _color;
    protected:
        vector<Coords> _directions;
        FENChar _FENChar;

    public:
        Piece(Player _color){ this->_color = _color; }
        virtual FENChar $FENChar() const { return this->_FENChar; }
        virtual vector<Coords> $directions() const { return this->_directions; }
        Player $color() const { return this->_color; }
};

class Bishop: public Piece{
    public:
    Bishop(Player _color): Piece(_color){
        this->_FENChar =  _color == Player::White 
        ? FENChar::WhiteBishop : FENChar::BlackBishop;
        this->_directions = {
            {  1,  1 },
            {  1, -1 },
            { -1,  1 },
            { -1, -1 },
        };
    }
};

class Knight: public Piece{
    public: 
    Knight(Player _color): Piece(_color){
        this->_FENChar = _color == Player::White 
        ? FENChar::WhiteKnight : FENChar::BlackKnight;
        this->_directions = {
            {  1,  2 },
            {  1, -2 },
            { -1,  2 },
            { -1, -2 },
            {  2,  1 },
            { -2,  1 },
            {  2, -1 },
            { -2, -1 },
        };
    }
};

class Pawn: public Piece{
    private: 
    bool _hasMoved = false;
    void setBlackPawnDirections(){
        for (int i = 0; i < this->_directions.size(); i++) _directions[i].x *= -1;
    }

    public: 
    Pawn(Player _color): Piece(_color){
        this->_FENChar = _color == Player::White 
        ? FENChar::WhitePawn : FENChar::BlackPawn;
        if (_color == Player::Black) setBlackPawnDirections();
        this->_directions = {
            {  1,  0 },
            {  2,  0 },
            {  1,  1 },
            {  1, -1 },
        };
    }

    bool $hasMoved(){ return this->_hasMoved; }

    void hasMoved(){
        this->_hasMoved = true;
        this->_directions = {
            {  1,  0 },
            {  1,  1 },
            {  1, -1 },
        };
        if ($color() == Player::Black) setBlackPawnDirections();
    }
};

class King: public Piece{
    private:
    bool _hasMoved = false;

    public:
    King(Player _color):Piece(_color){
        this->_FENChar = _color == Player::White
        ? FENChar::WhiteKing : FENChar::BlackKing;
        this->_directions = {
            {  0,  1 },
            {  0, -1 },
            {  1,  0 },
            { -1,  0 },
            {  1,  1 },
            {  1, -1 },
            { -1,  1 },
            { -1, -1 },
        };
    }
    bool $hasMoved(){ return this->_hasMoved; }
    void hasMoved(){ this->_hasMoved = true; }
};

class Queen: public Piece{
    public:
    Queen(Player _color): Piece(_color){
        this->_FENChar = _color == Player::White
        ? FENChar::WhiteQueen : FENChar::BlackQueen;
        this->_directions = {
            {  0,  1 },
            {  0, -1 },
            {  1,  0 },
            { -1,  0 },
            {  1, -1 },
            { -1,  1 },
            {  1,  1 },
            { -1, -1 },
        };
    }
};

class Rook: public Piece{
    private:
    bool _hasMoved = false;

    public: 
    Rook(Player _color): Piece(_color){
        this->_FENChar = _color == Player::White
        ? FENChar::WhiteRook : FENChar::BlackRook;
        this->_directions = {
            {  0,  1 },
            {  0, -1 },
            {  1,  0 },
            { -1,  0 },
        };
    }

    bool $hasMoved(){ return this->_hasMoved; }
    void hasMoved(){ this->_hasMoved = true; }
};

class Blank: public Piece{
    private:
    Player _color = Player::null;
    public:
    Blank():Piece(_color){ this->_FENChar = FENChar::blank; }
};


// int main() {
//     Bishop blackBishop(Player::Black);
//     std::cout << "FEN Char: " << static_cast<char>(blackBishop.$FENChar()) << std::endl;
//     std::cout << "Direction: (" << blackBishop.$directions()[0].x << ", " << blackBishop.$directions()[0].y << ")" << std::endl;

//     return 0;
// }