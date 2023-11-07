#include "CreditsScene.h"
#include "Textures.h"
#include "Platformer.h"
#include "GameDemo.h"
#include "ImageDirectory.h"

CreditsScene::CreditsScene(Platformer* pOwner)
	:
	m_pOwner(pOwner),
	m_background_1(Vector2{ 0,0 }, Vector2{ WINDOWWIDTH, WINDOWHEIGHT }, nullptr, BACKGROUND),
	m_background_2(Vector2{ WINDOWWIDTH,0 }, Vector2{ WINDOWWIDTH, WINDOWHEIGHT }, nullptr, BACKGROUND),
	m_skipInfo_1(Vector2{ (WINDOWWIDTH - 150),(WINDOWHEIGHT - 50) },
				 pOwner->GetGame()->GetFonts()->GetFont(FONT2),
				 SDL_Color{WHITE},
				 pOwner->GetGame()->GetRenderer()),
	m_skipInfo_2(Vector2{ (WINDOWWIDTH - 150),(WINDOWHEIGHT - 30) },
				 pOwner->GetGame()->GetFonts()->GetFont(FONT2),
				 SDL_Color{ WHITE },
				 pOwner->GetGame()->GetRenderer())
{
}

CreditsScene::~CreditsScene()
{
}

void CreditsScene::Enter()
{
	InitCreditScene();
}

void CreditsScene::Update(double deltaTime)
{
	UpdateBackgrounds(deltaTime);
	

	if(!m_vpCreditsText.empty())
	{
		for (auto& element : m_vpCreditsText)
		{
			size_t index = 0;
			element->Update(deltaTime);
			if (element->GetTransform().y < -50)
			{
				delete element;
				m_vpCreditsText.erase(m_vpCreditsText.begin() + index);
			}
			++index;
		}
	}
	else
	{
		m_pOwner->LoadScene(Platformer::SceneName::kMainMenu);
	}
}

void CreditsScene::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	// Background
	m_background_1.Render(pRenderer, pTextures->GetTexture(m_background_1.GetTextureName()));
	m_background_2.Render(pRenderer, pTextures->GetTexture(m_background_2.GetTextureName()));

	// Skip Info
	m_skipInfo_1.Render(pRenderer);
	m_skipInfo_2.Render(pRenderer);

	// Credit Text objects
	for (auto& element : m_vpCreditsText)
	{
		element->Render(pRenderer);
	}
}

bool CreditsScene::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
	// Keyboard Event
	case SDL_KEYDOWN:
	case SDL_KEYUP:
	{
		if (ProcessKeyboardEvent(&pEvent->key) == true)
			return true;
		break;
	}
	}
	return false;
}

void CreditsScene::Exit()
{
	Destory();
}

void CreditsScene::InitCreditScene()
{
	
	m_background_1.TryMove(Vector2{ LEFT });
	m_background_2.TryMove(Vector2{ LEFT });

	TextObject* text;


	// TITLE
	// Color of the text
	SDL_Color color{ BLACK };

	// Type of font
	TTF_Font* font = m_pOwner->GetGame()->GetFonts()->GetFont(FONT3);

	SDL_Renderer* pRenderer = m_pOwner->GetGame()->GetRenderer();

	text = new TextObject(s_kStartingPosition,font,color,pRenderer);

	// Set text to render
	text->SetText("[PLATFORMER]");

	// Direction to move
	text->TryMove(Vector2{ UP });

	// Add to vector
	m_vpCreditsText.push_back(text);

	// CREDIT
	text = new TextObject(Vector2{ s_kStartingPosition.m_x,s_kStartingPosition.m_y + 100 }, font, color, pRenderer);

	text->SetText("Programmed by: ");

	text->TryMove(Vector2{ UP });
	
	m_vpCreditsText.push_back(text);


	text = new TextObject(Vector2{ s_kStartingPosition.m_x,s_kStartingPosition.m_y + 200 }, font, color, pRenderer);

	text->SetText("Thank You!");

	text->TryMove(Vector2{ UP });

	m_vpCreditsText.push_back(text);

	// Skip Info
	font = m_pOwner->GetGame()->GetFonts()->GetFont(FONT2);
	
	m_skipInfo_1.SetText("Return: Skip");
	m_skipInfo_2.SetText("Spacebar: FastForward");


}

bool CreditsScene::ProcessKeyboardEvent(SDL_KeyboardEvent* pData)
{
	if ((int)pData->state == 1 && (int)pData->repeat == 0)   // Key Press, ignore repeat keys
	{
		switch ((int)pData->keysym.sym)
		{
			case SDLK_SPACE:
			{
				for (auto& element : m_vpCreditsText)
					element->SetSpeed(100);
				break;
			}
			case SDLK_RETURN:
			{
				m_pOwner->LoadScene(Platformer::SceneName::kMainMenu);
				break;
			}
		default:
			break;
		}
	}
	// Key Release
	else if ((int)pData->state == 0)
	{
		switch ((int)pData->keysym.sym)
		{
			case SDLK_SPACE:
			{
				for (auto& element : m_vpCreditsText)
					element->SetSpeed(50);
				break;
			}
		default:
			break;
		}
	}
	return false;
}

void CreditsScene::UpdateBackgrounds(double deltaTime)
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

void CreditsScene::Destory()
{
	for (auto& element : m_vpCreditsText)
	{
		delete element;
	}
}
