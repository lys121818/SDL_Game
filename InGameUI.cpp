#include "InGameUI.h"
#include "Textures.h"
#include "ImageDirectory.h"
#include "TextObject.h"

InGameUI::InGameUI(GameObject* pPlayer, Fonts* pFonts, SDL_Renderer* pRenderer)
	:
	m_pPlayer(pPlayer),
	m_pHealthBar(nullptr),
	m_pFont(pFonts),
	m_pRenderer(pRenderer)
{
}

InGameUI::~InGameUI()
{
	Destory();
}

void InGameUI::InitUI()
{
	HealthBarSettings();
}


void InGameUI::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	// Rendering UI objects
	for (auto& element : m_mpUIObjects)
	{
		element->Render(pRenderer,pTextures->GetTexture(element->GetTextureName()));
	}
}

// Update on call
void InGameUI::UpdateUI()
{
	UpdateHealthbar();
}


void InGameUI::UpdateHealthbar()
{
	// Calculate current health in percentage
	float percentage = ((float)m_pPlayer->GetStatus().m_health / (float)PLAYER_MAX_HEALTH);

	// transform for current health bar
	SDL_Rect currentHealthUI
	{
		m_pHealthBar->GetTransform().x,
		m_pHealthBar->GetTransform().y,
		(int)((float)m_mpUIObjects[2]->GetTransform().w * (float)percentage),	// calculate with empty health bar
		m_pHealthBar->GetTransform().h
	};

	m_pHealthBar->SetTransform(currentHealthUI);
}

void InGameUI::HealthBarSettings()
{
	UIObject* UIImageObject;

	// Basic Transform of the Health bar
	SDL_Rect UIImageTransform
	{
		(int)s_kMaxHealthBarPosition.m_x,	// X
		(int)s_kMaxHealthBarPosition.m_y,	// Y
		(int)s_kMaxHealthBarSize.m_x,		// W
		(int)s_kMaxHealthBarSize.m_y		// H
	};

	// [BasicBar]
	UIImageObject = new UIObject(UIImageTransform, HEALTHUI,0);

	m_mpUIObjects.push_back(UIImageObject);

	// [Health Symbol]
	UIImageTransform.x = (int)s_kMaxHealthBarPosition.m_x + 7;
	UIImageTransform.y = (int)s_kMaxHealthBarPosition.m_y + ((int)s_kMaxHealthBarSize.m_y / 2) - 15;
	UIImageTransform.w = 30;
	UIImageTransform.h = 30;

	UIImageObject = new UIObject(UIImageTransform, HEALTHUI, 3);

	m_mpUIObjects.push_back(UIImageObject);

	// [BlankBar]
	UIImageTransform.x = (int)s_kMaxHealthBarPosition.m_x + 45;
	UIImageTransform.y = (int)s_kMaxHealthBarPosition.m_y + 12;
	UIImageTransform.w = (int)s_kMaxHealthBarSize.m_x - 60;
	UIImageTransform.h = (int)s_kMaxHealthBarSize.m_y - 25;

	UIImageObject = new UIObject(UIImageTransform, HEALTHUI, 2);

	m_mpUIObjects.push_back(UIImageObject);
	

	// [Health Bar]
	m_pHealthBar = new UIObject(UIImageTransform, HEALTHUI, 1);	

	m_mpUIObjects.push_back(m_pHealthBar);



}

void InGameUI::Destory()
{
	for (auto& element : m_mpUIObjects)
	{
		delete element;
	}
}

