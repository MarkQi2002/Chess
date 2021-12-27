// Include Modules
#include <iostream>
#include <sstream>
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
    // Variable Declaration
    Board mainBoard;
    string currentPlayer = white;
    bool gameOver = false;
    bool startGame = true;  // This Indicated The Beginning of the Game (True)

    // For Assigning Players
    int firstPlayer = -1;
    int secondPlayer = -1;

    // Input Interpretation
    string line;
    string command;

    // Prompt User For Input
    cout << "\033[33mRead PDF for input instructions\033[0m" << endl;
    cout << "> ";
    getline(cin, line);

    // Main Game Part
    while (!cin.eof() && !gameOver){
        // Variable Declaration
        bool moveValid = true;

        // New sstream for each input
        stringstream lineStream(line);

        // Read form string stream into comman
        command = "";
        lineStream >> command;

        // Check if Command is Valid
        if (command != normalCommandList[0] && command != normalCommandList[1] && command != normalCommandList[2] && command != normalCommandList[3]){
            cout << "\033[31mInvalid Command\033[0m" << endl;
        }

        // Game Started and Command is "game"
        if (command == "game" && !startGame) cout << "\033[31mGame Already Started\033[0m" << endl;
        
        // Game Not Started and Command is "game"
        if (command == "game" && startGame){
            // Set Players 1 (FirstHand)
            while (firstPlayer == -1){
                string playerSelectOne;
                cout << "\033[35mPlease Choose Player One (White), Human (0), AI1 (1), AI2 (2), AI3 (3), AI4 (4): \033[0m";
                getline(cin, playerSelectOne);
                if (playerSelectOne != "0" && playerSelectOne != "1" && playerSelectOne != "2" && playerSelectOne != "3" && playerSelectOne != "4") cout << "\033[31mInvalid Input\033[0m" << endl;
                else firstPlayer = stoi(playerSelectOne);
            }

            // Set Player 2 (SecondHand)
            while (secondPlayer == -1){
                string playerSelectTwo;
                cout << "\033[35mPlease Choose Player Two (Black), Human (0), AI1 (1), AI2 (2), AI3 (3), AI4 (4): \033[0m";
                getline(cin, playerSelectTwo);
                if (playerSelectTwo != "0" && playerSelectTwo != "1" && playerSelectTwo != "2" && playerSelectTwo != "3" && playerSelectTwo != "4") cout << "\033[31mInvalid Input\033[0m" << endl;
                else secondPlayer = stoi(playerSelectTwo);
            }
        }

        // For Command "resign" (Easy)
        if (command == "resign"){
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
        if (command == "move"){
            // Controlling Input
            string originalPosition;
            string nextPosition;
            string temp;
            bool validInput = true;
            bool extraInput = false;
            
            // Getting Input From stringstream
            lineStream >> originalPosition >> nextPosition >> temp;

            // Verify Input
            if (temp != "") extraInput = true;
            if (originalPosition.size() != 2) validInput = false;
            if (nextPosition.size() != 2) validInput = false;

            // Invalid Input
            if (!validInput) cout << "\033[31mInvalid Position\033[0m" << endl;
            if (extraInput) cout << "\033[31mToo Many Arguments\033[0m" << endl;

        }

        // For Command "setup" (Difficult)
        if (command == "setup"){

        }

        // Switching Turns if Move is Valid
        if (!gameOver && moveValid && command == "move"){
            if (currentPlayer == white) currentPlayer = black;
            else if (currentPlayer == black) currentPlayer = white;
        }

        // Seek User Input Again
        // Prompt User For Input
        cout << "\033[33mRead PDF for input instructions\033[0m" << endl;
        cout << "> ";
        getline(cin, line);
    }

    // Draw the Board
    mainBoard.draw();
    
    return 0;
}