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

bool checkDraw(const char board[]) {
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') return false;
    }
    return true;
}