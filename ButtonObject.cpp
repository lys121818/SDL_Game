#include <iostream>

#include "ImageDirectory.h"
#include "ButtonObject.h"

ButtonObject::ButtonObject(SDL_Rect transform, const char* directory, const int index, Button_State type, const char* name)
	:
	m_pSpriteName(directory),
	m_transform(transform),
	m_imageComponent(directory, &m_transform),
	m_currentState(type)
{
	m_status.m_name = name;
	m_isOnHover = false;

	if (type != Button_State::m_Disable)
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
}


void ButtonObject::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	if (pTexture == nullptr)
	{
		std::cout << "[ButtonObject] The texture hasn't been Set up\n";
		return;
	}
	m_imageComponent.Render(pRenderer, pTexture);
}


void ButtonObject::ButtonState()
{
	if (m_isAble)
	{
		if (m_isOnHover)
		{
			if (m_isClicked)
			{
				SetButtonState(Button_State::m_Click);
				m_currentState = Button_State::m_Click;
			}
			else
			{
				SetButtonState(Button_State::m_Hover);
				m_currentState = Button_State::m_Hover;
			}
		}
		else
		{
			SetButtonState(Button_State::m_Normal);
			m_currentState = Button_State::m_Normal;
		}
	}
	else
	{
		SetButtonState(Button_State::m_Disable);
		m_currentState = Button_State::m_Disable;
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
			case Button_State::m_Normal:
			{
				m_imageComponent.SetImageFrame("Normal");
				break;
			}
			case Button_State::m_Hover:
			{
				m_imageComponent.SetImageFrame("Hover");
				break;
			}
			case Button_State::m_Click:
			{
				m_imageComponent.SetImageFrame("Click");
				break;
			}
			case Button_State::m_Disable:
			{
				m_imageComponent.SetImageFrame("Disable");
				break;
			}
		default:
			break;
		}
	}
}
