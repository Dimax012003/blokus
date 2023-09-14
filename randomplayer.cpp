#include <cstdlib>
#include "player.h"
#include "algorithms.h"

RandomPlayer::RandomPlayer(int id) : Player(id) {

}

Move* RandomPlayer::makeMove(Board* board) {
    // Get possible moves of all pieces
    int numPossibleMoves;
    Move** possibleMoves = getPossibleMoves(board, numPossibleMoves);

    // Shuffle the possible moves
    shuffle(possibleMoves, numPossibleMoves);

    // Get the move to play
    Move* moveToPlay = new Move(possibleMoves[0]);

    // Delete the possible moves
    for (int i = 0; i < numPossibleMoves; i++)
        delete possibleMoves[i];
    delete[] possibleMoves;

    // Return the move to play
    return moveToPlay;
}


