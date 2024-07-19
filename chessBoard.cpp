#include "./pieces.cpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

enum Square {
    KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, BLANK
};

bool isInstanceOf(const Piece current, Square piece){
    switch(piece){
        case Square::BISHOP:
            return current.$FENChar() == FENChar::BlackBishop || 
            current.$FENChar() == FENChar::WhiteBishop;
        case Square::KNIGHT:
            return current.$FENChar() == FENChar::BlackKnight ||
            current.$FENChar() == FENChar::WhiteKnight;
        case Square::QUEEN:
            return current.$FENChar() == FENChar::BlackQueen ||
            current.$FENChar() == FENChar::WhiteQueen;
        case Square::KING:
            return current.$FENChar() == FENChar::BlackKing ||
            current.$FENChar() == FENChar::WhiteKing;
        case Square::ROOK:
            return current.$FENChar() == FENChar::BlackRook ||
            current.$FENChar() == FENChar::WhiteRook;
        case Square::PAWN:
            return current.$FENChar() == FENChar::BlackPawn ||
            current.$FENChar() == FENChar::WhitePawn;
        case Square::BLANK:
            return current.$FENChar() == FENChar::blank;
        default:
            return false;
    }
}

class ChessBoard{
    private:
    vector<vector<Piece>> chessBoard;
    const int chessBoardSize = 8;
    Player _playerColor = Player::White;
    map<string, vector<Coords>>_safeSquares;

    bool areCoordsValid(int x, int y){
        return x >= 0 && y >= 0 && x < this->chessBoardSize && y < this->chessBoardSize;
    }

    bool isPositionSafeAfterMove(Piece piece, int prevX, int prevY, int newX, int newY){
        const Piece newPiece = this->chessBoard[newX][newY];

        // can't put piece on square that has another piece of same color
        if (!isInstanceOf(newPiece, Square::BLANK) && newPiece.$color() == piece.$color()) return false;

        //simulate position
        this->chessBoard[prevX][prevY] = Blank();
        this->chessBoard[newX][newY] = piece;

        const bool isPositionSafe = !this->isInCheck(piece.$color());

        //restore position
        this->chessBoard[prevX][prevY] = piece;
        this->chessBoard[newX][newY] = newPiece;

        return isPositionSafe;
    }

    map<string, vector<Coords>> findSafeSquares(){
        map<string, vector<Coords>> safeSquares;
        for (int x = 0; x < this->chessBoardSize; x++){
            for (int y = 0; y < this->chessBoardSize; y++){
                const Piece piece = this->chessBoard[x][y];
                if (isInstanceOf(piece, Square::BLANK) || piece.$color() != this->_playerColor) continue;

                vector<Coords> pieceSafeSquares;

                const vector<Coords> pieceDirections = piece.$directions();
                for (int i = 0; i < pieceDirections.size() ; i++){
                    int dx = pieceDirections[i].x;
                    int dy = pieceDirections[i].y;
                    int newX = x + dx;
                    int newY = y + dy;

                    if (!this->areCoordsValid(newX, newY)) continue;

                    Piece newPiece = this->chessBoard[newX][newY];
                    if (!isInstanceOf(newPiece, Square::BLANK) && newPiece.$color() == piece.$color()) continue;

                    // need to restrict pawn moves in certain directions 
                    if (isInstanceOf(piece, Square::PAWN)){
                        //cant move pawn two sqaures straight if there is piece infront of him
                        if (dx == 2 || dx == -2){
                            if (!isInstanceOf(newPiece, Square::BLANK)) continue;
                            if (!isInstanceOf(this->chessBoard[newX + (dx == 2 ? -1: 1)][newY], Square::BLANK)) continue;
                        }

                        //cant move pawn one sqaure straight if another pawn infront of it
                        if ((dx == 1 || dx == -1) && dy == 0 && !isInstanceOf(newPiece, Square::BLANK)) continue;

                        // can't move pawn diagonally if there is no piece or same color piece as pawn
                        if ((dy == 1 || dy == -1) && (isInstanceOf(newPiece, Square::BLANK) || newPiece.$color() == piece.$color())) continue;
                    }

                    if (isInstanceOf(piece, Square::PAWN) || isInstanceOf(piece, Square::KNIGHT) || isInstanceOf(piece, Square::KING)){
                        if (isPositionSafeAfterMove(piece, x, y, newX, newY))
                            pieceSafeSquares.push_back({ newX, newY });
                    } else {
                        while(this->areCoordsValid(newX, newY)){
                            newPiece = this->chessBoard[newX][newY];
                            if (!isInstanceOf(newPiece, Square::BLANK) && newPiece.$color() == piece.$color()) break;
                            
                            if (isPositionSafeAfterMove(piece, x, y, newX, newY))
                                pieceSafeSquares.push_back({ newX, newY });
                            
                            if (!isInstanceOf(newPiece, Square::BLANK)) break;

                            newX += dx;
                            newY += dy;
                        }
                    }
                }
                if (pieceSafeSquares.size() > 0)
                    safeSquares.insert(pair<string, vector<Coords>>(to_string(x)+","+to_string(y), pieceSafeSquares));
            }
        }
        return safeSquares;
    }

