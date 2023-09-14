#include "player.h"
#include "algorithms.h"

ComputerPlayer::ComputerPlayer(int id) : Player(id) {

}

int ComputerPlayer::evaluateBoard(Board* board) {
    int i,j;
    int sum1=0,sum2=0;
    char player1=getSymbol();
    for(i=0;i<board->getSizeX();i++){
        for(j=0;j<board->getSizeY();j++){
            if(board->squareBelongsToPlayer(i,j,player1)){
                sum1++;
            }
        }
    }
    for(i=0;i<board->getSizeX();i++){
        for(j=0;j<board->getSizeY();j++){
            if(board->squareBelongsToPlayer(i,j,opponent->getSymbol())){
                sum2++;
            }
        }
    }

        return sum1-sum2;

}

Move* ComputerPlayer::makeMove(Board* board) {
    // Get possible moves of all pieces
    int numPossibleMoves;
    Move** possibleMoves = getPossibleMoves(board, numPossibleMoves);

    // Get scores of the possible moves
    int* possibleMovesScores = new int[numPossibleMoves];
    for (int i = 0; i < numPossibleMoves; i++)
        possibleMovesScores[i] = evaluateMove(board, possibleMoves[i]);

    // Get the move to play
    Move* moveToPlay = new Move(getElementWithMaxScore(possibleMoves, possibleMovesScores, numPossibleMoves));

    // Delete the possible moves and the scores
    for (int i = 0; i < numPossibleMoves; i++)
        delete possibleMoves[i];
    delete[] possibleMoves;
    delete[] possibleMovesScores;

    // Return the move to play
    return moveToPlay;
}
