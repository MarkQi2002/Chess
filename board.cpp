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
#include "empty.h"

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
            if (i % 2 == 0 && j % 2 == 1) mainBoard[i][j] = new Empty(i, j, empty, emptyTwo);
            else if (i % 2 == 1 && j % 2 == 0) mainBoard[i][j] = new Empty(i, j, empty, emptyTwo);
            else mainBoard[i][j] = new Empty(i, j, empty, emptyOne);
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

// Destructor
Board::~Board(){
    for (int i = 0; i < 8; i++){
        for (int j = 0 ; j < 8; j++){   
            //mainBoard[i][j] is of type Piece*, so this line of code will call the destructor of class Piece by defualt
            //unless we make all destructors virtual(dynamic binding) 
            delete mainBoard[i][j];
        }
    }
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
            mainBoard[i][j] -> printType();
        }
        cout << endl;
    }

    cout << "  abcdefgh" << endl;
}

// Basic Swap Location
void Board::exchangePosition(vector <int> original, vector <int> next){
    // Change Piece Location
    mainBoard[original[0]][original[1]] -> move(next);
    mainBoard[next[0]][next[1]] -> move(original);
    

    // Swap Them
    Piece* temp;
    temp = mainBoard[original[0]][original[1]];
    mainBoard[original[0]][original[1]] = mainBoard[next[0]][next[1]];
    mainBoard[next[0]][next[1]] = temp;

    // For Empty Type
    if (mainBoard[original[0]][original[1]] -> getColor() == empty) mainBoard[original[0]][original[1]] -> checkType();
    if (mainBoard[next[0]][next[1]] -> getColor() == empty) mainBoard[original[0]][original[1]] -> checkType();
}

// Conquer Other Pieces
void Board::conquerMove(vector <int> original, vector <int> next){
    // Output Result of Conquering
    string conqueredType;
    string conqueredColor = mainBoard[next[0]][next[1]] -> getColor();

    if (mainBoard[next[0]][next[1]] -> getType() == whiteKing || mainBoard[next[0]][next[1]] -> getType() == blackKing) conqueredType = "King";
    else if (mainBoard[next[0]][next[1]] -> getType() == whiteQueen || mainBoard[next[0]][next[1]] -> getType() == blackQueen) conqueredType = "Queen";
    else if (mainBoard[next[0]][next[1]] -> getType() == whiteBishop || mainBoard[next[0]][next[1]] -> getType() == blackBishop) conqueredType = "Bishop";
    else if (mainBoard[next[0]][next[1]] -> getType() == whiteRook || mainBoard[next[0]][next[1]] -> getType() == blackRook) conqueredType = "Rook";
    else if (mainBoard[next[0]][next[1]] -> getType() == whiteKnight || mainBoard[next[0]][next[1]] -> getType() == blackKnight) conqueredType = "Knight";
    else if (mainBoard[next[0]][next[1]] -> getType() == whitePawn || mainBoard[next[0]][next[1]] -> getType() == blackPawn) conqueredType = "Pawn";

    cout << "\033[32mYou Have Conquered " << conqueredColor << "'s " << conqueredType << "\033[0m" << endl;
    
    // Change Piece Location
    mainBoard[original[0]][original[1]] -> move(next);
    
    // Delete The Conquered Piece
    delete mainBoard[next[0]][next[1]];
    mainBoard[next[0]][next[1]] = mainBoard[original[0]][original[1]];
    
    // Set Original Location to Empty
    if (original[0] % 2 == 0 && original[1] % 2 == 1) mainBoard[original[0]][original[1]] = new Empty(original[0], original[1], empty, emptyTwo);
    else if (original[0] % 2 == 1 && original[1] % 2 == 0) mainBoard[original[0]][original[1]] = new Empty(original[0], original[1], empty, emptyTwo);
    else mainBoard[original[0]][original[1]] = new Empty(original[0], original[1], empty, emptyOne);
}