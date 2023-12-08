#include "BossStage.h"

#include "ImageDirectory.h"
#include "Platformer.h"
#include "GameDemo.h"
#include "SoundDirectory.h"
#include "Bullet.h"

#include <assert.h>
#include <iomanip>

BossStage::BossStage(Platformer* pOwner, size_t fileIndex)
	:
    m_fileIndex(fileIndex),
	m_pOwner(pOwner),
	m_pInGameUI(nullptr),
    m_pBossUI(nullptr),
	m_pBackground(nullptr),
	m_pPlayer(nullptr),
	m_pTiledMap(nullptr)
{
	m_CurrentTime = 0.0;
}

BossStage::~BossStage()
{
}

void BossStage::Enter()
{
    assert(m_fileIndex < 4);

    Load(m_fileIndex);

    InitGame();
    m_pInGameUI->InitUI();
    m_pBossUI->InitUI();

    m_pOwner->SetBGMusic(BOSS_STAGE_SOUND);
}

void BossStage::Update(double deltaTime)
{
    if (m_loadingTime <= LOADINGTIME)
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
    {
        m_pInGameUI->UpdateUI(deltaTime);
        m_pBossUI->UpdateUI(deltaTime);
    }
}

void BossStage::Render(SDL_Renderer* pRenderer, Textures* pTextures)
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
            bullet->Render(pRenderer, pTextures->GetTexture(bullet->GetTextureName()));
        }

        for (auto& bullet : m_vpBossBullets)
        {
            bullet->Render(pRenderer, pTextures->GetTexture(bullet->GetTextureName()));
        }
        // Render Tiles
        m_pTiledMap->Render(pRenderer, pTextures);

        // Render Player
        m_pPlayer->Render(pRenderer, pTextures->GetTexture(m_pPlayer->GetTextureName()));

        // Render UI
        m_pInGameUI->Render(pRenderer, pTextures);

        m_pBossUI->Render(pRenderer, pTextures);
    }

}

