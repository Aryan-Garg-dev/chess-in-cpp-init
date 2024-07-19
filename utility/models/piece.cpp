#include <iostream> 
#include <initializer_list>
using namespace std;

class Coords{
    public:
    int x, y;
    Coords(initializer_list<int>list){
        auto iter = list.begin();
        this->x = *iter;
        advance(iter, 1);
        this->y = *iter;
    }
    Coords(int x = -1, int y = -1){
        this->x = x;
        this->y = y;
    }
    Coords(const Coords& other){
        this->x = other.x;
        this->y = other.y;
    }

    bool operator<(const Coords& other) const {
        if (x == other.x){
            return y < other.y;
        }
        return x < other.x;
    }
};

enum Player { White, Black, null };

enum FENChar {
    WhitePawn = 'P',
    WhiteKnight = 'N',
    WhiteBishop = 'B',
    WhiteRook = 'R',
    WhiteQueen = 'Q',
    WhiteKing = 'K',
    BlackPawn = 'p',
    BlackKnight = 'n',
    BlackBishop = 'b',
    BlackRook = 'r',
    BlackQueen = 'q',
    BlackKing = 'k',
    blank = ' '
};







