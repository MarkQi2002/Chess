// Pragma Once
#ifndef _board_h
#define _board_h

#include "globals.h"
#include "piece.h"

using namespace std;

// Define Class Board
class Board{
    private:
        // Variable Declaration
        Piece* mainBoard[boardSize][boardSize];

    public:
        // Constructor
        Board();

        // Destructor
        ~Board();

        // Accessors and Mutators
        Piece* getBoard(int row, int col);
        void setBoard(int row, int col, Piece* newPiece);

        // Utility Functions
        void draw();
        void exchangePosition(vector <int> original, vector <int> next);
        void conquerMove(vector <int> original, vector <int> next);
        void upgradePawn(vector <int> original, vector <int> next, char upgradeType);
        bool checkWin();
};

#endif
