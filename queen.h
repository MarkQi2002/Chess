// Pragma Once
#ifndef _queen_h
#define _queen_h

// Include Modules
#include "globals.h"
#include "piece.h"

// Pawn Class
class Queen:public Piece{
    private:
        // Variable Declaration
        char type;
    public:
        // Constructor
        Queen(int xLoc, int yLoc, string newColor, char newType);

        // Destructor
        virtual ~Queen();

        // Accessors and Mutators
        char getType();
        void setType(char newType);

        // Utility Functions
        virtual void print();
        void printType();
};

#endif