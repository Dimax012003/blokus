#include <iostream>
#include "piece.h"

Piece::Piece(int id, char player, Square*** squares, int sizeX, int sizeY) {
    this->id = id;
    this->player = player;
    this->squares = squares;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    placed = false;
}

Piece::~Piece(){
    deleteSquares();
}

void Piece::deleteSquares(){
    for (int i = 0; i < sizeX; i++) {
        for(int j = 0; j < sizeY; j++)
            delete squares[i][j];
        delete[] squares[i];
    }
    delete[] squares;
}

int Piece::getId() {
    return id;
}

char Piece::getPlayer() {
    return player;
}

void Piece::setPlaced(bool placed){
    this->placed = placed;
}

void Piece::setPlaced() {
    placed = true;
}

bool Piece::isPlaced() {
    return placed;
}

int Piece::getSizeX(){
    return sizeX;
}

int Piece::getSizeY(){
    return sizeY;
}

Square* Piece::getSquare(int x, int y) {
    return squares[x][y];
}

bool Piece::squareHasPiece(int x, int y) {
    return squares[x][y]->hasPiece();
}

void Piece::rotatePieceClockwise() {
    Square*** newSquares = new Square**[sizeY];
    for (int j = 0; j < sizeY; j++)
        newSquares[j] = new Square*[sizeX];
    for (int i = 0; i < sizeX; i++){
        for (int j = 0; j < sizeY; j++)
            newSquares[j][sizeX - 1 - i] = new Square(j, sizeX - 1 - i, squares[i][j]->getPlayer());
    }
    deleteSquares();
    squares = newSquares;
    int temp = sizeX;
    sizeX = sizeY;
    sizeY = temp;
}

void Piece::rotatePiece(Orientation orientation) {
    switch (orientation) {
    case LEFT:
        rotatePieceClockwise();
    case DOWN:
        rotatePieceClockwise();
    case RIGHT:
        rotatePieceClockwise();
    case UP:
        ;
    }
}

void Piece::flipPiece() {
    for (int i = 0; i < sizeX; i++) {
        for(int j = 0; j < sizeY / 2; j++){
            char player = squares[i][j]->getPlayer();
            squares[i][j]->addPiece(squares[i][sizeY-1-j]->getPlayer());
            squares[i][sizeY-1-j]->addPiece(player);
        }
    }
}

string Piece::toString() {
    stringstream sstm;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 4; j++){
            if (i < sizeX && j < sizeY)
                sstm << ((squares[i][j]->getPlayer() == '-') ? ' ' : squares[i][j]->getPlayer()) << " ";
            else
                sstm << "  ";
        }
        if (i < sizeX && sizeY == 5)
            sstm << ((squares[i][sizeY - 1]->getPlayer() == '-') ? ' ' : squares[i][sizeY - 1]->getPlayer()) << "\n";
        else
            sstm << " \n";
    }
    string result = sstm.str();
    return result;
}

Piece* Piece::deepCopy(){
    Square*** newSquares = new Square**[sizeX];
    for(int i = 0; i < sizeX; i++) {
        newSquares[i] = new Square*[sizeY];
        for(int j = 0; j < sizeY; j++)
            newSquares[i][j] = new Square(i, j, squares[i][j]->getPlayer());
    }
    return new Piece(id, player, newSquares, sizeX, sizeY);
}
