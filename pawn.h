// Pragma Once
#ifndef _pawn_h
#define _pawn_h

// Include Modules
#include "globals.h"
#include "piece.h"

// Pawn Class
class Pawn:public Piece{
    private:
        // Variable Declaration
        char type;
        bool firstMove;

    public:
        // Constructor
        Pawn(int xLoc, int yLoc, string newColor, char newType);

        // Destructor
        virtual ~Pawn();

        // Accessors and Mutators
        char getType();
        bool getFirstMove();
        void setFirstMove(bool newFirstMove);
        void setType(char newType);

        // Utility Functions
        virtual void print();
        void printType();
};

#endif