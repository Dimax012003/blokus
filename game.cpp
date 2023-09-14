#include <iomanip>
#include <iostream>
#include "game.h"

Game::Game(Board* board, Player** players) {
    this->board = board;
    this->players = players;
    score = new int[2];
    numTurns = 0;
    playerTurn = 0;
}

Game::~Game() {
    delete[] score;
}

int Game::getPlayerTurn() {
    return playerTurn;
}

int Game::getNumTurns() {
    return numTurns;
}

void Game::endTurn() {
    // Change to the other player
    playerTurn = 1 - playerTurn;
    // Increment the number of turns
    numTurns++;
}

void Game::printState() {
    cout << "Board:" << endl << board->toString() << endl;
    cout << "Score: " << board->computeScore(players[0]) << " - " << board->computeScore(players[1]) << endl << endl;
    players[0]->printAvailablePieces();
    players[1]->printAvailablePieces();
}

bool Game::makeMove(){
    bool valid = false;
    if (playerCanPlaceAnyPiece(playerTurn)) {
        // if the player has any valid move then it must be made
        Board* boardCopy = board->deepCopy();
        Move* pmove = players[playerTurn]->makeMove(boardCopy);
        if (board->pieceCanBePlaced(pmove->getPiece(), pmove->getX(), pmove->getY(), pmove->getOrientation(), pmove->getFlip())) {
            board->placePiece(pmove->getPiece(), pmove->getX(), pmove->getY(), pmove->getOrientation(), pmove->getFlip());
            valid = true;
            cout << players[playerTurn]->getName() << " played " << pmove->toString() << endl << endl;
        }
        delete pmove;
    }
    else
        valid = true; // if the player does not have any valid moves then no move will be made
    return valid;
}

bool Game::playerCanPlaceAnyPiece(int index) {
    return players[index]->canPlaceAnyPiece(board);
}

bool Game::playersCanPlaceAnyPiece() {
    return players[0]->canPlaceAnyPiece(board) || players[1]->canPlaceAnyPiece(board);
}

int Game::getPoints(int index) {
    // Measure how many squares have been played from the player
    int score = 0;
    for (int i = 0; i < board->getSizeX(); i++) {
        for (int j = 0; j < board->getSizeY(); j++) {
            if (board->squareBelongsToPlayer(i, j, players[index]))
                score++;
        }
    }

    // Check if player has played all pieces
    if (players[index]->getNumberOfAvailablePieces() == 0){
        score += 15;
        // Check if the last piece played by player is the first piece
        if (board->getLastPiecePlayedByPlayer(players[index])->getId() == 1)
            score += 5;
    }
    return score;
}
