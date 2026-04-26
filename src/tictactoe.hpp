#include <string>

void displayBoard(const char board[]);
bool checkWin(const char board[], char player);
bool checkDraw(const char board[]);
int validateMove(std::string input, const char board[]);
int computerMove(const char board[]);

