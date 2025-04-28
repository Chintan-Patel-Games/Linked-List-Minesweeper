#pragma once

namespace Cell
{
    struct Cell
    {
        bool isMine = false;
        bool revealed = false;
        bool flagged = false;
        int neighborMines = 0;
    };
}