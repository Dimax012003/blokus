#ifndef BOARD_H
#define BOARD_H

#include <string>
#include "piece.h"
class Player;

/**
 * Class that implements a board of the game.
 */
class Board {
private:
    int boardSizeX; // the number of rows of the board, which must be equal to 14 (the board is a 14 x 14 area)
    int boardSizeY; // the number of columns of the board, which must be equal to 14 (the board is a 14 x 14 area)
    Square*** squares; // a 14 x 14 array of squares (objects of type Square*)
    Piece* lastPiecePlayedByFirstPlayer; // the last piece that was played by the first player
    Piece* lastPiecePlayedBySecondPlayer; // the last piece that was played by the second player
public:
    /**
     * Initializes this board, by creating a 14 x 14 array of squares.
     */
    Board();

    /**
     * Deletes this board, by deleting the array of squares.
     */
    ~Board();

    /**
     * Returns the number of rows of the board.
     *
     * @return the number of rows of the board.
     */
    int getSizeX();

    /**
     * Returns the number of columns of the board.
     *
     * @return the number of columns of the board.
     */
    int getSizeY();

    /**
     * Checks if a square placed in (x, y) is occupied by a piece.
     *
     * @param x the row of the square.
     * @param y the column of the square.
     * @return true if the square is occupied by a piece, or false otherwise.
     */
    bool hasPiece(int x, int y);

    /**
     * Checks if a square placed in (x, y) belongs to a given player, i.e. it is occupied by the player piece.
     *
     * @param x the row of the square.
     * @param y the column of the square.
     * @param player the symbol of the player of the square as a char.
     * @return true if the square is occupied by a piece of the player, or false otherwise.
     */
    bool squareBelongsToPlayer(int x, int y, char player);

    /**
     * Checks if a square placed in (x, y) belongs to a given player, i.e. it is occupied by the player piece.
     *
     * @param x the row of the square.
     * @param y the column of the square.
     * @param player the player of the square as an object.
     * @return true if the square is occupied by a piece of the player, or false otherwise.
     */
    bool squareBelongsToPlayer(int x, int y, Player* player);

    /**
     * Checks if the given player has placed any pieces on the board. This method should return
     * true if no square of the board is occupied by a piece of the player, or false otherwise.
     *
     * @param player the player to be checked if any player pieces are on the board.
     * @return true if no square of the board is occupied by a piece of the player, or false otherwise.
     */
    bool playerHasPlacedNoPieces(char player);

    /**
     * Returns the last piece played by the given player.
     *
     * @param player the player of which the last piece played is returned.
     * @return the last piece played by the given player.
     */
    Piece* getLastPiecePlayedByPlayer(Player* player);

    /**
     * Places a piece of the player given its position (x, y). We assume that any
     * orientation or flip of the piece has been performed before calling this method.
     *
     * @param piece the piece to be placed on the board.
     * @param x the row of the first (upper left) square of the piece.
     * @param y the column of the first (upper left) square of the piece.
     */
    void placePiece(Piece* piece, int x, int y);

    /**
     * Places a piece of the player given its position (x, y), its orientation and its flip.
     *
     * @param piece the piece to be placed on the board.
     * @param x the row of the first (upper left) square of the piece.
     * @param y the column of the first (upper left) square of the piece.
     * @param orientation the rotation of the piece as an Orientation variable (UP, RIGHT, DOWN, LEFT).
     * @param flip the flip of the piece as a Flip variable (NO, YES).
     */
    void placePiece(Piece* piece, int x, int y, Orientation orientation, Flip flip);

    /**
     * Returns a string representation of the board. It is a 14 x 14 area of chars, where each char denotes whether
     * the square is unoccupied ('-'), belongs to the first player ('#') or to the second player ('O').
     *
     * @return the board as a string.
     */
    string toString();

    /**
     * Returns a copy of this board. The copy contains a new array of squares that has the same values as the
     * squares of this board. After calling this function, it is important to delete the newly created board.
     *
     * @return a new board that is a copy of this board.
     */
    Board* deepCopy();

    /**
     * Checks if a piece can be placed on the position (x, y) on the board. We assume that any
     * orientation or flip of the piece has been performed before calling this method.
     * A piece can be placed on the board if the following conditions are true:
     * - If it is the first piece of the player (i.e. the player has placed no other pieces yet), then
     *   it must touch square 4, 4 for the first player (#) or 9, 9 for the second player (O).
     * - If it is not the first piece of the player (i.e. the player has already placed other piece(s)),
     *   then the piece must touch at least one corner with any other piece of the same player.
     * - The piece must be inside the bounds of the board (i.e. inside the 14 x 14 area).
     * - The piece must not fall on top of any other piece (any square can be occupied only once).
     * - The piece must not touch any other piece of the same player edge-by-edge.
     * - The piece must not touch any other piece of the same player edge-by-edge.
     *
     * Hint: Checking for a piece requires checking for its squares that are occupied (have char player
     *       equal to # or O). It is possible that a piece has e.g. 9 squares (3 x 3) and some of them
     *       are occupied while others are not:
     *
     *                                                0 1 2
     *                                              0 - # -
     *                                              1 - # -
     *                                              2 # # #
     *
     *       Checking for this piece requires that we check for all of its squares that are occupied
     *       (i.e. have a #/O and not a -). Each of these squares must follow the rules outlined above.
     *
     * @param piece the piece to be placed on the board.
     * @param x the row of the first (upper left) square of the piece.
     * @param y the column of the first (upper left) square of the piece.
     * @return true if the piece can be placed on the board, or false otherwise.
     */
    bool pieceCanBePlaced(Piece* piece, int x, int y);

    /**
     * Checks if a piece can be placed on the position (x, y) on the board, with the given orientation
     * and the given flip. This method makes a copy of the piece (to avoid changing its orientation and
     * flip) and calls the other pieceCanBePlaced method.
     *
     * @param piece the piece to be placed on the board.
     * @param x the row of the first (upper left) square of the piece.
     * @param y the column of the first (upper left) square of the piece.
     * @param orientation the rotation of the piece as an Orientation variable (UP, RIGHT, DOWN, LEFT).
     * @param flip the flip of the piece as a Flip variable (NO, YES).
     * @return true if the piece can be placed on the board, or false otherwise.
     */
    bool pieceCanBePlaced(Piece* piece, int x, int y, Orientation orientation, Flip flip);

    /**
     * Computes and returns the score of the given player at the end of the game. The score is the total
     * number of squares occupied by the player. Also, if the player has played all the pieces then the
     * score is increased by 15 more points. In this case (with all pieces played). if the smallest piece
     * (that with id 1) was played as the last player move, then the score is increased by 5 more points.
     *
     * @param player the player of which the score is computed.
     * @return the score of the given player.
     */
    int computeScore(Player* player);
};

#endif // BOARD_H
