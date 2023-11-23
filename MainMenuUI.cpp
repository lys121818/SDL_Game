#include "MainMenuUI.h"
#include "MainMenu.h"
#include "ImageDirectory.h"
#include <assert.h>
MainMenuUI::MainMenuUI(Fonts* pFont, SDL_Renderer* pRenderer)
	:
	m_isSet(false),
	m_isNew(true),
	m_pFont(pFont),
	m_pRenderer(pRenderer),
	m_pTextImage(nullptr),
	m_pTextBox(nullptr),
	m_keyboardButtonIndex(-1),
	m_pInfoText(nullptr)
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
	// Remove all buttons except accept button
	if (m_isNew && m_vpButtons.size() > 1)
	{
		for (size_t i = 1; i < m_vpButtons.size(); ++i)
		{
			delete m_vpButtons[i];
			m_vpButtons.pop_back();
		}
	}

	// [Buttons]
	for (auto& element : m_vpButtons)
	{
		element->Update(deltaTime);
	}

}

void MainMenuUI::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	// [Box]
	m_pTextBox->Render(pRenderer, pTextures->GetTexture(m_pTextBox->GetTextureName()));

	// [Buttons]
	for (auto& element : m_vpButtons)
	{
		element->Render(pRenderer, pTextures->GetTexture(element->GetTextureName()));
	}

	// [User Input]
	// Create Mode
	if (m_isNew)
	{
		if(m_text.size())
			m_pTextImage->Render(pRenderer);
	}
	// [Info Text]
	// Select Mode
	else
	{
		m_pInfoText->Render(pRenderer);
	}

}

