// Pragma Once
#ifndef _piece_h
#define _piece_h

// Include Modules
#include "globals.h"

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

        // Destructor
        virtual ~Piece();
        
        // Accessors and Mutators
        vector <int> getPosition(); 
        string getColor();
        void move(vector <int> newPosition);
        void setColor(string newColor);
        virtual void checkType(); // For Empty Class

        // Utility Function
        virtual void print();
        virtual void printType(); // make the whole class abstract, not necessary though.
};

#endif