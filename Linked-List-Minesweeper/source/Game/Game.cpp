#include "../../header/Game/Game.h"
#include <iostream>

using namespace std;

namespace Game
{
    void Game::printRules() // Prints the game rules and instructions for the player
    {
        cout << "----------------------------------------\n";
        cout << "        Welcome to Minesweeper!\n";
        cout << "----------------------------------------\n";
        cout << "[Rules]\n";
        cout << "- Reveal all safe cells without hitting a mine.\n";
        cout << "- Flag cells you think are mines.\n\n";
        cout << "[How to Play]\n";
        cout << "- r row col --> reveal\n";
        cout << "- f row col --> flag/unflag\n";
        cout << "First move is always safe.\n\n";
    }
    
    void Game::run() // Main game loop: handles input, board updates, and win/loss conditions
    {
        printRules();  // Display rules at game start

        bool gameOver = false;  // Game loop control flag
        char command;           // Command input: 'r' for reveal, 'f' for flag
        int row, col;           // Cell coordinates

        // Game continues until player wins or hits a mine
        while (!gameOver)
        {
            board.display();  // Show the current state of the board

            // Get user input
            cout << "Enter command (r row col) or (f row col): ";

            if (!(cin >> command >> row >> col)) {
                cout << "Invalid input format! Please use: r row col or f row col\n";
                cin.clear();               // Clear the error state
                cin.ignore(10000, '\n');   // Discard the rest of the line
                continue;                  // Prompt again
            }

            if (command == 'r') // Reveal cell
            {
                bool safe = board.reveal(row, col);
                if (!safe) // Hit a mine
                {
                    board.display(true);  // Reveal all mines
                    cout << "Game Over! You hit a mine!\n";
                    gameOver = true;
                }
                else if (board.isGameWon()) // All safe cells revealed
                {
                    board.display();  // Show final board
                    cout << "Congratulations! You won!\n";
                    gameOver = true;
                }
            }
            // Flag or unflag a cell
            else if (command == 'f') board.toggleFlag(row, col);
            // Invalid input
            else cout << "Invalid command!\n";
        }
    }
}