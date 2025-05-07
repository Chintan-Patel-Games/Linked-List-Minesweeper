#include "header/Game/Game.h"
#include <iostream>

using namespace std;

int main()
{
    bool playAgain = true;   // Flag to control whether the game should restart
    Game::Game g;            // Create a Game object
    char choice;             // Store player's choice to play again

    while (playAgain)
    {
        g.run();             // Start the game loop

        // Ask the player if they want to play again
        cout << "Play again? (y/n): ";
        cin >> choice;
        if (choice == 'n' || choice == 'N') playAgain = false;
    }

    cout << "Thanks for playing!\n";
    return 0; // Exit program
}