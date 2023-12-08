#include "LoadFileScene.h"
#include "ImageDirectory.h"
#include "Platformer.h"
#include "GameDemo.h"
#include "SaveFileDirectory.h"
#include <assert.h>

LoadFileScene::LoadFileScene(Platformer* pOwner)
	:
	loadIndex(0),
	m_keyboardButtonIndex(-1),
	m_pOwner(pOwner),
	m_background_1(Vector2<double>{ 0, 0 }, Vector2<double>{WINDOWWIDTH, WINDOWHEIGHT }, nullptr, BACKGROUND, 0, 0, "BackGround"),
	m_background_2(Vector2<double>{ WINDOWWIDTH, 0 }, Vector2<double>{ WINDOWWIDTH, WINDOWHEIGHT }, nullptr, BACKGROUND, 0, 0, "BackGround")
{
}

LoadFileScene::~LoadFileScene()
{
}

void LoadFileScene::Enter()
{
	// Background Setups
	m_background_1.TryMove(Vector2<double>(LEFT), BACKGROUND_MOVE_SPEED);
	m_background_2.TryMove(Vector2<double>(LEFT), BACKGROUND_MOVE_SPEED);

	// Set button objects
	SetButtons();
}

void LoadFileScene::Update(double deltaTime)
{
	BackgroundUpdates(deltaTime);
	ButtonUpdates(deltaTime);
}

void LoadFileScene::Render(SDL_Renderer* pRenderer, Textures* pTextures)
{
	m_background_1.Render(pRenderer, pTextures->GetTexture(m_background_1.GetTextureName()));
	m_background_2.Render(pRenderer, pTextures->GetTexture(m_background_1.GetTextureName()));

	for (auto& element : m_vpButtons)
	{
		element->Render(pRenderer, pTextures->GetTexture(element->GetTextureName()));
	}
}

