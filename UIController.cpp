#include "UIController.h"
#include "Textures.h"
#include "ImageDirectory.h"

UIController::UIController(GameState* pOwner, GameObject* pPlayer)
	:
	m_pOwner(pOwner),
	m_pPlayer(pPlayer)
{
}

UIController::~UIController()
{
}

void UIController::InitUI()
{
	HealthBarSettings();
}

void UIController::Update()
{
	UpdateHealthUI();
}

void UIController::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	for (auto& element : m_mpUIObjects)
	{
		element->Render(pRenderer,pTextures->GetTexture(element->GetTextureName()));
	}
}

void UIController::AddUIImage(SDL_Rect* pTransform, const char* spriteName)
{
}

void UIController::UpdateHealthUI()
{
	float percentage = ((float)m_pPlayer->GetStatus().m_health / (float)PLAYERMAXHEALTH);
	

	SDL_Rect currentHealthUI
	{
		s_kMaxHealthBarPosition.m_x + 45,
		s_kMaxHealthBarPosition.m_y + 12,
		(int)((float)(s_kMaxHealthBarSize.m_x - 60) * (float)percentage),
		s_kMaxHealthBarSize.m_y - 25
	};
	m_pHealthBar->SetTransform(currentHealthUI);
}

void UIController::HealthBarSettings()
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

	// BasicBar
	UIImageObject = new UIObject(UIImageTransform, HEALTHUI,0);

	m_mpUIObjects.push_back(UIImageObject);

	// BlankBar
	UIImageTransform.x += 45;
	UIImageTransform.y += 12;
	UIImageTransform.w -= 60;
	UIImageTransform.h -= 25;

	UIImageObject = new UIObject(UIImageTransform, HEALTHUI, 2);

	m_mpUIObjects.push_back(UIImageObject);
	

	// Actual Health Bar
	m_pHealthBar = new UIObject(UIImageTransform, HEALTHUI, 1);	// Trying index 1 or 4 (Long and short)

	m_mpUIObjects.push_back(m_pHealthBar);


}

