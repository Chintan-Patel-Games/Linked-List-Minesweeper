#pragma once
#include "../../header/Cell/Cell.h"
#include <vector>

namespace Board
{
    class Board
    {
    private:
        static const int BOARD_SIZE = 9;            // Size of the square game board (9x9)
        static const int MINES = 8;                 // Total number of mines to be placed

        std::vector<std::vector<Cell::Cell>> grid;  // 2D grid representing the board
        bool firstMove;                             // Flag to prevent placing a mine on the first move

        bool isInside(int row, int col);            // Checks if the given (row, col) is within board boundaries
        void placeMines(int safeRow, int safeCol);  // Randomly places mines on the board, avoiding the first clicked cell
        void floodReveal(int row, int col);         // Reveals adjacent empty cells using BFS-style flood fill
        bool checkWin();                            // Checks if all non-mine cells are revealed

    public:
        Board();
        void display(bool revealMines = false);    // Displays the current state of the board; revealMines reveals all mines if true
        bool reveal(int row, int col);             // Reveals a cell; returns false if it's a mine (i.e., game over)
        void toggleFlag(int row, int col);         // Toggles a flag on a hidden cell
        bool isGameWon();                          // Returns true if the player has won the game
    };
}