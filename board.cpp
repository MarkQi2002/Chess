// Include Modules
#include "globals.h"
#include "board.h"
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

// Constructors
Board::Board(){
    // According to Handout
    // First Row
    mainBoard[0][0] = new Rook(0, 0, black, blackRook);
    mainBoard[0][1] = new Knight(0, 1, black, blackKnight);
    mainBoard[0][2] = new Bishop(0, 2, black, blackBishop);
    mainBoard[0][3] = new Queen(0, 3, black, blackQueen);
    mainBoard[0][4] = new King(0, 4, black, blackKing);
    mainBoard[0][5] = new Bishop(0, 5, black, blackBishop);
    mainBoard[0][6] = new Knight(0, 6, black, blackKnight);
    mainBoard[0][7] = new Rook(0, 7, black, blackRook);

    // Second Row
    for (int i = 0; i < boardSize; i++){
        mainBoard[1][i] = new Pawn(1, i, black, blackPawn);
    }

    // Third, Fourth, Fifth, and Sixth Row
    for (int i = 2; i < 6; i++){
        for (int j = 0; j < boardSize; j++){
            mainBoard[i][j] = new Piece(i, j, empty);
        }
    }

    // Seventh Row
    for (int i = 0; i < boardSize; i++){
        mainBoard[6][i] = new Pawn(6, i, white, whitePawn);
    }

    // Eighth Row
    mainBoard[7][0] = new Rook(7, 0, white, whiteRook);
    mainBoard[7][1] = new Knight(7, 1, white, whiteKnight);
    mainBoard[7][2] = new Bishop(7, 2, white, whiteBishop);
    mainBoard[7][3] = new Queen(7, 3, white, whiteQueen);
    mainBoard[7][4] = new King(7, 4, white, whiteKing);
    mainBoard[7][5] = new Bishop(7, 5, white, whiteBishop);
    mainBoard[7][6] = new Knight(7, 6, white, whiteKnight);
    mainBoard[7][7] = new Rook(7, 7, white, whiteRook);
}

// Accessors
Piece* Board::getBoard(int row, int col){
    return mainBoard[row][col];
}

// Mutators
void Board::setBoard(int row, int col, Piece* newPiece){
    mainBoard[row][col] = newPiece;
}

// Utility Functions
void Board::draw(){
    // Double For Loop To Draw the Board
    for (int i = 0; i < boardSize; i++){
        cout << (8 - i) << " ";
        for (int j = 0; j < boardSize; j++){
            mainBoard[i][j] -> print();
        }
        cout << endl;
    }

    cout << "  abcdefgh" << endl;
}