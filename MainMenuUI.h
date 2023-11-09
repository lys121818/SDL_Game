#pragma once
#include "UIInterface.h"
#include "TextObject.h"
#include "SDL_ttf.h"
#include "Fonts.h"
#include "ButtonObject.h"
#include "ImageObject.h"
#include <fstream>
#include <map>
#include <string>

class GameState;
class MainMenuUI : public UIInterface
{
	static constexpr size_t s_kMaxCharCount = 10;
private:
	Fonts* m_pFont;

	SDL_Renderer* m_pRenderer;

	// Textbox for User Input
	TextObject* m_pTextImage;

	// Text of user input
	std::string m_text;

	// Input Boxes
	ImageObject* m_pTextBox;

	// Text for Instruction
	TextObject* m_pInfoText;

	// Buttons
	std::vector<ButtonObject*> m_vpButtons;

	// Index of selected button
	int m_keyboardButtonIndex;

	// Check if the job is done
	bool m_isSet;

	// Check if the info already exist
	bool m_isNew;

public:
	MainMenuUI(Fonts* pFont, SDL_Renderer* pRenderer);
	~MainMenuUI();

	void InitUI() override;

	// Inherited via UIInterface
	// Update on call
	void UpdateUI() override;

	// Update in loop
	void UpdateUI(double deltaTime) override;

	void Render(SDL_Renderer* pRenderer, Textures* pTextures) override;

	bool HandleEvent(SDL_Event* pEvent) override;

private:

	// PROCESSING EVENT
	bool ProcessTextInputEvent(SDL_TextInputEvent* pEvent);
	// Every events using keyboards works here
	bool ProcessKeyboardEvent(SDL_KeyboardEvent* pData);

	// Changes button focus when using keyboard
	void ChangeButtonFocus(int direction);

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