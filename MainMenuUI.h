#pragma once
#include "UIInterface.h"
#include "TextObject.h"
#include "SDL_ttf.h"
#include "ButtonObject.h"
#include <fstream>
#include <map>
#include <string>

class GameState;
class MainMenuUI : public UIInterface
{
	static constexpr size_t s_kMaxCharCount = 10;
private:
	TTF_Font* m_pFont;
	SDL_Renderer* m_pRenderer;

	// Textbox for User Input
	TextObject* m_pTextImage;

	// Text of user input
	std::string m_text;

	// Input Boxes
	std::map<SDL_Rect*,SDL_Color*> m_vpTextBoxes;

	// Buttons
	std::vector<ButtonObject*> m_vpButtons;

	// Check if the job is done
	bool m_isSet;

	// Check if the info already exist
	bool m_isNew;

public:
	MainMenuUI(TTF_Font* pFont, SDL_Renderer* pRenderer);
	~MainMenuUI();

	void InitUI() override;

	// Inherited via UIInterface
	void UpdateUI() override;
	void UpdateUI(double deltaTime) override;
	void Render(SDL_Renderer* pRenderer, Textures* pTextures) override;

	virtual bool HandleEvent(SDL_Event* pEvent) override;



private:

	// PROCESSING EVENT
	bool ProcessTextInputEvent(SDL_TextInputEvent* pEvent);
	// Every events using keyboards works here
	bool ProcessKeyboardEvent(SDL_KeyboardEvent* pData);
	// Every events using mouse works here
	bool ProcessMouseEvent(SDL_MouseButtonEvent* pData);
	// Every events using Window works here
	bool ProcessWindowEvent(SDL_WindowEvent* pData);

	// Save the text in txt file
	void SaveTextFile(std::string text = "");

	// Update UI (On call Updates)
	void UpdateTextbox();
	void UpdateButton();

	// Settings of UI placement
	void TextBoxSettings();

	// Modes
	void CreateMode();
	void SelectMode();

	// delete allocated memories
	void Destory();

};