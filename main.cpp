// Include Modules
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Header Files
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

// Can be deleted
#define white "White"
#define black "Black"

// Input Related Declaration
string normalCommandList[4] = {"game", "resign", "move", "setup"};

// The Main Function
int main(){
    // FOR TESTING USE ONLY
    ifstream input;
    int count = 0;
    string input_input[2048];
    input.open("testOne.txt");

    for (int i = 0; i < 2048; i++){
        getline(input, input_input[i]);
    }

    // Variable Declaration
    Board mainBoard;
    string currentPlayer = white;
    bool gameOver = false;
    bool startGame = true;  // This Indicated The Beginning of the Game (Default: True)
    bool setUpMode = false; // This Indicated Set Up Mode (Default: Flase)

    // For Assigning Players
    int firstPlayer = -1;
    int secondPlayer = -1;

    // Input Interpretation
    string line;
    string command;

    // Prompt User For Input (Comment This For Testing)
    /*
    cout << "\033[33mRead PDF for input instructions\033[0m" << endl;
    cout << "\033[36mCurrent Player: " << currentPlayer << "\033[0m" << endl;
    cout << "> ";
    getline(cin, line);
    */

    // Main Game Part
    while (!cin.eof() && !gameOver && input_input[count] != "eof"){
        // TESTING USE ONLY
        stringstream lineStream(input_input[count]);
        cout << "\033[36m> " << input_input[count] << "\033[0m" << endl;
        count++;


        // Variable Declaration
        bool moveValid = true;

        // New sstream for each input
        // stringstream lineStream(line);

        // Read form string stream into comman
        command = "";
        lineStream >> command;

        // Check if Command is Valid
        if (command != normalCommandList[0] && command != normalCommandList[1] && command != normalCommandList[2] && command != normalCommandList[3]){
            cout << "\033[31mInvalid Command\033[0m" << endl;
        }

        // Game Started and Command is "game"
        if (command == "game" && !startGame && !setUpMode) cout << "\033[31mGame Already Started\033[0m" << endl;
        
        // Game Not Started and Command is "game"
        if (command == "game" && startGame && !setUpMode){
            // Set Players 1 (FirstHand)
            while (firstPlayer == -1){
                string playerSelectOne;
                cout << "\033[35mPlease Choose Player One (White), Human (0), AI1 (1), AI2 (2), AI3 (3), AI4 (4): \033[0m";
                // TESTING USE ONLY
                playerSelectOne = input_input[count];
                cout << endl;

                //getline(cin, playerSelectOne);
                if (playerSelectOne != "0" && playerSelectOne != "1" && playerSelectOne != "2" && playerSelectOne != "3" && playerSelectOne != "4") cout << "\033[31mInvalid Input\033[0m" << endl;
                else firstPlayer = stoi(playerSelectOne);
            }

            // Set Player 2 (SecondHand)
            while (secondPlayer == -1){
                string playerSelectTwo;
                cout << "\033[35mPlease Choose Player Two (Black), Human (0), AI1 (1), AI2 (2), AI3 (3), AI4 (4): \033[0m";
                // TESTING USE ONLY
                playerSelectTwo = input_input[count + 1];
                cout << endl;

                //getline(cin, playerSelectTwo);
                if (playerSelectTwo != "0" && playerSelectTwo != "1" && playerSelectTwo != "2" && playerSelectTwo != "3" && playerSelectTwo != "4") cout << "\033[31mInvalid Input\033[0m" << endl;
                else secondPlayer = stoi(playerSelectTwo);
            }

            startGame = false;
        }
        
        // Game Not Started and Command is not "game"
        if (command != "game" && startGame && !setUpMode) cout << "\033[31mGame Not Started\033[0m" << endl;

        // For Command "resign" (Easy)
        if (command == "resign" && !startGame && !setUpMode){
            if (currentPlayer == white){
                cout << "\033[35mPlayer One (";
                if (firstPlayer == Player) cout << "Human";
                else if (firstPlayer == AI1) cout << "AI1";
                else if (firstPlayer == AI2) cout << "AI2";
                else if (firstPlayer == AI3) cout << "AI3";
                else if (firstPlayer == AI4) cout << "AI4";
                cout << ") Wins!\033[0m" << endl;
            }

            else if (currentPlayer == black){
                cout << "\033[35mPlayer Two (";
                if (secondPlayer == Player) cout << "Human";
                else if (secondPlayer == AI1) cout << "AI1";
                else if (secondPlayer == AI2) cout << "AI2";
                else if (secondPlayer == AI3) cout << "AI3";
                else if (secondPlayer == AI4) cout << "AI4";
                cout << ") Wins!\033[0m" << endl;
            }
        }

        // For Command "move" (Difficult)
        if (command == "move" && !startGame && !setUpMode){
            // Controlling Input
            string originalPosition;
            string nextPosition;
            string pawnUpgrade;
            string temp;
            bool validInput = true;
            bool extraInput = false;
            bool pawnInput = false;

            // Variable Declaration
            int originalxLoc;   // Row Number
            int originalyLoc;   // Column Number
            int nextxLoc;
            int nextyLoc;
            vector <int> original;
            vector <int> next;
            
            // Getting Input From stringstream
            lineStream >> originalPosition >> nextPosition >> pawnUpgrade;

            // Verify Input
            if (temp != "") extraInput = true;
            if (nextPosition[1] != '8' && nextPosition[1] != '1' && pawnUpgrade != "") extraInput = true;
            if ((nextPosition[1] == '8' || nextPosition[1] == '1') && pawnUpgrade.length() == 1) pawnInput = true;
            if (originalPosition.size() != 2) validInput = false;
            if (nextPosition.size() != 2) validInput = false;

            // Invalid Input
            if (!validInput) {moveValid = false; cout << "\033[31mInvalid Position\033[0m" << endl;}
            if (extraInput) {validInput = false; moveValid = false; cout << "\033[31mToo Many Arguments\033[0m" << endl;}

            // For Extracting Valid Input
            if (validInput){
                // Original Position
                if (originalPosition[0] == 'a') originalyLoc = 0;
                else if (originalPosition[0] == 'b') originalyLoc = 1;
                else if (originalPosition[0] == 'c') originalyLoc = 2;
                else if (originalPosition[0] == 'd') originalyLoc = 3;
                else if (originalPosition[0] == 'e') originalyLoc = 4;
                else if (originalPosition[0] == 'f') originalyLoc = 5;
                else if (originalPosition[0] == 'g') originalyLoc = 6;
                else if (originalPosition[0] == 'h') originalyLoc = 7;

                originalxLoc = 8 - (originalPosition[1] - '0'); // Row Number

                // Next Position
                if (nextPosition[0] == 'a') nextyLoc = 0;
                else if (nextPosition[0] == 'b') nextyLoc = 1;
                else if (nextPosition[0] == 'c') nextyLoc = 2;
                else if (nextPosition[0] == 'd') nextyLoc = 3;
                else if (nextPosition[0] == 'e') nextyLoc = 4;
                else if (nextPosition[0] == 'f') nextyLoc = 5;
                else if (nextPosition[0] == 'g') nextyLoc = 6;
                else if (nextPosition[0] == 'h') nextyLoc = 7;

                nextxLoc = 8 - (nextPosition[1] - '0'); // Row Number

                // Pawn Upgrade
                if (pawnInput){
                    if (pawnUpgrade[0] != whiteQueen && pawnUpgrade[0] != whiteBishop && pawnUpgrade[0] != whiteRook && pawnUpgrade[0] != whiteKnight && pawnUpgrade[0] != blackQueen && pawnUpgrade[0] != blackBishop && pawnUpgrade[0] != blackRook && pawnUpgrade[0] != blackKnight) {validInput = false; moveValid = false; cout << "\033[31mInvalid Input For Upgrade\033[0m" << endl;}
                }

                // Testing Use
                /*
                cout << "Original Row Number:" << originalxLoc << endl;
                cout << "Original Column Number: " << originalyLoc << endl;
                cout << "Next Row Number: " << nextxLoc << endl;
                cout << "Next Column Number: " << nextyLoc << endl;
                */
            }
            // Check On Board or Not
            if (originalxLoc < 0 || originalxLoc > 7 || originalyLoc < 0 || originalyLoc > 7 || nextxLoc < 0 || nextxLoc > 7 || nextyLoc < 0 || nextyLoc > 7) {moveValid = false; cout << "\033[31mLocation Outside Board\033[0m" << endl;}

            // Check If Original Location if Empty or Not
            if (validInput && mainBoard.getBoard(originalxLoc, originalyLoc) -> getColor() == empty) {moveValid = false; cout << "\033[31mOriginal Location Empty\033[0m" << endl;}

            // Setting Variables
            original.push_back(originalxLoc);
            original.push_back(originalyLoc);
            next.push_back(nextxLoc);
            next.push_back(nextyLoc);

            // ExchangePosition
            // mainBoard.exchangePosition(original, next);

            // For White
            if (currentPlayer == white && validInput){
                // For Moving Pawns
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == whitePawn){
                    if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black && nextxLoc == originalxLoc - 1 && (nextyLoc == originalyLoc + 1 || nextyLoc == originalyLoc - 1)) mainBoard.conquerMove(original, next);
                    else if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getFirstMove() == true && (nextxLoc == 5 || nextxLoc == 4) && nextyLoc == originalyLoc) mainBoard.exchangePosition(original, next);
                    else if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getFirstMove() == false && nextxLoc == originalxLoc - 1 && nextyLoc == originalyLoc) mainBoard.exchangePosition(original, next);
                    else {moveValid = false; cout << "\033[31mInvalid Move\033[0m" << endl;}
                }

                // For Moving King
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == whiteKing){
                    if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black && (nextxLoc == originalxLoc - 1 || nextxLoc == originalxLoc || nextxLoc == originalxLoc + 1) && (nextyLoc == originalyLoc - 1 || nextyLoc == originalyLoc || nextyLoc == originalyLoc + 1)) mainBoard.conquerMove(original, next);
                    else if ((nextxLoc == originalxLoc - 1 || nextxLoc == originalxLoc || nextxLoc == originalxLoc + 1) && (nextyLoc == originalyLoc - 1 || nextyLoc == originalyLoc || nextyLoc == originalyLoc + 1)) mainBoard.exchangePosition(original, next);
                    else {moveValid = false; cout << "\033[31mInvalid Move\033[0m" << endl;}
                }

                // For Moving Rook
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == whiteRook){
                    bool blocked = false;
                    if (originalxLoc != nextxLoc && originalyLoc != nextyLoc) {moveValid = false; cout << "\033[31mNot Horizontal Or Vertical\033[0m" << endl;}
                    else if (originalxLoc == nextxLoc){
                        for (int i = 1; i < abs(nextyLoc - originalyLoc); i++){
                            if (nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc, originalyLoc - i) -> getColor() != empty) blocked = true;
                        }
                    }

                    else if (originalyLoc == nextyLoc){
                        for (int i = 1; i < abs(nextxLoc - originalxLoc); i++){
                            if (nextxLoc > originalxLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc) -> getColor() != empty) blocked = true;
                        }
                    }
                    
                    if (!moveValid) {}
                    else if (blocked == true) {moveValid = false; cout << "\033[31mThe Path is Blocked\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black) mainBoard.conquerMove(original, next);
                    else mainBoard.exchangePosition(original, next);
                }

                // For Moving Bishop
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == whiteBishop){
                    bool blocked = false;
                    if (abs(nextxLoc - originalxLoc) != abs(nextyLoc - originalyLoc) || abs(nextxLoc - originalxLoc) == 0) {moveValid = false; cout << "\033[31mNot Diagonal Move or Same Position\033[0m" << endl;}
                    else {
                        for (int i = 1; i < abs(nextxLoc - originalxLoc); i++){
                            if (nextxLoc > originalxLoc && nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc > originalxLoc && nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc - i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc - i) -> getColor() != empty) blocked = true;
                        }
                    }

                    if (!moveValid) {}
                    else if (blocked == true) {moveValid = false; cout << "\033[31mThe Path is Blocked\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black) mainBoard.conquerMove(original, next);
                    else mainBoard.exchangePosition(original, next);
                }

                // For Moving Queen
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == whiteQueen){
                    bool blocked = false;
                    if ((originalxLoc != nextxLoc && originalyLoc != nextyLoc) || (abs(nextxLoc - originalxLoc) != abs(nextyLoc - originalyLoc) && abs(nextxLoc - originalxLoc) == 0)) {moveValid = false; cout << "\033[31mNot Diagonal, Horizontal, or Vertical Move\033[0m" << endl;}
                    else if (originalxLoc == nextxLoc){
                        for (int i = 1; i < abs(nextyLoc - originalyLoc); i++){
                            if (nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc, originalyLoc - i) -> getColor() != empty) blocked = true;
                        }
                    }

                    else if (originalyLoc == nextyLoc){
                        for (int i = 1; i < abs(nextxLoc - originalxLoc); i++){
                            if (nextxLoc > originalxLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc) -> getColor() != empty) blocked = true;
                        }
                    }
                    else {
                        for (int i = 1; i < abs(nextxLoc - originalxLoc); i++){
                            if (nextxLoc > originalxLoc && nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc > originalxLoc && nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc - i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc - i) -> getColor() != empty) blocked = true;
                        }
                    }

                    if (!moveValid) {}
                    else if (blocked == true) {moveValid = false; cout << "\033[31mThe Path is Blocked\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black) mainBoard.conquerMove(original, next);
                    else mainBoard.exchangePosition(original, next);
                }

                // For Moving Knight
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == whiteKnight){
                    bool conquer = false;
                    if ((abs(nextxLoc - originalxLoc) != 1 && abs(nextyLoc - originalyLoc) != 2) && (abs(nextxLoc - originalxLoc) != 2 || abs(nextyLoc - originalyLoc) != 1)) {moveValid = false; cout << "\033[31mInvalid Move For Knight\033[0m" << endl;}
                    else conquer = true;
                    
                    if (!conquer) {}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black) mainBoard.conquerMove(original, next);
                    else mainBoard.exchangePosition(original, next);
                }
            }
            // For Black
            else if (currentPlayer == black && validInput){
                // For Moving Pawns
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == blackPawn){
                    if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty&& mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white && nextxLoc == originalxLoc + 1 && (nextyLoc == originalyLoc + 1 || nextyLoc == originalyLoc - 1)) mainBoard.conquerMove(original, next);
                    else if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getFirstMove() == true && (nextxLoc == 2 || nextxLoc == 3) && nextyLoc == originalyLoc) mainBoard.exchangePosition(original, next);
                    else if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getFirstMove() == false && nextxLoc == originalxLoc + 1 && nextyLoc == originalyLoc) mainBoard.exchangePosition(original, next);
                    else {moveValid = false; cout << "\033[31mInvalid Move\033[0m" << endl;}
                }

                // For Moving King
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == blackKing){
                    if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white && (nextxLoc == originalxLoc - 1 || nextxLoc == originalxLoc || nextxLoc == originalxLoc + 1) && (nextyLoc == originalyLoc - 1 || nextyLoc == originalyLoc || nextyLoc == originalyLoc + 1)) mainBoard.conquerMove(original, next);
                    else if ((nextxLoc == originalxLoc - 1 || nextxLoc == originalxLoc || nextxLoc == originalxLoc + 1) && (nextyLoc == originalyLoc - 1 || nextyLoc == originalyLoc || nextyLoc == originalyLoc + 1)) mainBoard.exchangePosition(original, next);
                    else {moveValid = false; cout << "\033[31mInvalid Move\033[0m" << endl;}
                }

                // For Moving Rook
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == blackRook){
                    bool blocked = false;
                    if (originalxLoc != nextxLoc && originalyLoc != nextyLoc) {moveValid = false; cout << "\033[31mNot Horizontal Or Vertical\033[0m" << endl;}
                    else if (originalxLoc == nextxLoc){
                        for (int i = 1; i < abs(nextyLoc - originalyLoc); i++){
                            if (nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc, originalyLoc - i) -> getColor() != empty) blocked = true;
                        }
                    }

                    else if (originalyLoc == nextyLoc){
                        for (int i = 1; i < abs(nextxLoc - originalxLoc); i++){
                            if (nextxLoc > originalxLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc) -> getColor() != empty) blocked = true;
                        }
                    }
                    
                    if (!moveValid) {}
                    else if (blocked == true) {moveValid = false; cout << "\033[31mThe Path is Blocked\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white) mainBoard.conquerMove(original, next);
                    else mainBoard.exchangePosition(original, next);
                }

                // For Moving Bishop
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == blackBishop){
                    bool blocked = false;
                    if (abs(nextxLoc - originalxLoc) != abs(nextyLoc - originalyLoc) || abs(nextxLoc - originalxLoc) == 0) {moveValid = false; cout << "\033[31mNot Diagonal Move or Same Position\033[0m" << endl;}
                    else {
                        for (int i = 1; i < abs(nextxLoc - originalxLoc); i++){
                            if (nextxLoc > originalxLoc && nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc > originalxLoc && nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc - i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc - i) -> getColor() != empty) blocked = true;
                        }
                    }

                    if (!moveValid) {}
                    else if (blocked == true) {moveValid = false; cout << "\033[31mThe Path is Blocked\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white) mainBoard.conquerMove(original, next);
                    else mainBoard.exchangePosition(original, next);
                }

                // For Moving Queen
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == blackQueen){
                    bool blocked = false;
                    if ((originalxLoc != nextxLoc && originalyLoc != nextyLoc) || (abs(nextxLoc - originalxLoc) != abs(nextyLoc - originalyLoc) && abs(nextxLoc - originalxLoc) == 0)) {moveValid = false; cout << "\033[31mNot Diagonal, Horizontal, or Vertical Move\033[0m" << endl;}
                    else if (originalxLoc == nextxLoc){
                        for (int i = 1; i < abs(nextyLoc - originalyLoc); i++){
                            if (nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc, originalyLoc - i) -> getColor() != empty) blocked = true;
                        }
                    }

                    else if (originalyLoc == nextyLoc){
                        for (int i = 1; i < abs(nextxLoc - originalxLoc); i++){
                            if (nextxLoc > originalxLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc) -> getColor() != empty) blocked = true;
                        }
                    }
                    else {
                        for (int i = 1; i < abs(nextxLoc - originalxLoc); i++){
                            if (nextxLoc > originalxLoc && nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc > originalxLoc && nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc + i, originalyLoc - i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && nextyLoc > originalyLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc + i) -> getColor() != empty) blocked = true;
                            else if (nextxLoc < originalxLoc && nextyLoc < originalyLoc && mainBoard.getBoard(originalxLoc - i, originalyLoc - i) -> getColor() != empty) blocked = true;
                        }
                    }

                    if (!moveValid) {}
                    else if (blocked == true) {moveValid = false; cout << "\033[31mThe Path is Blocked\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white) mainBoard.conquerMove(original, next);
                    else mainBoard.exchangePosition(original, next);
                }
            
                // For Moving Knight
                if (mainBoard.getBoard(originalxLoc, originalyLoc) -> getType() == blackKnight){
                    bool conquer = false;
                    if ((abs(nextxLoc - originalxLoc) != 1 && abs(nextyLoc - originalyLoc) != 2) && (abs(nextxLoc - originalxLoc) != 2 || abs(nextyLoc - originalyLoc) != 1)) {moveValid = false; cout << "\033[31mInvalid Move For Knight\033[0m" << endl;}
                    else conquer = true;
                    
                    if (!conquer) {}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == black) {moveValid = false; cout << "\033[31mNext Position is Occupied\033[0m" << endl;}
                    else if (mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() != empty && mainBoard.getBoard(nextxLoc, nextyLoc) -> getColor() == white) mainBoard.conquerMove(original, next);
                    else mainBoard.exchangePosition(original, next);
                }
            }
        }

        // For Command "setup" (Difficult)
        if (command == "setup" && !startGame && !setUpMode){
            // Enable SetUp Mode
            setUpMode = true;
        }

        // Switching Turns if Move is Valid
        if (!gameOver && moveValid && command == "move" && !startGame){
            if (currentPlayer == white) currentPlayer = black;
            else if (currentPlayer == black) currentPlayer = white;
        }

        // Draw the Board
        mainBoard.draw();

        // Seek User Input Again
        // Prompt User For Input (Comment This For Testing)
        /*
        cout << "\033[33mRead PDF for input instructions\033[0m" << endl;
        cout << "\033[36mCurrent Player: " << currentPlayer << "\033[0m" << endl;
        cout << "> ";
        getline(cin, line);
        */
    }

    // Draw the Board
    mainBoard.draw();
    
    return 0;
}