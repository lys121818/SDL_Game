// From the passed Assignmnet
/*
*/
#include <time.h>
#include <chrono>
#include <cassert>
#include "GameDemo.h"





////////////
// PUBLIC //
////////////
int GameDemo::Init()
{
    int failedInit;
    // Return errorCode when it fails to create window
    failedInit = CreateWindow();
    if(failedInit != 0)
        return failedInit;
    InitGame();

    
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
    //SDL_DestroyRenderer(m_pRenderer);

    // SDL window cleanup
    SDL_DestroyWindow(m_pWindow);

    // Delete the vectors I've created
    {
        // Get size of array
        
    }

    //SDL overall deinit
    SDL_Quit();
}




/////////////
// PRIVATE //
/////////////

bool GameDemo::ProcessEvents()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt) != 0)
    {
        // Quit when true returns
        // KeyBoard Event
        if (ProcessKeyboardEvent(&evt.key) == true)
            return true;
        // Mouse Event
        if (ProcessMouseEvent(&evt.button) == true)
            return true;
        // Window Event
        if (ProcessWindowEvent(&evt.window) == true)
            return true;
    }
    return false;
}

void GameDemo::UpdateGameState(double deltatime)
{
    std::vector<GameObject*>::iterator iter = m_vpGameObjects.begin();

    // Draw objects.
    for (iter; iter < m_vpGameObjects.end(); ++iter)
    {
        GameObject* pGameObject = *iter;
        if (pGameObject == nullptr)
        {
            // we've reached the end
            break;
        }
        else
        {
            // Tell the next GameObject to update.
            pGameObject->Update(deltatime);
        }
    }
}

void GameDemo::DisplayOutput()
{
    // Rendering any objects in the game.

    // Clear the screen.

    // Set background color.
    //SDL_SetRenderDrawColor(m_pRenderer, BACKGROUND);

    // Execute the clear.
    SDL_RenderClear(m_pRenderer);

    std::vector<GameObject*>::iterator iter = m_vpGameObjects.begin();

    // Draw objects.
    for (iter; iter < m_vpGameObjects.end(); ++iter)
    {
        GameObject* pGameObject = *iter;
        if (pGameObject == nullptr)
        {
            // we've reached the end
            break;
        }
        else
        {
            // Tell the next GameObject to update.
            pGameObject->Render(m_pRenderer);
        }
    }
    // Presenting.
    SDL_RenderPresent(m_pRenderer);

}


// Every events using keyboards works here
bool GameDemo::ProcessKeyboardEvent(SDL_KeyboardEvent* pData)
{
    if ((int)pData->state == 1 && (int)pData->repeat == 0)   // Key Press, ignore repeat keys
    {
        switch (pData->keysym.sym)
        {
            // Run
            case SDLK_LSHIFT:
            {
                m_pPlayer->SprintSpeed();
                break;
            }

            // Move Left
            case SDLK_a:
            {
                m_pPlayer->MoveLeft();
                break;
            }

            // Move Right
            case SDLK_d:
            {
                m_pPlayer->MoveRight();
                break;

            }

            // Move Up
            case SDLK_w:
            {
                m_pPlayer->MoveUp();
                break;

            }

            // Move Down
            case SDLK_s:
            {
                m_pPlayer->MoveDown();
                break;
            }

            // Quit
            case SDLK_q:
            {
                if (pData->keysym.mod & KMOD_LCTRL)
                    return true;
                break;
            }
        default:
            break;
        }
    }
    else if ((int)pData->state == 0) // Key Release
    {
        switch (pData->keysym.sym)
        {
            // Stop Run
            case SDLK_LSHIFT:
            {
                m_pPlayer->NormalSpeed();
                break;
            }

            // Stop Moving Left
            case SDLK_a:
            {
                m_pPlayer->StopLeft();
                break;
            }

            // Stop Moving Right
            case SDLK_d:
            {
                m_pPlayer->StopRight();
                break;

            }

            // Stop Moving Up
            case SDLK_w:
            {
                m_pPlayer->StopUp();
                break;
            }

            // Stop Moving Down
            case SDLK_s:
            {
                m_pPlayer->StopDown();
                break;

            }
        default:
            break;
        }
    }
    return false;
}
// Every events using mouse works here
bool GameDemo::ProcessMouseEvent(SDL_MouseButtonEvent* pData)
{
    if ((int)pData->type == SDL_MOUSEBUTTONDOWN)
    {
        switch (pData->button)
        {
            case SDL_BUTTON_LEFT:
            {
                m_pPlayer->MoveDown();
                break;
            }
            case SDL_BUTTON_RIGHT:
            {
                m_pPlayer->MoveUp();
                break;
            }
        default:
            break;
        }
    }
    else if ((int)pData->type == SDL_MOUSEBUTTONUP)
    {
        switch (pData->button)
        {
            case SDL_BUTTON_LEFT:
            {
                m_pPlayer->StopDown();
                break;
            }
            case SDL_BUTTON_RIGHT:
            {
                m_pPlayer->StopUp();
                break;
            }
        default:
            break;
        }
    }
    return false;
}
// Every events using Window works here
bool GameDemo::ProcessWindowEvent(SDL_WindowEvent* pData)
{
    switch (pData->event)
    {
        case SDL_WINDOWEVENT_CLOSE:
        {
            return true;
        }
    default:
        break;
    }
    return false;
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
        800,   // width of the window size
        600,    // height of the window size
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

void GameDemo::InitGame()
{
    // Set GameTime to 0sec
    m_CurrentTime = (double)0.0;

    // Set Background
    m_pBackground = new ImageObject(m_pRenderer, Vector2{ 0,0 }, BACKGROUND);
    // Add Background to vector m_vpGameObjects
    AddGameObject(m_pBackground);

    // Set Player Object
    m_pPlayer = new CubeColider(m_pRenderer, Vector2{ 550,550 });
    // Add player to vector m_vpGameObjects
    AddGameObject(m_pPlayer);
}

// Add gameobject to vector
void GameDemo::AddGameObject(GameObject* object)
{
    // Creates the Object only if it's under amount of s_kMaxGameObjectCount
    if (m_vpGameObjects.size() >= s_kMaxGameObjectCount)
        return;
    // add the gameobject to vector
    m_vpGameObjects.push_back(object);
}
