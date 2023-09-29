
#include <iostream>
#include "GameDemo.h"

#include <SDL.h>



int main(int argc, char* argv[])
{
    GameDemo game;
    int errorCode = game.Init();
// Add the program body starting from here

    if (errorCode == 0)
    {
        // Run the game
        game.Run();
    }

    // Destroy SDL elements
    game.Destroy();

    return 0;   //success

}

