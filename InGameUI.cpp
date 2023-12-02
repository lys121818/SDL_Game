#include "InGameUI.h"
#include "Textures.h"
#include "ImageDirectory.h"
#include "TextObject.h"

InGameUI::InGameUI(GameObject* pObject, Fonts* pFonts, SDL_Renderer* pRenderer)
	:
	m_pGameObject(pObject),
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
	float percentage = ((float)m_pGameObject->GetStatus().m_health / (float)m_pGameObject->GetStatus().m_maxHealth);

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

	m_mpUIObjects.push_back(UIImageObject);

	// [Health Symbol]
	UIImageTransform.x = (int)position.m_x + 7;
	UIImageTransform.y = (int)position.m_y + ((int)size.m_y / 2) - 15;
	UIImageTransform.w = 30;
	UIImageTransform.h = 30;

	UIImageObject = new UIObject(UIImageTransform, HEALTHUI, 3);

	m_mpUIObjects.push_back(UIImageObject);

	// [BlankBar]
	UIImageTransform.x = (int)position.m_x + 45;
	UIImageTransform.y = (int)position.m_y + 12;
	UIImageTransform.w = (int)size.m_x - 60;
	UIImageTransform.h = (int)size.m_y - 25;

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

