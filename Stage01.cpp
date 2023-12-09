#include "Stage01.h"
#include "AiStateMachineEnemy.h"
#include "ImageDirectory.h"
#include "SaveFileDirectory.h"
#include "Platformer.h"
#include "GameDemo.h"
#include "SoundDirectory.h"
#include "Bullet.h"
#include "SaveData.h"
#include "ParticleSystem.h"
#include <assert.h>


#include <iomanip>

Stage01::Stage01(Platformer* pOwner, size_t fileIndex)
    :
    m_fileIndex(fileIndex),
    m_pOwner(pOwner),
    m_pInGameUI(nullptr),
    m_pBackground(nullptr),
    m_pPlayer(nullptr),
    m_pTiledMap(nullptr),
    m_isPause(false)
{
    m_CurrentTime = 0.0;
    m_loadingTime = 0.0;
    m_saves = 0;
}

Stage01::~Stage01()
{
}

void Stage01::Enter()
{
    assert(m_fileIndex < 4);

    Load(m_fileIndex);

    InitGame();
    m_pInGameUI->InitUI();
    m_pOwner->SetBGMusic(GAMEPLAY_SOUND);

}

void Stage01::Update(double deltaTime)
{
    if(m_loadingTime <= LOADINGTIME)
        m_loadingTime += deltaTime;

    if (m_loadingTime > LOADINGTIME && !m_isPause)
    {
        // current time
        if (m_isPause == false)
            m_CurrentTime += deltaTime;

        std::cout << "My Saved Times: " << m_saves << std::endl;

        std::cout << m_CurrentTime << std::endl;

        UpdateGamestate(deltaTime);
    }
    if (m_isPause)
        m_pInGameUI->UpdateUI(deltaTime);
}

