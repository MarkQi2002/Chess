// Include Modules
#include "globals.h"
#include "king.h"

// Constructor
King::King(int xLoc, int yLoc, string newColor, char newType):Piece(xLoc, yLoc, newColor){
    type = newType;
    castling = true;
}

// Accessor
char King::getType(){
    return type;
}

bool King::getCastling(){
    return castling;
}

// Mutator
void King::setCastling(bool newCastling){
    castling = newCastling;
}

void King::setType(char newType){
    type = newType;
}

// Utility Functions
void King::print(){
    Piece::print();
    cout << "Type: " << type << endl;
}

void King::printType(){
    cout << type;
}