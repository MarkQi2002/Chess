// Pragma Once
#ifndef _bishop_h
#define _bishop_h

// Include Modules
#include "globals.h"
#include "piece.h"

// Pawn Class
class Bishop:public Piece{
    private:
        // Variable Declaration
        char type;
    public:
        // Constructor
        Bishop(int xLoc, int yLoc, string newColor, char newType);

        // Accessors and Mutators
        char getType();
        void setType(char newType);

        // Utility Functions
        virtual void print();
        void printType();
};

#endif