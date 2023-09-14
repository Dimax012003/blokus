#include <iostream>
#include <cstdlib>
#include "player.h"

Player::Player(int id) {
    this->id = id;
    if (id == 0) name = "Player 1";
    else if (id == 1) name = "Player 2";
    numPieces = 21;
    symbol = (id == 0) ? '#' : 'O';
    pieces = new Piece*[numPieces];
    createPieces();
    opponent = NULL;
}

Player::~Player() {
    for (int i = 0; i < numPieces; i++)
        delete pieces[i];
    delete[] pieces;
}

void Player::setOpponent(Player* player){
    opponent = player;
}

int Player::getId(){
    return id;
}

char Player::getSymbol(){
    return symbol;
}


string Player::getName() {
    return name;
}

Piece* Player::getPiece(int index) {
    return pieces[index];
}

int Player::getNumberOfPlacedPieces() {
    int numPlacedPieces = 0;
    for (int i = 0; i < numPieces; i++) {
        if (pieces[i]->isPlaced())
            numPlacedPieces++;
    }
    return numPlacedPieces;
}

int Player::getNumberOfAvailablePieces() {
    return numPieces - getNumberOfPlacedPieces();
}

Move** Player::getPossibleMoves(Board* board, int& numPossibleMoves) {
    numPossibleMoves = 0;
    Orientation orientations[] = {UP, RIGHT, DOWN, LEFT};
    Flip flips[] = {NO, YES};
    for (int i = 0; i < numPieces; i++){
        if (!pieces[i]->isPlaced()){
            for (int x = 0; x < board->getSizeX(); x++) {
                for (int y = 0; y < board->getSizeY(); y++) {
                    for (int o = 0; o < 4; o++) {
                        for (int f = 0; f < 2; f++) {
                            if (board->pieceCanBePlaced(pieces[i], x, y, orientations[o], flips[f]))
                                numPossibleMoves++;
                        }
                    }
                }
            }
        }
    }
    Move** possibleMoves = new Move*[numPossibleMoves];
    int moveIndex = 0;
    for (int i = 0; i < numPieces; i++){
        if (!pieces[i]->isPlaced()){
            for (int x = 0; x < board->getSizeX(); x++) {
                for (int y = 0; y < board->getSizeY(); y++) {
                    for (int o = 0; o < 4; o++) {
                        for (int f = 0; f < 2; f++) {
                            if (board->pieceCanBePlaced(pieces[i], x, y, orientations[o], flips[f]))
                                possibleMoves[moveIndex++] = new Move(pieces[i], x, y, orientations[o], flips[f]);
                        }
                    }
                }
            }
        }
    }

    return possibleMoves;
}

Move** Player::getPossibleMoves(Board* board, Piece* piece, int& numPossibleMoves) {
    numPossibleMoves = 0;
    if (piece->isPlaced())
        return NULL;
    Orientation orientations[] = {UP, RIGHT, DOWN, LEFT};
    Flip flips[] = {NO, YES};
    for (int x = 0; x < board->getSizeX(); x++) {
        for (int y = 0; y < board->getSizeY(); y++) {
            for (int o = 0; o < 4; o++) {
                for (int f = 0; f < 2; f++) {
                    if (board->pieceCanBePlaced(piece, x, y, orientations[o], flips[f]))
                        numPossibleMoves++;
                }
            }
        }
    }

    Move** possibleMoves = new Move*[numPossibleMoves];
    int moveIndex = 0;
    for (int x = 0; x < board->getSizeX(); x++) {
        for (int y = 0; y < board->getSizeY(); y++) {
            for (int o = 0; o < 4; o++) {
                for (int f = 0; f < 2; f++) {
                    if (board->pieceCanBePlaced(piece, x, y, orientations[o], flips[f]))
                        possibleMoves[moveIndex++] = new Move(piece, x, y, orientations[o], flips[f]);
                }
            }
        }
    }

    return possibleMoves;
}

bool Player::canPlacePiece(Board* board, Piece* piece) {
    Orientation orientations[] = {UP, RIGHT, DOWN, LEFT};
    Flip flips[] = {NO, YES};
    if (!piece->isPlaced()) {
        for (int x = 0; x < board->getSizeX(); x++) {
            for (int y = 0; y < board->getSizeY(); y++) {
                for (int o = 0; o < 4; o++) {
                    for (int f = 0; f < 2; f++) {
                        if (board->pieceCanBePlaced(piece, x, y, orientations[o], flips[f]))
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Player::canPlaceAnyPiece(Board* board) {
    for (int i = 0; i < numPieces; i++) {
        if (canPlacePiece(board, pieces[i]))
            return true;
    }
    return false;
}

Player* Player::deepCopy() {
    Player* player = new RandomPlayer(id);
    player->name = name;
    player->setOpponent(opponent);
    for (int i = 0; i < player->numPieces; i++){
        delete player->pieces[i];
        player->pieces[i] = this->pieces[i]->deepCopy();
    }
    return player;
}

int Player::evaluateBoard(Board* board) {
    return 0;
}

int Player::evaluateMove(Board* board, Move* amove) {
    // Create copies of board and piece
    Board* boardCopy = board->deepCopy();
    Piece* pieceCopy = amove->getPiece()->deepCopy();

    // Place the piece on the board
    boardCopy->placePiece(pieceCopy, amove->getX(), amove->getY(), amove->getOrientation(), amove->getFlip());

    // Calculate the score
    int score = evaluateBoard(boardCopy);

    // Delete copies of board and piece
    delete boardCopy;
    delete pieceCopy;

    // Return the score
    return score;
}
