// Include Modules
#include "globals.h"
#include "empty.h"

// Constructor
Empty::Empty(int xLoc, int yLoc, string newColor, char newType):Piece(xLoc, yLoc, newColor){
    type = newType;
}

// Destructor
Empty::~Empty(){

}

// Accessor
char Empty::getType(){
    return type;
}

// Mutator
void Empty::setType(char newType){
    type = newType;
}

void Empty::checkType(){
    if (getPosition()[0] % 2 == 0 && getPosition()[1] % 2 == 1) setType(emptyTwo);
    else if (getPosition()[0] % 2 == 1 && getPosition()[1] % 2 == 0) setType(emptyTwo);
    else setType(emptyOne);
}

// Utility Functions
void Empty::print(){
    Piece::print();
    cout << "Type: " << type << endl;
}

void Empty::printType(){
    cout << type;
}