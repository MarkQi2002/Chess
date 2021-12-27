// Pragma Once
#ifndef _knight_h
#define _knight_h

// Include Modules
#include "globals.h"
#include "piece.h"

// Pawn Class
class Knight:public Piece{
    private:
        // Variable Declaration
        char type;
    public:
        // Constructor
        Knight(int xLoc, int yLoc, string newColor, char newType);

        // Destructor
        virtual ~Knight();

        // Accessors and Mutators
        char getType();
        void setType(char newType);

        // Utility Functions
        virtual void print();
        void printType();
};

#endif