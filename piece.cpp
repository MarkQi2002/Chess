// Include Modules
#include "globals.h"
#include "piece.h"

// Constructor
Piece::Piece(int xLoc, int yLoc, string newColor){
    position.push_back(xLoc);
    position.push_back(yLoc);
    color = newColor;
}

// Mutators
void Piece::move(vector <int> newPosition){
    position = newPosition;
}

// Accessors
vector <int> Piece::getPosition(){
    return position;
}

string Piece::getColor(){
    return color;
}

// Utility Functions
void Piece::draw(){
    cout << "Color: " << color << endl;
    cout << "Position: xLoc " << position[0] << " yLoc " << position[1] << endl;
}