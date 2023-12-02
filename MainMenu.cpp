#include <iostream>
#include "MainMenu.h"
#include "Platformer.h"
#include "ButtonObject.h"
#include "ImageDirectory.h"
#include "Defines.h"
#include "ButtonType.h"
#include "Vector2.h"
#include "SoundDirectory.h"
#include "GameDemo.h"
#include <SDL_mixer.h>
#include <assert.h>

MainMenu::MainMenu(Platformer* pOwner)
	:
	m_pOwner(pOwner),
	m_background_1(Vector2<double>{ 0,0 }, Vector2<double>{WINDOWWIDTH, WINDOWHEIGHT }, nullptr, BACKGROUND, 0, 0, "BackGround"),
	m_background_2(Vector2<double>{ WINDOWWIDTH,0 }, Vector2<double>{ WINDOWWIDTH, WINDOWHEIGHT }, nullptr, BACKGROUND, 0, 0, "BackGround"),
	m_pHoverButton(nullptr),
	m_keyboardButtonIndex(-1),
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
	m_background_1.TryMove(Vector2<double>(LEFT), BACKGROUND_MOVE_SPEED);
	m_background_2.TryMove(Vector2<double>(LEFT), BACKGROUND_MOVE_SPEED);

	// Set button objects
	SetButtons();

	// Set UI
	SetUI();

	m_pOwner->SetBGMusic(MAINMENU1_SOUND, MAINMENU2_SOUND);
}

void MainMenu::Update(double deltaTime)
{
	BackgroundUpdates(deltaTime);

	// When player info is set
	if (isSetUI)
	{
		for (auto& element : m_vpButtons)
		{
			element->Update(deltaTime);
		}
	}
	else
	{
		m_pMainMenuUI->UpdateUI(deltaTime);
	}
}

void MainMenu::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	// Render Background
	m_background_1.Render(pRenderer, pTextures->GetTexture(m_background_1.GetTextureName()));
	m_background_2.Render(pRenderer, pTextures->GetTexture(m_background_1.GetTextureName()));

	// When UserInput is done
	if (isSetUI)
	{
		for (auto& element : m_vpButtons)
		{
			element->Render(pRenderer, pTextures->GetTexture(element->GetTextureName()));
		}
	}
	else
	{
		m_pMainMenuUI->Render(pRenderer, pTextures);
	}
}

bool MainMenu::HandleEvent(SDL_Event* pEvent)
{
	// User Input
	if (!isSetUI)
	{
		isSetUI = m_pMainMenuUI->HandleEvent(pEvent);
	}
	// Main Menu
	else
	{
		// buttons handles event its own
		for (auto& element : m_vpButtons)
		{
			element->HandleEvent(pEvent);
		}

		// Quit when true returns
		switch (pEvent->type)
		{
			// Reset keyboard index when mouse event happens
			case SDL_MOUSEMOTION:
			{
				m_keyboardButtonIndex = -1;
				break;
			}
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
			// pasue music
			case SDLK_p:
			{
				m_pOwner->ToggleMusic();
				break;
			}
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
				if (m_keyboardButtonIndex >= 0 && m_keyboardButtonIndex < (int)m_vpButtons.capacity())
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
	Destory();
}

void MainMenu::SetButtons()
{
	ButtonObject* button;
	SDL_Rect buttonTransform;
	
	// [Start Button]
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		100,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	// Font to use in button object
	TTF_Font* font = m_pOwner->GetGame()->GetFonts()->GetFont(FONT1);

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Start");

	// Set Callback for button
	button->SetCallback([this]()->void
		{
			m_pOwner->LoadScene(Platformer::SceneName::kGamePlay);
		});

	button->SetTextInButton(font, "START", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());
	m_vpButtons.push_back(button);

	// [Load Button]
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		200,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Load");


	button->SetTextInButton(font, "LOAD", SDL_Color(GRAY), m_pOwner->GetGame()->GetRenderer());

	button->SetCallback([this]()->void
		{
			m_pOwner->GetSave()->Load();
		});

	m_vpButtons.push_back(button);

	// [Quit Button]
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

	// [Credits Button]
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		400,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Credits");

	button->SetCallback([this]()->void
		{
			m_pOwner->LoadScene(Platformer::SceneName::kCredit);
		});

	button->SetTextInButton(font, "CREDITS", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());
	m_vpButtons.push_back(button);

}

void MainMenu::SetUI()
{
	// Create UI
	m_pMainMenuUI = new MainMenuUI(m_pOwner->GetGame()->GetFonts(),
					m_pOwner->GetGame()->GetRenderer());

	// Set UI
	m_pMainMenuUI->InitUI();

}

void MainMenu::SetMusic()
{

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
		m_background_1.SetPosition(Vector2<double>{ WINDOWWIDTH ,0.0 });
	}
	else if (m_background_2.GetTransform().x <= -WINDOWWIDTH)
	{
		m_background_2.SetPosition(Vector2<double>{ WINDOWWIDTH ,0.0 });
	}
}

void MainMenu::Destory()
{
	for (auto& element : m_vpButtons)
	{
		delete element;
	}

	delete m_pMainMenuUI;
}

void MainMenu::ChangeButtonFocus(int direction)
{
	assert(m_vpButtons.size() > 0);

	int nextDirectionIndex = (m_keyboardButtonIndex + direction);

	// set to first index if its negative value
	if (nextDirectionIndex < 0)
	{
		m_keyboardButtonIndex = 0;
	}
	// set to last index if its over size
	else if (nextDirectionIndex >= (int)m_vpButtons.size())
	{
		m_keyboardButtonIndex = (int)(m_vpButtons.size() - 1);
	}
	else
	{
		m_keyboardButtonIndex = nextDirectionIndex;
	}

	// if the button is disable and next index exist
	if (!m_vpButtons[m_keyboardButtonIndex]->GetAble() &&
		(m_keyboardButtonIndex + direction >= 0 && m_keyboardButtonIndex + direction < (int)m_vpButtons.size()))
	{

		ChangeButtonFocus(direction);
	}

	// Change Hover setting if the button is able
	for (size_t i = 0; i < m_vpButtons.size(); ++i)
	{
		if (m_vpButtons[m_keyboardButtonIndex]->GetAble())
		{
			if (i == m_keyboardButtonIndex)
				m_vpButtons[i]->SetHover(true);
			else
				m_vpButtons[i]->SetHover(false);
		}
	}

}
