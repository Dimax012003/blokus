#include <iostream>
#include <cstdlib>
#include "board.h"
#include "player.h"

using namespace std;

Board::Board() {
    boardSizeX = 14;
    boardSizeY = 14;
    squares = new Square**[boardSizeX];
    for (int i = 0; i < boardSizeX; i++) {
        squares[i] = new Square*[boardSizeY];
        for (int j = 0; j < boardSizeY; j++)
            squares[i][j] = new Square(i, j);
    }
}

Board::~Board() {
    for (int i = 0; i < boardSizeX; i++) {
        for(int j = 0; j < boardSizeY; j++)
            delete squares[i][j];
        delete[] squares[i];
    }
    delete[] squares;
}

int Board::getSizeX() {
    return boardSizeX;
}

int Board::getSizeY() {
    return boardSizeY;
}

bool Board::hasPiece(int x, int y) {
    return squares[x][y]->hasPiece();
}

bool Board::squareBelongsToPlayer(int x, int y, char player) {
    return squares[x][y]->getPlayer() == player;
}

bool Board::squareBelongsToPlayer(int x, int y, Player* player) {
    return squareBelongsToPlayer(x, y, player->getSymbol());
}

bool Board::playerHasPlacedNoPieces(char player) {
    for (int i = 0; i < boardSizeX; i++) {
        for (int j = 0; j < boardSizeY; j++) {
            if (squares[i][j]->getPlayer() == player)
                return false;
        }
    }
    return true;
}

Piece* Board::getLastPiecePlayedByPlayer(Player* player){
    return player->getSymbol() == '#' ? lastPiecePlayedByFirstPlayer : lastPiecePlayedBySecondPlayer;
}

bool Board::pieceCanBePlaced(Piece* piece, int x, int y, Orientation orientation, Flip flip){
    // Make a copy of the piece to rotate and flip it virtually
    Piece* cpiece = piece->deepCopy();

    // Rotate and flip piece
    cpiece->rotatePiece(orientation);
    if (flip == YES)
        cpiece->flipPiece();

    // Check if piece can be placed on the board
    bool canBePlaced = pieceCanBePlaced(cpiece, x, y);

    // Delete the copy of piece that was created
    delete cpiece;

    // Return whether the piece can be placed
    return canBePlaced;
}

void Board::placePiece(Piece* piece, int x, int y) {
    // Play the move by setting the board squares
    for(int i = 0; i < piece->getSizeX(); i++) {
        for(int j = 0; j < piece->getSizeY(); j++) {
            if (piece->squareHasPiece(i, j))
                squares[x + i][y + j]->addPiece(piece->getPlayer());
        }
    }

    // Set the piece as placed
    piece->setPlaced();
    if (piece->getPlayer() == '#')
        lastPiecePlayedByFirstPlayer = piece;
    else
        lastPiecePlayedBySecondPlayer = piece;
}

void Board::placePiece(Piece* piece, int x, int y, Orientation orientation, Flip flip) {
    // Rotate and flip piece
    piece->rotatePiece(orientation);
    if (flip == YES)
        piece->flipPiece();

    placePiece(piece, x, y);
}

string Board::toString() {
    stringstream sstm;
    sstm << "     ________________________________________________ \n"
         << "    |                                                |\n"
         << "    |      0  1  2  3  4  5  6  7  8  9 10 11 12 13  |\n";
    for(int i = 0; i < boardSizeX; i++) {
        sstm << "    |  " << i << " ";
        if (i < 10) sstm << " ";
        for(int j = 0; j < boardSizeY; j++)
            sstm << " " << (hasPiece(i, j) ? squares[i][j]->getPlayer() : '-') << " ";
        sstm << " |\n";
    }
    sstm << "    |________________________________________________|\n";
    return sstm.str();
};

Board* Board::deepCopy() {
    Board* board = new Board();
    for (int i = 0; i < boardSizeX; i++) {
        for (int j = 0; j < boardSizeY; j++) {
            board->squares[i][j]->addPiece(squares[i][j]->getPlayer());
        }
    }
    return board;
}

bool Board::pieceCanBePlaced(Piece* piece, int x, int y) {
    // Check that first piece touches square (4, 4) for player 1(#) or square (9, 9) for player 2(O)
    char player = piece->getPlayer();
    if (playerHasPlacedNoPieces(player)) {
        for(int i = 0; i < piece->getSizeX(); i++) {
            for(int j = 0; j < piece->getSizeY(); j++) {
                if (piece->squareHasPiece(i, j)) {
                    if (player == '#' && x + i == 4 && y + j == 4)
                        return true;
                    else if (player == 'O' && x + i == 9 && y + j == 9)
                        return true;
                }
            }
        }
        return false;
    }

    // Check all other conditions
    bool touchesAtLeastOneCorner = false;
    for(int i = 0; i < piece->getSizeX(); i++) {
        for(int j = 0; j < piece->getSizeY(); j++) {
            if (piece->squareHasPiece(i, j)) {
                // Check if any part of the piece is out of bounds
                if (x + i < 0 || x + i > 13 || y + j < 0 || y + j > 13)
                    return false;
                // Check that piece does not fall on top of any other piece
                if (squares[x + i][y + j]->hasPiece())
                    return false;
                // Check that piece does not touch any other piece of the same player edge-by-edge
                if (   (x + i - 1 >= 0  && squares[x + i - 1][y + j]->hasPiece(player))
                        || (x + i + 1 <= 13 && squares[x + i + 1][y + j]->hasPiece(player))
                        || (y + j - 1 >= 0  && squares[x + i][y + j - 1]->hasPiece(player))
                        || (y + j + 1 <= 13 && squares[x + i][y + j + 1]->hasPiece(player))
                   )
                    return false;
                // Check that piece touches at least one corner with any other piece of the same player
                if (   (x + i - 1 >= 0  && y + j - 1 >= 0  && squares[x + i - 1][y + j - 1]->hasPiece(player))
                        || (x + i - 1 >= 0  && y + j + 1 <= 13 && squares[x + i - 1][y + j + 1]->hasPiece(player))
                        || (x + i + 1 <= 13 && y + j - 1 >= 0  && squares[x + i + 1][y + j - 1]->hasPiece(player))
                        || (x + i + 1 <= 13 && y + j + 1 <= 13 && squares[x + i + 1][y + j + 1]->hasPiece(player))
                   )
                    touchesAtLeastOneCorner = true;
            }
        }
    }
    return touchesAtLeastOneCorner;
}

int Board::computeScore(Player* player){
    // Measure how many squares have been played from the player
    int score = 0;
    for (int i = 0; i < boardSizeX; i++) {
        for (int j = 0; j < boardSizeY; j++) {
            if (squareBelongsToPlayer(i, j, player))
                score++;
        }
    }

    // Check if player has played all pieces
    if (player->getNumberOfAvailablePieces() == 0){
        score += 15;
        // Check if the last piece played by player is the first piece
        if (getLastPiecePlayedByPlayer(player)->getId() == 1)
            score += 5;
    }
    return score;
}
