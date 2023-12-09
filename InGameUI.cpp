#include "InGameUI.h"
#include "Textures.h"
#include "ImageDirectory.h"
#include "TextObject.h"
#include "ButtonObject.h"
#include <assert.h>

InGameUI::InGameUI(GameState* pOwner, GameObject* pObject, Fonts* pFonts, SDL_Renderer* pRenderer)
	:
	m_pOwner(pOwner),
	m_pGameObject(pObject),
	m_pHealthBar(nullptr),
	m_pFont(pFonts),
	m_pRenderer(pRenderer),
	m_keyboardButtonIndex(-1),
	m_isPause(false),
	m_menuBox(SDL_Rect{0,0,0,0})
{
}

InGameUI::~InGameUI()
{
	Destory();
}

void InGameUI::InitUI()
{
	SetPauseMenu();
}


void InGameUI::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	// Rendering UI objects
	for (auto& element : m_vpUIObjects)
	{
		element->Render(pRenderer,pTextures->GetTexture(element->GetTextureName()));
	}
	if (m_isPause)
	{
		SDL_SetRenderDrawColor(pRenderer, GRAY);
		SDL_RenderFillRect(pRenderer, &m_menuBox);

		for (auto& button : m_vpButtons)
		{
			button->Render(pRenderer, pTextures->GetTexture(button->GetTextureName()));
		}
	}
}

// Update on call
void InGameUI::UpdateUI()
{
	UpdateHealthbar();

}

void InGameUI::UpdateUI(double deltaTime)
{
	UpdatePauseMenu(deltaTime);
}


bool InGameUI::HandleEvent(SDL_Event* pEvent)
{
	// buttons handles event its own
	for (auto& element : m_vpButtons)
	{
		element->HandleEvent(pEvent);
	}

	return m_isPause;
}

void InGameUI::UpdateHealthbar()
{
	// Calculate current health in percentage
	float percentage = ((float)m_pGameObject->GetStatus().m_health / (float)m_pGameObject->GetStatus().m_maxHealth);

	// transform for current health bar
	SDL_Rect currentHealthUI
	{
		m_pHealthBar->GetTransform().x,
		m_pHealthBar->GetTransform().y,
		(int)((float)m_vpUIObjects[2]->GetTransform().w * (float)percentage),	// calculate with empty health bar
		m_pHealthBar->GetTransform().h
	};

	m_pHealthBar->SetTransform(currentHealthUI);
}

void InGameUI::SetPauseMenu()
{
	// Box
	m_menuBox =
	{
		WINDOWWIDTH / 2 - 200,
		50,
		400,
		500
	};

	// Buttons
	ButtonObject* button;

	// [Load Button 1]
	SDL_Rect buttonTransform =
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		100,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	// Font to use in button object

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "SAVE 1");

	// Set Callback for button
	button->SetCallback([this]()->void
		{
			m_pOwner->Save(1);
		});

	button->SetTextInButton(m_pFont->GetFont(FONT2), "SAVE 1", SDL_Color(BLUE), m_pRenderer);
	m_vpButtons.push_back(button);

	// [Load Button 2]
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		200,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "SAVE 2");


	button->SetTextInButton(m_pFont->GetFont(FONT2), "SAVE 2", SDL_Color(BLUE), m_pRenderer);

	button->SetCallback([this]()->void
		{
			m_pOwner->Save(2);
		});

	m_vpButtons.push_back(button);

	// [Load Button 3]
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		300,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "SAVE 3");

	button->SetTextInButton(m_pFont->GetFont(FONT2), "SAVE 3", SDL_Color(BLUE), m_pRenderer);

	button->SetCallback([this]()->void
		{
			m_pOwner->Save(3);
		});

	m_vpButtons.push_back(button);

	// [Resume]
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		400,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Resume");

	button->SetCallback([this]()->bool
		{
			TogglePause();
			return true;
		});

	button->SetTextInButton(m_pFont->GetFont(FONT2), "RESUME", SDL_Color(BLUE), m_pRenderer);
	m_vpButtons.push_back(button);

}

void InGameUI::UpdatePauseMenu(double deltaTime)
{
	for (auto& button : m_vpButtons)
		button->Update(deltaTime);
}

void InGameUI::AddHealthBar(Vector2<double> position, Vector2<double> size)
{
	UIObject* UIImageObject;

	// Basic Transform of the Health bar
	SDL_Rect UIImageTransform
	{
		(int)position.m_x,	// X
		(int)position.m_y,	// Y
		(int)size.m_x,		// W
		(int)size.m_y		// H
	};

	// [BasicBar]
	UIImageObject = new UIObject(UIImageTransform, HEALTHUI,0);

	m_vpUIObjects.push_back(UIImageObject);

	// [Health Symbol]
	UIImageTransform.x = (int)position.m_x + 7;
	UIImageTransform.y = (int)position.m_y + ((int)size.m_y / 2) - 15;
	UIImageTransform.w = 30;
	UIImageTransform.h = 30;

	UIImageObject = new UIObject(UIImageTransform, HEALTHUI, 3);

	m_vpUIObjects.push_back(UIImageObject);

	// [BlankBar]
	UIImageTransform.x = (int)position.m_x + 45;
	UIImageTransform.y = (int)position.m_y + 12;
	UIImageTransform.w = (int)size.m_x - 60;
	UIImageTransform.h = (int)size.m_y - 25;

	UIImageObject = new UIObject(UIImageTransform, HEALTHUI, 2);

	m_vpUIObjects.push_back(UIImageObject);
	

	// [Health Bar]
	m_pHealthBar = new UIObject(UIImageTransform, HEALTHUI, 1);	

	m_vpUIObjects.push_back(m_pHealthBar);



}

void InGameUI::ChangeButtonFocus(int direction)
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

void InGameUI::Destory()
{
	for (auto& element : m_vpUIObjects)
	{
		delete element;
	}

	for (auto& element : m_vpButtons)
	{
		delete element;
	}

}

