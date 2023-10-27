// From the passed Assignmnet
/*
*/
#include <time.h>
#include <chrono>
#include <cassert>
#include "GameDemo.h"
#include "Platformer.h"

////////////
// PUBLIC //
////////////
int GameDemo::Init(GameStateMachine* pGameStateMachine)
{
    int failedInit;
    // Return errorCode when it fails to create window
    failedInit = CreateWindow();
    if(failedInit != 0)
        return failedInit;

    if (pGameStateMachine != nullptr)
    {
        m_pStateMachine = pGameStateMachine;
    }

	return 0;
}

// where the Game mainly Runs
void GameDemo::Run()
{
    bool quit = false;

    // Get the current time to store for the previous loop.
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    while(!quit)
    {
        // Get this frame's time
        auto thisFrameTime = std::chrono::high_resolution_clock::now();

        // Get the duration that has passed.
        std::chrono::duration<double> lastFrameDuration = thisFrameTime - lastFrameTime;

        // Convert duration into a double, which we use for delta time.
        double deltaTime = lastFrameDuration.count();

        // Reset lastFrameTime to thisFrameTime.
        lastFrameTime = thisFrameTime;

        m_CurrentTime += deltaTime;

        quit = ProcessEvents();
        UpdateGameState(deltaTime);
        DisplayOutput();
    }
    
}

void GameDemo::Destroy()
{
    // Destroy Renderer.
    SDL_DestroyRenderer(m_pRenderer);

    // SDL window cleanup
    SDL_DestroyWindow(m_pWindow);

    SDL_Quit();
}




/////////////
// PRIVATE //
/////////////

bool GameDemo::ProcessEvents()
{
    if (m_pStateMachine == nullptr)
        return true;

    bool doQuit = false;


    SDL_Event evt;
    while (SDL_PollEvent(&evt) != 0)
    {
        doQuit = m_pStateMachine->HandleEvent(&evt);

        return doQuit;
    }
    //return m_pPlayer->FinishGame();
    return doQuit;
}

void GameDemo::UpdateGameState(double deltaTime)
{
    if (m_pStateMachine == nullptr)
        return;

    m_pStateMachine->UpdateCurrentState(deltaTime);



}

void GameDemo::DisplayOutput()
{
    if (m_pStateMachine == nullptr)
        return;

    // Clear the screen.
    // Execute the clear.
    SDL_SetRenderDrawColor(m_pRenderer, BLACK);
    SDL_RenderClear(m_pRenderer);

    
    m_pStateMachine->RenderCurrentState(m_pRenderer);


    // Presenting.
    SDL_RenderPresent(m_pRenderer);

}


// Create Window
int GameDemo::CreateWindow()
{
    /*
    SDL_Init(subsystems)
    There are 7 more subsystems(Audio, CDROM, Event Handling, FileI/O, Joystick Handling, Threading, Timers) other than Video.
    this returns 0 if succeeded
    */
    int m_errorCode;

    m_errorCode = SDL_Init(SDL_INIT_VIDEO);

    if (m_errorCode != 0)
    {
        std::cout << "Failed to initialize SDL. Error: " << SDL_GetError() << std::endl;     // indicate the error
        return 1;   // initializing error
    }
    else
    std::cout << "Successfully initialized SDL!" << std::endl;      // Successfully initalized to SDL


    // SDL window init
    m_pWindow = SDL_CreateWindow(
        "Hello SDL",    // title of the window
        SDL_WINDOWPOS_CENTERED, // x position of the window
        SDL_WINDOWPOS_CENTERED, // y position of the window
        WINDOWWIDTH,   // width of the window size
        WINDOWHEIGHT,    // height of the window size
        0    // SDL_WINDOW_RESIZABLE: able to resize size of the window by manually
    );
    // Make sure that the window gets created successfully

    // window creation error
    if (m_pWindow == nullptr)
    {
        std::cout << "Failed to create window. Error: " << SDL_GetError() << std::endl;
        return 2;   // window creation error
    }

    // Create Renderer.
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if (m_pRenderer == nullptr)
    {
        SDL_DestroyWindow(m_pWindow);
        std::cout << "Failed to create renderer. Error: " << SDL_GetError();
        return 3;   // renderer creation error
    }
    // You must set the blend mode if you want to support alpha.
    SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);

    return m_errorCode;
}

