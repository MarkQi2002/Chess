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
        bool castling;

    public:
        // Constructor
        King(int xLoc, int yLoc, string newColor, char newType);

        // Destructor
        virtual ~King();

        // Accessors and Mutators
        char getType();
        bool getCastling();
        void setCastling(bool newCastling);
        void setType(char newType);

        // Utility Functions
        virtual void print();
        void printType();
};

#endif