#pragma once

namespace Cell
{
    // Represents the state of a cell on the board
    enum class CellState
    {
        Hidden,     // Cell has not been revealed yet
        Revealed,   // Cell has been revealed
        Flagged     // Cell has been flagged by the player
    };

    // Represents a single cell on the Minesweeper board
    struct Cell
    {
        bool isMine = false;                   // True if this cell contains a mine
        CellState state = CellState::Hidden;   // Current state (hidden/revealed/flagged)
        int neighborMines = 0;                 // Number of mines in adjacent cells

        // Returns true if the cell has been revealed
        bool isRevealed() const { return state == CellState::Revealed; }

        // Returns true if the cell is flagged
        bool isFlagged() const { return state == CellState::Flagged; }
    };
}