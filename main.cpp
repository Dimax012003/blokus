#include <ctime>
#include <cstdlib>
#include <iostream>
#include "game.h"

using namespace std;

int main() {
    // Uncomment the following line to make the moves random
     srand(time(NULL));

    // Initialize the game objects
    Board* board = new Board();
    Player** players = new Player*[2];
    Game* game = new Game(board, players);

    // Initialize players
    players[0] = new ComputerPlayer(0);
    players[1] = new RandomPlayer(1);
    players[0]->setOpponent(players[1]);
    players[1]->setOpponent(players[0]);

    int playerTurn = game->getPlayerTurn();
    do {
        cout << "Turn of " << players[playerTurn]->getName() << " - ";
        game->printState();

        if (!game->makeMove()){
            cout << "Error in move of player " << players[playerTurn]->getName() << "! Exiting..." << endl;
            std::exit(0);
        }

        game->endTurn();
        playerTurn = game->getPlayerTurn();
        // Uncomment the following line to add a delay
        // for(int i = 0; i < 100000000; i++);
    } while(game->playersCanPlaceAnyPiece());
    game->printState();

    // Print the winner and the final score of the game
    int player1points = board->computeScore(players[0]);
    int player2points = board->computeScore(players[1]);
    if (player1points > player2points)
        cout << players[0]->getName() << " has won! (Score: " << player1points << " - " << player2points << ")" << endl;
    else if (player1points < player2points)
        cout << players[1]->getName() << " has won! (Score: " << player1points << " - " << player2points << ")" << endl;
    else
        cout << "It's a draw! (Score: " << player1points << " - " << player2points << ")" << endl;

    // Delete all objects
    delete game;
    for (int i = 0; i < 2; i++)
        delete players[i];
    delete[] players;
    delete board;

    return 0;
}

