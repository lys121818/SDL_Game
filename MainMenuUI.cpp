#include "MainMenuUI.h"
#include "MainMenu.h"
#include "ImageDirectory.h"
#include <assert.h>
MainMenuUI::MainMenuUI(TTF_Font* pFont, SDL_Renderer* pRenderer)
	:
	m_isSet(false),
	m_isNew(true),
	m_pFont(pFont),
	m_pRenderer(pRenderer),
	m_pTextImage(nullptr)
{
	
}

MainMenuUI::~MainMenuUI()
{
	Destory();
}

void MainMenuUI::InitUI()
{
	TextBoxSettings();
}

void MainMenuUI::UpdateUI()
{
	UpdateTextbox();
	UpdateButton();
}

void MainMenuUI::UpdateUI(double deltaTime)
{
	if (m_vpButtons.size() > 1 && m_isNew)
	{
		delete m_vpButtons[1];
		m_vpButtons.pop_back();
	}
	for (auto& element : m_vpButtons)
	{
		element->Update(deltaTime);
	}

}

void MainMenuUI::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	// TODO change this vector text boxes to image object
	if (m_isNew)
	{
		for (auto& element : m_vpTextBoxes)
		{
			SDL_SetRenderDrawColor(pRenderer,element.second->r,element.second->g,element.second->b,element.second->a);
			SDL_RenderFillRect(pRenderer, element.first);
		}
		m_pTextImage->Render(pRenderer);

	}

	for (auto& element : m_vpButtons)
	{
		element->Render(pRenderer, pTextures->GetTexture(element->GetTextureName()));
	}
}

bool MainMenuUI::HandleEvent(SDL_Event* pEvent)
{
	for (auto& element : m_vpButtons)
	{
		element->HandleEvent(pEvent);
	}
	switch (pEvent->type)
	{
		case SDL_TEXTINPUT:
		{
			ProcessTextInputEvent(&pEvent->text);
			break;
		}
		case SDL_KEYDOWN:
		{
			if (ProcessKeyboardEvent(&pEvent->key) == true)
				return true;
			break;
		}
	default:
		break;
	}
	return m_isSet;
}

bool MainMenuUI::ProcessTextInputEvent(SDL_TextInputEvent* pData)
{
	switch ((int)pData->type)
	{
		case SDL_TEXTINPUT:
		{
			if (m_text.size() < s_kMaxCharCount)
			{
				m_text += pData->text;
				UpdateUI();
			}
			break;
		}
	default:
		break;
	}
	return false;
}

bool MainMenuUI::ProcessKeyboardEvent(SDL_KeyboardEvent* pData)
{
	if ((int)pData->state == 1 && (int)pData->repeat == 0)   // Key Press, ignore repeat keys
	{
		switch ((int)pData->keysym.sym)
		{
		case SDLK_BACKSPACE:
		{
			if (m_text.size())
			{
				m_text.pop_back();
				UpdateUI();
			}
			break;
		}
		case SDLK_RETURN:
		{
			if (m_text.size())
			{
				SaveTextFile(m_text);
				return m_isSet;
			}
			break;
		}
		default:
			break;
		}
	}
	return m_isSet;
}


void MainMenuUI::SaveTextFile(std::string text)
{
	std::ofstream file;
	file.open(PLAYER_INFO, std::ofstream::out | std::ofstream::trunc);
	file << text;
	file.close();
	m_isSet = true;
}

void MainMenuUI::UpdateTextbox()
{
	m_pTextImage->SetText(m_text.c_str());
}

void MainMenuUI::UpdateButton()
{
	if (m_isNew)
	{
		// When creating new accept button
		if (m_text.size())
		{
			// accept button
			m_vpButtons[0]->SetAble(true);
		}
		else
			m_vpButtons[0]->SetAble(false);
	}
	//m_pAcceptButton->Update(NULL);
}

void MainMenuUI::TextBoxSettings()
{
	std::ifstream file;

	// Check if the file is empty
	file.open(PLAYER_INFO);
	if (file.get() > 0)
		m_isNew = false;
	file.close();
	
	SDL_Rect buttonTransform;
	ButtonObject* newButton;
	// Accept Button
	buttonTransform = SDL_Rect{ ZERO, 200,50 };
	
	newButton = new ButtonObject(buttonTransform, BUTTONS, Button_State::kDisable, "Accept");

	newButton->SetTextInButton(m_pFont, "ACCEPT", SDL_Color{ BLACK }, m_pRenderer);

	m_vpButtons.push_back(newButton);

	// Cancle Button
	newButton = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Cancle");

	newButton->SetTextInButton(m_pFont, "CANCLE", SDL_Color{ BLACK }, m_pRenderer);

	m_vpButtons.push_back(newButton);

	// text Box
	m_pTextImage = new TextObject(Vector2{ WINDOWWIDTH / 2,WINDOWHEIGHT / 2}, m_pFont, SDL_Color{ BLACK }, m_pRenderer);

	std::pair<SDL_Rect*, SDL_Color*> pair;

	pair.first = new SDL_Rect{ (WINDOWWIDTH / 2) - 165,(WINDOWHEIGHT / 2) - 30,330,60 };
	pair.second = new SDL_Color{ BLACK };
	m_vpTextBoxes.insert(pair);

	pair.first = new SDL_Rect{ (WINDOWWIDTH / 2) - 150,(WINDOWHEIGHT / 2) - 25,300,50 };
	pair.second = new SDL_Color{ BLUE };
	m_vpTextBoxes.insert(pair);

	// Creating Mode
	if (m_isNew)
	{
		CreateMode();
	}
	// User select Mode
	else
	{
		SelectMode();
	}



}

void MainMenuUI::CreateMode()
{
	// Accept button
	// Set position
	m_vpButtons[0]->SetPosition(Vector2{ (int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2), (int)(WINDOWHEIGHT / 2) + 100 });

	// Set callback
	m_vpButtons[0]->SetCallback([this]()->void
		{
			SaveTextFile(m_text);
		});
}

void MainMenuUI::SelectMode()
{
	// Accept button
	// Make Active
	m_vpButtons[0]->SetAble(true);

	// Set position
	m_vpButtons[0]->SetPosition(Vector2{ (int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2) - 150, (int)(WINDOWHEIGHT / 2) + 100 });

	// Set callback
	m_vpButtons[0]->SetCallback([this]()->void
		{
			// Empty txt file
			std::ifstream file;
			file.open(PLAYER_INFO, std::ofstream::out | std::ofstream::trunc);
			file.close();

			m_isNew = true;
			CreateMode();
		});

	// Cancle button
	// Make Active
	m_vpButtons[1]->SetAble(true);

	// Set position
	m_vpButtons[1]->SetPosition(Vector2{ (int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2) + 150, (int)(WINDOWHEIGHT / 2) + 100 });

	// Set callback
	m_vpButtons[1]->SetCallback([this]()->void
		{
			m_isSet = true;
		});
}

void MainMenuUI::Destory()
{
	for (auto& element : m_vpTextBoxes)
	{
		delete element.first;
		delete element.second;
	}
	for (auto& element : m_vpButtons)
	{
		delete element;
	}

	if(m_pTextImage != nullptr)
		delete m_pTextImage;
}