bool MainMenuUI::HandleEvent(SDL_Event* pEvent)
{
	// [Buttons]
	for (auto& element : m_vpButtons)
	{
		element->HandleEvent(pEvent);
	}

	switch (pEvent->type)
	{
		case SDL_MOUSEMOTION:
		{
			// Set default
			m_keyboardButtonIndex = -1;
			break;
		}
		case SDL_TEXTINPUT:
		{
			// Create Mode
			if (m_isNew)
			{
				ProcessTextInputEvent(&pEvent->text);
			}
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
			// Get user input
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
		// Keyboard Event on Create Mode
		if (m_isNew)
		{
			switch ((int)pData->keysym.sym)
			{
				case SDLK_LEFT:
				{
					ChangeButtonFocus(-1);
					break;
				}
				case SDLK_RIGHT:
				{
					ChangeButtonFocus(1);
					break;
				}

				// Erase text
				case SDLK_BACKSPACE:
				{
					if (m_text.size())
					{
						m_text.pop_back();
						UpdateUI();
					}
					break;
				}

				// Trigger Button
				case SDLK_RETURN:
				{
					// Select
					if (m_keyboardButtonIndex >= 0 && m_keyboardButtonIndex < (int)m_vpButtons.capacity())
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

		// Keyboard Event on Select Mode
		else
		{
			switch ((int)pData->keysym.sym)
			{
				case SDLK_a:
				case SDLK_LEFT:
				{
					ChangeButtonFocus(-1);
					break;
				}

				case SDLK_d:
				case SDLK_RIGHT:
				{
					ChangeButtonFocus(1);
					break;
				}

				// Trigger Button
				case SDLK_SPACE:
				case SDLK_RETURN:
				{
					// Select
					if (m_keyboardButtonIndex >= 0 && m_keyboardButtonIndex < (int)m_vpButtons.capacity())
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
	}

	return m_isSet;
}

void MainMenuUI::ChangeButtonFocus(int direction)
{
	assert(m_vpButtons.size() > 0);

	// index to move
	int nextDirectionIndex = (m_keyboardButtonIndex + direction);

	// set to first index if its negative value
	if (nextDirectionIndex < 0)
	{
		m_keyboardButtonIndex = 0;
	}
	// set to last index if its over size
	else if (nextDirectionIndex >= (int)m_vpButtons.size())
	{
		m_keyboardButtonIndex = (int)(m_vpButtons.size() - 1);
	}
	else
	{
		m_keyboardButtonIndex = nextDirectionIndex;
	}

	// if the button is disable and next index exist
	if (!m_vpButtons[m_keyboardButtonIndex]->GetAble() &&
		(m_keyboardButtonIndex + direction >= 0 && m_keyboardButtonIndex + direction < (int)m_vpButtons.size()))
	{

		ChangeButtonFocus(direction);
	}

	// Change Hover setting if the button is able
	for (size_t i = 0; i < (int)m_vpButtons.size(); ++i)
	{
		if (m_vpButtons[m_keyboardButtonIndex]->GetAble())
		{
			if (i == m_keyboardButtonIndex)
				m_vpButtons[i]->SetHover(true);
			else
				m_vpButtons[i]->SetHover(false);
		}
	}

}

void MainMenuUI::SaveTextFile(std::string text)
{
	std::ofstream file;

	// Clear txt file before save
	file.open(PLAYER_INFO, std::ofstream::out | std::ofstream::trunc);

	file << text;

	file.close();

	m_isSet = true;
}

void MainMenuUI::UpdateTextbox()
{
	if(m_text.size())
		m_pTextImage->SetText(m_text.c_str());
}

void MainMenuUI::UpdateButton()
{
	// Create Mode
	if (m_isNew)
	{
		// Accept button
		if (m_text.size())
		{
			m_vpButtons[0]->SetAble(true);
		}
		else
		{
			m_vpButtons[0]->SetAble(false);
		}
	}
}

void MainMenuUI::TextBoxSettings()
{
	std::ifstream file;

	// Check if the file is empty
	file.open(PLAYER_INFO);

	if (file.get() > 0)
		m_isNew = false;

	file.close();
	
	// [Buttons]
	SDL_Rect buttonTransform;
	ButtonObject* newButton;
	TTF_Font* font;

	// Accept Button
	font = m_pFont->GetFont(FONT2);

	buttonTransform = SDL_Rect{ ZERO, (int)BUTTON_WIDTH,(int)BUTTON_HEIGHT };
	
	newButton = new ButtonObject(buttonTransform, BUTTONS, Button_State::kDisable, "Accept");

	newButton->SetTextInButton(font, "ACCEPT", SDL_Color{ BLACK }, m_pRenderer);

	m_vpButtons.push_back(newButton);

	// Cancle Button
	newButton = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Cancle");

	newButton->SetTextInButton(font, "CANCLE", SDL_Color{ BLACK }, m_pRenderer);

	m_vpButtons.push_back(newButton);

	// [User Input]
	m_pTextImage = new TextObject(Vector2<double>{ WINDOWWIDTH / 2,WINDOWHEIGHT / 2}, font, SDL_Color{ BLACK }, m_pRenderer);

	// [Box]
	m_pTextBox = new ImageObject
	(
		Vector2<double>{ (WINDOWWIDTH / 2) - 165,(WINDOWHEIGHT / 2) - 30 },
		Vector2<double>{ 330,60 },
		nullptr,
		TEXT_BAR
	);

	// [Instruction]
	m_pInfoText = new TextObject
	(
		Vector2<double>{ (WINDOWWIDTH / 2),(WINDOWHEIGHT / 2) - 50 },
		font, SDL_Color{ BLACK },
		m_pRenderer
	);

	m_pInfoText->SetText("Want to reset the Character?");

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
	// [Accept button]
	// Make Deactive
	m_vpButtons[0]->SetAble(false);

	// Set position
	m_vpButtons[0]->SetPosition(Vector2<double>{ (WINDOWWIDTH / 2) - (BUTTON_WIDTH / 2), (WINDOWHEIGHT / 2) + 100 });

	// Set Text
	m_vpButtons[0]->SetTextInButton(m_pFont->GetFont(FONT2), "ACCEPT", SDL_Color{BLACK}, m_pRenderer);

	// Set callback
	m_vpButtons[0]->SetCallback([this]()->void
		{
			SaveTextFile(m_text);
		});

	// [Box]
	// Change box position
	SDL_Rect boxTransform
	{
		(WINDOWWIDTH / 2) - 165,
		(WINDOWHEIGHT / 2) - 30,
		330,
		60
	};

	m_pTextBox->SetTransform(boxTransform);
}

void MainMenuUI::SelectMode()
{
	// [Accept button]
	// Make Active
	m_vpButtons[0]->SetAble(true);

	// Set position
	m_vpButtons[0]->SetPosition(Vector2<double>{ (WINDOWWIDTH / 2) - (BUTTON_WIDTH / 2) - 150, (WINDOWHEIGHT / 2) + 100 });

	// Set Text
	m_vpButtons[0]->SetTextInButton(m_pFont->GetFont(FONT2), "YES", SDL_Color{ BLACK }, m_pRenderer);

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

	// [Cancle button]
	// Make Active
	m_vpButtons[1]->SetAble(true);

	// Set position
	m_vpButtons[1]->SetPosition(Vector2<double>{ (WINDOWWIDTH / 2) - (BUTTON_WIDTH / 2) + 150, (WINDOWHEIGHT / 2) + 100 });

	// Set Text
	m_vpButtons[1]->SetTextInButton(m_pFont->GetFont(FONT2), "NO", SDL_Color{ BLACK }, m_pRenderer);

	// Set callback
	m_vpButtons[1]->SetCallback([this]()->void
		{
			m_isSet = true;
		});

	// [Box]
	// Change box position
	SDL_Rect boxTransform
	{
		(WINDOWWIDTH / 2) - 325,
		(WINDOWHEIGHT / 2) - 100,
		650,
		100
	};

	m_pTextBox->SetTransform(boxTransform);
}

void MainMenuUI::Destory()
{
	for (auto& element : m_vpButtons)
	{
		delete element;
	}

	if (m_pTextBox != nullptr)
		delete m_pTextBox;

	if(m_pTextImage != nullptr)
		delete m_pTextImage;

	if (m_pInfoText != nullptr)
		delete m_pInfoText;
}
