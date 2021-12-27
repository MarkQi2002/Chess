// Pragma Once
#ifndef _king_h
#define _king_h

// Include Modules
#include "globals.h"
#include "piece.h"

// Pawn Class
class King:public Piece{
    private:
        // Variable Declaration
        char type;
    public:
        // Constructor
        King(int xLoc, int yLoc, string newColor, char newType);

        // Accessors and Mutators
        char getType();
        void setType(char newType);

        // Utility Functions
        virtual void print();
        void printType();
};

#endif