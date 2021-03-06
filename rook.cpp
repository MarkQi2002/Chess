// Include Modules
#include "globals.h"
#include "rook.h"

// Constructor
Rook::Rook(int xLoc, int yLoc, string newColor, char newType):Piece(xLoc, yLoc, newColor){
    type = newType;
}

// Destructor
Rook::~Rook(){

}

// Accessor
char Rook::getType(){
    return type;
}

// Mutator
void Rook::setType(char newType){
    type = newType;
}

// Utility Functions
void Rook::print(){
    Piece::print();
    cout << "Type: " << type << endl;
}

void Rook::printType(){
    cout << type;
}