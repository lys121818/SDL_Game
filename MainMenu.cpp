#include <iostream>
#include "MainMenu.h"
#include "Platformer.h"
#include "ButtonObject.h"
#include "ImageDirectory.h"
#include "Defines.h"
#include "ButtonType.h"
#include "Vector2.h"
#include "GameDemo.h"
#include <assert.h>

MainMenu::MainMenu(Platformer* pOwner)
	:
	m_pOwner(pOwner),
	m_background_1(Vector2{ 0,0 }, Vector2{WINDOWWIDTH, WINDOWHEIGHT }, nullptr, BACKGROUND, 0, 0, "BackGround"),
	m_background_2(Vector2{ WINDOWWIDTH,0 }, Vector2{ WINDOWWIDTH, WINDOWHEIGHT }, nullptr, BACKGROUND, 0, 0, "BackGround"),
	m_pHoverButton(nullptr),
	m_keyboardButtonIndex(-1),
	m_textBox(SDL_Rect{300,300,300,50}),
	m_pMainMenuUI(nullptr),
	isSetUI(false)
{

}

MainMenu::~MainMenu()
{
}

void MainMenu::Enter()
{
	// Background Setups
	m_background_1.TryMove(Vector2(LEFT), BACKGROUND_MOVE_SPEED);
	m_background_2.TryMove(Vector2(LEFT), BACKGROUND_MOVE_SPEED);

	// Set button objects
	SetButtons();

	SetUI();
}

void MainMenu::Update(double deltaTime)
{
	BackgroundUpdates(deltaTime);
	if (isSetUI)
	{
		for (auto& element : m_vpButtons)
		{
			element->Update(deltaTime);
		}
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
	if (isSetUI)
	{
	}
	else
	{
		m_pMainMenuUI->Render(pRenderer, pTextures);
	}
}

bool MainMenu::HandleEvent(SDL_Event* pEvent)
{
	for (auto& element : m_vpButtons)
	{
		element->HandleEvent(pEvent);
	}

	if (!isSetUI)
	{
		isSetUI = m_pMainMenuUI->HandleEvent(pEvent);
	}
	else
	{
		// Quit when true returns
		switch (pEvent->type)
		{
			// Mouse Event
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			{
				if (ProcessMouseEvent(&pEvent->button) == true)
					return true;
				break;
			}

			// Keyboard Event
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				if (ProcessKeyboardEvent(&pEvent->key) == true)
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
	}

	return false;
}


////////////////
//	PRIVATE	  //
////////////////

// Every events using mouse works here
bool MainMenu::ProcessMouseEvent(SDL_MouseButtonEvent* pData)
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

bool MainMenu::ProcessKeyboardEvent(SDL_KeyboardEvent* pData)
{
	if ((int)pData->state == 1 && (int)pData->repeat == 0)   // Key Press, ignore repeat keys
	{
		switch ((int)pData->keysym.sym)
		{
		// Move Up
		case SDLK_w:
		case SDLK_UP:
		{
			ChangeButtonFocus(-1);
			break;
		}

		// Move Down
		case SDLK_s:
		case SDLK_DOWN:
		{
			ChangeButtonFocus(1);
			break;
		}
		case SDLK_SPACE:
		case SDLK_RETURN:
		{
			if (m_keyboardButtonIndex >= 0 && m_keyboardButtonIndex < m_vpButtons.capacity())
			{
				if (m_vpButtons[m_keyboardButtonIndex]->GetSelected() == true)
					m_vpButtons[m_keyboardButtonIndex]->Trigger();
			}
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
	
	// Start Button
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		100,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	TTF_Font* font = m_pOwner->GetGame()->GetFonts()->GetFont(FONT1);

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Start");

	button->SetCallback([this]()->void
		{
			m_pOwner->LoadScene(Platformer::SceneName::kGamePlay);
		});

	button->SetTextInButton(font, "START", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());

	m_vpButtons.push_back(button);

	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		200,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kDisable, "Settings");


	button->SetTextInButton(font, "SETTINGS", SDL_Color(GRAY), m_pOwner->GetGame()->GetRenderer());
	m_vpButtons.push_back(button);

	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		300,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Quit");

	button->SetCallback([this]()->void
		{
			m_pOwner->GetGame()->Quit();
		});

	button->SetTextInButton(font, "QUIT", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());
	m_vpButtons.push_back(button);


	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		400,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Quit");

	button->SetCallback([this]()->void
		{
			m_pOwner->LoadScene(Platformer::SceneName::kCredit);
		});

	button->SetTextInButton(font, "CREDITS", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());
	m_vpButtons.push_back(button);

}

void MainMenu::SetUI()
{
	m_pMainMenuUI = new MainMenuUI(m_pOwner->GetGame()->GetFonts()->GetFont(FONT2),
					SDL_Color{ BLACK },
					m_pOwner->GetGame()->GetRenderer());

	// Set UI
	m_pMainMenuUI->InitUI();

}


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

void MainMenu::ChangeButtonFocus(int direction)
{
	int nextDirectionIndex = (m_keyboardButtonIndex + direction);

	// set to first index if its negative value
	if (nextDirectionIndex < 0)
	{
		m_keyboardButtonIndex = 0;
	}
	// set to last index if its over capacity
	else if (nextDirectionIndex >= m_vpButtons.capacity())
	{
		m_keyboardButtonIndex = m_vpButtons.capacity() - 1;
	}
	else
	{
		m_keyboardButtonIndex = nextDirectionIndex;
	}


	if (!m_vpButtons[m_keyboardButtonIndex]->GetAble())
		ChangeButtonFocus(direction);

	for (size_t i = 0; i < m_vpButtons.capacity(); ++i)
	{
		if (i == m_keyboardButtonIndex)
			m_vpButtons[i]->SetHover(true);
		else
			m_vpButtons[i]->SetHover(false);
	}

}
