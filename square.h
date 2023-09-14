#ifndef SQUARE_H
#define SQUARE_H

#include <sstream>

using namespace std;

/**
 * Class that implements a square of the game.
 */
class Square {
private:
    int x; // the row of the square
    int y; // the column of the square
    char player; // char indicating if the square has part of a piece of the first player (#), the second player (O) or none (-)

public:
    /**
     * Initializes a square setting its coordinates to the ones given and its player character
     * to '-' as no piece is placed on the square.
     *
     * @param x the row of the square.
     * @param y the column of the square.
     */
    Square(int x, int y);

    /**
     * Initializes a square setting its coordinates to the ones given and its player character
     * to the one given, indicating if the square has part of a piece of the first player (#),
     * the second player (O) or none (-).
     *
     * @param x the row of the square.
     * @param y the column of the square.
     * @param player char indicating where the square belongs (# for first player, O for second player, - for none).
     */
    Square(int x, int y, char player);

    /**
     * Returns the row of the square.
     *
     * @return the row of the square.
     */
    int getX();

    /**
     * Returns the column of the square.
     *
     * @return the column of the square.
     */
    int getY();

    /**
     * Adds a part of a piece to this square by setting the corresponding player variable to the character given.
     *
     * @param player char denoting which player owns the piece placed on the square ('#' for first or 'O' for second player).
     */
    void addPiece(char player);

    /**
     * Removes the piece from this square by setting the corresponding variable of the player to the '-' character.
     */
    void removePiece();

    /**
     * Checks if the square is occupied by a piece.
     *
     * @return true if the square is occupied by a piece, or false otherwise.
     */
    bool hasPiece();

    /**
     * Checks if the square is occupied by a piece of the given player.
     *
     * @param player char denoting if the square belongs to the first ('#') or the second ('O') player.
     * @return true if the square is occupied by a piece, or false otherwise.
     */
    bool hasPiece(char player);

    /**
     * Returns the character of the player who owns the piece placed on this square.
     *
     * @return '#' for the first player, 'O' for the second player, or '-' if the square does not have any piece on it.
     */
    char getPlayer();
};

#endif // SQUARE_H
