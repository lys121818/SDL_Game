#include "BackgroundMusicComponent.h"
#include <iostream>

BackgroundMusicComponent::BackgroundMusicComponent()
    :
    m_pCurrentBackgroundMusic(nullptr),
    m_pNextBackgroundMusic(nullptr),
    m_currentBGMusic(nullptr),
    m_isPlaying(true)
{
}

BackgroundMusicComponent::~BackgroundMusicComponent()
{
    Destroy();
}

void BackgroundMusicComponent::UpdateBGMusic()
{
    // If playing is done
    if(Mix_PlayingMusic() == 0)
    {
        // is next bg music exist change
        if (m_pNextBackgroundMusic != nullptr)
        {
            _Mix_Music* temp;

            // swap current and next bg music
            temp = m_pCurrentBackgroundMusic;
            m_pCurrentBackgroundMusic = m_pNextBackgroundMusic;
            m_pNextBackgroundMusic = temp;

            Mix_PlayMusic(m_pCurrentBackgroundMusic, 0);

        }
        // if next bg doesn't exist play current music
        else
        {
            Mix_PlayMusic(m_pCurrentBackgroundMusic, 0);
        }
    }
}

void BackgroundMusicComponent::SetBGMusic(const char* pFisrtDir, const char* pSecondDir)
{
    // if the current playing music is same keep play
    if (m_currentBGMusic == pFisrtDir)
        return;

    m_currentBGMusic = pFisrtDir;
    m_pCurrentBackgroundMusic = Mix_LoadMUS(m_currentBGMusic);

    // play music if its not null
    if (m_pCurrentBackgroundMusic == nullptr)
    {
        std::cout << "Fail to load music. Error: " << Mix_GetError();
    }
    else
    {
        Mix_PlayMusic(m_pCurrentBackgroundMusic, 0);
    }

    m_pNextBackgroundMusic = Mix_LoadMUS(pSecondDir);
}

void BackgroundMusicComponent::ToggleMusic()
{
    if (m_isPlaying)
    {
        Mix_PauseMusic();
        m_isPlaying = false;
    }
    else
    {
        Mix_ResumeMusic();
        m_isPlaying = true;
    }
}

void BackgroundMusicComponent::Destroy()
{
    if (m_pCurrentBackgroundMusic != nullptr)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(m_pCurrentBackgroundMusic);
        m_pCurrentBackgroundMusic = nullptr;
    }
    if (m_pNextBackgroundMusic != nullptr)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(m_pNextBackgroundMusic);
        m_pNextBackgroundMusic = nullptr;
    }
}
