#include <iostream>

#include "src/tictactoe.hpp"

using namespace std;

int main() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    bool sessionActive = true;

    while (sessionActive) {
        // --- Mode Selection ---
        bool vsComputer = false;
        while (true) {
            cout << "\nWould you like to play against a human or computer (human/computer)?  ";
            string modeChoice;
            getline(cin, modeChoice);
            if (modeChoice == "human") {
                vsComputer = false;
                break;
            } else if (modeChoice == "computer") {
                vsComputer = true;
                break;
            } else {
                cout << "\nThat is not a valid entry!" << endl;
            }
        }

        // --- Order Selection (only when playing vs computer) ---
        bool computerGoesFirst = false;
        if (vsComputer) {
            while (true) {
                cout << "\nShould the computer go first or second (first/second)?  ";
                string orderChoice;
                getline(cin, orderChoice);
                if (orderChoice == "first") {
                    computerGoesFirst = true;
                    break;
                } else if (orderChoice == "second") {
                    computerGoesFirst = false;
                    break;
                } else {
                    cout << "\nThat is not a valid entry!" << endl;
                }
            }
        }

        // --- Game Setup ---
        char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char currentPlayer = 'X';
        bool gameActive = true;

        // If computer goes first, it plays as X; human plays as O.
        // If computer goes second, human plays as X; computer plays as O.
        char computerSymbol = computerGoesFirst ? 'X' : 'O';

        while (gameActive) {
            displayBoard(board);

            int move = 0;

            // Determine whose turn it is
            bool isComputerTurn = vsComputer && (currentPlayer == computerSymbol);

            if (isComputerTurn) {
                cout << "Computer's turn..." << endl;
                move = computerMove(board);
            } else {
                while (true) {
                    cout << "What is your move?  ";
                    string input;
                    getline(cin, input);

                    move = validateMove(input, board);
                    if (move > 0) break; // Valid

                    // If invalid, show error and board
                    cout << "\nThat is not a valid move! Try again." << endl;
                    displayBoard(board);
                }
            }

            board[move - 1] = currentPlayer;

            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                if (isComputerTurn) {
                    cout << "The computer wins!" << endl;
                } else {
                    cout << "Player " << currentPlayer << " wins!" << endl;
                }
                gameActive = false;
            } else if (checkDraw(board)) {
                displayBoard(board);
                cout << "It's a draw!" << endl;
                gameActive = false;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        // --- Play Again ---
        while (true) {
            cout << "\nWould you like to play again (yes/no)?  ";
            string choice;
            getline(cin, choice);
            if (choice == "yes" || choice == "y") {
                sessionActive = true;
                break;
            } else if (choice == "no" || choice == "n") {
                sessionActive = false;
                break;
            } else {
                cout << "\nThat is not a valid entry!" << endl;
            }
        }
    }
    cout << "\nGoodbye!" << endl;
    return 0;
}