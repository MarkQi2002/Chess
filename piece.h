// Pragma Once
#ifndef _piece_h
#define _piece_h

// Include Modules
#include <iostream>
#include <string>
#include <vector>

using namespace std; 

// Piece Class
class Piece{
    private:
        // Variable Declaration 
        vector <int> position;
        string color;

    public: 
        // Constructor
        Piece(int xLoc, int yLoc, string newColor);
        
        // Accessors and Mutators
        void move(vector <int> newPosition);
        vector <int> getPosition(); 
        string getColor();

        // Utility Function
        void draw();
};

#endif