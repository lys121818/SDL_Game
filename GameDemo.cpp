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
        m_vpBackgrounds.clear();
        m_vpGameObjects.clear();
    }
    // Destory texture when game ends.
    for (auto iter = m_mpTextures.begin(); iter != m_mpTextures.end(); ++iter)
    {
        SDL_DestroyTexture(iter->second);
    }

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
        switch (evt.type)
        {
        // KeyBoard Event
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (ProcessKeyboardEvent(&evt.key) == true)
                return true;
            break;

        // Mouse Event
        // Quit when true returns
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            if (ProcessMouseEvent(&evt.button) == true)
                return true;
            break;

        default:
            // Window Event
            if (ProcessWindowEvent(&evt.window) == true)
                return true;
            break;
        }
    }
    return false;
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
    }
    // Update Player Object
    m_pPlayer->Update(deltatime);
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
            element->Render(m_pRenderer, m_mpTextures[element->GetName()]);
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
            element->Render(m_pRenderer, m_mpTextures[element->GetName()]);
        }
    }
    
    //Render Player Object
    if (m_pPlayer->GetTransform().x >= (0 - m_pPlayer->GetTransform().w) &&
        m_pPlayer->GetTransform().x < WINDOWWIDTH &&   // Window width
        m_pPlayer->GetTransform().y >= (0 - m_pPlayer->GetTransform().h) &&
        m_pPlayer->GetTransform().y < WINDOWHEIGHT)    // Window height
    {
        m_pPlayer->Render(m_pRenderer, m_mpTextures[m_pPlayer->GetName()]);
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

            // Shooting
            case SDLK_SPACE:
            {
                // shooting objects when hit spacebar
                //GameObject* bullet = new Bullet(m_pPlayer->GetPosition(), BULLET);
                //AddGameObject(bullet);
                m_pPlayer->GetAnimationComponent()->PlayAnimation("jump");
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
        switch (pData->button)
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
    switch (pData->event)
    {
        // Quit when Window X button is pressed
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

    // Load images that are being use in the game.
    PreLoadImages();
    // Add Background to vector m_vpGameObjects
    InitBackground();

    // Set Player Object
    m_pPlayer = new CubeColider(s_kPlayerStartingPoisition,PLAYER,m_pRenderer);

    // Add GameObjects to m_vpGameObjects
    stationary = new ImageObject(Vector2{ 600,50 }, 50, 50, STATIONARY1);
    AddGameObject(stationary);

    stationary = new ImageObject(Vector2{ 50,500 }, 50, 50, STATIONARY2);
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

// Add all the images that are being load in the game
void GameDemo::PreLoadImages()
{
    // Simple adding by using directory of the image
    AddImagesToTexture(BACKGROUND);
    AddImagesToTexture(PLAYER);
    AddImagesToTexture(BULLET);
    AddImagesToTexture(STATIONARY1);
    AddImagesToTexture(STATIONARY2);
}

// Get directory of image from parameter
void GameDemo::AddImagesToTexture(const char* image)
{
    std::pair<const char*, SDL_Texture*> imageTexture;  //Pair to pass inform to m_mpTextures
    // Add directory of image as key of texture
    imageTexture.first = image;

    // Load image
    SDL_Surface* pImageSurface = IMG_Load(imageTexture.first);

    // Error when it fails to load the image
    if (pImageSurface == nullptr)
    {
        std::cout << "Image loading failed Error: " << SDL_GetError() << std::endl;
    }
    // SDL_Surface -> SDL_Texture
    // Create texture from surface and save in pair
    imageTexture.second = SDL_CreateTextureFromSurface(m_pRenderer, pImageSurface);

    // Error when it fails to load the texture
    if (imageTexture.second == nullptr)
    {
        std::cout << "Texture loading failed Error: " << SDL_GetError();
    }
    // add to mpTextures when image and texture loading is successfully done
    m_mpTextures.insert(imageTexture);
    // Free surface from memory as it's no longer needed.
    SDL_FreeSurface(pImageSurface);

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
