#include <iostream>

#include "ImageDirectory.h"
#include "ButtonObject.h"

ButtonObject::ButtonObject(SDL_Rect transform, const char* directory, Button_State type, const char* name)
	:
	m_pSpriteName(directory),
	m_transform(transform),
	m_imageComponent(directory, &m_transform),
	m_currentState(type),
	m_textComponent(&m_transform)
{
	m_status.m_name = name;
	m_isOnHover = false;

	m_callback = nullptr;

	if (type != Button_State::kDisable)
		m_isAble = true;

	SetButtonState(m_currentState);
	SetImage();

}

ButtonObject::~ButtonObject()
{
}


void ButtonObject::Update(double deltaTime)
{
	ButtonState();
	m_textComponent.Update();
}


void ButtonObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	if (pTexture == nullptr)
	{
		std::cout << "[ButtonObject] The texture hasn't been Set up\n";
		return;
	}
	m_imageComponent.Render(pRenderer, pTexture);

	m_textComponent.Render(pRenderer);
}

void ButtonObject::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
	case SDL_MOUSEMOTION:
	{
		if (m_isAble)
		{
			if (HitTest(pEvent->button.x, pEvent->button.y))
			{
				if (m_currentState != Button_State::kClick)
				{
					m_isOnHover = true;
				}
			}
			else
			{
				m_isAble = true;
				m_isOnHover = false;
				m_isClicked = false;
			}
		}
		else
		{
			m_isAble = false;
			m_isOnHover = false;
			m_isClicked = false;
		}

		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		if (m_callback != nullptr && HitTest(pEvent->button.x, pEvent->button.y))
		{
			SetButtonState(Button_State::kClick);
			m_isClicked = true;
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		if (m_isClicked)
		{
			if (m_isAble)
			{
				m_isClicked = false;
				Trigger();
			}
		}
		break;
	}
	default:
		break;
	}
}


void ButtonObject::SetAble(bool isAble)
{
	m_isAble = isAble;

	if (!isAble)
	{
		m_isOnHover = false;
		m_isClicked = false;
	}
}

void ButtonObject::SetTextInButton(TTF_Font* pFont, const char* pText, SDL_Color color, SDL_Renderer* pRenderer)
{
	m_textComponent.SetText(pFont, pText, color, pRenderer);

}

void ButtonObject::ButtonState()
{
	if (m_isAble)
	{
		if (m_isOnHover)
		{
			if (m_isClicked)
			{
				SetButtonState(Button_State::kClick);
			}
			else
			{
				SetButtonState(Button_State::kHover);
			}
		}
		else
		{
			SetButtonState(Button_State::kNormal);
		}
	}
	else
	{
		SetButtonState(Button_State::kDisable);
	}
}

void ButtonObject::SetButtonState(Button_State state)
{
	if (m_currentState == state)
		return;

	m_currentState = state;
	SetImage();
}

void ButtonObject::SetImage()
{
	
	if (strcmp(m_pSpriteName, BUTTONS) == 0)
	{
		switch (m_currentState)
		{
			case Button_State::kNormal:
			{
				m_imageComponent.SetImageFrame("Normal");
				break;
			}
			case Button_State::kHover:
			{
				m_imageComponent.SetImageFrame("Hover");
				break;
			}
			case Button_State::kClick:
			{
				m_imageComponent.SetImageFrame("Click");
				break;
			}
			case Button_State::kDisable:
			{
				m_imageComponent.SetImageFrame("Disable");
				break;
			}
		default:
			break;
		}
	}
}

void ButtonObject::Trigger()
{
	if (m_callback != nullptr)
	{
		m_callback();
	}
}

bool ButtonObject::HitTest(int x, int y)
{
	if (x > m_transform.x && x < (m_transform.x + m_transform.w) &&
		y > m_transform.y && y < (m_transform.y + m_transform.h))
	{
		return true;
	}

	return false;
}
