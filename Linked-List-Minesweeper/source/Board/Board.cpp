#include "../../header/Board/Board.h"
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

namespace Board
{
    Board::Board()
    {
        srand(time(0)); // Seed for random mine placement
        firstMove = true;
        grid.resize(BOARD_SIZE, vector<Cell::Cell>(BOARD_SIZE)); // 9x9 grid of cells
    }

    bool Board::isInside(int row, int col) // Checks if the given position is within the board boundaries
    {
        return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
    }

    void Board::placeMines(int safeRow, int safeCol) // Randomly places mines on the board, ensuring the first move is safe
    {
        int placed = 0;
        int row, col;

        while (placed < MINES)
        {
            row = rand() % BOARD_SIZE;
            col = rand() % BOARD_SIZE;

            // Skip if it's the first revealed cell or already a mine
            if ((row == safeRow && col == safeCol) || grid[row][col].isMine)
                continue;

            grid[row][col].isMine = true;
            placed++;
        }

        // Directions for checking surrounding 8 cells
        int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
        int count, nr, nc;

        // Calculate number of neighboring mines for each non-mine cell
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {
				if (grid[row][col].isMine) continue; // Skip if it's a mine

				count = 0; // Count of neighboring mines
                for (int d = 0; d < 8; d++)
                {
                    nr = row + dr[d];   // neighbor row
                    nc = col + dc[d];   // neighbor column
                    if (isInside(nr, nc) && grid[nr][nc].isMine)
						count++; // Increment count if neighbor is a mine
                }

				grid[row][col].neighborMines = count; // Set the count of neighboring mines
            }
        }
    }

    void Board::display(bool revealMines) // Displays the board to the console
    {
        cout << "\n    ";
        for (int i = 0; i < BOARD_SIZE; i++) cout << i << " ";
        cout << "\n   ";
        for (int i = 0; i < BOARD_SIZE; i++) cout << "--";
        cout << "-\n";

        for (int row = 0; row < BOARD_SIZE; row++)
        {
            cout << row << " | ";
            for (int col = 0; col < BOARD_SIZE; col++)
            {
                const auto& cell = grid[row][col];

                // If we want to reveal mines (usually after losing)
                if (revealMines && cell.isMine) cout << "* ";
                else if (cell.isRevealed())
                {
                    // Show number or empty space
                    if (cell.neighborMines > 0) cout << cell.neighborMines << " ";
                    else cout << ". ";
                }
                else if (cell.isFlagged()) cout << "F ";
                else cout << "# ";
            }
            cout << "|\n";
        }

        cout << "   ";
        for (int i = 0; i < BOARD_SIZE; i++) cout << "--";
        cout << "-\n\n";
    }

    void Board::floodReveal(int row, int col) // Reveals adjacent empty cells using flood fill (non-recursive to avoid stack overflow)
    {
        queue<pair<int, int>> q;  // Queue to store the cells to be processed for flood fill
        q.push({ row, col });      // Start the flood fill from the given (row, col)

        // Directions for checking the 8 surrounding cells (top-left, top, top-right, left, right, bottom-left, bottom, bottom-right)
        int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
        int cr, cc, nr, nc;

        // Process the queue until it is empty
        while (!q.empty())
        {
            pair<int, int> current = q.front();  // Get the current cell from the queue
            cr = current.first;  // Current row of the cell being processed
            cc = current.second; // Current column of the cell being processed
            q.pop();  // Remove the current cell from the queue

            // Check all 8 surrounding cells (neighbors) of the current cell
            for (int d = 0; d < 8; ++d)
            {
                nr = cr + dr[d];  // Neighbor row based on direction
                nc = cc + dc[d];  // Neighbor column based on direction

                // Check if the neighboring cell is within the bounds of the grid
                if (isInside(nr, nc))
                {
                    auto& neighbor = grid[nr][nc];  // Reference to the neighboring cell

                    // Only process the neighbor if it hasn't been revealed and is not flagged
                    if (!neighbor.isRevealed() && !neighbor.isFlagged())
                    {
                        neighbor.state = Cell::CellState::Revealed;  // Mark the neighbor as revealed

                        // If the neighboring cell has no adjacent mines, continue the flood to reveal its neighbors
                        if (neighbor.neighborMines == 0)
                            q.push({ nr, nc });  // Add the neighbor to the queue for further processing
                    }
                }
            }
        }
    }

    bool Board::reveal(int row, int col) // Reveals a cell and processes logic like game over or flood reveal
    {
        if (!isInside(row, col) || grid[row][col].isFlagged())
            return true; // Invalid move, do nothing

        // On first move, place mines making sure it's not a mine
        if (firstMove)
        {
            placeMines(row, col);
            firstMove = false;
        }

        grid[row][col].state = Cell::CellState::Revealed;

        if (grid[row][col].isMine) return false; // Hit a mine: game over

        // Reveal neighboring cells if current is empty
        if (grid[row][col].neighborMines == 0) floodReveal(row, col);

        return true; // Move was safe
    }

    void Board::toggleFlag(int row, int col) // Toggles a flag on a hidden cell
    {
        if (!isInside(row, col)) return;

        auto& cell = grid[row][col];
        if (cell.isRevealed()) return;

        if (cell.isFlagged()) cell.state = Cell::CellState::Hidden;
        else cell.state = Cell::CellState::Flagged;
    }

    bool Board::checkWin() // Checks if all non-mine cells are revealed (win condition)
    {
        for (int row = 0; row < BOARD_SIZE; row++)
            for (int col = 0; col < BOARD_SIZE; col++)
                if (!grid[row][col].isMine && !grid[row][col].isRevealed()) return false;
        return true;
    }

    // Public method to check if the game is won
    bool Board::isGameWon() { return checkWin(); }
}
