#include <string>

void displayBoard(const char board[]);
bool checkWin(const char board[], char player);
bool checkDraw(const char board[], int trapCell = 0);
int validateMove(std::string input, const char board[]);
int computerMove(const char board[], int trapCell = 0);
int setTrapCell();
bool isTrap(int move, int trapCell);