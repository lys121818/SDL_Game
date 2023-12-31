// From the passed Assignmnet
/*
*/
#include <time.h>
#include <chrono>
#include <cassert>
#include <iostream>
#include <SDL_ttf.h>
#include "GameDemo.h"
#include "Platformer.h"
#include "SoundDirectory.h"

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
        m_quit = false;
        m_pStateMachine = pGameStateMachine;
        m_pTextures = new Textures(m_pRenderer);
        m_pFonts = new Fonts();
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

        if (m_quit)
            quit = true;
    }
    
}

void GameDemo::Destroy()
{
    // Destroy Renderer.
    SDL_DestroyRenderer(m_pRenderer);

    // Destory Audio
    Mix_CloseAudio();

    // Destroy Textures
    delete m_pTextures;

    // Destroy Fonts
    delete m_pFonts;

    // SDL window cleanup
    SDL_DestroyWindow(m_pWindow);

    SDL_Quit();
}

void GameDemo::Quit()
{
    m_quit = true;
}




/////////////
// PRIVATE //
/////////////

// load textures being used in the scene
void GameDemo::PreloadTexture()
{
    m_pTextures->PreloadTextures(m_pStateMachine->GetScene());

}

// load Fonts being used in the scene
void GameDemo::PreloadFonts()
{
    m_pFonts->PreloadFonts(m_pStateMachine->GetScene());
}

bool GameDemo::ProcessEvents()
{
    if (m_pStateMachine == nullptr)
        return true;

    bool quit = false;


    SDL_Event evt;
    while (SDL_PollEvent(&evt) != 0)
    {
        quit = m_pStateMachine->HandleEvent(&evt);

        return quit;
    }

    return quit;
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

    
    m_pStateMachine->RenderCurrentState(m_pRenderer,m_pTextures);


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
    int errorCode;

    errorCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (errorCode != 0)
    {
        std::cout << "Failed to initialize SDL. Error: " << SDL_GetError() << std::endl;     // indicate the error
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        system("pause");
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
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        system("pause");
        return 2;   // window creation error
    }

    // Create Renderer.
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if (m_pRenderer == nullptr)
    {
        SDL_DestroyWindow(m_pWindow);
        std::cout << "Failed to create renderer. Error: " << SDL_GetError();
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        system("pause");
        return 3;   // renderer creation error
    }

    errorCode = TTF_Init();

    if (errorCode != 0)
    {
        std::cout << "Failed to initialize TTF. Error: " << SDL_GetError() << std::endl;     // indicate the error
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        system("pause");
        return 4;   // initializing error
    }

    // Initialize file types support.
    errorCode = Mix_Init(MIX_INIT_MP3 | MIX_INIT_MOD | MIX_INIT_OGG);
    if (errorCode == 0)
    {
        std::cout << "Mixer_Init() failed. Error: " << Mix_GetError() << std::endl;
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        system("pause");
        return 4;
    }


    errorCode = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY * 2, MIX_DEFAULT_FORMAT, 6, 1024 * 4);

    if (errorCode != 0)
    {
        std::cout << "Failed to Open Mix_OpenAudio(). Error: " << SDL_GetError() << std::endl;     // indicate the error
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        system("pause");
        return 4;   // initializing error
    }

    // You must set the blend mode if you want to support alpha.
    SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);

    return errorCode;
}

