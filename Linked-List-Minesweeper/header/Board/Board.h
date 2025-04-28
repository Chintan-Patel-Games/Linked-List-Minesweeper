#pragma once  
#include "../../header/Cell/Cell.h"  
#include <vector>  

namespace Board  
{  
   class Board  
   {  
   private:  
       static const int N = 5;  
       static const int MINES = 5;  
       std::vector<std::vector<Cell::Cell>> grid;
       bool firstMove;  

       bool isInside(int r, int c);  
       void placeMines(int safeR, int safeC);  
       void floodReveal(int r, int c);  
       bool checkWin();  

   public:  
       Board();  
       void display(bool revealMines = false);  
       bool reveal(int r, int c);  
       void toggleFlag(int r, int c);  
       bool isGameWon();  
   };  
}