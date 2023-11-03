#include "WinScreen.h"
#include "ImageDirectory.h"
#include "Platformer.h"
#include "GameDemo.h"

WinScreen::WinScreen(Platformer* pOwner)
	:
	m_pOwner(pOwner),
	m_Background(Vector2{ 0,0 }, Vector2{ WINDOWWIDTH, WINDOWHEIGHT }, nullptr, BACKGROUND, 0, 0, "WinState"),
	m_pHoverButton(nullptr),
	m_winImage(Vector2{ 200,-10 }, Vector2{400,500} , nullptr, WIN_STATE, 0, 0, "Win")
{
	isOnAction = true;
}

WinScreen::~WinScreen()
{
}

void WinScreen::Enter()
{
	SetButtons();
	m_winImage.SetAction(ImageActionComponent::ActionState::kPoping);
}

void WinScreen::Update(double deltaTime)
{
	if (isOnAction)
	{
		if (m_winImage.GetActionState() == ImageActionComponent::ActionState::kNormal)
			isOnAction = false;
	}
	// Print buttons when action is done
	for (auto& element : m_vpButtons)
	{
		element->Update(deltaTime);
	}
	m_winImage.Update(deltaTime);

}

void WinScreen::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	m_Background.Render(pRenderer, pTextures->GetTexture(m_Background.GetTextureName()));

	m_winImage.Render(pRenderer, pTextures->GetTexture(m_winImage.GetTextureName()));
	if (!isOnAction)
	{
		// Print buttons when action is done
		for (auto& element : m_vpButtons)
		{
			element->Render(pRenderer, pTextures->GetTexture(element->GetTextureName()));
		}
	}
}

bool WinScreen::HandleEvent(SDL_Event* pEvent)
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
bool WinScreen::ProcessMouseEvent(SDL_MouseButtonEvent* pData)
{
	if ((int)pData->type == SDL_MOUSEBUTTONDOWN)
	{
		switch ((int)pData->button)
		{
		case SDL_BUTTON_LEFT:
		{
			// If mouse is on hover to the button
			if (m_pHoverButton != nullptr)
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
				if (m_pHoverButton->GetStatus().m_name == "MainMenu" && m_pHoverButton->GetClicked())
				{
					m_pHoverButton->SetClick(false);
					m_pOwner->LoadScene(Platformer::SceneName::kMainMenu);
				}
				else if (m_pHoverButton->GetStatus().m_name == "Restart" && m_pHoverButton->GetClicked())
				{
					m_pHoverButton->SetClick(false);
					m_pOwner->LoadScene(Platformer::SceneName::kGamePlay);
				}
				else if (m_pHoverButton->GetStatus().m_name == "Quit" && m_pHoverButton->GetClicked())
				{
					m_pHoverButton->SetClick(false);
					return true;
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


void WinScreen::Exit()
{
	Destory();
}

void WinScreen::SetButtons()
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
	button->SetTextInButton(font, "Q U I T", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());
	m_vpButtons.push_back(button);


}

void WinScreen::Destory()
{
	for (auto& element : m_vpButtons)
	{
		delete element;
	}
}
