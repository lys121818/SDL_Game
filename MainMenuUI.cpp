#include "MainMenuUI.h"
#include "MainMenu.h"

MainMenuUI::MainMenuUI(TTF_Font* pFont, SDL_Color color, SDL_Renderer* pRenderer)
	:
	m_pFont(pFont),
	m_color(color),
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
}

void MainMenuUI::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	// TODO change this vector text boxes to image object
	for (auto& element : m_vpTextBoxes)
	{
		SDL_SetRenderDrawColor(pRenderer,element.second->r,element.second->g,element.second->b,element.second->a);
		SDL_RenderFillRect(pRenderer, element.first);
	}
	m_pTextImage->Render(pRenderer);
}

bool MainMenuUI::HandleEvent(SDL_Event* pEvent)
{
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
	return false;
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
			SaveTextFile();
			return true;
			break;
		}
		default:
			break;
		}
	}
	return false;
}

bool MainMenuUI::ProcessMouseEvent(SDL_MouseButtonEvent* pData)
{

	return false;
}

bool MainMenuUI::ProcessWindowEvent(SDL_WindowEvent* pData)
{

	return false;
}

void MainMenuUI::SaveTextFile()
{
	std::ofstream file;
	file.open(PLAYER_INFO, std::ofstream::out | std::ofstream::trunc);
	file << m_text;
	file.close();
}

void MainMenuUI::UpdateTextbox()
{
	m_pTextImage->SetText(m_text.c_str());
}

void MainMenuUI::TextBoxSettings()
{
	// text Writing
	m_pTextImage = new TextObject(Vector2{ WINDOWWIDTH / 2,WINDOWHEIGHT / 2}, m_pFont, m_color, m_pRenderer);

	std::pair<SDL_Rect*, SDL_Color*> pair;


	pair.first = new SDL_Rect{ (WINDOWWIDTH / 2) - 165,(WINDOWHEIGHT / 2) - 30,330,60 };
	pair.second = new SDL_Color{ BLACK };
	m_vpTextBoxes.insert(pair);

	pair.first = new SDL_Rect{ (WINDOWWIDTH / 2) - 150,(WINDOWHEIGHT / 2) - 25,300,50 };
	pair.second = new SDL_Color{ BLUE };
	m_vpTextBoxes.insert(pair);


}

void MainMenuUI::Destory()
{
	for (auto& element : m_vpTextBoxes)
	{
		delete element.first;
		delete element.second;
	}
	delete m_pTextImage;
}
