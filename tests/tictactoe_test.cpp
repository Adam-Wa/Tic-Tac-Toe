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
}
