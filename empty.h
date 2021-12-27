// Pragma Once
#ifndef _empty_h
#define _empty_h

// Include Modules
#include "globals.h"
#include "piece.h"

// Pawn Class
class Empty:public Piece{
    private:
        // Variable Declaration
        char type;
    public:
        // Constructor
        Empty(int xLoc, int yLoc, string newColor, char newType);

        // Destructor
        virtual ~Empty();

        // Accessors and Mutators
        char getType();
        void setType(char newType);

        // Utility Functions
        virtual void print();
        void printType();
};

#endif