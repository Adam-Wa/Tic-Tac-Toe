#include <iostream>

#include "src/tictactoe.hpp"

using namespace std;

int main() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    bool sessionActive = true;

    while (sessionActive) {
        char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char currentPlayer = 'X';
        bool gameActive = true;

        while (gameActive) {
            displayBoard(board);

            int move = 0;
            while (true) {
                cout << "What is your move? ";
                string input;
                getline(cin, input);

                move = validateMove(input, board);
                if (move > 0) break; // Valid

                // If invalid, show error and board
                cout << "\nThat is not a valid move! Try again." << endl;
                displayBoard(board);
            }

            board[move - 1] = currentPlayer;

            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                cout << "Player " << currentPlayer << " wins!" << endl;
                gameActive = false;
            } else if (checkDraw(board)) {
                displayBoard(board);
                cout << "It's a draw!" << endl;
                gameActive = false;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        // Play Again
        while (true) {
            cout << "\nWould you like to play again (yes/no)? ";
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
