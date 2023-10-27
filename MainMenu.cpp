#include <iostream>
#include "MainMenu.h"
#include "Platformer.h"
#include "ButtonObject.h"
#include "ImageDirectory.h"
#include "Defines.h"
#include "ButtonType.h"

MainMenu::MainMenu(Platformer* pOwner)
	:m_pOwner(pOwner),
	 m_background_1(SDL_Rect{ 0,0,WINDOWWIDTH,WINDOWHEIGHT },nullptr,BACKGROUND,0,0,"BackGround"),
	 m_background_2(SDL_Rect{ WINDOWWIDTH,0,WINDOWWIDTH,WINDOWHEIGHT }, nullptr, BACKGROUND, 0, 0, "BackGround")
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Enter()
{
	// Background Setups
	m_background_1.TryMove(Vector2(LEFT));
	m_background_2.TryMove(Vector2(LEFT));

	// Set button objects
	SetButtons();

}

void MainMenu::Update(double deltaTime)
{
	BackgroundUpdates(deltaTime);
	for (auto& element : m_vpButtons)
	{
		element->Update(deltaTime);
	}
}

void MainMenu::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	// Render Background
	m_background_1.Render(pRenderer, pTextures->GetTexture(m_background_1.GetTextureName()));
	m_background_2.Render(pRenderer, pTextures->GetTexture(m_background_1.GetTextureName()));

	for (auto& element : m_vpButtons)
	{
		element->Render(pRenderer, pTextures->GetTexture(element->GetTextureName()));
	}

}

bool MainMenu::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
		// Mouse Event
		// Quit when true returns
		case SDL_MOUSEMOTION:
		{
			for (auto& element : m_vpButtons)
			{
				// if the button is able
				if (element->GetAble())
				{
					// if the mouse is inside the button
					if (pEvent->button.x > element->GetTransform().x &&
						pEvent->button.x < (element->GetTransform().x + element->GetTransform().w) &&
						pEvent->button.y > element->GetTransform().y &&
						pEvent->button.y < (element->GetTransform().y + element->GetTransform().h))
					{
						// Set Hover to true and break (Mouse is single object)
						m_pHoverButton = element;
						m_pHoverButton->SetHover(true);
						break;
					}
					else
					{
						m_pHoverButton = nullptr;
						element->SetClick(false);
						element->SetHover(false);
					}
				}
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		{
			if (ProcessMouseEvent(&pEvent->button) == true)
				return true;
			break;
		}

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

// Every events using mouse works here
bool MainMenu::ProcessMouseEvent(SDL_MouseButtonEvent* pData)
{
	if ((int)pData->type == SDL_MOUSEBUTTONDOWN)
	{
		switch ((int)pData->button)
		{
		case SDL_BUTTON_LEFT:
		{
			// If mouse is on hover to the button
			if(m_pHoverButton != nullptr)
				m_pHoverButton->SetClick(true);
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
			// If mouse is on hover to the button
			if (m_pHoverButton != nullptr)
			{
				if (m_pHoverButton->GetStatus().m_name == "Start" && m_pHoverButton->GetClicked())
				{
					m_pHoverButton->SetClick(false);
					m_pOwner->LoadScene(Platformer::SceneName::m_GamePlay);
				}
			}
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

void MainMenu::Exit()
{
}

void MainMenu::SetButtons()
{
	ButtonObject* button;
	SDL_Rect buttonTransform;
	
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTONWIDTH / 2),	// X
		100,				// Y
		(int)BUTTONWIDTH,	// W
		(int)BUTTONHEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, 0, Button_State::m_Normal, "Start");
	m_vpButtons.push_back(button);




}



////////////////
//	PRIVATE	  //
////////////////

/// <summary>
/// Updates for Background
/// </summary>
void MainMenu::BackgroundUpdates(double deltaTime)
{
	// Update Background
	m_background_1.Update(deltaTime);
	m_background_2.Update(deltaTime);

	if (m_background_1.GetTransform().x <= -WINDOWWIDTH)
	{
		m_background_1.SetPosition(Vector2{ WINDOWWIDTH ,0.0 });
	}
	else if (m_background_2.GetTransform().x <= -WINDOWWIDTH)
	{
		m_background_2.SetPosition(Vector2{ WINDOWWIDTH ,0.0 });
	}
}

void MainMenu::Destory()
{
	for (auto& element : m_vpButtons)
	{
		delete element;
	}

}
