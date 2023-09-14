#ifndef PIECE_H
#define PIECE_H

#include "square.h"

/**
 * Enumeration for the orientation of the piece
 */
enum Orientation {UP, RIGHT, DOWN, LEFT};

/**
 * Enumeration for the flip of the piece
 */
enum Flip {NO, YES};

/**
 * Class that implements a piece of the game.
 */
class Piece {
private:
    int id;
    bool placed; // boolean denoting if this piece has been placed on the board (true) or not (false)
    char player; // char denoting the player that owns this pieces, '#' for the first player, 'O' for the second player, '-' for none
    int sizeX; // the number of rows of the piece.
    int sizeY; // the number of columns of the piece.
    Square*** squares; // the squares of the piece

public:
    /**
     * Initializes a piece given its id, setting its size to 5 and initializing its squares.
     * Note that each square has its coordinates (x, y) and the char of the player.
     * We must also set that the piece is initially is not placed.
     *
     * @param id the id of the piece.
     * @param player char of the player who owns the piece.
     * @param squares array of squares os this a piece (with char piecePlayer) or not.
     * @param sizeX the number of rows of the piece.
     * @param sizeY the number of columns of the piece.
     */
    Piece(int id, char player, Square*** squares, int sizeX, int sizeY);

    /**
     * Deletes this piece, by deleting the array of squares.
     */
    ~Piece();

    /**
     * Deletes the array of squares of this piece.
     */
    void deleteSquares();

    /**
     * Returns the id of the piece.
     *
     * @return the id of the piece.
     */
    int getId();

    /**
     * Returns the player that owns the piece.
     *
     * @return char of the player who owns the piece.
     */
    char getPlayer();

    /**
     * Sets the placed variable of the piece to the boolean value given.
     *
     * @param placed the value to be given to the placed variable.
     */
    void setPlaced(bool placed);

    /**
     * Sets the placed variable of the piece to true.
     */
    void setPlaced();

    /**
     * Checks whether the piece has been placed on the board.
     *
     * @return true if the piece has been placed on the board, or false otherwise.
     */
    bool isPlaced();

    /**
     * Returns the number of rows of the piece.
     *
     * @return the number of rows of the piece.
     */
    int getSizeX();

    /**
     * Returns the number of columns of the piece.
     *
     * @return the number of columns of the piece.
     */
    int getSizeY();

    /**
     * Returns a specific square of the piece given its coordinates.
     *
     * @param x the row of the square to be returned.
     * @param y the column of the square to be returned.
     * @return the square of the piece at row x and column y.
     */
    Square* getSquare(int x, int y);

    /**
     * Checks whether a specific square has part of the piece given its coordinates.
     *
     * @param x the row of the square to be checked.
     * @param y the column of the square to be checked.
     * @return true if the square has part of the piece on it, or false otherwise.
     */
    bool squareHasPiece(int x, int y);

    /**
     * Rotates the piece clockwise. An example clockwise rotation is the following:
     *
     *    Initial state         Rotated
     *         - #               # - -
     *         - #      ---->    # # #
     *         # #
     */
    void rotatePieceClockwise();

    /**
     * Rotates the piece according to the orientation received as input. Orientation UP means that the piece should not be
     * rotated at all, RIGHT means that the piece must be rotated clockwise one time, DOWN means that it must be rotated clockwise
     * two times, and LEFT means that it must be rotated clockwise three times.
     *
     * @param orientation the orientation of the square to be returned.
     */
    void rotatePiece(Orientation orientation);

    /**
     * Flips the piece horizontally. An example horizontal flip is the following:
     *
     *    Initial state          Flipped
     *         - #                 # -
     *         - #      ---->      # -
     *         # #                 # #
     */
    void flipPiece();

    /**
     * Returns a string representation of this piece. It is an area of chars, where each char denotes whether
     * the square is unoccupied ('-'), belongs to the first player ('#') or to the second player ('O').
     *
     * @return the piece as a string.
     */
    string toString();

    /**
     * Returns a copy of this piece. The copy contains a new array of squares that has the same values as the
     * squares of this piece. After calling this function, it is important to delete the newly created piece.
     *
     * @return a new piece that is a copy of this piece.
     */
    Piece* deepCopy();
};

#endif // PIECE_H
