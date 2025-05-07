#include "../../header/Game/Game.h"
#include <iostream>

using namespace std;

namespace Game
{
    void Game::printRules()
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

    void Game::run()
    {
        printRules();

        bool gameOver = false;

        while (!gameOver)
        {
            board.display();
            cout << "Enter command (r row col) or (f row col): ";
            char command;
            int r, c;
            cin >> command >> r >> c;

            if (command == 'r')
            {
                bool safe = board.reveal(r, c);
                if (!safe)
                {
                    board.display(true);
                    cout << "💥 Game Over! You hit a mine!\n";
                    gameOver = true;
                }
                else if (board.isGameWon())
                {
                    board.display();
                    cout << "🎉 Congratulations! You won!\n";
                    gameOver = true;
                }
            }
            else if (command == 'f') board.toggleFlag(r, c);
            else cout << "Invalid command!\n";
        }
    }
}