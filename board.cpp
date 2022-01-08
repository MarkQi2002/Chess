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

void Board::upgradePawn(vector <int> original, vector <int> next, char upgradeType){
    // Delete Original and Next
    delete mainBoard[original[0]][original[1]];
    delete mainBoard[next[0]][next[1]];
    
    // Create New Piece
    if (upgradeType == whiteQueen) mainBoard[next[0]][next[1]] = new Queen(next[0], next[1], white, whiteQueen);
    else if (upgradeType == whiteBishop) mainBoard[next[0]][next[1]] = new Bishop(next[0], next[1], white, whiteBishop);
    else if (upgradeType == whiteRook) mainBoard[next[0]][next[1]] = new Rook(next[0], next[1], white, whiteRook);
    else if (upgradeType == whiteKnight) mainBoard[next[0]][next[1]] = new Knight(next[0], next[1], white, whiteKnight);
    else if (upgradeType == blackQueen) mainBoard[next[0]][next[1]] = new Queen(next[0], next[1], black, blackQueen);
    else if (upgradeType == blackBishop) mainBoard[next[0]][next[1]] = new Bishop(next[0], next[1], black, blackBishop);
    else if (upgradeType == blackRook) mainBoard[next[0]][next[1]] = new Rook(next[0], next[1], black, blackRook);
    else if (upgradeType == blackKnight) mainBoard[next[0]][next[1]] = new Knight(next[0], next[1], black, blackKnight);
    
    // Set Original Location to Empty
    if (original[0] % 2 == 0 && original[1] % 2 == 1) mainBoard[original[0]][original[1]] = new Empty(original[0], original[1], empty, emptyTwo);
    else if (original[0] % 2 == 1 && original[1] % 2 == 0) mainBoard[original[0]][original[1]] = new Empty(original[0], original[1], empty, emptyTwo);
    else mainBoard[original[0]][original[1]] = new Empty(original[0], original[1], empty, emptyOne);
}

bool Board::checkWin(){
    // Variable Declaration
    bool whiteWin = true;
    bool blackWin = true;

    // Check If King Still Exists
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (mainBoard[i][j] -> getType() == whiteKing) blackWin = false;
            else if (mainBoard[i][j] -> getType() == blackKing) whiteWin = false;
        }
    }

    // Output To User
    if (whiteWin) {cout << "\033[35mWhite Won!!!\033[0m" << endl; return true;}
    else if (blackWin) {cout << "\033[35mBlack Won!!!\033[0m" << endl; return true;}
    else return false;
}

