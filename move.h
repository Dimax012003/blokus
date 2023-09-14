#ifndef MOVE_H
#define MOVE_H

#include "piece.h"

/**
 * Class that implements a move of the game.
 */
class Move
{
private:
    Piece* piece; // the piece that is placed as part of the move
    int x; // the row where the upper left square of the piece is placed
    int y; // the column where the upper left square of the piece is placed
    Orientation orientation; // piece rotation as enumeration (UP for no rotation/0 degrees, RIGHT for 90 degrees, DOWN for 180 degrees, LEFT for 270 degrees)
    Flip flip; // piece flip as enumeration (NO for no flip, YES for horizontal flip)

public:
    /**
     * Initializes a move setting its piece to be placed, the coordinates for the upper left square of
     * the piece, the orientation, and the flip of the piece to the values given as parameters.
     *
     * @param piece the piece that is placed.
     * @param x the row of the upper left square of the move.
     * @param y the column of the upper left square of the move.
     * @param orientation the orientation of the piece that is placed.
     * @param flip the flip of the piece that is placed.
     */
    Move(Piece* piece, int x, int y, Orientation orientation, Flip flip);

    /**
     * Initializes a move setting its elements to those of the one given. This method practically copies
     * the move, however the piece should not be copied.
     *
     * @param move the move to be copied to this move.
     */
    Move(Move* amove);

    /**
     * Sets the piece of this move to the one given.
     *
     * @param piece the piece that should be set for this move.
     */
    void setPiece(Piece* piece);

    /**
     * Returns the piece that is placed by this move.
     *
     * @return the piece that is placed by this move.
     */
    Piece* getPiece();

    /**
     * Returns the row of the upper left square of the move.
     *
     * @return the row of the upper left square of the move.
     */
    int getX();

    /**
     * Returns the column of the upper left square of the move.
     *
     * @return the column of the upper left square of the move.
     */
    int getY();

    /**
     * Returns the orientation of the piece of the move.
     *
     * @return the orientation of the piece of the move.
     */
    Orientation getOrientation();

    /**
     * Returns the flip of the piece of the move.
     *
     * @return the flip of the piece of the move.
     */
    Flip getFlip();

    /**
     * Returns a string representation of this move. It contains all the elements of the move.
     *
     * @return the move as a string.
     */
    string toString();
};

#endif // MOVE_H
