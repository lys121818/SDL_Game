
#include <iostream>
#include "GameDemo.h"
#include "Platformer.h"
//#include <vld.h>
#include <random>
#include <SDL.h>

#include "RNG.h"


int main(int argc, char* argv[])
{
    GameDemo game;
    
    Platformer stateMachine(&game);   // Choosing game to play

    int errorCode = game.Init(&stateMachine);
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

