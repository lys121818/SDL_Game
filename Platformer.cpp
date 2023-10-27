#include "Platformer.h"
#include "GameState.h"
#include "MainMenu.h"
#include "GameDemo.h"

Platformer::Platformer(GameDemo* pOwner)
    : m_pOwner(pOwner)
{
    LoadScene(SceneName::m_MainMenu);
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
        m_pNextState = nullptr;
    }
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Update(deltaTime);
    }
}

void Platformer::RenderCurrentState(SDL_Renderer* pRenderer)
{
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Render(pRenderer, m_pTextures);
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
        m_pCurrentState->Exit();
    }

    // delete the old state
    delete m_pCurrentState;

    // Load the new state
    m_pCurrentState = pNewState;

    // Enter the new state
    pNewState->Enter();
}

void Platformer::LoadScene(SceneName scene)
{
    m_pTextures = new Textures(m_pOwner->GetRenderer());
    switch (scene)
    {
        case SceneName::m_MainMenu:
        {
            m_pNextState = new MainMenu(this);

            // Preload the textures being used for scene
            m_pTextures->PreloadTextures((size_t)scene);
            break;
        }
        case SceneName::m_GamePlay:
        {

        }
        // TODO: allocate game state
    }

}


void Platformer::Destory()
{
    delete m_pTextures;
    delete m_pNextState;
    delete m_pCurrentState;
    delete m_pOwner;
}
