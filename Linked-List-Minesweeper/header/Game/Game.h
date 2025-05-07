#pragma once
#include "../../header/Board/Board.h"

namespace Game
{
    class Game
    {
    private:
        Board::Board board;

    public:
        void printRules();
        void run();
    };
}