void Board::checkMate(){
    // Variable Declaration
    int whiteKingXLoc;
    int whiteKingYLoc;
    bool whiteKingCheckMate = false;
    int blackKingXLoc;
    int blackKingYLoc;
    bool blackKingCheckMate = false;
    
    // Get Location of Both Kings
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (mainBoard[i][j] -> getType() == whiteKing) {whiteKingXLoc = i; whiteKingYLoc = j;}
            if (mainBoard[i][j] -> getType() == blackKing) {blackKingXLoc = i; blackKingYLoc = j;}
        }
    }

    // For White King
    // Check For Pawns
    if (whiteKingXLoc >= 2 && whiteKingXLoc == 0 && mainBoard[whiteKingXLoc - 1][whiteKingYLoc + 1] -> getType() == blackPawn) whiteKingCheckMate = true;
    else if (whiteKingXLoc >= 2 && whiteKingYLoc > 0 && whiteKingYLoc < 7 && (mainBoard[whiteKingXLoc - 1][whiteKingYLoc - 1] -> getType() == blackPawn || mainBoard[whiteKingXLoc - 1][whiteKingYLoc + 1] -> getType() == blackPawn)) whiteKingCheckMate = true;
    else if (whiteKingXLoc >= 2 && whiteKingXLoc == 7 && mainBoard[whiteKingXLoc - 1][whiteKingYLoc - 1] -> getType() == blackPawn) whiteKingCheckMate = true;

    // Check For King
    if ((blackKingXLoc == whiteKingXLoc - 1 || blackKingXLoc == whiteKingXLoc || blackKingXLoc == whiteKingXLoc + 1) && (blackKingYLoc == whiteKingYLoc - 1 || blackKingYLoc == whiteKingYLoc || blackKingYLoc == whiteKingYLoc + 1)) whiteKingCheckMate = true;

    // Check For Rook and Part of Queen
    bool blockedBlackRook = false;
    bool blockedBlackQueen = false;
    for (int i = whiteKingXLoc + 1; i < abs(boardSize - whiteKingXLoc); i++){
        if (mainBoard[i][whiteKingYLoc] -> getType() != emptyOne && mainBoard[i][whiteKingYLoc] -> getType() != emptyTwo && mainBoard[i][whiteKingYLoc] -> getType() != blackRook && mainBoard[i][whiteKingYLoc] -> getType() != blackQueen) {blockedBlackRook = true; blockedBlackQueen = true;}
        else if (mainBoard[i][whiteKingYLoc] -> getType() == blackRook && !blockedBlackRook) whiteKingCheckMate = true;
        else if (mainBoard[i][whiteKingYLoc] -> getType() == blackQueen && !blockedBlackQueen) whiteKingCheckMate = true;
    }

    blockedBlackRook = false;
    blockedBlackQueen = false;

    for (int i = whiteKingXLoc - 1; i >= 0; i--){
        if (mainBoard[i][whiteKingYLoc] -> getType() != emptyOne && mainBoard[i][whiteKingYLoc] -> getType() != emptyTwo && mainBoard[i][whiteKingYLoc] -> getType() != blackRook && mainBoard[i][whiteKingYLoc] -> getType() != blackQueen) {blockedBlackRook = true; blockedBlackQueen = true;}
        else if (mainBoard[i][whiteKingYLoc] -> getType() == blackRook && !blockedBlackRook) whiteKingCheckMate = true;
        else if (mainBoard[i][whiteKingYLoc] -> getType() == blackQueen && !blockedBlackQueen) whiteKingCheckMate = true;
    }

    blockedBlackRook = false;
    blockedBlackQueen = false;

    for (int i = whiteKingYLoc + 1; i < abs(boardSize - whiteKingXLoc); i++){
        if (mainBoard[whiteKingXLoc][i] -> getType() != emptyOne && mainBoard[whiteKingXLoc][i] -> getType() != emptyTwo && mainBoard[whiteKingXLoc][i] -> getType() != blackRook && mainBoard[whiteKingXLoc][i] -> getType() != blackQueen) {blockedBlackRook = true; blockedBlackQueen = true;}
        else if (mainBoard[whiteKingXLoc][i] -> getType() == blackRook && !blockedBlackRook) whiteKingCheckMate = true;
        else if (mainBoard[whiteKingXLoc][i] -> getType() == blackQueen && !blockedBlackQueen) whiteKingCheckMate = true;
    }

    blockedBlackRook = false;
    blockedBlackQueen = false;

    for (int i = whiteKingYLoc - 1; i >= 0; i--){
        if (mainBoard[whiteKingXLoc][i] -> getType() != emptyOne && mainBoard[whiteKingXLoc][i] -> getType() != emptyTwo && mainBoard[whiteKingXLoc][i] -> getType() != blackRook && mainBoard[whiteKingXLoc][i] -> getType() != blackQueen) {blockedBlackRook = true; blockedBlackQueen = true;}
        else if (mainBoard[whiteKingXLoc][i] -> getType() == blackRook && !blockedBlackRook) whiteKingCheckMate = true;
        else if (mainBoard[whiteKingXLoc][i] -> getType() == blackQueen && !blockedBlackQueen) whiteKingCheckMate = true;
    }

    // Check For Bishop and Other Part of Queen
    bool blockedBlackBishop = false;
    blockedBlackQueen = false;

    for (int i = 1; i < boardSize; i++){
        if (whiteKingXLoc + i < boardSize && whiteKingYLoc + i < boardSize){
            if (mainBoard[whiteKingXLoc + i][whiteKingYLoc + i] -> getType() != emptyOne && mainBoard[whiteKingXLoc + i][whiteKingYLoc + i] -> getType() != emptyTwo && mainBoard[whiteKingXLoc + i][whiteKingYLoc + i] -> getType() != blackBishop && mainBoard[whiteKingXLoc + i][whiteKingYLoc + i] -> getType() != blackQueen){
                blockedBlackBishop = true;
                blockedBlackQueen = true;
            }
            else if (mainBoard[whiteKingXLoc + i][whiteKingYLoc + i] -> getType() == blackBishop && !blockedBlackBishop) whiteKingCheckMate = true;
            else if (mainBoard[whiteKingXLoc + i][whiteKingYLoc + i] -> getType() == blackQueen && !blockedBlackQueen) whiteKingCheckMate = true;
        }
    }

    blockedBlackBishop = false;
    blockedBlackQueen = false;
    for (int i = 1; i < boardSize; i++){
        if (whiteKingXLoc + i < boardSize && whiteKingYLoc - i >= 0){
            if (mainBoard[whiteKingXLoc + i][whiteKingYLoc - i] -> getType() != emptyOne && mainBoard[whiteKingXLoc + i][whiteKingYLoc - i] -> getType() != emptyTwo && mainBoard[whiteKingXLoc + i][whiteKingYLoc - i] -> getType() != blackBishop && mainBoard[whiteKingXLoc + i][whiteKingYLoc - i] -> getType() != blackQueen){
                blockedBlackBishop = true;
                blockedBlackQueen = true;
            }
            else if (mainBoard[whiteKingXLoc + i][whiteKingYLoc - i] -> getType() == blackBishop && !blockedBlackBishop) whiteKingCheckMate = true;
            else if (mainBoard[whiteKingXLoc + i][whiteKingYLoc - i] -> getType() == blackQueen && !blockedBlackQueen) whiteKingCheckMate = true;
        }
    }

    blockedBlackBishop = false;
    blockedBlackQueen = false;
    for (int i = 1; i < boardSize; i++){
        if (whiteKingXLoc - i >= 0 && whiteKingYLoc + i < boardSize){
            if (mainBoard[whiteKingXLoc - i][whiteKingYLoc + i] -> getType() != emptyOne && mainBoard[whiteKingXLoc - i][whiteKingYLoc + i] -> getType() != emptyTwo && mainBoard[whiteKingXLoc - i][whiteKingYLoc + i] -> getType() != blackBishop && mainBoard[whiteKingXLoc - i][whiteKingYLoc + i] -> getType() != blackQueen){
                blockedBlackBishop = true;
                blockedBlackQueen = true;
            }
            else if (mainBoard[whiteKingXLoc - i][whiteKingYLoc + i] -> getType() == blackBishop && !blockedBlackBishop) whiteKingCheckMate = true;
            else if (mainBoard[whiteKingXLoc - i][whiteKingYLoc + i] -> getType() == blackQueen && !blockedBlackQueen) whiteKingCheckMate = true;
        }
    }

    blockedBlackBishop = false;
    blockedBlackQueen = false;
    for (int i = 1; i < boardSize; i++){
        if (whiteKingXLoc - i >= 0 && whiteKingYLoc - i >= 0){
            if (mainBoard[whiteKingXLoc - i][whiteKingYLoc - i] -> getType() != emptyOne && mainBoard[whiteKingXLoc - i][whiteKingYLoc - i] -> getType() != emptyTwo && mainBoard[whiteKingXLoc - i][whiteKingYLoc - i] -> getType() != blackBishop && mainBoard[whiteKingXLoc - i][whiteKingYLoc - i] -> getType() != blackQueen){
                blockedBlackBishop = true;
                blockedBlackQueen = true;
            }
            else if (mainBoard[whiteKingXLoc - i][whiteKingYLoc - i] -> getType() == blackBishop && !blockedBlackBishop) whiteKingCheckMate = true;
            else if (mainBoard[whiteKingXLoc - i][whiteKingYLoc - i] -> getType() == blackQueen && !blockedBlackQueen) whiteKingCheckMate = true;
        }
    }

    // Check For Knight
    if (whiteKingXLoc + 1 < boardSize && whiteKingYLoc + 2 < boardSize){
        if (mainBoard[whiteKingXLoc + 1][whiteKingYLoc + 2] -> getType() == blackKnight) whiteKingCheckMate = true;
    }
    if (whiteKingXLoc + 2 < boardSize && whiteKingYLoc + 1 < boardSize){
        if (mainBoard[whiteKingXLoc + 2][whiteKingYLoc + 1] -> getType() == blackKnight) whiteKingCheckMate = true;
    }
    if (whiteKingXLoc + 1 < boardSize && whiteKingYLoc - 2 >= 0){
        if (mainBoard[whiteKingXLoc + 1][whiteKingYLoc - 2] -> getType() == blackKnight) whiteKingCheckMate = true;
    }
    if (whiteKingXLoc + 2 < boardSize && whiteKingYLoc - 1 >= 0){
        if (mainBoard[whiteKingXLoc + 2][whiteKingYLoc - 1] -> getType() == blackKnight) whiteKingCheckMate = true;
    }
    if (whiteKingXLoc - 1 >= 0 && whiteKingYLoc + 2 < boardSize){
        if (mainBoard[whiteKingXLoc - 1][whiteKingYLoc + 2] -> getType() == blackKnight) whiteKingCheckMate = true;
    }
    if (whiteKingXLoc - 2 >= 0 && whiteKingYLoc + 1 < boardSize){
        if (mainBoard[whiteKingXLoc - 2][whiteKingYLoc + 1] -> getType() == blackKnight) whiteKingCheckMate = true;
    }
    if (whiteKingXLoc - 1 >= 0 && whiteKingYLoc - 2 >= 0){
        if (mainBoard[whiteKingXLoc - 1][whiteKingYLoc - 2] -> getType() == blackKnight) whiteKingCheckMate = true;
    }
    if (whiteKingXLoc - 2 >= 0 && whiteKingYLoc - 1 >= 0){
        if (mainBoard[whiteKingXLoc - 2][whiteKingYLoc - 1] -> getType() == blackKnight) whiteKingCheckMate = true;
    }


    // For Black King
    // Check For Pawns
    if (blackKingXLoc <= 6 && blackKingXLoc == 0 && mainBoard[blackKingXLoc + 1][blackKingYLoc + 1] -> getType() == whitePawn) blackKingCheckMate = true;
    else if (blackKingXLoc <= 6 && blackKingYLoc > 0 && blackKingYLoc < 7 && (mainBoard[blackKingXLoc + 1][blackKingYLoc - 1] -> getType() == whitePawn || mainBoard[blackKingXLoc + 1][blackKingYLoc + 1] -> getType() == whitePawn)) blackKingCheckMate = true;
    else if (blackKingXLoc <= 6 && blackKingXLoc == 7 && mainBoard[blackKingXLoc + 1][blackKingYLoc - 1] -> getType() == whitePawn) blackKingCheckMate = true;
    

    // Check For King
    if ((blackKingXLoc == whiteKingXLoc - 1 || blackKingXLoc == whiteKingXLoc || blackKingXLoc == whiteKingXLoc + 1) && (blackKingYLoc == whiteKingYLoc - 1 || blackKingYLoc == whiteKingYLoc || blackKingYLoc == whiteKingYLoc + 1)) blackKingCheckMate = true;

    // Check For Rook and Part of Queen
    bool blockedWhiteRook = false;
    bool blockedWhiteQueen = false;
    for (int i = blackKingXLoc + 1; i < abs(boardSize - blackKingXLoc); i++){
        if (mainBoard[i][blackKingYLoc] -> getType() != emptyOne && mainBoard[i][blackKingYLoc] -> getType() != emptyTwo && mainBoard[i][blackKingYLoc] -> getType() != whiteRook && mainBoard[i][blackKingYLoc] -> getType() != whiteQueen) {blockedWhiteRook = true; blockedWhiteQueen = true;}
        else if (mainBoard[i][blackKingYLoc] -> getType() == whiteRook && !blockedWhiteRook) blackKingCheckMate = true;
        else if (mainBoard[i][blackKingYLoc] -> getType() == whiteQueen && !blockedWhiteQueen) blackKingCheckMate = true;
    }

    blockedWhiteRook = false;
    blockedWhiteQueen = false;

    for (int i = blackKingXLoc - 1; i >= 0; i--){
        if (mainBoard[i][blackKingYLoc] -> getType() != emptyOne && mainBoard[i][blackKingYLoc] -> getType() != emptyTwo && mainBoard[i][blackKingYLoc] -> getType() != whiteRook && mainBoard[i][blackKingYLoc] -> getType() != whiteQueen) {blockedWhiteRook = true; blockedWhiteQueen = true;}
        else if (mainBoard[i][blackKingYLoc] -> getType() == whiteRook && !blockedWhiteRook) blackKingCheckMate = true;
        else if (mainBoard[i][blackKingYLoc] -> getType() == whiteQueen && !blockedWhiteQueen) blackKingCheckMate = true;
    }

    blockedWhiteRook = false;
    blockedWhiteQueen = false;

    for (int i = blackKingYLoc + 1; i < abs(boardSize - blackKingXLoc); i++){
        if (mainBoard[blackKingXLoc][i] -> getType() != emptyOne && mainBoard[blackKingXLoc][i] -> getType() != emptyTwo && mainBoard[blackKingXLoc][i] -> getType() != whiteRook && mainBoard[blackKingXLoc][i] -> getType() != whiteQueen) {blockedWhiteRook = true; blockedWhiteQueen = true;}
        else if (mainBoard[blackKingXLoc][i] -> getType() == whiteRook && !blockedWhiteRook) blackKingCheckMate = true;
        else if (mainBoard[blackKingXLoc][i] -> getType() == whiteQueen && !blockedWhiteQueen) blackKingCheckMate = true;
    }

    blockedWhiteRook = false;
    blockedWhiteQueen = false;

    for (int i = blackKingYLoc - 1; i >= 0; i--){
        if (mainBoard[blackKingXLoc][i] -> getType() != emptyOne && mainBoard[blackKingXLoc][i] -> getType() != emptyTwo && mainBoard[blackKingXLoc][i] -> getType() != whiteRook && mainBoard[blackKingXLoc][i] -> getType() != whiteQueen) {blockedWhiteRook = true; blockedWhiteQueen = true;}
        else if (mainBoard[blackKingXLoc][i] -> getType() == whiteRook && !blockedWhiteRook) blackKingCheckMate = true;
        else if (mainBoard[blackKingXLoc][i] -> getType() == whiteQueen && !blockedWhiteQueen) blackKingCheckMate = true;
    }

    // Check For Bishop and Other Part of Queen
    bool blockedWhiteBishop = false;
    blockedWhiteQueen = false;

    for (int i = 1; i < boardSize; i++){
        if (blackKingXLoc + i < boardSize && blackKingYLoc + i < boardSize){
            if (mainBoard[blackKingXLoc + i][blackKingYLoc + i] -> getType() != emptyOne && mainBoard[blackKingXLoc + i][blackKingYLoc + i] -> getType() != emptyTwo && mainBoard[blackKingXLoc + i][blackKingYLoc + i] -> getType() != whiteBishop && mainBoard[blackKingXLoc + i][blackKingYLoc + i] -> getType() != whiteQueen){
                blockedWhiteBishop = true;
                blockedWhiteQueen = true;
            }
            else if (mainBoard[blackKingXLoc + i][blackKingYLoc + i] -> getType() == whiteBishop && !blockedWhiteBishop) blackKingCheckMate = true;
            else if (mainBoard[blackKingXLoc + i][blackKingYLoc + i] -> getType() == whiteQueen && !blockedWhiteQueen) blackKingCheckMate = true;
        }
    }

    blockedWhiteBishop = false;
    blockedWhiteQueen = false;
    for (int i = 1; i < boardSize; i++){
        if (blackKingXLoc + i < boardSize && blackKingYLoc - i >= 0){
            if (mainBoard[blackKingXLoc + i][blackKingYLoc - i] -> getType() != emptyOne && mainBoard[blackKingXLoc + i][blackKingYLoc - i] -> getType() != emptyTwo && mainBoard[blackKingXLoc + i][blackKingYLoc - i] -> getType() != whiteBishop && mainBoard[blackKingXLoc + i][blackKingYLoc - i] -> getType() != whiteQueen){
                blockedWhiteBishop = true;
                blockedWhiteQueen = true;
            }
            else if (mainBoard[blackKingXLoc + i][blackKingYLoc - i] -> getType() == whiteBishop && !blockedWhiteBishop) blackKingCheckMate = true;
            else if (mainBoard[blackKingXLoc + i][blackKingYLoc - i] -> getType() == whiteQueen && !blockedWhiteQueen) blackKingCheckMate = true;
        }
    }

    blockedWhiteBishop = false;
    blockedWhiteQueen = false;
    for (int i = 1; i < boardSize; i++){
        if (blackKingXLoc - i >= 0 && blackKingYLoc + i < boardSize){
            if (mainBoard[blackKingXLoc - i][blackKingYLoc + i] -> getType() != emptyOne && mainBoard[blackKingXLoc - i][blackKingYLoc + i] -> getType() != emptyTwo && mainBoard[blackKingXLoc - i][blackKingYLoc + i] -> getType() != whiteBishop && mainBoard[blackKingXLoc - i][blackKingYLoc + i] -> getType() != whiteQueen){
                blockedWhiteBishop = true;
                blockedWhiteQueen = true;
            }
            else if (mainBoard[blackKingXLoc - i][blackKingYLoc + i] -> getType() == whiteBishop && !blockedWhiteBishop) blackKingCheckMate = true;
            else if (mainBoard[blackKingXLoc - i][blackKingYLoc + i] -> getType() == whiteQueen && !blockedWhiteQueen) blackKingCheckMate = true;
        }
    }

    blockedWhiteBishop = false;
    blockedWhiteQueen = false;
    for (int i = 1; i < boardSize; i++){
        if (blackKingXLoc - i >= 0 && blackKingYLoc - i >= 0){
            if (mainBoard[blackKingXLoc - i][blackKingYLoc - i] -> getType() != emptyOne && mainBoard[blackKingXLoc - i][blackKingYLoc - i] -> getType() != emptyTwo && mainBoard[blackKingXLoc - i][blackKingYLoc - i] -> getType() != whiteBishop && mainBoard[blackKingXLoc - i][blackKingYLoc - i] -> getType() != whiteQueen){
                blockedWhiteBishop = true;
                blockedWhiteQueen = true;
            }
            else if (mainBoard[blackKingXLoc - i][blackKingYLoc - i] -> getType() == whiteBishop && !blockedWhiteBishop) blackKingCheckMate = true;
            else if (mainBoard[blackKingXLoc - i][blackKingYLoc - i] -> getType() == whiteQueen && !blockedWhiteQueen) blackKingCheckMate = true;
        }
    }

    // Check For Knight
    if (blackKingXLoc + 1 < boardSize && blackKingYLoc + 2 < boardSize){
        if (mainBoard[blackKingXLoc + 1][blackKingYLoc + 2] -> getType() == whiteKnight) blackKingCheckMate = true;
    }
    if (blackKingXLoc + 2 < boardSize && blackKingYLoc + 1 < boardSize){
        if (mainBoard[blackKingXLoc + 2][blackKingYLoc + 1] -> getType() == whiteKnight) blackKingCheckMate = true;
    }
    if (blackKingXLoc + 1 < boardSize && blackKingYLoc - 2 >= 0){
        if (mainBoard[blackKingXLoc + 1][blackKingYLoc - 2] -> getType() == whiteKnight) blackKingCheckMate = true;
    }
    if (blackKingXLoc + 2 < boardSize && blackKingYLoc - 1 >= 0){
        if (mainBoard[blackKingXLoc + 2][blackKingYLoc - 1] -> getType() == whiteKnight) blackKingCheckMate = true;
    }
    if (blackKingXLoc - 1 >= 0 && blackKingYLoc + 2 < boardSize){
        if (mainBoard[blackKingXLoc - 1][blackKingYLoc + 2] -> getType() == whiteKnight) blackKingCheckMate = true;
    }
    if (blackKingXLoc - 2 >= 0 && blackKingYLoc + 1 < boardSize){
        if (mainBoard[blackKingXLoc - 2][blackKingYLoc + 1] -> getType() == whiteKnight) blackKingCheckMate = true;
    }
    if (blackKingXLoc - 1 >= 0 && blackKingYLoc - 2 >= 0){
        if (mainBoard[blackKingXLoc - 1][blackKingYLoc - 2] -> getType() == whiteKnight) blackKingCheckMate = true;
    }
    if (blackKingXLoc - 2 >= 0 && blackKingYLoc - 1 >= 0){
        if (mainBoard[blackKingXLoc - 2][blackKingYLoc - 1] -> getType() == whiteKnight) blackKingCheckMate = true;
    }

    // Output For White King Being CheckMate
    if (whiteKingCheckMate) cout << "\033[33mWhite King Has Been CheckMate By Black\033[0m" << endl;

    // Output For Black King Being CheckMate
    if (blackKingCheckMate) cout << "\033[33mBlack King Has Been CheckMate By White\033[0m" << endl;
}

