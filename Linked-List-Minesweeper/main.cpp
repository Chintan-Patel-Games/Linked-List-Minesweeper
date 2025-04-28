#include "header/Game/Game.h"
#include <iostream>

using namespace std;

int main()
{
   bool playAgain = true;
   while (playAgain)
   {
       Game::Game g;
       g.run();

       cout << "Play again? (y/n): ";
       char choice;
       cin >> choice;
       if (choice == 'n' || choice == 'N') playAgain = false;
   }

   cout << "Thanks for playing!\n";
   return 0;
}