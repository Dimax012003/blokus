#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "move.h"
#include "piece.h"
#include "board.h"

/**
 * Class that implements a player of the game.
 */
class Player {
private:
    int id;
    char symbol;

protected:
    string name;
    int numPieces; // the number of pieces of the player (initialized to 21)
    Piece** pieces; // the pieces of the player
    Player* opponent; // the opponent of the player

public:
    /**
     * Initializes a player setting the index and the name. The numPieces is set to 21.
     * Finally, the createPieces method must be called to create all the pieces of the player.
     *
     * @param id the id of the player.
     */
    Player(int id);

    /**
     * Deletes this player by deleting the array of pieces.
     */
    virtual ~Player();

    /**
     * Sets the opponent of the player to the one given.
     *
     * @param player the opponent of this player.
     */
    void setOpponent(Player* player);

    /**
     * Returns the id of the player.
     *
     * @return the id of the player.
     */
    int getId();

    /**
     * Returns the symbol of the player (# for the first player, O for the second).
     *
     * @return the symbol of the player as a char '#' or 'O'.
     */
    char getSymbol();

    /**
     * Returns the name of the player.
     *
     * @return the name of the player.
     */
    string getName();

    /**
     * Returns a piece of the player given its index.
     *
     * @param index the index of the piece to be returned.
     * @return a piece of the player given its index.
     */
    Piece* getPiece(int index);

    /**
     * Returns the number of the placed pieces of the player, i.e. the number
     * of pieces that have been placed on the board.
     *
     * @return the number of the placed pieces of the player.
     */
    int getNumberOfPlacedPieces();

    /**
     * Returns the number of the available pieces of the player, i.e. the number
     * of pieces that have not been placed yet.
     *
     * @return the number of the available pieces of the player.
     */
    int getNumberOfAvailablePieces();

    /**
     * Receives the current state of the board and returns a move.
     *
     * This method has to be implemented from all derived classes of Player.
     *
     * @return an object of type Move containing a piece, its position, its orientation, and its flip.
     */
    virtual Move* makeMove(Board* board) = 0;

    /**
     * Returns the possible moves for any piece, so that it is placed in any square of the board,
     * any orientation and any flip. The moves are returned as a dynamic Move array (Move**, i.e. array
     * of Move* objects) and their number (i.e. the size of the array) is returned as a function parameter.
     *
     * @param board the board to check where any piece can be placed.
     * @param numPossibleMoves the number of possible moves, used as a return parameter.
     * @return the possible moves for any piece (and their number as a parameter).
     */
    Move** getPossibleMoves(Board* board, int& numPossibleMoves);

    /**
     * Returns the possible moves for the given piece, so that it is placed in any square of the board,
     * any orientation and any flip. The moves are returned as a dynamic Move array (Move**, i.e. array
     * of Move* objects) and their number (i.e. the size of the array) is returned as a function parameter.
     *
     * @param board the board to check where the piece can be placed.
     * @param piece the piece to check where it can be placed.
     * @param numPossibleMoves the number of possible moves of the piece, used as a return parameter.
     * @return the possible moves for the given piece (and their number as a parameter).
     */
    Move** getPossibleMoves(Board* board, Piece* piece, int& numPossibleMoves);

    /**
     * Checks if the player can place the given piece in any square of the board, any orientation and any flip.
     *
     * @param board the board to check if any piece can be placed.
     * @param piece the piece to check if it can be placed.
     * @return true if the piece can be placed on the board, or false otherwise.
     */
    bool canPlacePiece(Board* board, Piece* piece);

    /**
     * Checks if the player can place any piece in any square of the board, any orientation and any flip.
     * This method is used to determine whether the player can make any move in order to end the game.
     *
     * @param board the board to check if any piece can be placed.
     * @return true if the piece can be placed on the board, or false otherwise.
     */
    bool canPlaceAnyPiece(Board* board);

    /**
     * Prints the available pieces of the player, This method calls the printPiecesSideBySide method to
     * print the pieces side by side.
     */
    void printAvailablePieces();

    /**
     * Returns a copy of this player. The copy contains a new array of pieces that has the same values as the
     * pieces of this player. After calling this function, it is important to delete the newly created player.
     *
     * @return a new player that is a copy of this player.
     */
    Player* deepCopy();