bool LoadFileScene::HandleEvent(SDL_Event* pEvent)
{
	// buttons handles event its own
	for (auto& element : m_vpButtons)
	{
		element->HandleEvent(pEvent);
	}

	// Quit when true returns
	switch (pEvent->type)
	{
		// Reset keyboard index when mouse event happens
		case SDL_MOUSEMOTION:
		{
			m_keyboardButtonIndex = -1;
			break;
		}
		// Mouse Event
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		{
			if (ProcessMouseEvent(&pEvent->button) == true)
				return true;
			break;
		}

		// Keyboard Event
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		{
			if (ProcessKeyboardEvent(&pEvent->key) == true)
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
		default:
			break;
	}

	return false;
}

void LoadFileScene::Exit()
{
	Destory();
}

bool LoadFileScene::ProcessMouseEvent(SDL_MouseButtonEvent* pData)
{
	return false;
}

bool LoadFileScene::ProcessKeyboardEvent(SDL_KeyboardEvent* pData)
{
	if ((int)pData->state == 1 && (int)pData->repeat == 0)   // Key Press, ignore repeat keys
	{
		switch ((int)pData->keysym.sym)
		{
			// pasue music
			case SDLK_p:
			{
				m_pOwner->ToggleMusic();
				break;
			}
			// Move Up
			case SDLK_w:
			case SDLK_UP:
			{
				ChangeButtonFocus(-1);
				break;
			}

			// Move Down
			case SDLK_s:
			case SDLK_DOWN:
			{
				ChangeButtonFocus(1);
				break;
			}
			case SDLK_SPACE:
			case SDLK_RETURN:
			{
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
	return false;
}

void LoadFileScene::SetButtons()
{
	ButtonObject* button;
	SDL_Rect buttonTransform;

	// [Load Button 1]
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		100,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	// Font to use in button object
	TTF_Font* font = m_pOwner->GetGame()->GetFonts()->GetFont(FONT1);

	Button_State buttonState;

	if (m_pOwner->GetSaveData()->Load(_SAVE_FOLDER_1, _SAVE_STAGE))
		buttonState = Button_State::kNormal;
	else
		buttonState = Button_State::kDisable;

	button = new ButtonObject(buttonTransform, BUTTONS, buttonState, "LOAD 1");

	// Set Callback for button
	button->SetCallback([this]()->void
		{
			size_t stage = LoadSaveFile(1);
			loadIndex = 1;
			if (stage == 1)
			{
				SetSceneOnLoad(stage,loadIndex);
			}
			else if (stage == 2)
			{
				SetSceneOnLoad(stage, loadIndex);
			}
		});

	button->SetTextInButton(font, "LOAD 1", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());
	m_vpButtons.push_back(button);

	// [Load Button 2]
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		200,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	if (m_pOwner->GetSaveData()->Load(_SAVE_FOLDER_2, _SAVE_STAGE))
		buttonState = Button_State::kNormal;
	else
		buttonState = Button_State::kDisable;

	button = new ButtonObject(buttonTransform, BUTTONS, buttonState, "LOAD 2");

	button->SetTextInButton(font, "LOAD 2", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());

	button->SetCallback([this]()->void
		{
			size_t stage = LoadSaveFile(2);
			loadIndex = 2;
			if (stage == 1)
			{
				SetSceneOnLoad(stage, loadIndex);
			}
			else if (stage == 2)
			{
				SetSceneOnLoad(stage, loadIndex);
			}
		});

	m_vpButtons.push_back(button);

	// [Load Button 3]
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		300,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	if (m_pOwner->GetSaveData()->Load(_SAVE_FOLDER_3, _SAVE_STAGE))
		buttonState = Button_State::kNormal;
	else
		buttonState = Button_State::kDisable;

	button = new ButtonObject(buttonTransform, BUTTONS, buttonState, "LOAD 3");

	button->SetTextInButton(font, "LOAD 3", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());

	button->SetCallback([this]()->void
		{
			size_t stage = LoadSaveFile(3);
			loadIndex = 3;
			if (stage == 1)
			{
				SetSceneOnLoad(stage, loadIndex);
			}
			else if (stage == 2)
			{
				SetSceneOnLoad(stage, loadIndex);
			}
		});

	m_vpButtons.push_back(button);

	// [Main Menu]
	buttonTransform = SDL_Rect
	{
		(int)(WINDOWWIDTH / 2) - (int)(BUTTON_WIDTH / 2),	// X
		400,				// Y
		(int)BUTTON_WIDTH,	// W
		(int)BUTTON_HEIGHT	// H
	};

	button = new ButtonObject(buttonTransform, BUTTONS, Button_State::kNormal, "Back");

	button->SetCallback([this]()->void
		{
			m_pOwner->LoadScene(Platformer::SceneName::kMainMenu);
		});

	button->SetTextInButton(font, "BACK", SDL_Color(BLUE), m_pOwner->GetGame()->GetRenderer());
	m_vpButtons.push_back(button);
}

void LoadFileScene::BackgroundUpdates(double deltaTime)
{
	// Update Background
	m_background_1.Update(deltaTime);
	m_background_2.Update(deltaTime);

	if (m_background_1.GetTransform().x <= -WINDOWWIDTH)
	{
		m_background_1.SetPosition(Vector2<double>{ WINDOWWIDTH, 0.0 });
	}
	else if (m_background_2.GetTransform().x <= -WINDOWWIDTH)
	{
		m_background_2.SetPosition(Vector2<double>{ WINDOWWIDTH, 0.0 });
	}
}

void LoadFileScene::ButtonUpdates(double deltaTime)
{
	for (auto& element : m_vpButtons)
	{
		element->Update(deltaTime);
	}
}

void LoadFileScene::Destory()
{
	for (auto& element : m_vpButtons)
	{
		delete element;
	}
}

void LoadFileScene::ChangeButtonFocus(int direction)
{
	assert(m_vpButtons.size() > 0);

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
	for (size_t i = 0; i < m_vpButtons.size(); ++i)
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

void LoadFileScene::SetSceneOnLoad(size_t level, size_t fileNumber)
{
	switch (level)
	{
		case 0:
		{
			m_pOwner->LoadScene(Platformer::SceneName::kGamePlay, fileNumber);
			break;
		}
		case 1:
		{
			m_pOwner->LoadScene(Platformer::SceneName::kGamePlay, fileNumber);
			break;
		}
		case 2:
		{
			m_pOwner->LoadScene(Platformer::SceneName::kBoss, fileNumber);
			break;
		}
		default:
			break;

	}
}

size_t LoadFileScene::LoadSaveFile(size_t index)
{
	size_t loadedLevel = 0;

	switch (index)
	{
		case 1:
		{
			m_pOwner->GetSaveData()->Load(_SAVE_FOLDER_1, _SAVE_STAGE);
			loadedLevel = (size_t)m_pOwner->GetSaveData()->GetData().m_stage;
			break;
		}
		case 2:
		{
			m_pOwner->GetSaveData()->Load(_SAVE_FOLDER_2, _SAVE_STAGE);
			loadedLevel = (size_t)m_pOwner->GetSaveData()->GetData().m_stage;
			break;
		}
		case 3:
		{
			m_pOwner->GetSaveData()->Load(_SAVE_FOLDER_3, _SAVE_STAGE);
			loadedLevel = (size_t)m_pOwner->GetSaveData()->GetData().m_stage;
			break;
		}
	default:
		break;
	}

	return loadedLevel;
}