// For SetUp Mode
void Board::clearBoard(){
    // Delete The Original Board
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            delete mainBoard[i][j];
        }
    }

    // Make The Entire Board Filled With Empty
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (i % 2 == 0 && j % 2 == 1) mainBoard[i][j] = new Empty(i, j, empty, emptyTwo);
            else if (i % 2 == 1 && j % 2 == 0) mainBoard[i][j] = new Empty(i, j, empty, emptyTwo);
            else mainBoard[i][j] = new Empty(i, j, empty, emptyOne);
        }
    }
}

void Board::addPiece(int row, int col, char type){
    // Variable Declaration
    bool whiteKingExist = false;
    bool blackKingExist = false;

    // Check For King
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (mainBoard[i][j] -> getType() == whiteKing) whiteKingExist = true;
            else if (mainBoard[i][j] -> getType() == blackKing) blackKingExist = true;
        }
    }

    // Delete Original Piece
    delete mainBoard[row][col];
    
    // Create New Piece
    if (type == whiteKing && !whiteKingExist) mainBoard[row][col] = new King(row, col, white, whiteKing);
    else if (type == whiteKing && whiteKingExist) cout << "\033[31mWhite King Already Exists\033[0m" << endl;
    else if (type == whiteQueen) mainBoard[row][col] = new Queen(row, col, white, whiteQueen);
    else if (type == whiteBishop) mainBoard[row][col] = new Bishop(row, col, white, whiteBishop);
    else if (type == whiteRook) mainBoard[row][col] = new Rook(row, col, white, whiteRook);
    else if (type == whiteKnight) mainBoard[row][col] = new Knight(row, col, white, whiteKnight);
    else if (type == whitePawn) mainBoard[row][col] = new Pawn(row, col, white, whitePawn);
   
    else if (type == blackKing && !blackKingExist) mainBoard[row][col] = new King(row, col, black, blackKing);
    else if (type == blackKing && blackKingExist) cout << "\033[31mBlack King Already Exists\033[0m" << endl;
    else if (type == blackQueen) mainBoard[row][col] = new Queen(row, col, black, blackQueen);
    else if (type == blackBishop) mainBoard[row][col] = new Bishop(row, col, black, blackBishop);
    else if (type == blackRook) mainBoard[row][col] = new Rook(row, col, black, blackRook);
    else if (type == blackKnight) mainBoard[row][col] = new Knight(row, col, black, blackKnight);
    else if (type == blackPawn) mainBoard[row][col] = new Pawn(row, col, black, blackPawn);
}

void Board::removePiece(int row, int col){
    // Delete the Piece
    delete mainBoard[row][col];

    // Set Position to Empty
    if (row % 2 == 0 && col % 2 == 1) mainBoard[row][col] = new Empty(row, col, empty, emptyTwo);
    else if (row % 2 == 1 && col % 2 == 0) mainBoard[row][col] = new Empty(row, col, empty, emptyTwo);
    else mainBoard[row][col] = new Empty(row, col, empty, emptyOne);
}

void Board::checkKing(bool & setUpMode){
    // Variable Declaration
    bool whiteKingExist = false;
    bool blackKingExist = false;

    // Check For King
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (mainBoard[i][j] -> getType() == whiteKing) whiteKingExist = true;
            else if (mainBoard[i][j] -> getType() == blackKing) blackKingExist = true;
        }
    }

    if (!whiteKingExist || !blackKingExist) {setUpMode = true; cout << "\033[31mAt Least One King is Missing, Set Up Mode Continues\033[0m" << endl;}
    else {setUpMode = false; cout << "\033[35mSet Up Complete!\033[0m" << endl;}
}
