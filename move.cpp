#include "move.h"

Move::Move(Piece* piece, int x, int y, Orientation orientation, Flip flip){
    this->piece = piece;
    this->x = x;
    this->y = y;
    this->orientation = orientation;
    this->flip = flip;
}

Move::Move(Move* amove) {
    piece = amove->getPiece();
    x = amove->getX();
    y = amove->getY();
    orientation = amove->getOrientation();
    flip = amove->getFlip();
}

void Move::setPiece(Piece* piece){
    this->piece = piece;
}

Piece* Move::getPiece(){
    return piece;
}

int Move::getX(){
    return x;
}

int Move::getY(){
    return y;
}

Orientation Move::getOrientation(){
    return orientation;
}

Flip Move::getFlip(){
    return flip;
}

string Move::toString() {
    string orientationStr[] = {"UP", "RIGHT", "DOWN", "LEFT"};
    stringstream sstm;
    sstm << "piece " << piece->getId() << " at (" << x << "," << y << ") with orientation "
         << orientationStr[orientation] << " and " << (flip ? "with" : "without") << " flip";
    string result = sstm.str();
    return result;
}
