#include <iostream>
#include "square.h"

Square::Square(int x, int y){
    this->x = x;
    this->y = y;
    player = '-';
}

Square::Square(int x, int y, char player){
    this->x = x;
    this->y = y;
    this->player = player;
}

int Square::getX() {
    return x;
}

int Square::getY(){
    return y;
}

void Square::addPiece(char player) {
    this->player = player;
}

char Square::getPlayer(){
    return player;
}

void Square::removePiece() {
    player = '-';
}

bool Square::hasPiece() {
    return player != '-';
}

bool Square::hasPiece(char player){
    return this->player == player;
}
