// Include Modules
#include "globals.h"
#include "board.h"
#include "piece.h"

// Constructors
Board::Board(){
    // According to Handout
    // First Row
    for (int i = 0; i < boardSize; i++){
        if (i % 7 == 0) mainBoard[0][i] = blackRook;
        else if (i % 5 == 1) mainBoard[0][i] = blackKnight;
        else if (i % 3 == 2) mainBoard[0][i] = blackBishop;
        else if (i == 3) mainBoard[0][i] = blackQueen;
        else if (i == 4) mainBoard[0][i] = blackKing;
    }

    // Second Row
    for (int i = 0; i < boardSize; i++){
        mainBoard[1][i] = blackPawn;
    }

    // Third, Fourth, Fifth, and Sixth Row
    for (int i = 2; i < 6; i++){
        for (int j = 0; j < boardSize; j++){
            if (i % 2 == 0 && j % 2 == 1) mainBoard[i][j] = '_';
            else if (i % 2 == 1 && j % 2 == 0) mainBoard[i][j] = '_';
            else mainBoard[i][j] = ' ';
        }
    }

    // Seventh Row
    for (int i = 0; i < boardSize; i++){
        mainBoard[6][i] = whitePawn;
    }

    // Eighth Row
    for (int i = 0; i < boardSize; i++){
        if (i % 7 == 0) mainBoard[7][i] = whiteRook;
        else if (i % 5 == 1) mainBoard[7][i] = whiteKnight;
        else if (i % 3 == 2) mainBoard[7][i] = whiteBishop;
        else if (i == 3) mainBoard[7][i] = whiteQueen;
        else if (i == 4) mainBoard[7][i] = whiteKing;
    }
}

// Accessors
char Board::getBoard(int row, int col){
    return mainBoard[row][col];
}

// Mutators
void Board::setBoard(int row, int col, char player){
    mainBoard[row][col] = player;
}

// Utility Functions
void Board::draw(){
    // Double For Loop To Draw the Board
    for (int i = 0; i < boardSize; i++){
        cout << (8 - i) << " ";
        for (int j = 0; j < boardSize; j++){
            cout << mainBoard[i][j];
        }
        cout << endl;
    }

    cout << "  abcdefgh" << endl;
}