    public:
    ChessBoard(){
        this->chessBoard = {
            { 
                Rook(Player::White), Knight(Player::White), Bishop(Player::White), Queen(Player::White),
                King(Player::White), Bishop(Player::White), Knight(Player::White), Rook(Player::White) 
            },
            { 
                Pawn(Player::White), Pawn(Player::White), Pawn(Player::White), Pawn(Player::White), 
                Pawn(Player::White), Pawn(Player::White), Pawn(Player::White), Pawn(Player::White), 
            },
            { Blank(), Blank(), Blank(), Blank(), Blank(), Blank(), Blank(), Blank() },  
            { Blank(), Blank(), Blank(), Blank(), Blank(), Blank(), Blank(), Blank() }, 
            { Blank(), Blank(), Blank(), Blank(), Blank(), Blank(), Blank(), Blank() },  
            { Blank(), Blank(), Blank(), Blank(), Blank(), Blank(), Blank(), Blank() },
            { 
                Pawn(Player::Black), Pawn(Player::Black), Pawn(Player::Black), Pawn(Player::Black), 
                Pawn(Player::Black), Pawn(Player::Black), Pawn(Player::Black), Pawn(Player::Black), 
            },
            { 
                Rook(Player::Black), Knight(Player::Black), Bishop(Player::Black), Queen(Player::Black),
                King(Player::Black), Bishop(Player::Black), Knight(Player::Black), Rook(Player::Black) 
            },
        };
        this->_safeSquares = findSafeSquares();
    }

    const vector<vector<Piece>> $chessBoard(){ return this->chessBoard; }
    
    Player $playerColor(){ return this->_playerColor; }

    bool isInCheck(Player playerColor){
        for (int x = 0; x < this->chessBoardSize; x++){
            for (int y = 0; y < this->chessBoardSize; y++){
                const Piece piece = this->chessBoard[x][y];
                if (isInstanceOf(piece, Square::BLANK) || piece.$color() == playerColor) continue;
                
                const vector<Coords> pieceDirections = piece.$directions();
                for (int i = 0; i < pieceDirections.size(); i++){
                    int dx = pieceDirections[i].x;
                    int dy = pieceDirections[i].y;
                    int newX = x + dx;
                    int newY = y + dy;
                    
                    if (!this->areCoordsValid(newX, newY)) continue;

                    if (isInstanceOf(piece, Square::PAWN) || isInstanceOf(piece, Square::KNIGHT) || isInstanceOf(piece, Square::KING)){
                        // pawn only attacks diagonally
                        if (isInstanceOf(piece, Square::PAWN) && dy == 0) continue;

                        const Piece attackedPiece = this->chessBoard[newX][newY];
                        if (isInstanceOf(attackedPiece, Square::KING) && attackedPiece.$color() == playerColor) return true;
                    } else {
                        while(this->areCoordsValid(newX, newY)){
                            const Piece attackedPiece = this->chessBoard[newX][newY];
                            if (isInstanceOf(attackedPiece, Square::KING) && attackedPiece.$color() == playerColor) return true;

                            if (!isInstanceOf(attackedPiece, Square::BLANK)) break;

                            newX += dx;
                            newY += dy;
                        }
                    }
                } 
            }
        }
        return false;
    }

    vector<vector<FENChar>> chessBoardView(){
        vector<vector<FENChar>> chessBoardView(this->chessBoardSize);
        for (int x = 0; x < this->chessBoardSize; x++){
            vector<FENChar>row(this->chessBoardSize);
            for (int y = 0; y < this->chessBoardSize; y++){
                row[y] = this->chessBoard[x][y].$FENChar();
            }
            chessBoardView[x]= row;
        }
        return chessBoardView;
    }

    map<string, vector<Coords>> $safeSquares(){ return this->_safeSquares; }

    // void move(int prevX, int prevY, int newX, int newY){
    //     if (!this->areCoordsValid(prevX, prevY) || !this->areCoordsValid(newX, newY)) return;
        
    //     const Piece piece = this->chessBoard[prevX][prevY];
    //     if (isInstanceOf(piece, Square::BLANK) || piece.$color() != this->_playerColor) return;
        
    //     const string key = to_string(prevX)+","+to_string(prevY);
    //     if (this->_safeSquares.count(key) > 0){
    //         vector<Coords>pieceSafeSquares = this->_safeSquares.at(key);
    //         bool areNewCoordsSafe = false;
    //         for (int i = 0; i < pieceSafeSquares.size(); i++){
    //             if (newX == pieceSafeSquares[i].x && newY == pieceSafeSquares[i].y){
    //                 areNewCoordsSafe = true;
    //             }
    //         }
    //         if (!areNewCoordsSafe){
    //             cout<<"Sqaure is not safe"<<endl;
    //             return;
    //         }
    //     } else { return; }

    //     if (isInstanceOf(piece, Pawn) || isInstanceOf(piece, Rook) || isInstanceOf(piece, King)){}

    //     //update the board
    //     this->chessBoard[prevX][prevY] = Blank();
    //     this->chessBoard[newX][newY] = piece;

    //     this->_playerColor = _playerColor == Player::White ? Player::Black : Player::White;
    //     this->_safeSquares = this->findSafeSquares();

        
    // }
};

