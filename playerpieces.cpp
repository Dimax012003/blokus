#include <iomanip>
#include <iostream>
#include "player.h"

void Player::createPieces() {
    char o = (id == 0 ? '#' : 'O'), i = '-';

    char allspieces[21][5][5] = {{
                                {o, i, i, i, i}, // Piece 1
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 2
                                {o, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 3
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 4
                                {o, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 5
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 6
                                {i, o, i, i, i},
                                {o, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 7
                                {o, o, i, i, i},
                                {o, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, o, i, i, i}, // Piece 8
                                {o, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, o, i, i, i}, // Piece 9
                                {i, o, o, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 10
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {o, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 11
                                {i, o, i, i, i},
                                {i, o, i, i, i},
                                {o, o, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 12
                                {i, o, i, i, i},
                                {o, o, i, i, i},
                                {o, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 13
                                {o, o, i, i, i},
                                {o, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, o, i, i, i}, // Piece 14
                                {i, o, i, i, i},
                                {o, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 15
                                {o, o, i, i, i},
                                {o, i, i, i, i},
                                {o, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 16
                                {i, o, i, i, i},
                                {o, o, o, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 17
                                {o, i, i, i, i},
                                {o, o, o, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, o, i, i, i}, // Piece 18
                                {i, o, o, i, i},
                                {i, i, o, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 19
                                {o, o, o, i, i},
                                {i, i, o, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {o, i, i, i, i}, // Piece 20
                                {o, o, o, i, i},
                                {i, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                                }, {
                                {i, o, i, i, i}, // Piece 21
                                {o, o, o, i, i},
                                {i, o, i, i, i},
                                {i, i, i, i, i},
                                {i, i, i, i, i}
                            }};
    for (int i = 0; i < 21; i++){
        // Compute the size of each piece
        int sizeX = 0;
        int sizeY = 0;
        for(int x = 0; x < 5; x++){
            for(int y = 0; y < 5; y++) {
                if (allspieces[i][x][y] != '-'){
                    sizeX = (x + 1 > sizeX) ? (x + 1) : sizeX;
                    sizeY = (y + 1 > sizeY) ? (y + 1) : sizeY;
                }
            }
        }
        // Create the squares of each piece
        Square*** squares = new Square**[sizeX];
        for(int x = 0; x < sizeX; x++) {
            squares[x] = new Square*[sizeY];
            for(int y = 0; y < sizeY; y++) {
                squares[x][y] = new Square(x, y, allspieces[i][x][y]);
            }
        }
        // Create the piece
        pieces[i] = new Piece(i + 1, id == 0 ? '#' : 'O', squares, sizeX, sizeY);
    }
};

void Player::printPiecesSideBySide(Piece** pieces, int pstart, int pend){
    // Compute the number of pieces to be print
    int numPieces = pend - pstart;

    // Print the ids of the pieces and concatenate the pieces using a stream
    stringstream ss[numPieces];
    cout << "   ";
    for (int i = pstart; i < pend; i++){
        cout << (pieces[i]->getId() > 9 ? "" : " ") << pieces[i]->getId() << "          ";
        ss[i - pstart] << pieces[i]->toString();
    }
    cout << endl;

    // Print the pieces line by line
    string to[numPieces];
    for (int j = 0; j < 5; j++){
        for (int i = pstart; i < pend; i++){
            getline(ss[i - pstart], to[i - pstart], '\n');
            cout << to[i - pstart] << "   ";
        }
        cout << endl;
    }
}

void Player::printAvailablePieces(){
    // Create an array with the available pieces of the player
    int numAvailablePieces = getNumberOfAvailablePieces();
    Piece** availablePieces = new Piece*[numAvailablePieces];
    int j = 0;
    for (int i = 0; i < numPieces; i++){
        if (!pieces[i]->isPlaced())
            availablePieces[j++] = pieces[i];
    }

    // Print the name of the player, the number of available pieces, and the available pieces
    cout << name << " has " << numAvailablePieces << " available pieces:" << endl;
    if (numAvailablePieces > 7){
        printPiecesSideBySide(availablePieces, 0, 7);
        if (numAvailablePieces > 14){
            printPiecesSideBySide(availablePieces, 7, 14);
            printPiecesSideBySide(availablePieces, 14, numAvailablePieces);
        }
        else
            printPiecesSideBySide(availablePieces, 7, numAvailablePieces);
    }
    else
        printPiecesSideBySide(availablePieces, 0, numAvailablePieces);
    delete[] availablePieces;
}
