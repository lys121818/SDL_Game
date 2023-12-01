
#include <iostream>
#include <random>
#include "GameDemo.h"
#include "Platformer.h"
//#include <vld.h>
#include <SDL.h>

void Example()
{
    std::mt19937 engine;

    std::random_device randomDevice;
    unsigned int seed = randomDevice();

    engine.seed(seed);

    // random digits from range of (a, b)
    std::uniform_int_distribution<unsigned int> distribution(1, 6);

    for (int i = 0; i < 100; ++i)
    {
        unsigned int randomNumber = distribution(engine);
        std::cout << randomNumber << std::endl;
    }
}

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

