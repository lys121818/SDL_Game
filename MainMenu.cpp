#include "MainMenu.h"
#include "Platformer.h"
MainMenu::MainMenu(Platformer* pOwner)
	:m_pOwner(pOwner),
	 m_background(SDL_Rect{ 0,0,640,480 },nullptr,BACKGROUND,0,0,"BackGround")
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Enter()
{
}

void MainMenu::Update(double deltaTime)
{
}

void MainMenu::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	m_background.Render(pRenderer, pTextures->GetTexture(m_background.GetTextureName()));
}

bool MainMenu::HandleEvent(SDL_Event* pEvent)
{
	
	switch (pEvent->type)
	{
		// determine action base on event type
		case SDL_WINDOWEVENT:
		{
			if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
			{
				return true;
			}
			break;
		}

	}

	return false;
}

void MainMenu::Exit()
{
}
