// From the passed Assignmnet
/*
*/
#include <time.h>
#include <chrono>
#include <cassert>
#include "SDL_image.h" 
#include "GameDemo.h"
#include "Bullet.h"
#include "AnimationObject.h"
#include "EnemyObject.h"
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
    SDL_DestroyRenderer(m_pRenderer);

    // SDL window cleanup
    SDL_DestroyWindow(m_pWindow);

    // Delete the vectors I've created
    {
        DestoryGameObjects(m_vpBackgrounds);
        DestoryGameObjects(m_vpGameObjects);
    }
    // Destory texture when game ends.
    delete m_pTexture;

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
        switch ((int)evt.type)
        {
        // KeyBoard Event
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (ProcessKeyboardEvent(&evt.key) == true)
                return true;
            break;
        break;
        // Mouse Event
        // Quit when true returns
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            if (ProcessMouseEvent(&evt.button) == true)
                return true;
            break;
        break;
        default:
            // Window Event
            if (ProcessWindowEvent(&evt.window) == true)
                return true;
            break;
        }
    }
    return m_pPlayer->FinishGame();
}

void GameDemo::UpdateGameState(double deltatime)
{
    // currently dont have anything updating in background
    //for (auto& element : m_vpBackgrounds)
    //    element->Update(deltatime);

    // Update GameObjects
    for (auto& element : m_vpGameObjects)
    {
        element->Update(deltatime);
        //element->GetTransform();
    }

}

void GameDemo::DisplayOutput()
{
    // Rendering any objects in the game.

    // Clear the screen.
    // Execute the clear.
    SDL_RenderClear(m_pRenderer);

    //Render Background
    for (auto& element : m_vpBackgrounds)
    {
        // Only render inside the window size (on visible)
        if (element->GetTransform().x >= (0- element->GetTransform().w) && 
            element->GetTransform().x < WINDOWWIDTH  - 10&&   // Window width
            element->GetTransform().y >= (0 - element->GetTransform().h) && 
            element->GetTransform().y < WINDOWHEIGHT - 10)    // Window height
        {
            element->Render(m_pRenderer, m_pTexture->GetTexture( element->GetTextureName() ) );
        }
    }


    //Render GameObjects
    for (auto& element : m_vpGameObjects)
    {
        // Only render inside the window size (on visible)
        if (element->GetTransform().x >= (0 - element->GetTransform().w) &&
            element->GetTransform().x < WINDOWWIDTH &&   // Window width
            element->GetTransform().y >= (0 - element->GetTransform().h) &&
            element->GetTransform().y < WINDOWHEIGHT)    // Window height
        {
            element->Render(m_pRenderer, m_pTexture->GetTexture( element->GetTextureName() ) );
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
        switch ((int)pData->keysym.sym)
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

            // Shooting
            case SDLK_SPACE:
            {
                // shooting objects when hit spacebar
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
        switch ((int)pData->keysym.sym)
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
        switch ((int)pData->button)
        {
            case SDL_BUTTON_LEFT:
            {
                break;
            }
            case SDL_BUTTON_RIGHT:
            {
                break;
            }
        default:
            break;
        }
    }
    else if ((int)pData->type == SDL_MOUSEBUTTONUP)
    {
        switch ((int)pData->button)
        {
            case SDL_BUTTON_LEFT:
            {
                break;
            }
            case SDL_BUTTON_RIGHT:
            {
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
    switch ((int)pData->event)
    {
        // Quit when Window X button is pressed
        case SDL_WINDOWEVENT_CLOSE:
        {
            return true;
            break;
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

void GameDemo::InitGame()
{
    // Temperary gameobject
    GameObject* stationary;
    // Set GameTime to 0sec
    m_CurrentTime = (double)0.0;

    /// TEXTURE
    // Create Texture Pointer class
    m_pTexture = new Textures(m_pRenderer);
    // Load images that are being use in the game.
    m_pTexture->PreloadTextures(1);

    // Add Background to vector m_vpGameObjects
    InitBackground();

    /// GAMEOBJECT
    // Set Player Object
    // Player ColliderBox Setting
    SDL_Rect playerTransform{ 
        (int)s_kPlayerStartingPoisition.m_x, // X position of collider box
        (int)s_kPlayerStartingPoisition.m_y, // Y position of collider box
        (int)s_kPlayerStartingSize.m_x,      // Width of collider box
        (int)s_kPlayerStartingSize.m_y       // Height of collider box
    };
    m_pPlayer = new CubeColider(playerTransform,&m_collisionReferee, PUMPKIN,m_pRenderer,Type::m_Player);
    AddGameObject(m_pPlayer);
    // Add GameObjects to m_vpGameObjects
    stationary = new EnemyObject( SDL_Rect{ 500,400,100,150 }, &m_collisionReferee, ZOMBIEMALE,0, Type::m_Enemy);
    AddGameObject(stationary);
    stationary = new EnemyObject( SDL_Rect{ 500,100,100,150 }, &m_collisionReferee, ZOMBIEMALE,0, Type::m_DamageZone);
    AddGameObject(stationary);

    stationary = new EnemyObject(SDL_Rect{ 100,400,100,150 }, &m_collisionReferee, ZOMBIEFEMALE, 0, Type::m_HealingZone);
    AddGameObject(stationary); 
    stationary = new EnemyObject(SDL_Rect{ 100,100,100,150 }, &m_collisionReferee, ZOMBIEFEMALE, 0, Type::m_Wall);
    AddGameObject(stationary);

}

// Setting the tiles background
void GameDemo::InitBackground()
{
    // Set Background tiles
    Vector2 tilePosition;
    // count of tiles needed in width
    int tilesX = (WINDOWWIDTH / s_kBackgroundWidth);
    if (WINDOWWIDTH % s_kBackgroundWidth != 0)
        ++tilesX;   // add extra if it's short
    // count of tiles needed in height
    int tilesY = (WINDOWHEIGHT / s_kBackgroundHeight);
    if (WINDOWHEIGHT % s_kBackgroundHeight != 0)
        ++tilesY;   // add extra if it's short

    // runs loop size of tiles needed for width
    for (int x = 0; x < tilesX; ++x)
    {
        // runs loop size of tiles needed for height
        for (int y = 0; y < tilesY; ++y)
        {
            // Add tiles to vector
            tilePosition.m_x = x * s_kBackgroundWidth;
            tilePosition.m_y = y * s_kBackgroundHeight;
            m_vpBackgrounds.push_back(new ImageObject(tilePosition, s_kBackgroundWidth, s_kBackgroundHeight, BACKGROUND));
        }
    }
}

// Destory the elements in vector of GameObject
void GameDemo::DestoryGameObjects(std::vector<GameObject*> vector)
{
    for (auto& element : vector)
    {
        delete element;
    }
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
