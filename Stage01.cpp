#include "Stage01.h"
#include "EnemyObject.h"
#include "ImageDirectory.h"
#include "Platformer.h"
#include <iomanip>

Stage01::Stage01(Platformer* pOwner)
    :
    m_pOwner(pOwner),
    m_UIController(nullptr)
{
    m_CurrentTime = 0.0;

    // GameObject and Tiles Setting
    InitGame();
}

Stage01::~Stage01()
{
}

void Stage01::Enter()
{

}

void Stage01::Update(double deltaTime)
{
    // current time
    m_CurrentTime += deltaTime;
    if (m_CurrentTime < LOADINGTIME)
        std::cout << "Game Starts in " << std::setprecision(1) << (LOADINGTIME - m_CurrentTime) << std::endl;
    else if (m_CurrentTime > LOADINGTIME)
    {
        // Update GameObjects
        for (auto& element : m_vpGameObjects)
        {
            element->Update(deltaTime);
        }
        m_UIController->Update();
    }
    UpdateGamestate();
}

// Rendering any objects in the game.
void Stage01::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
    m_pBackground->Render(pRenderer, pTextures->GetTexture(m_pBackground->GetTextureName()));

    // loading 
    if (m_CurrentTime > LOADINGTIME)
    {
        //Render GameObjects
        for (auto& element : m_vpGameObjects)
        {
            // Only render inside the window size (on visible)
            if (element->GetTransform().x >= (0 - element->GetTransform().w) &&
                element->GetTransform().x < WINDOWWIDTH &&   // Window width
                element->GetTransform().y >= (0 - element->GetTransform().h) &&
                element->GetTransform().y < WINDOWHEIGHT)    // Window height
            {
                element->Render(pRenderer, pTextures->GetTexture(element->GetTextureName()));
            }
        }

        m_pTiledMap->Render(pRenderer, pTextures);
        m_UIController->Render(pRenderer, pTextures);
    }
    

}

bool Stage01::HandleEvent(SDL_Event* pEvent)
{
    // Check if the game is over

    switch ((int)pEvent->type)
    {
        // KeyBoard Event
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {


            if (ProcessKeyboardEvent(&pEvent->key) == true)
            {
                return true;
            }
            break;
        }

        // Mouse Event
        // Quit when true returns
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            if (ProcessMouseEvent(&pEvent->button) == true)
                return true;
            break;
        }

        // Window Event
        case SDL_WINDOWEVENT:
        {
            if (ProcessWindowEvent(&pEvent->window) == true)
                return true;
            break;
        }
    default:
        break;
    }

	return false;
}


// Every events using keyboards works here
bool Stage01::ProcessKeyboardEvent(SDL_KeyboardEvent* pData)
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
            m_pPlayer->TryMove(Vector2{ LEFT });
            break;
        }

        // Move Right
        case SDLK_d:
        {
            m_pPlayer->TryMove(Vector2{ RIGHT });
            break;
        }

        // Move Up
        case SDLK_w:
        {
            m_pPlayer->TryMove(Vector2{ UP });
            break;
        }

        // Move Down
        case SDLK_s:
        {
            m_pPlayer->TryMove(Vector2{ DOWN });
            break;
        }

        // Shooting
        case SDLK_SPACE:
        {
            m_pPlayer->SetJump();
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
            m_pPlayer->TryMove(Vector2{ STOPLEFT });
            break;
        }

        // Stop Moving Right
        case SDLK_d:
        {
            m_pPlayer->TryMove(Vector2{ STOPRIGHT });
            break;
        }

        // Stop Moving Up
        case SDLK_w:
        {
            m_pPlayer->TryMove(Vector2{ STOPUP });
            break;
        }

        // Stop Moving Down
        case SDLK_s:
        {
            m_pPlayer->TryMove(Vector2{ STOPDOWN });
            break;

        }
        default:
            break;
        }
    }
    return false;
}
// Every events using mouse works here
bool Stage01::ProcessMouseEvent(SDL_MouseButtonEvent* pData)
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
bool Stage01::ProcessWindowEvent(SDL_WindowEvent* pData)
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



void Stage01::InitGame()
{

    // Temperary gameobject
    GameObject* stationary;
    // Set GameTime to 0sec
    m_CurrentTime = (double)0.0;

    /// TILEMAP
    m_pTiledMap = new TiledMap(TILEMAP);
    m_pTiledMap->Init(&m_collisionReferee);

    /// GAMEOBJECT

    Vector2 position;
    Vector2 size;

    position.m_x = 0;
    position.m_y = 0;
    size.m_x = WINDOWWIDTH;
    size.m_y = WINDOWHEIGHT;

    m_pBackground = new ImageObject(position,size, nullptr, BACKGROUND, 0, (size_t)ObjectType::kBackGround, "BackGround");


    // Set Player Object
    // Player ColliderBox Setting
    SDL_Rect playerTransform{
        (int)s_kPlayerStartingPoisition.m_x, // X position of collider box
        (int)s_kPlayerStartingPoisition.m_y, // Y position of collider box
        (int)s_kPlayerStartingSize.m_x,      // Width of collider box
        (int)s_kPlayerStartingSize.m_y       // Height of collider box
    };

    m_pPlayer = new PlayerObject(playerTransform, &m_collisionReferee, (size_t)ObjectType::kPlayer);
    AddGameObject(m_pPlayer);

    // Add GameObjects to m_vpGameObjects
    SDL_Rect objectTransform;
    objectTransform.w = (int)ENEMYWIDTH;
    objectTransform.h = (int)ENEMYHEIGHT;

    // Setting starting position of the enemy
    objectTransform.x = 100;
    objectTransform.y = 50;
    stationary = new EnemyObject(objectTransform, &m_collisionReferee, ZOMBIEFEMALE, (size_t)ObjectType::kEnemy, "Zombie_Female");
    AddGameObject(stationary);

    objectTransform.x = 650; // X
    objectTransform.y = 50; // Y
    stationary = new EnemyObject(objectTransform, &m_collisionReferee, ZOMBIEMALE, (size_t)ObjectType::kEnemy, "Zombie_Male");
    AddGameObject(stationary);

    m_UIController = new UIController(this, m_pPlayer);
    m_UIController->InitUI();

}

// Destory the elements in vector of GameObject
void Stage01::DestoryGameObjects(std::vector<GameObject*> vector)
{
    for (auto& element : vector)
    {
        delete element;
    }
}

// Add gameobject to vector
void Stage01::AddGameObject(GameObject* object)
{
    // Creates the Object only if it's under amount of s_kMaxGameObjectCount
    if (m_vpGameObjects.size() >= s_kMaxGameObjectCount)
        return;
    // add the gameobject to vector
    m_vpGameObjects.push_back(object);
}

bool Stage01::UpdateGamestate()
{
    if (m_pPlayer->GetWinState())
    {
        if (m_pPlayer->GetStatus().m_health > 0)
        {
            m_pOwner->LoadScene(Platformer::SceneName::kVictory);
        }
        else
        {
            m_pOwner->LoadScene(Platformer::SceneName::kDead);
        }
    }

    return false;
}

void Stage01::Exit()
{
    // Delete the vectors I've created
    {
        m_pTiledMap->Delete();
        DestoryGameObjects(m_vpGameObjects);
    }

    delete m_pBackground;
    // Destory texture when game ends.
    delete m_pTiledMap;
}
