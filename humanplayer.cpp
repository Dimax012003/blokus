#include <iostream>
#include "player.h"

HumanPlayer::HumanPlayer(int id) : Player(id) {

}

HumanPlayer::HumanPlayer(int id, string name) : Player(id) {
    this->name = name;
}

Move* HumanPlayer::makeMove(Board* board) {
    int pieceId, x, y;
    int orientation, flip;
    cout << "Select piece (1-21), orientation (0 for UP, 1 for RIGHT, 2 for DOWN, 3 for LEFT), " <<
            "flip (0 for NO, 1 for YES), position (x, y), (e.g. 3 0 0 3 4): " << endl;
    if (getNumberOfPlacedPieces() == 0)
        cout << "First piece must touch square " << (getId() == 0 ? "4, 4" : "9, 9") << endl;
    cin >> pieceId >> orientation >> flip >> x >> y;
    return new Move(pieces[pieceId-1], x, y, (Orientation)orientation, (Flip)flip);
}

