#include "LossScreen.h"
#include "ImageDirectory.h"
#include "Platformer.h"
#include "GameDemo.h"

LossScreen::LossScreen(Platformer* pOwner)
	:
	m_pOwner(pOwner),
	m_Background(Vector2{ 0,0 }, Vector2{ WINDOWWIDTH, WINDOWHEIGHT }, nullptr, BACKGROUND,0, 0, "LossState"),
	m_pHoverButton(nullptr),
	m_lossImage(Vector2{ 200,20 }, Vector2{ 400,500 }, nullptr, LOSS_STATE, 0, 0, "Loss"),
	m_keyboardButtonIndex(-1)
{
	isOnAction = true;
}

LossScreen::~LossScreen()
{
}

void LossScreen::Enter()
{
	SetButtons();
	m_lossImage.SetAction(ImageActionComponent::ActionState::kPoping);
}

void LossScreen::Update(double deltaTime)
{
	if (isOnAction)
	{
		if (m_lossImage.GetActionState() == ImageActionComponent::ActionState::kNormal)
			isOnAction = false;
	}

	for (auto& element : m_vpButtons)
	{
		element->Update(deltaTime);
	}
	m_lossImage.Update(deltaTime);
}

void LossScreen::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	m_Background.Render(pRenderer, pTextures->GetTexture(m_Background.GetTextureName()));

	m_lossImage.Render(pRenderer, pTextures->GetTexture(m_lossImage.GetTextureName()));

	if (!isOnAction)
	{
		// Print buttons after action is done
		for (auto& element : m_vpButtons)
		{
			element->Render(pRenderer, pTextures->GetTexture(element->GetTextureName()));
		}
	}
}

bool LossScreen::HandleEvent(SDL_Event* pEvent)
{
	for (auto& element : m_vpButtons)
	{
		element->HandleEvent(pEvent);
	}

	switch (pEvent->type)
	{
		// Mouse Event
		// Quit when true returns
	case SDL_MOUSEMOTION:
	{

		break;
	}
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

	return false;
}


bool LossScreen::ProcessMouseEvent(SDL_MouseButtonEvent* pData)
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

bool LossScreen::ProcessKeyboardEvent(SDL_KeyboardEvent* pData)
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


void LossScreen::Exit()
{
	Destory();
}

void LossScreen::SetButtons()
{
	ButtonObject* button;
	SDL_Rect buttonTransform;

	// Start Button
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTONWIDTH / 2),	// X
		s_kFirstButtonY,				// Y
		(int)BUTTONWIDTH,	// W
		(int)BUTTONHEIGHT	// H
	};

	TTF_Font* font = m_pOwner->GetGame()->GetFonts()->GetFont(FONT2);

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "MainMenu");

	button->SetCallback([this]()->void
		{
			m_pOwner->LoadScene(Platformer::SceneName::kMainMenu);
		});

	button->SetTextInButton(font, "MAIN MENU", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());
	m_vpButtons.push_back(button);

	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTONWIDTH / 2),	// X
		s_kFirstButtonY + s_kDistanceBetweenButtons,				// Y
		(int)BUTTONWIDTH,	// W
		(int)BUTTONHEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Restart");

	button->SetCallback([this]()->void
		{
			m_pOwner->LoadScene(Platformer::SceneName::kGamePlay);
		});

	button->SetTextInButton(font, "RESTART", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());
	m_vpButtons.push_back(button);

	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTONWIDTH / 2),	// X
		s_kFirstButtonY + (s_kDistanceBetweenButtons * 2),				// Y
		(int)BUTTONWIDTH,	// W
		(int)BUTTONHEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Quit");

	button->SetCallback([this]()->void
		{
			m_pOwner->GetGame()->Quit();
		});

	button->SetTextInButton(font, "Q U I T", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());
	m_vpButtons.push_back(button);
}

void LossScreen::Destory()
{
	for (auto& element : m_vpButtons)
	{
		delete element;
	}
}

void LossScreen::ChangeButtonFocus(int direction)
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
