#include "Platformer.h"
#include "GameState.h"
#include "GameDemo.h"
#include "MainMenu.h"
#include "WinScreen.h"
#include "Stage01.h"

Platformer::Platformer(GameDemo* pOwner)
    : m_pOwner(pOwner),
      m_currentScene(SceneName::m_MainMenu)
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

    // delete the old state
    Destory();
}

void Platformer::UpdateCurrentState(double deltaTime)
{
    if (m_pNextState != nullptr)
    {
        ChangeState(m_pNextState);
        m_pOwner->PreloadTexture();
        m_pNextState = nullptr;
    }
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Update(deltaTime);
    }
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
    //m_pOwner->PreloadTexture();

    // Enter the new state
    pNewState->Enter();
}

void Platformer::LoadScene(SceneName scene)
{
    switch (scene)
    {
        case SceneName::m_MainMenu:
        {
            m_pNextState = new MainMenu(this);
            m_currentScene = SceneName::m_MainMenu;
            break;
        }
        case SceneName::m_GamePlay:
        {
            m_pNextState = new Stage01(this);
            m_currentScene = SceneName::m_GamePlay;
            break;
        }
        case SceneName::m_Victory:
        {
            m_pNextState = new WinScreen(this);
            m_currentScene = SceneName::m_Victory;
            break;
        }
        default:
            break;
        // TODO: allocate game state
    }

}


void Platformer::Destory()
{
    delete m_pNextState;
    delete m_pCurrentState;
}
