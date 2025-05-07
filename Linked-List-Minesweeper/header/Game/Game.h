#pragma once
#include "../../header/Board/Board.h"

namespace Game
{
    class Game
    {
    private:
        Board::Board board;

    public:
        void printRules(); // Displays the game rules to the player
        void run(); // Starts and manages the main game loop (user input, board updates, win/loss checks)
    };
}