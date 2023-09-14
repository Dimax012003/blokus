#ifndef GAME_H
#define GAME_H

#include "player.h"

/**
 * Class denoting the game.
 */
class Game
{
private:
    Board* board;
    Player** players;
    int numTurns;
    int playerTurn;
    int* score;

public:
    /**
     * Initializes a game setting the board, the deck and the players.
     * The score is also initialized.
     *
     * @param board the board of the game.
     * @param players the players of the game.
     */
    Game(Board* board, Player** players);

    /**
     * Deletes the game by deleting the score. Warning: this method does not also delete
     * the board, the deck and the players! These are deleted by the main function.
     */
    ~Game();

    /**
     * Returns the number of turns of the game.
     *
     * @return the number of turns of the game.
     */
    int getNumTurns();

    /**
     * Returns the turn of the game (either 0 or 1).
     *
     * @return the turn of the game.
     */
    int getPlayerTurn();

    /**
     * Ends the current turn by giving the turn to the other player (or applying the result of a card).
     */
    void endTurn();

    /**
     * Prints the state of the game including all players and their board.
     */
    void printState();

    /**
     * Makes the next move of the game by calling the relevant function of the player that has the turn to play.
     * Returns true if the given move is valid or false if the given move is invalid.
     *
     * @return true if the move given by the player is valid, or false otherwise.
     */
    bool makeMove();

    /**
     * Checks whether the player of which the index is given can make any move, i.e. can place any piece.
     *
     * @param index the index of the player to check whether the player can place any piece.
     * @return true if the player of which the index is given can place any piece, or false otherwise.
     */
    bool playerCanPlaceAnyPiece(int index);

    /**
     * Checks whether any of the two players can place any piece. This check is used to end the game
     *
     * @return true if at least one of the players can place any piece, or false otherwise.
     */
    bool playersCanPlaceAnyPiece();

    /**
     * Returns the points of a player given its index. Apart from the points gathered during the game,
     * at the end of the game if the player has lost, then he/she earns 0 points. If the player has won,
     * then he/she earns 50 points for the victory, as well as 10 points for every square of a Carrier ship
     * that is not hit, 5 points for every square of a Battleship ship that is not hit, and 1 point for
     * every square of any other ship that is not hit. These points are added to the already computed points
     * of the player from the start of the game.
     *
     * @param index the index of a player, either 0 or 1.
     * @return the points of a player given its index.
     */
    int getPoints(int index);
};

#endif // GAME_H
