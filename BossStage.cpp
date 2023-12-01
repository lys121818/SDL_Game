#include "BossStage.h"

#include "ImageDirectory.h"
#include "Platformer.h"
#include "GameDemo.h"
#include "SoundDirectory.h"
#include "Bullet.h"

#include <iomanip>

BossStage::BossStage(Platformer* pOwner)
	:
	m_pOwner(pOwner),
	m_pInGameUI(nullptr),
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
	InitGame();
}

void BossStage::Update(double deltaTime)
{
	m_CurrentTime += deltaTime;
	if (m_CurrentTime < LOADINGTIME)
		std::cout << "Game Starts in " << std::setprecision(1) << (LOADINGTIME - m_CurrentTime) << std::endl;
	else if (m_CurrentTime > LOADINGTIME)
	{
		UpdateGamestate(deltaTime);
	}
}

void BossStage::Render(SDL_Renderer* pRenderer, Textures* pTextures)
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
    }

}

bool BossStage::HandleEvent(SDL_Event* pEvent)
{
    if (m_CurrentTime > LOADINGTIME)
    {
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

    /// TILEMAP
    m_pTiledMap = new TiledMap(BOSSMAP);
    m_pTiledMap->Init(&m_collisionReferee);

    /// GAMEOBJECT

    Vector2<double> position;
    Vector2<double> size;

    position.m_x = 0;
    position.m_y = 0;
    size.m_x = WINDOWWIDTH;
    size.m_y = WINDOWHEIGHT;

    m_pBackground = new ImageObject(position, size, nullptr, BACKGROUND, 0, (size_t)ObjectType::kBackGround, "BackGround");


    // Set Player Object
    // Player ColliderBox Setting
    SDL_Rect playerTransform{
        (int)200, // X position of collider box
        (int)100, // Y position of collider box
        (int)s_kPlayerStartingSize.m_x,      // Width of collider box
        (int)s_kPlayerStartingSize.m_y       // Height of collider box
    };

    m_pPlayer = new PlayerObject(playerTransform, &m_collisionReferee, (size_t)ObjectType::kPlayer);
    m_pPlayer->SetNameTag(
        m_pOwner->GetGame()->GetFonts()->GetFont(ARIAL),
        SDL_Color(BLACK),
        m_pOwner->GetGame()->GetRenderer()
    );

    AddGameObject(m_pPlayer);


    // Add GameObjects to m_vpGameObjects
    SDL_Rect objectTransform;
    objectTransform.w = (int)300;
    objectTransform.h = (int)300;

    // Setting starting position of the enemy
    objectTransform.x = 500;
    objectTransform.y = 150;
    m_pBossEnemy = new AiStateMachineEnemyBoss(m_pPlayer, objectTransform, &m_collisionReferee, BOSS, (size_t)ObjectType::kEnemy, "Boss");
    m_pBossEnemy->SetTargetObject(m_pPlayer);
    AddGameObject(m_pBossEnemy);

    m_pBossEnemy->SetCallBack([this]()->void
        {
            SpawnBossBullet(m_pBossEnemy->GetRage(), m_pBossEnemy->GetTransform());
        });

    // UI
    m_pInGameUI = new InGameUI(m_pPlayer, m_pOwner->GetGame()->GetFonts(), m_pOwner->GetGame()->GetRenderer());
    m_pInGameUI->InitUI();
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
        for (auto& element : m_vpBullets)
            delete element;
    }

    delete m_pInGameUI;

    delete m_pBackground;

    // Destory texture when game ends.
    delete m_pTiledMap;
}

void BossStage::AddGameObject(GameObject* object)
{
    // add the gameobject to vector
    m_vpGameObjects.push_back(object);
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
        Bullet* newBullet = new Bullet(startingTransform, &m_collisionReferee, (size_t)ObjectType::kPlayerBullet);

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

        Bullet* newBullet = new Bullet(startingTransform, &m_collisionReferee, (size_t)ObjectType::kPlayerBullet);

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

    Bullet* newBullet = new Bullet(startingTransform, &m_collisionReferee, (size_t)ObjectType::kEnemeyBullet,m_pPlayer,isAutoLock);

    newBullet->TryMove();

    m_vpBossBullets.push_back(newBullet);
}

void BossStage::UpdateGameObjects(double deltaTime)
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


    if (m_pPlayer->GetActive() == false)
        delete m_pPlayer;

}

void BossStage::Exit()
{
    m_pTiledMap->Delete();
    DestoryGameObjects();
}