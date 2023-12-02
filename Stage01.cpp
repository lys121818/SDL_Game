#include "Stage01.h"
#include "AiStateMachineEnemy.h"
#include "ImageDirectory.h"
#include "Platformer.h"
#include "GameDemo.h"
#include "SoundDirectory.h"
#include "Bullet.h"
#include "SaveData.h"

#include <iomanip>

Stage01::Stage01(Platformer* pOwner)
    :
    m_pOwner(pOwner),
    m_pInGameUI(nullptr),
    m_pBackground(nullptr),
    m_pPlayer(nullptr),
    m_pTiledMap(nullptr)
{
    m_CurrentTime = 0.0;

    // GameObject and Tiles Setting
}

Stage01::~Stage01()
{
}

void Stage01::Enter()
{
    // Get the save data reference
    SaveData* pSave = m_pOwner->GetSave();
    SaveData::Data& data = pSave->GetData();

    pSave->Load();
    // Check if it has been loaded.
    if (pSave->GetIsLoaded() == false)
    {
        // set default data
        std::cout << "Load Fail";
    }

    std::cout << "Player Position X: " << data.m_playerPosition.m_x << std::endl;
    std::cout << "Player Position Y: " << data.m_playerPosition.m_y << std::endl;

    //for (std::vector<Vector2<int>>::iterator iter = data.m_enemyPositions.begin(); iter < data.m_enemyPositions.end(); ++iter)
    //{
    //    int index = 0;
    //    std::cout << "Enemy Position X: " << (*iter).m_x << std::endl;
    //    std::cout << "Enemy Position Y: " << (*iter).m_y << std::endl;
    //    
    //    std::cout << "Sprite Name: " << data.m_enemySprite[index] << std::endl;
    //    ++index;
    //}
    // If it has not, we need to write some default data.


    InitGame();
    m_pOwner->SetBGMusic(GAMEPLAY_SOUND);
}

