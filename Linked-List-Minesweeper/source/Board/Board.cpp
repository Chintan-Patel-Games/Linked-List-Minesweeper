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
        srand(time(0));
        firstMove = true;
        grid.resize(N, vector<Cell::Cell>(N));
    }

    bool Board::isInside(int r, int c)
    {
        return r >= 0 && r < N && c >= 0 && c < N;
    }

    void Board::placeMines(int safeR, int safeC)
    {
        int placed = 0;
        while (placed < MINES)
        {
            int r = rand() % N;
            int c = rand() % N;
            if ((r == safeR && c == safeC) || grid[r][c].isMine) continue;
            grid[r][c].isMine = true;
            placed++;
        }

        int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                if (grid[r][c].isMine) continue;
                int count = 0;
                for (int d = 0; d < 8; d++)
                {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (isInside(nr, nc) && grid[nr][nc].isMine) count++;
                }
                grid[r][c].neighborMines = count;
            }
        }
    }

    void Board::display(bool revealMines)
    {
        cout << "\n    ";
        for (int i = 0; i < N; i++) cout << i << " ";
        cout << "\n   ";
        for (int i = 0; i < N; i++) cout << "--";
        cout << "-\n";

        for (int r = 0; r < N; r++)
        {
            cout << r << " | ";
            for (int c = 0; c < N; c++)
            {
                if (revealMines && grid[r][c].isMine) cout << "* ";
                else if (grid[r][c].revealed)
                {
                    if (grid[r][c].neighborMines > 0) cout << grid[r][c].neighborMines << " ";
                    else cout << ". ";
                }
                else if (grid[r][c].flagged) cout << "F ";
                else cout << "# ";
            }
            cout << "|\n";
        }

        cout << "   ";
        for (int i = 0; i < N; i++) cout << "--";
        cout << "-\n\n";
    }

    void Board::floodReveal(int r, int c)
    {
        queue<pair<int, int>> q;
        q.push({ r, c });

        int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        while (!q.empty())
        {
            pair<int, int> current = q.front();
            int cr = current.first;
            int cc = current.second;
            q.pop();

            for (int d = 0; d < 8; ++d)
            {
                int nr = cr + dr[d];
                int nc = cc + dc[d];
                if (isInside(nr, nc) && !grid[nr][nc].revealed && !grid[nr][nc].flagged)
                {
                    grid[nr][nc].revealed = true;
                    if (grid[nr][nc].neighborMines == 0) q.push({ nr, nc });
                }
            }
        }
    }

    bool Board::reveal(int r, int c)
    {
        if (!isInside(r, c) || grid[r][c].flagged) return true;

        if (firstMove)
        {
            placeMines(r, c);
            firstMove = false;
        }

        grid[r][c].revealed = true;

        if (grid[r][c].isMine) return false; // Game over

        if (grid[r][c].neighborMines == 0) floodReveal(r, c);

        return true;
    }

    void Board::toggleFlag(int r, int c)
    {
        if (isInside(r, c) && !grid[r][c].revealed) grid[r][c].flagged = !grid[r][c].flagged;
    }

    bool Board::checkWin()
    {
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                if (!grid[r][c].isMine && !grid[r][c].revealed) return false;
            }
        }
        return true;
    }

    bool Board::isGameWon() { return checkWin(); }
}