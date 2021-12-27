// Include Modules
#include "globals.h"
#include "king.h"

// Constructor
King::King(int xLoc, int yLoc, string newColor, char newType):Piece(xLoc, yLoc, newColor){
    type = newType;
}

// Accessor
char King::getType(){
    return type;
}

// Mutator
void King::setType(char newType){
    type = newType;
}

// Utility Functions
void King::print(){
    Piece::print();
    cout << "Type: " << type << endl;
}