bool BossStage::HandleEvent(SDL_Event* pEvent)
{
    if (m_loadingTime > LOADINGTIME)
    {

        // UI Button event
        if (m_isPause)
        {
            if (!m_pInGameUI->HandleEvent(pEvent))
                m_isPause = !m_isPause;

            if (!m_pBossUI->HandleEvent(pEvent))
                m_isPause = !m_isPause;
        }

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


bool BossStage::ProcessKeyboardEvent(SDL_KeyboardEvent* pData)
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
            m_isPause = !m_isPause;
            m_pInGameUI->TogglePause();
            m_pBossUI->TogglePause();
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
            m_pPlayer->TryMove(Vector2<double>{ LEFT });
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

bool BossStage::ProcessWindowEvent(SDL_WindowEvent* pData)
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

void BossStage::InitGame()
{
    // Set GameTime to 0sec
    m_CurrentTime = (double)0.0;

    m_loadingTime = (double)0.0;

    /// TILEMAP
    m_pTiledMap = new TiledMap(BOSSMAP);
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

    if (m_fileIndex == 0)
    {
                                /*-----------
                                    PLAYER
                                -----------*/

        objectTransform =
        {
            (int)200, // X position of collider box
            (int)100, // Y position of collider box
            (int)s_kPlayerStartingSize.m_x,      // Width of collider box
            (int)s_kPlayerStartingSize.m_y       // Height of collider box
        };

        CreateGameObject(objectTransform, (size_t)ObjectType::kPlayer, PLAYER_SPRITE, PLAYER_MAX_HEALTH);


                                    /*-----------
                                        BOSS
                                    -----------*/

            objectTransform =
        {
            (int)500, // X position of collider box
            (int)150, // Y position of collider box
            (int)300,      // Width of collider box
            (int)300       // Height of collider box
        };

        CreateGameObject(objectTransform, (size_t)ObjectType::kEnemy, BOSS, BOSS_MAX_HEALTH);


    }


    // UI
    m_pInGameUI = new InGameUI(this, m_pPlayer, m_pOwner->GetGame()->GetFonts(), m_pOwner->GetGame()->GetRenderer());
    m_pInGameUI->AddHealthBar(Vector2<double> {HEALTHBAR_POSITION}, Vector2<double> {HEALTBARH_SIZE_VECTOR2});

    m_pBossUI = new InGameUI(this, m_pBossEnemy, m_pOwner->GetGame()->GetFonts(), m_pOwner->GetGame()->GetRenderer());
    m_pBossUI->AddHealthBar(Vector2<double> {WINDOWHEIGHT / 2}, Vector2<double> {400, 80});

}

void BossStage::DestoryGameObjects()
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

    if (m_vpBossBullets.empty() != true)
    {
        for (auto& element : m_vpBossBullets)
            delete element;
    }

    delete m_pInGameUI;

    delete m_pBossUI;

    delete m_pBackground;

    // Destory texture when game ends.
    delete m_pTiledMap;
}

void BossStage::AddGameObject(GameObject* object)
{
    // add the gameobject to vector
    m_vpGameObjects.push_back(object);
}

void BossStage::CreateGameObject(const SDL_Rect& transform, size_t objectType, const char* spriteName, int health)
{

    switch (objectType)
    {
    case (size_t)ObjectType::kPlayer:
    {
        // create player
        m_pPlayer = new PlayerObject(transform, &m_collisionReferee, objectType);

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
        m_pBossEnemy = new AiStateMachineEnemyBoss(m_pPlayer, transform, &m_collisionReferee, BOSS, objectType, "Boss");
        m_pBossEnemy->SetTargetObject(m_pPlayer);
        m_pBossEnemy->SetHealth(health);

        m_pBossEnemy->SetCallBack("Attack", [this]()->void
            {
                SpawnBossBullet(m_pBossEnemy->GetRage(), m_pBossEnemy->GetTransform());
            });

        m_pBossEnemy->SetCallBack("Defeat", [this]()->void
            {
                m_pOwner->LoadScene(Platformer::SceneName::kVictory);
            });

        AddGameObject(m_pBossEnemy);

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
    default:
        break;
    }
}

bool BossStage::UpdateGamestate(double deltaTime)
{
    UpdateGameObjects(deltaTime);


    if (m_pPlayer->GetWinState())
    {
        if (m_pPlayer->GetStatus().m_health > 0)
        {
            m_pOwner->LoadScene(Platformer::SceneName::kVictory);
        }
        else
        {
            m_pOwner->LoadScene(Platformer::SceneName::kLoss);
        }
    }

    return false;
}

void BossStage::SpawnBullets()
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

void BossStage::SpawnBossBullet(bool isAutoLock, SDL_Rect spawnTransform)
{
    SDL_Rect startingTransform
    {
        spawnTransform.x,
        spawnTransform.y + (spawnTransform.h / 2),
        (int)BULLET_SIZE,
        (int)BULLET_SIZE
    };

    Bullet* newBullet = new Bullet(m_pBossEnemy, startingTransform, &m_collisionReferee, (size_t)ObjectType::kEnemeyBullet,m_pPlayer,isAutoLock);

    newBullet->TryMove();

    m_vpBossBullets.push_back(newBullet);
}

void BossStage::UpdateGameObjects(double deltaTime)
{
    // Update GameObjects
    std::vector<GameObject*>::iterator iter;
    
    m_pInGameUI->UpdateUI();
    m_pBossUI->UpdateUI();

    iter = m_vpGameObjects.begin();

    for (iter; iter < m_vpGameObjects.end(); ++iter)
    {
        if ((*iter)->GetActive())
        {
            (*iter)->Update(deltaTime);
        }
        else
        {
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
                delete* iter;
                iter = m_vpBullets.erase(iter);
                break;
            }
        }
    }

    // Boss Bullets
    iter = m_vpBossBullets.begin();
    for (iter; iter < m_vpBossBullets.end(); ++iter)
    {
        if ((*iter)->GetActive())
        {
            (*iter)->Update(deltaTime);
        }
        else
        {
            delete* iter;
            iter = m_vpBossBullets.erase(iter);
            break;
        }
    }

}

void BossStage::Exit()
{
    m_pTiledMap->Delete();
    DestoryGameObjects();
}


/*------------------------------------------
|	Attempts to save the data to disk.		|
|	Returns true if successful.				|
-------------------------------------------*/
bool BossStage::Save(size_t index)
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
bool BossStage::SaveDataIntoFiles(const char* folderName)
{
    std::string path;

    // Get data reference.
    SaveData* pSave = m_pOwner->GetSaveData();

    // save stage data to name
    pSave->Load(folderName, _SAVE_STAGE);

    /*-----------
        STAGE
    -----------*/

    // Get data file to save
    SaveData::Data& saveData = pSave->GetData();

    // Save the Stage 01
    saveData.m_stage = 2;

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

    transformData = m_pBossEnemy->GetTransform();

    strcpy_s(saveData.m_pSpriteName, m_pBossEnemy->GetTextureName());

    strcpy_s(saveData.m_pPlayerName, m_pBossEnemy->GetName());

    saveData.m_position.m_x = transformData.x;

    saveData.m_position.m_y = transformData.y;

    saveData.m_health = m_pBossEnemy->GetStatus().m_health;

    pSave->Save(folderName, _SAVE_BOSS);


    /*-----------------
        END ENEMIES
    -----------------*/

    m_pOwner->LoadScene(Platformer::SceneName::kMainMenu);

    return true;
}

/*=================
    Load Data
=================*/
bool BossStage::Load(size_t index)
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

bool BossStage::LoadDataFromFiles(const char* folderName)
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

    CreateGameObject(transformData, (size_t)ObjectType::kPlayer, PLAYER_SPRITE, loadData.m_health);

    m_pPlayer->GetStatus().m_name = loadData.m_pPlayerName;
    /*---------------
        END PLAYER
    ---------------*/


    /*-------------
        ENEMIES
    -------------*/

    // Enemy file name
    std::string path;

    size_t index = 1;

    isLoaded = pSave->Load(folderName, _SAVE_BOSS);


    transformData =
    {
        (int)500, // X position of collider box
        (int)150, // Y position of collider box
        (int)300,      // Width of collider box
        (int)300       // Height of collider box
    };

    CreateGameObject(transformData, (size_t)ObjectType::kEnemy, BOSS, loadData.m_health);


    /*-----------------
        END ENEMIES
    -----------------*/


    return isLoaded;
}
