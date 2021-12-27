// Pragma Once
#ifndef _rook_h
#define _rook_h

// Include Modules
#include "globals.h"
#include "piece.h"

// Pawn Class
class Rook:public Piece{
    private:
        // Variable Declaration
        char type;
    public:
        // Constructor
        Rook(int xLoc, int yLoc, string newColor, char newType);

        // Accessors and Mutators
        char getType();
        void setType(char newType);

        // Utility Functions
        virtual void print();
};

#endif