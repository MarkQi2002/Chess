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

    }

    // Draw the Board
    mainBoard.draw();
    
    return 0;
}