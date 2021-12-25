// Pragma Once
#ifndef _board_h
#define _board_h

#include <iostream>
#include "globals.h"

using namespace std;

// Define Class Board
class Board{
    private:
        char mainBoard[boardSize][boardSize];

    public:
        // Constructor
        Board();

        // Accessors and Mutators
        void setBoard(int row, int col, char player);
        char getBoard(int row, int col);

        // Utility Functions
        void draw();
};

#endif
