// Include Modules
#include "globals.h"
#include "queen.h"

// Constructor
Queen::Queen(int xLoc, int yLoc, string newColor, char newType):Piece(xLoc, yLoc, newColor){
    type = newType;
    castling = true;
}

// Destructor
Queen::~Queen(){
    
}

// Accessor
char Queen::getType(){
    return type;
}

bool Queen::getCastling(){
    return castling;
}

// Mutator
void Queen::setCastling(bool newCastling){
    castling = newCastling;
}

void Queen::setType(char newType){
    type = newType;
}

// Utility Functions
void Queen::print(){
    Piece::print();
    cout << "Type: " << type << endl;
}

void Queen::printType(){
    cout << type;
}