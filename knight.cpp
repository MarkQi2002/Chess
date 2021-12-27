// Include Modules
#include "globals.h"
#include "knight.h"

// Constructor
Knight::Knight(int xLoc, int yLoc, string newColor, char newType):Piece(xLoc, yLoc, newColor){
    type = newType;
}

// Destructor
Knight::~Knight(){

}

// Accessor
char Knight::getType(){
    return type;
}

// Mutator
void Knight::setType(char newType){
    type = newType;
}

// Utility Functions
void Knight::print(){
    Piece::print();
    cout << "Type: " << type << endl;
}

void Knight::printType(){
    cout << type;
}