// Include Modules
#include "globals.h"
#include "bishop.h"

// Constructor
Bishop::Bishop(int xLoc, int yLoc, string newColor, char newType):Piece(xLoc, yLoc, newColor){
    type = newType;
}

// Destructor
Bishop::~Bishop(){

}

// Accessor
char Bishop::getType(){
    return type;
}

// Mutator
void Bishop::setType(char newType){
    type = newType;
}

// Utility Functions
void Bishop::print(){
    Piece::print();
    cout << "Type: " << type << endl;
}

void Bishop::printType(){
    cout << type;
}