void Stage01::Update(double deltaTime)
{
    // current time
    m_CurrentTime += deltaTime;
    //if (m_CurrentTime < LOADINGTIME)
    //    std::cout << "Game Starts in " << std::setprecision(1) << (LOADINGTIME - m_CurrentTime) << std::endl;
    if (m_CurrentTime > LOADINGTIME)
    {
        UpdateGamestate(deltaTime);
        
    }

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

        for (auto& bullet : m_vpBullets)
        {
            bullet->Render(pRenderer,pTextures->GetTexture(bullet->GetTextureName()));
        }

        // Render Tiles
        m_pTiledMap->Render(pRenderer, pTextures);

        // Render Player
        m_pPlayer->Render(pRenderer, pTextures->GetTexture(m_pPlayer->GetTextureName()));

        // Render UI
        m_pInGameUI->Render(pRenderer, pTextures);
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
            case SDLK_x:
            {
                SpawnBullets();
                break;
            }
            // pasue
            case SDLK_p:
            {
                m_CurrentTime = 0.0;
                bool success = true;

                if (success)
                    std::cout << "[Stage01] Saved successfully" << std::endl;
                else
                    std::cout << "[Stage01] Failed to Save" << std::endl;

                break;
            }
                // Run
            case SDLK_LSHIFT:
            {
                m_pPlayer->SprintSpeed();
                break;
            }

            // Move Left
            case SDLK_LEFT:
            {
                m_pPlayer->TryMove(Vector2{ LEFT });
                break;
            }

            // Move Right
            case SDLK_RIGHT:
            {
                m_pPlayer->TryMove(Vector2<double>{ RIGHT });
                break;
            }


            // Jumping
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
            case SDLK_LEFT:
            {
                m_pPlayer->TryMove(Vector2<double>{ STOPLEFT });
                break;
            }
            // Stop Moving Right
            case SDLK_RIGHT:
            {
                m_pPlayer->TryMove(Vector2<double>{ STOPRIGHT });
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
    //m_vpBullets.reserve(s_kMaxBulletCount);

    // Temperary gameobject
    GameObject* stationary;
    // Set GameTime to 0sec
    m_CurrentTime = (double)0.0;

    /// TILEMAP
    m_pTiledMap = new TiledMap(TILEMAP);
    m_pTiledMap->Init(&m_collisionReferee);

    /// GAMEOBJECT

    Vector2<double> position;
    Vector2<double> size;

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
    m_pPlayer->SetNameTag(
        m_pOwner->GetGame()->GetFonts()->GetFont(ARIAL),
        SDL_Color(BLACK),
        m_pOwner->GetGame()->GetRenderer()
    );
    
    // Add GameObjects to m_vpGameObjects
    SDL_Rect objectTransform;
    objectTransform.w = (int)ENEMY_WIDTH;
    objectTransform.h = (int)ENEMY_HEIGHT;

    // Setting starting position of the enemy
    objectTransform.x = 100;
    objectTransform.y = 50;
    stationary = new AiStateMachineEnemy(m_pPlayer, objectTransform, &m_collisionReferee, ZOMBIEFEMALE, (size_t)ObjectType::kEnemy, "Zombie_Female");
    stationary->SetTargetObject(m_pPlayer);
    AddGameObject(stationary);

    objectTransform.x = 650; // X
    objectTransform.y = 50; // Y
    stationary = new AiStateMachineEnemy(m_pPlayer, objectTransform, &m_collisionReferee, ZOMBIEMALE, (size_t)ObjectType::kEnemy, "Zombie_Male");
    stationary->SetTargetObject(m_pPlayer);
    AddGameObject(stationary);

    m_pInGameUI = new InGameUI(m_pPlayer, m_pOwner->GetGame()->GetFonts(),m_pOwner->GetGame()->GetRenderer());
    m_pInGameUI->AddHealthBar(Vector2<double> {HEALTHBAR_POSITION}, Vector2<double> {HEALTBARH_SIZE_VECTOR2});

    m_pPlayer->SetTriggerFunction(HEALTHBAR_UI_FUNCTION, [this]()->void
        {
            m_pInGameUI->UpdateUI();
        });

    AddGameObject(m_pPlayer);

}

// Destory the elements in vector of GameObject
void Stage01::DestoryGameObjects()
{
    for (auto& element : m_vpGameObjects)
    {
        delete element;
    }
    
    if (m_vpBullets.empty() != true)
    {
        for (auto& element : m_vpBullets)
            delete element;
    }

    delete m_pInGameUI;

    delete m_pBackground;

    // Destory texture when game ends.
    delete m_pTiledMap;
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

bool Stage01::UpdateGamestate(double deltaTime)
{
    UpdateGameObjects(deltaTime);


    if (m_pPlayer->GetWinState())
    {
        if (m_pPlayer->GetStatus().m_health > 0)
        {
            m_pOwner->LoadScene(Platformer::SceneName::kBoss);
        }
        else
        {
            m_pOwner->LoadScene(Platformer::SceneName::kLoss);
        }
    }

    return false;
}

void Stage01::SpawnBullets()
{
    if (m_vpBullets.size() >= s_kMaxBulletCount)
        return;

    SDL_Rect playerTransform = m_pPlayer->GetTransform();



    // moving right
    if (m_pPlayer->GetStatus().m_isRight)
    {
        SDL_Rect startingTransform
        {
            playerTransform.x + (playerTransform.w),
            playerTransform.y + (playerTransform.h / 2),
            (int)BULLET_SIZE,
            (int)BULLET_SIZE
        };
        Bullet* newBullet = new Bullet(m_pPlayer, startingTransform, &m_collisionReferee, (size_t)ObjectType::kPlayerBullet);

        newBullet->TryMove(Vector2<double>{RIGHT});

        m_vpBullets.push_back(newBullet);
    }
    // moving left
    else
    {
        SDL_Rect startingTransform
        {
            playerTransform.x - (playerTransform.w / 2) ,
            playerTransform.y + (playerTransform.h / 2),
            (int)BULLET_SIZE,
            (int)BULLET_SIZE
        };

        Bullet* newBullet = new Bullet(m_pPlayer, startingTransform, &m_collisionReferee, (size_t)ObjectType::kPlayerBullet);

        newBullet->TryMove(Vector2<double>{LEFT});

        m_vpBullets.push_back(newBullet);
    }



}

void Stage01::UpdateGameObjects(double deltaTime)
{
    // Update GameObjects
    std::vector<GameObject*>::iterator iter;

    iter = m_vpGameObjects.begin();

    for (iter; iter < m_vpGameObjects.end(); ++iter)
    {
        if ((*iter)->GetActive())
        {
            (*iter)->Update(deltaTime);
        }
        else
        {
            if ((*iter)->GetStatus().m_type == (size_t)ObjectType::kEnemy)
                --m_enemyCount;
            delete* iter;
            iter = m_vpGameObjects.erase(iter);
            break;
        }
    }

    // Bullets
    if (m_vpBullets.size() > 0)
    {
        iter = m_vpBullets.begin();
        for (iter; iter < m_vpBullets.end(); ++iter)
        {
            if ((*iter)->GetActive())
            {
                (*iter)->Update(deltaTime);
            }
            else
            {
                delete *iter;
                iter = m_vpBullets.erase(iter);
                break;
            }
        }
    }


    if (m_pPlayer->GetActive() == false)
        delete m_pPlayer;

}

void Stage01::Exit()
{
    // Delete the vectors I've created
    {
        m_pTiledMap->Delete();
        DestoryGameObjects();
    }


}

/*------------------------------------------
|	Attempts to save the data to disk.		|
|	Returns true if successful.				|
-------------------------------------------*/
bool Stage01::Save()
{
    // Get data reference.
    SaveData* pSave = m_pOwner->GetSave();
    SaveData::Data& saveData = pSave->GetData();

    // Update the value that we want to save
    saveData.m_playerPosition.m_x = m_pPlayer->GetTransform().x;
    saveData.m_playerPosition.m_y = m_pPlayer->GetTransform().y;

    // Save Enemies
    for (auto& object : m_vpGameObjects)
    {
        // Save enemies position
        if (object->GetStatus().m_type == (size_t)ObjectType::kEnemy)
        {
            Vector2<int> position{ object->GetTransform().x,object->GetTransform().y };
            saveData.m_enemyPositions.push_back(position);
            saveData.m_enemySprite.push_back(object->GetTextureName());
        }
    }


    // Perform the save operation.


    return pSave->Save();
}
