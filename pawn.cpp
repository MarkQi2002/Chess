// Include Modules
#include "globals.h"
#include "pawn.h"

// Constructor
Pawn::Pawn(int xLoc, int yLoc, string newColor, char newType):Piece(xLoc, yLoc, newColor){
    type = newType;
    firstMove = true;
}

// Destructor
Pawn::~Pawn(){

}

// Accessor
char Pawn::getType(){
    return type;
}

bool Pawn::getFirstMove(){
    return firstMove;
}

// Mutator
void Pawn::setFirstMove(bool newFirstMove){
    firstMove = newFirstMove;
}

void Pawn::setType(char newType){
    type = newType;
}

// Utility Functions
void Pawn::print(){
    Piece::print();
    cout << "Type: " << type << endl;
}

void Pawn::printType(){
    cout << type;
}