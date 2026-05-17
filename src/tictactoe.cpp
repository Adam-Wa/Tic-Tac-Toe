#include "tictactoe.hpp"
#include <iostream>
#include <string>

using namespace std;

void displayBoard(const char board[]) {
    cout << "\n   " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "  -----------" << endl;
    cout << "   " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "  -----------" << endl;
    cout << "   " << board[6] << " | " << board[7] << " | " << board[8] << "\n" << endl;
}

int validateMove(string input, const char board[]) {
    // 1. Check if empty (No input/just enter)
    if (input.empty()) return 0;

    // 2. Check if it's a single digit 1-9 (Handles strings, symbols, decimals)
    if (input.length() == 1 && input[0] >= '1' && input[0] <= '9') {
        int move = input[0] - '0';

        // 3. Check if cell is already taken
        if (board[move - 1] == 'X' || board[move - 1] == 'O') {
            return -1;
        }
        return move;
    }
    return 0;
}

bool checkWin(const char board[], char p) {
    return ((board[0] == p && board[1] == p && board[2] == p) ||
            (board[3] == p && board[4] == p && board[5] == p) ||
            (board[6] == p && board[7] == p && board[8] == p) ||
            (board[0] == p && board[3] == p && board[6] == p) ||
            (board[1] == p && board[4] == p && board[7] == p) ||
            (board[2] == p && board[5] == p && board[8] == p) ||
            (board[0] == p && board[4] == p && board[8] == p) ||
            (board[2] == p && board[4] == p && board[6] == p));
}

// A draw means every cell is filled except the (optional) trap cell.
bool checkDraw(const char board[], int trapCell) {
    for (int i = 0; i < 9; i++) {
        // Skip the trap cell — it stays unmarked forever
        if (trapCell > 0 && i == trapCell - 1) continue;
        if (board[i] != 'X' && board[i] != 'O') return false;
    }
    return true;
}

// Returns a random 1-based position from the available spots on the board.
// The computer has no knowledge of the trap location — it picks blindly at
// random, giving it the same natural chance of hitting the trap as a human.
// Returns 0 if no move is available.
int computerMove(const char board[], int trapCell) {
    // Collect all available (unmarked) positions into a C-style array
    int available[9];
    int count = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            available[count] = i + 1;  // store 1-based position
            ++count;
        }
    }
    if (count == 0) return 0;

    // Pick a random index within the available positions
    return available[rand() % count];
}

// Picks a random trap cell position (1–9).
// Relies on srand() having been called once at program start in main().
int setTrapCell() {
    return (rand() % 9) + 1;  // 1-based position, range 1–9
}

// Returns true if the given move lands on the trap cell.
bool isTrap(int move, int trapCell) {
    return trapCell > 0 && move == trapCell;
}