    /**
     * Evaluates the state of the board that is given and provides a score. This method returns always zero
     * and can be extended if desired by the derived classes.
     *
     * @param board the board of the game to evaluate its state.
     * @return the score of the board as an integer.
     */
    virtual int evaluateBoard(Board* board);

protected:
    /**
     * Evaluates a potential move of the player when it is played on the given board. This method
     * creates copies of the board and the move in order to avoid changing the original objects and
     * calls the evaluateBoard method upon making the move. This method can be extended if desired by
     * the derived classes.
     *
     * @param board the board of the game to evaluate the move.
     * @param amove the move to be evaluated on the board.
     * @return the score of the move as an integer.
     */
    virtual int evaluateMove(Board* board, Move* amove);

private:
    /**
     * Creates the pieces of the player by calling the different constructors.
     */
    void createPieces();

    /**
     * Prints the given pieces from pstart to pend side by side.
     *
     * @param pieces the pieces to be printed.
     * @param pstart the start index of the array of pieces to be printed.
     * @param pend the end index of the array of pieces to be printed.
     */
    void printPiecesSideBySide(Piece** pieces, int pstart, int pend);
};

/**
 * Class that implements a human player that plays according to the input given by the console.
 */
class HumanPlayer : public Player {
public:
    /**
     * Initializes a human player calling the constructor of the player.
     *
     * @param id the id of the player.
     */
    HumanPlayer(int id);

    /**
     * Initializes a human player calling the constructor of the player and setting (overriding)
     * also the name of the player.
     *
     * @param id the id of the player.
     * @param name the name of the player.
     */
    HumanPlayer(int id, string name);

    /**
     * Receives the current state of the board and returns a move. A move contains the piece
     * to be placed on the board, its position (x, y), its orientation, and its flip.
     * The information of the move is read by the console.
     *
     * @return an object of type Move containing a piece, its position, its orientation, and its flip.
     */
    Move* makeMove(Board* board);
};

/**
 * Class that implements a computer player that plays randomly.
 */
class RandomPlayer : public Player {
public:
    /**
     * Initializes a random player calling the constructor of the computer player.
     *
     * @param id the id of the player.
     */
    RandomPlayer(int id);

    /**
     * Receives the current state of the board and returns a random move. A move contains the piece
     * to be placed on the board, its position (x, y), its orientation, and its flip.
     *
     * Step-by-step explanation:
     * - We find all possible moves of the player and store them in an array (using method getPossibleMoves).
     * - We shuffle the array (using the shuffle function).
     * - We choose the move to play (and create it using the Move(Move) constructor) that is in the first position.
     * - We delete the possible moves.
     *
     * @return an object of type Move containing a piece, its position, its orientation, and its flip.
     */
    Move* makeMove(Board* board);
};

/**
 * Class that implements a computer player.
 */
class ComputerPlayer : public Player {
protected:
    /**
     * Evaluates the state of the board that is given and provides a score. The score is calculated as
     * the number of squares of the board that are occupied by the player minus the number of squares
     * occupied by the opponent.
     *
     * Hint: this method can call the squareBelongsToPlayer method of class Board.
     *
     * @param board the board of the game to evaluate its state.
     * @return the score of the board (number of player squares minus number of opponent squares) as an integer.
     */
    int evaluateBoard(Board* board);
public:
    /**
     * Initializes a computer player calling the constructor of the player.
     *
     * @param id the id of the player.
     */
    ComputerPlayer(int id);

    /**
     * Receives the current state of the board and returns the move that has the best score according to
     * the evaluateMove function. A move contains the piece to be placed on the board, its position (x, y),
     * its orientation, and its flip.
     *
     * Step-by-step explanation:
     * - We find all possible moves of the player and store them in an array (using method getPossibleMoves).
     * - We create an array of integers and store the scores of the possible moves (calculated using the evaluateMove method).
     * - We choose the move to play (and create it using the Move(Move) constructor) that has the maximum score
     *   (using the getElementWithMaxScore function).
     * - We delete the possible moves and the scores.
     *
     * @return an object of type Move containing a piece, its position, its orientation, and its flip.
     */
    Move* makeMove(Board* board);
};

#endif // PLAYER_H
