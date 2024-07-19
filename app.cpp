#include "./chessBoard.cpp"
#include "./utility/colors.cpp"
#include <vector>
#include <map>
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;

/*
   [ ]: automated state management and message & error display,
   [ ]: move calculation, move storage
   [ ]: map for event coordinates for better display
   [ ]: for Player::Black, pawn movement are not working, (maybe: _directions is not updated)
*/

const vector<char> locations = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

enum gameState {
    moveError,   //Error
    //Events
    gameOver, //End
};


enum Element { SQUARE, BOUNDARY, PIECE, COORDINATES };

struct SelectedSquare{
    FENChar piece;
    int x;
    int y;

    SelectedSquare(FENChar piece = FENChar::blank, int x = -1, int y = -1){
        this->piece = piece;
        this->x = x;
        this->y = y;
    }
};

class Game{
    private:
    ChessBoard chessBoard;
    SelectedSquare selectedSquare = { FENChar::blank };
    Coords highlightedSquare;
    vector<Coords> pieceSafeSquares;

    public:
    map<gameState, bool> state = {
        { gameState::moveError, false },
        { gameState::gameOver,  false }
    };

    map<gameState, string> msg = {
        { gameState::moveError, "> Wrong move" },
        { gameState::gameOver,  "> Game Over" },
    };

    bool flip = true;
    
    Player $playerColor(){ return this->chessBoard.$playerColor(); }

    Type type(int x, int y, Element element){
        switch(element){
            case Element::SQUARE:
                if (state[gameState::moveError] && highlightedSquare.x == x && highlightedSquare.y == y){ return Type::Background; }
            case Element::PIECE:
                if (isSqaureSelected(x, y)){ return Type::BoldHighIntensity; }
                return Type::Bold;
            case Element::BOUNDARY:
                if (state[gameState::moveError]){ return Type::BoldHighIntensity; }
            case Element::COORDINATES:
                if ((highlightedSquare.x == x && x != -1) || (highlightedSquare.y == y && y != -1)){ return Type::BoldHighIntensity; }
            default:
                return Type::Regular;
        }
    }

    Color color(int x, int y, Element element){
        vector<vector<Piece>> board = this->chessBoard.$chessBoard();
        switch(element){
            case Element::SQUARE:
                if (state[gameState::moveError] && highlightedSquare.x == x && highlightedSquare.y == y){ return Color::Red; }
                if (isSqaureSelected(x, y)){ return Color::Yellow; }
                if (isSquareSafeForSelectedPiece(x, y)){ return Color::Yellow; }
                return (x+y)%2 == 0 && x != -1 && y != -1 ? Color::Blue : Color::White;
            case Element::PIECE:
                if (state[gameState::moveError] && highlightedSquare.x == x && highlightedSquare.y == y){ return Color::Red; }
                if (isSqaureSelected(x, y)){ return Color::Yellow; }
                if (board[x][y].$color()==Player::White){ return Color::White; }
                return Color::Blue;
            case Element::BOUNDARY:
                if (state[gameState::moveError]){ return Color::Red; }
                return Color::Black;
            case Element::COORDINATES:
                if ((highlightedSquare.x == x && x != -1) || (highlightedSquare.y == y && y != -1)){ return Color::Red; }
                return Color::Black;
            default:
                return Color::White;                
        }

    }

    void display(){
        cout<<$color(type(-1, -1, Element::BOUNDARY), color(-1, -1, Element::BOUNDARY))
        <<"   +----------------------------------------+"<<$reset<<endl;
        const vector<vector<Piece>> board = this->chessBoard.$chessBoard();
        for (int x = flip? 7: 0; flip? x >= 0 : x < 8; flip? x-- : x++){
            cout<<$color(type(x, -1, Element::COORDINATES), color(x, -1, Element::COORDINATES))<<" "<<1+x<<$reset;
            cout<<$color(type(-1, -1, Element::BOUNDARY), color(-1, -1, Element::BOUNDARY))<<" |"<<$reset;
            for (int y = flip? 0: 7; flip? y < 8 : y >= 0; flip? y++ : y--){
                cout<<$color(type(x, y, Element::SQUARE), color(x, y, Element::SQUARE))<<"["<<$reset;
                cout<<$color(type(x, y, Element::PIECE), color(x, y, Element::PIECE))<<" "<<(char) board[x][y].$FENChar()<<" "<<$reset;
                cout<<$color(type(x, y, Element::SQUARE), color(x, y, Element::SQUARE))<<"]"<<$reset;
            }
            cout<<$color(type(-1, -1, Element::BOUNDARY), color(-1, -1, Element::BOUNDARY))<<"|"<<$reset;
            cout<<endl;
            cout<<$color(type(-1, -1, Element::BOUNDARY), color(-1, -1, Element::BOUNDARY))
            <<"   +----------------------------------------+"<<$reset<<endl;
        }
        cout<<"      ";
        for (int y = flip? 0: 7; flip? y < 8 : y >= 0; flip? y++ : y--){
            cout<<$color(type(-1, y, Element::COORDINATES), color(-1, y, Element::COORDINATES))<<locations[y]<<"    "<<$reset;
        }
        cout<<endl;
    }

    map<string, vector<Coords>> safeSquares(){ return this->chessBoard.$safeSquares(); }

    bool isSqaureSelected(int x, int y){
        return selectedSquare.piece == FENChar::blank ? false
        : this->selectedSquare.x == x && this->selectedSquare.y == y;
    }

    bool isSquareSafeForSelectedPiece(int x, int y){
        for (int i = 0; i < this->pieceSafeSquares.size(); i++){
            if (this->pieceSafeSquares[i].x == x && this->pieceSafeSquares[i].y == y){
                return true;
            }
        }
        return false;
    }

    void selectingPiece(int x, int y){
        FENChar piece = this->chessBoard.chessBoardView()[x][y];
        if (piece == FENChar::blank) return;
        string key = to_string(x)+","+to_string(y);
        if (this->safeSquares().count(key) > 0) {
            this->pieceSafeSquares = this->safeSquares().at(key);
            this->selectedSquare = { piece, x, y };
        }
    }

    void highlightSquare(int x, int y){
        highlightedSquare.x = x;
        highlightedSquare.y = y;
    }
};

int main(){
    system("cls||clear");
    Game game;
    // game.flip = !game.flip;
    game.display();

    int y = getch();
    if ((char)y == 'x') return 0;
    cout<<(char)y<<"-";
    int x = getch();
    if ((char)x == 'x') return 0;
    cout<<(char)x<<endl;

    Coords move = { x-49, y-97 };
    if (move.x >= 8 || move.x < 0 || move.y < 0 || move.y >= 8){
        game.state[gameState::moveError] = true;
        system("cls||clear");
        game.display();
        cout<<$color(Type::Regular, Color::Red)<<game.msg[gameState::moveError]<<$reset<<endl;
        return 0;
    }
    game.selectingPiece(move.x, move.y);
    if (game.isSqaureSelected(move.x, move.y)){
        system("cls||clear");
        game.display();
    } else {
        game.state[gameState::moveError] = true;
        game.highlightSquare(move.x, move.y);
        system("cls||clear");
        game.display();
        cout<<$color(Type::Regular, Color::Red)<<game.msg[gameState::moveError]<<$reset<<endl;
        return 0;
    }

    return 0;
}