#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/tictactoe.hpp"

TEST_CASE("Move Validation") {
    char board[9] = {'1', 'X', '3', '4', '5', '6', '7', '8', '9'};

    SECTION("Rejects non-numeric strings") {
        REQUIRE(validateMove("foobar", board) == 0);
    }
    SECTION("Rejects out-of-bounds numbers") {
        REQUIRE(validateMove("258", board) == 0);
    }
    SECTION("Rejects symbols") {
        REQUIRE(validateMove("$", board) == 0);
    }
    SECTION("Rejects already taken spots") {
        REQUIRE(validateMove("2", board) == -1);
    }
    SECTION("Accepts valid spots") {
        REQUIRE(validateMove("1", board) == 1);
    }
}

TEST_CASE("Win and Draw Conditions") {
    SECTION("Detects a vertical win") {
        char winBoard[9] = {'X', '2', '3', 'X', '5', '6', 'X', '8', '9'};
        REQUIRE(checkWin(winBoard, 'X') == true);
    }
    SECTION("Detects a draw") {
        char drawBoard[9] = {'X', 'O', 'X', 'X', 'O', 'O', 'O', 'X', 'X'};
        REQUIRE(checkDraw(drawBoard) == true);
    }
    SECTION("Detects a draw with trap cell excluded") {
        // Cell 5 (index 4) is the trap — it stays as '5', not X or O.
        // All other cells are filled, so it should still be a draw.
        char drawBoard[9] = {'X', 'O', 'X', 'X', '5', 'O', 'O', 'X', 'X'};
        REQUIRE(checkDraw(drawBoard, 5) == true);
    }
    SECTION("Not a draw when non-trap cells are still empty") {
        char board[9] = {'X', 'O', 'X', 'X', '5', 'O', 'O', 'X', '9'};
        REQUIRE(checkDraw(board, 5) == false);
    }
}

TEST_CASE("Computer Move") {
    SECTION("Returns a valid available position on an empty board") {
        char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        int move = computerMove(board);
        REQUIRE(move >= 1);
        REQUIRE(move <= 9);
    }
    SECTION("Only returns positions that are not already taken") {
        char board[9] = {'X', 'O', '3', '4', '5', '6', '7', '8', '9'};
        int move = computerMove(board);
        REQUIRE(move >= 3);
        REQUIRE(move <= 9);
    }
    SECTION("Takes the last remaining spot") {
        char board[9] = {'X', 'O', 'X', 'O', 'X', 'O', 'X', 'O', '9'};
        REQUIRE(computerMove(board) == 9);
    }
    SECTION("Returns 0 when the board is full") {
        char board[9] = {'X', 'O', 'X', 'X', 'O', 'O', 'O', 'X', 'X'};
        REQUIRE(computerMove(board) == 0);
    }
}

TEST_CASE("Trap Cell Logic") {
    SECTION("isTrap returns true when move matches trap cell") {
        REQUIRE(isTrap(5, 5) == true);
    }
    SECTION("isTrap returns false when move does not match trap cell") {
        REQUIRE(isTrap(3, 5) == false);
    }
    SECTION("isTrap returns false when trap is disabled (trapCell = 0)") {
        REQUIRE(isTrap(5, 0) == false);
    }
    SECTION("setTrapCell returns a value between 1 and 9") {
        int trap = setTrapCell();
        REQUIRE(trap >= 1);
        REQUIRE(trap <= 9);
    }
}