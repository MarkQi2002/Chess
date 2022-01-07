// Include Modules
#include "globals.h"
#include "piece.h"

// Constructor
Piece::Piece(int xLoc, int yLoc, string newColor){
    position.push_back(xLoc);
    position.push_back(yLoc);
    color = newColor;
}

// Destructor
Piece::~Piece(){

}

// Accessors
vector <int> Piece::getPosition(){
    return position;
}

string Piece::getColor(){
    return color;
}

bool Piece::getFirstMove(){
    return false; // THIS COULD BE WRONG
}

char Piece::getType(){
    return emptyOne; // THIS COULD BE WRONG
}

bool Piece::getCastling(){
    return false; // THIS COULD BE WRONG
}

// Mutators
void Piece::move(vector <int> newPosition){
    position = newPosition;
}

void Piece::setColor(string newColor){
    color = newColor;
}

void Piece::setFirstMove(bool newFirstMove){

}

void Piece::setType(char newType){

}

void Piece::setCastling(bool newCastling){

}

void Piece::checkType(){
    
}

// Utility Functions
void Piece::print(){
    cout << "Color: " << color << endl;
    cout << "Position: xLoc " << position[0] << " yLoc " << position[1] << endl;
}

void Piece::printType(){
    return;
}