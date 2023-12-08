#include "Platformer.h"
#include "GameState.h"
#include "GameDemo.h"
#include "MainMenu.h"
#include "WinScreen.h"
#include "Stage01.h"
#include "BossStage.h"
#include "LossScreen.h"
#include "ImageDirectory.h"
#include "CreditsScene.h"
#include "SoundDirectory.h"
#include "LoadFileScene.h"

Platformer::Platformer(GameDemo* pOwner)
    : 
    m_pOwner(pOwner),
    m_currentScene(SceneName::kMainMenu)
{

    LoadScene(m_currentScene);

}

Platformer::~Platformer()
{
    // Exit the current State
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Exit();
    }

    // delete the old stateb
    Destory();
}

void Platformer::UpdateCurrentState(double deltaTime)
{
    if (m_pNextState != nullptr)
    {
        // Preload textur
        m_pOwner->PreloadFonts();
        m_pOwner->PreloadTexture();
        ChangeState(m_pNextState);

        m_pNextState = nullptr;
    }
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Update(deltaTime);
    }
    m_musicComponent.UpdateBGMusic();
}

void Platformer::RenderCurrentState(SDL_Renderer* pRenderer, Textures* pTextures)
{
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Render(pRenderer, pTextures);
    }
}

bool Platformer::HandleEvent(SDL_Event* pEvent)
{
    if (m_pCurrentState != nullptr)
    {
        return m_pCurrentState->HandleEvent(pEvent);
    }

    return false;
}

void Platformer::ChangeState(GameState* pNewState)
{
    // Load the new state
        // Exit the current State
    if (m_pCurrentState != nullptr)
    {
        //m_pOwner.
        m_pCurrentState->Exit();

    }

    // delete the old state
    delete m_pCurrentState;

    // Load the new state
    m_pCurrentState = pNewState;

    // Enter the new state
    pNewState->Enter();
}

void Platformer::LoadScene(SceneName scene, size_t fileNumber)
{
    switch (scene)
    {
        case SceneName::kMainMenu:
        {
            m_pNextState = new MainMenu(this);
            m_currentScene = SceneName::kMainMenu;
            break;
        }
        case SceneName::kGamePlay:
        {
            m_pNextState = new Stage01(this, fileNumber);
            m_currentScene = SceneName::kGamePlay;
            break;
        }
        case SceneName::kBoss:
        {
            m_pNextState = new BossStage(this, fileNumber);
            m_currentScene = SceneName::kBoss;
            break;
        }
        case SceneName::kVictory:
        {
            m_pNextState = new WinScreen(this);
            m_currentScene = SceneName::kVictory;
            break;
        }
        case SceneName::kLoss:
        {
            m_pNextState = new LossScreen(this);
            m_currentScene = SceneName::kLoss;
            break;
        }
        case SceneName::kCredit:
        {
            m_pNextState = new CreditsScene(this);
            m_currentScene = SceneName::kCredit;
            break;
        }
        case SceneName::kLoadFile:
        {
            m_pNextState = new LoadFileScene(this);
            m_currentScene = SceneName::kLoadFile;
            break;
        }
        default:
            break;
    }

}


void Platformer::SetBGMusic(const char* pFirstMusic, const char* pSecondMusic)
{
    m_musicComponent.SetBGMusic(pFirstMusic, pSecondMusic);
}

void Platformer::ToggleMusic()
{
    m_musicComponent.ToggleMusic();
}

void Platformer::Destory()
{

    delete m_pNextState;

}