// Rendering any objects in the game.
void Stage01::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
    m_pBackground->Render(pRenderer, pTextures->GetTexture(m_pBackground->GetTextureName()));

    // loading 
    if (m_loadingTime > LOADINGTIME)
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
    // UI Button event
    if (m_isPause)
    {
        if (!m_pInGameUI->HandleEvent(pEvent))
            m_isPause = !m_isPause;

    }
    if (m_loadingTime > LOADINGTIME)
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
            // togle pasue
            case SDLK_p:
            {
                m_isPause = !m_isPause;
                m_pInGameUI->TogglePause();
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
    // reserve with max bulletCount
    m_vpBullets.reserve(s_kMaxBulletCount);

    // Set loading to 0sec
    m_loadingTime = 0.0;

    /// TILEMAP
    m_pTiledMap = new TiledMap(TILEMAP);
    m_pTiledMap->Init(&m_collisionReferee);

    /// GAMEOBJECT

    // transform info
    SDL_Rect objectTransform;

                        /*---------------
                            BACKGROUND
                        ---------------*/
    objectTransform =
    {
        0,
        0,
        WINDOWWIDTH,
        WINDOWHEIGHT
    };

    CreateGameObject(objectTransform, (size_t)ObjectType::kBackGround, BACKGROUND);

    // new file
    if (m_fileIndex == 0)
    {
                            /*-----------
                                PLAYER
                            -----------*/

        objectTransform =
        {
            (int)s_kPlayerStartingPoisition.m_x, // X position of collider box
            (int)s_kPlayerStartingPoisition.m_y, // Y position of collider box
            (int)s_kPlayerStartingSize.m_x,      // Width of collider box
            (int)s_kPlayerStartingSize.m_y       // Height of collider box
        };
    
        CreateGameObject(objectTransform, (size_t)ObjectType::kPlayer, PLAYER_SPRITE, PLAYER_MAX_HEALTH);


                            /*-------------
                                ENEMIES
                            -------------*/

        objectTransform =
        {
            (int)100,               // X position of collider box
            (int)50,                // Y position of collider box
            (int)ENEMY_WIDTH,       // Width of collider box
            (int)ENEMY_HEIGHT       // Height of collider box
        };

        CreateGameObject(objectTransform, (size_t)ObjectType::kEnemy, ZOMBIEMALE, 100);

        objectTransform =
        {
            (int)650,               // X position of collider box
            (int)50,                // Y position of collider box
            (int)ENEMY_WIDTH,       // Width of collider box
            (int)ENEMY_HEIGHT       // Height of collider box
        };

        CreateGameObject(objectTransform, (size_t)ObjectType::kEnemy, ZOMBIEFEMALE, 100);

    }

    // ParticleSystem* particle = new ParticleSystem(Vector2<float>{200, 200}, 50, 20, 30, false);
    // AddGameObject(particle);
                        /*-----------
                             U I
                        -----------*/

    m_pInGameUI = new InGameUI(this, m_pPlayer, m_pOwner->GetGame()->GetFonts(),m_pOwner->GetGame()->GetRenderer());
    m_pInGameUI->AddHealthBar(Vector2<double> {HEALTHBAR_POSITION}, Vector2<double> {HEALTBARH_SIZE_VECTOR2});
    m_pInGameUI->UpdateUI();

    m_pPlayer->SetTriggerFunction(HEALTHBAR_UI_FUNCTION, [this]()->void
        {
            m_pInGameUI->UpdateUI();
        });


    ParticleSystem* particle;
    particle = new ParticleSystem(Vector2<float>{400, 400}, 300, 50, 100, true);
    AddGameObject(particle);
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

void Stage01::CreateGameObject(const SDL_Rect& transform, size_t objectType, const char* pSpriteName, int health, const char* pPlayerName)
{


    switch (objectType)
    {
            case (size_t)ObjectType::kPlayer:
            {
                // create player
                m_pPlayer = new PlayerObject(transform, &m_collisionReferee, objectType, pSpriteName, pPlayerName);

                // name under player
                m_pPlayer->SetNameTag(
                    m_pOwner->GetGame()->GetFonts()->GetFont(ARIAL),
                    SDL_Color(BLACK),
                    m_pOwner->GetGame()->GetRenderer()
                );


                m_pPlayer->SetHealth(health);

                // add to vector
                AddGameObject(m_pPlayer);

                break;
            }
            case (size_t)ObjectType::kEnemy:
            {
                GameObject* enemyObject;

                if (std::string(pSpriteName).compare(ZOMBIEFEMALE) == 0)
                {
                    enemyObject = new AiStateMachineEnemy(m_pPlayer, transform, &m_collisionReferee, ZOMBIEFEMALE, objectType, "Zombie_Female");
                    enemyObject->SetTargetObject(m_pPlayer);
                    enemyObject->SetHealth(health);
                    AddGameObject(enemyObject);
                }
                else if (std::string(pSpriteName).compare(ZOMBIEMALE) == 0)
                {
                    enemyObject = new AiStateMachineEnemy(m_pPlayer, transform, &m_collisionReferee, ZOMBIEMALE,objectType, "Zombie_Male");
                    enemyObject->SetTargetObject(m_pPlayer);
                    enemyObject->SetHealth(health);
                    AddGameObject(enemyObject);
                }

                break;
            }
            case (size_t)ObjectType::kBackGround:
            {
                Vector2<double> position;
                Vector2<double> size;

                position.m_x = (double)transform.x;
                position.m_y = (double)transform.y;

                size.m_x = (double)transform.w;
                size.m_y = (double)transform.h;

                m_pBackground = new ImageObject(position, size, nullptr, BACKGROUND, 0, objectType, "BackGround");
                break;
            }
            case (size_t)ObjectType::kPlayerBullet:
            {
                Bullet* newBullet = new Bullet(m_pPlayer, transform, &m_collisionReferee, (size_t)ObjectType::kPlayerBullet);

                if(m_pPlayer->GetStatus().m_isRight)
                    newBullet->TryMove(Vector2<double>{RIGHT});
                else
                    newBullet->TryMove(Vector2<double>{LEFT});

                newBullet->SetCallback([this](size_t type, Vector2<float> position)->void 
                    {

                        SDL_Color color;
                        switch (type)
                        {
                            case (size_t)ObjectType::kEnemy:
                            case (size_t)ObjectType::kPlayer:
                            {
                                color = { RED };
                                break;
                            }
                            case (size_t)ObjectType::kWall:
                            {
                                color = { GRAY };
                                break;
                            }
                            default:
                                color = { BLACK };
                                break;
                        }

                        AddParticleEffect(position, 1, 50, 20, 30, false, nullptr, color);

                    });

                m_vpBullets.push_back(newBullet);

                break;
            }
        default:
            break;
    }
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

    SDL_Rect startingTransform;

    // moving right
    if (m_pPlayer->GetStatus().m_isRight)
    {
        startingTransform =
        {
            playerTransform.x + (playerTransform.w),
            playerTransform.y + (playerTransform.h / 2),
            (int)BULLET_SIZE,
            (int)BULLET_SIZE
        };
    }
    else
    {
        startingTransform =
        {
            playerTransform.x - (playerTransform.w / 2) ,
            playerTransform.y + (playerTransform.h / 2),
            (int)BULLET_SIZE,
            (int)BULLET_SIZE
        };
    }
    CreateGameObject(startingTransform, (size_t)ObjectType::kPlayerBullet, BULLET);

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
bool Stage01::Save(size_t index)
{
    // check for save has been successfully done
    bool isSaved = false;

    switch (index)
    {
        // Save file 01
        case 1:
        {
            isSaved = SaveDataIntoFiles(_SAVE_FOLDER_1);
            break;
        }
        // Save file 02
        case 2:
        {
            isSaved = SaveDataIntoFiles(_SAVE_FOLDER_2);
            break;
        }
        // Save file 03
        case 3:
        {
            isSaved = SaveDataIntoFiles(_SAVE_FOLDER_3);
            break;
        }
    default:
        break;
    }

    std::cout << "SAVE COMPLETE IN " << index << std::endl;

    return isSaved;
}

/*=================
    Save Data
=================*/
bool Stage01::SaveDataIntoFiles(const char* folderName)
{
    std::string path;

    // Get data reference.
    SaveData* pSave = m_pOwner->GetSaveData();

    // save stage data to name
    pSave->Load(folderName,_SAVE_STAGE);

                /*-----------
                    STAGE
                -----------*/

    // Get data file to save
    SaveData::Data& saveData = pSave->GetData();

    // Save the Stage 01
    saveData.m_stage = 1;

    saveData.m_playTime = m_CurrentTime;

    saveData.m_saves = ++m_saves;

    // Player file load and save
    pSave->Save(folderName, _SAVE_STAGE);


                /*---------------
                    END STAGE 
                ---------------*/

                /*-----------
                    PLAYER
                -----------*/

    SDL_Rect transformData = m_pPlayer->GetTransform();

    strcpy_s(saveData.m_pSpriteName, m_pPlayer->GetTextureName());

    strcpy_s(saveData.m_pPlayerName, m_pPlayer->GetName());

    saveData.m_position.m_x = transformData.x;

    saveData.m_position.m_y = transformData.y;

    saveData.m_health = m_pPlayer->GetStatus().m_health;

    pSave->Save(folderName, _SAVE_PLAYER);


                /*---------------
                    END PLAYER
                ---------------*/

                /*-------------
                    ENEMIES
                -------------*/

    size_t index = 1;
    for (auto& object : m_vpGameObjects)
    {
        // Save existing enemies
        if (object->GetStatus().m_type == (size_t)ObjectType::kEnemy)
        {
            transformData = object->GetTransform();

            strcpy_s(saveData.m_pSpriteName, object->GetTextureName());

            saveData.m_position.m_x = transformData.x;
            saveData.m_position.m_y = transformData.y;

            saveData.m_health = object->GetStatus().m_health;

            // name of the enemy file
            path = std::string("/enemy_0") + std::to_string(index) + std::string(".save");

            pSave->Save(folderName, path.c_str());
            ++index;

        }
    }

    // Set dead enemies health to 0
    if (index <= 3)
    {
        for (index; index < 4; ++index)
        {
            saveData.m_health = 0;
            strcpy_s(saveData.m_pSpriteName, "NULL");
            saveData.m_position = { 0,0 };
            path = std::string("/enemy_0") + std::to_string(index) + std::string(".save");
            pSave->Save(folderName, path.c_str());

        }
    }

                    /*-----------------
                        END ENEMIES
                    -----------------*/
    
    m_pOwner->LoadScene(Platformer::SceneName::kMainMenu);

    return true;
}

/*=================
    Load Data
=================*/
bool Stage01::Load(size_t index)
{
    bool isLoad = false;

    switch (index)
    {
        // No load file
        case 0:
        {
            isLoad = false;
            break;
        }

        // Load file 1
        case 1:
        {
            isLoad = LoadDataFromFiles(_SAVE_FOLDER_1);
            assert(isLoad);
            break;
        }
        // Load file 2
        case 2:
        {
            isLoad = LoadDataFromFiles(_SAVE_FOLDER_2);
            assert(isLoad);
            break;
        }
        // Load file 3
        case 3:
        {
            isLoad = LoadDataFromFiles(_SAVE_FOLDER_3);
            assert(isLoad);
            break;
        }

    default:
        break;
    }

    // can't be unloaded with valid index
    

    return isLoad;
}

bool Stage01::LoadDataFromFiles(const char* folderName)
{
    bool isLoaded = false;

    // Get the save data reference
    SaveData* pSave = m_pOwner->GetSaveData();

    isLoaded = pSave->Load(folderName, _SAVE_PLAYER);
    assert(isLoaded);

    SaveData::Data& loadData = pSave->GetData();


    m_CurrentTime = loadData.m_playTime;
    m_saves = loadData.m_saves;

                /*-----------
                    PLAYER
                -----------*/

    // Transform
    SDL_Rect transformData =
    {
        (int)loadData.m_position.m_x,
        (int)loadData.m_position.m_y,
        (int)PLAYER_WIDTH,
        (int)PLAYER_HEIGHT
    };

    CreateGameObject(transformData, (size_t)ObjectType::kPlayer, PLAYER_SPRITE, loadData.m_health, loadData.m_pPlayerName);

                /*---------------
                    END PLAYER
                ---------------*/


                /*-------------
                    ENEMIES
                -------------*/

    // Enemy file name
    std::string path;

    size_t index = 1;

    for (index; index < 4; ++index)
    {
        path = std::string("/enemy_0") + std::to_string(index) + std::string(".save");

        // Save existing enemies
        isLoaded = pSave->Load(folderName, path.c_str());

        // if enemy does not exist anymore
        if (loadData.m_health <= 0)
            break;

        transformData =
        {
            (int)loadData.m_position.m_x,
            (int)loadData.m_position.m_y,
            (int)ENEMY_WIDTH,
            (int)ENEMY_HEIGHT
        };

        std::cout << loadData.m_pSpriteName << std::endl;

        CreateGameObject(transformData, (size_t)ObjectType::kEnemy, loadData.m_pSpriteName, loadData.m_health);


    }

                /*-----------------
                    END ENEMIES
                -----------------*/


    return isLoaded;
}

void Stage01::AddParticleEffect(Vector2<float> position, int size, int particleCount, float particleSpeed, float radious, bool loop, const char* textureName, SDL_Color color)
{
    ParticleSystem* particleEffect = new ParticleSystem(position, particleCount, particleSpeed, radious, loop);

    if (textureName != nullptr)
        particleEffect->SetTextureName(textureName);
    else
        particleEffect->SetColor(color);

    particleEffect->SetSize(size);

    AddGameObject(particleEffect);
}
