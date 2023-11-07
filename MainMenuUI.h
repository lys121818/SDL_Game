#pragma once
#include "UIInterface.h"
#include "TextObject.h"
#include "SDL_ttf.h"
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
	SDL_Color m_color;

	TextObject* m_pTextImage;

	std::string m_text;

	std::map<SDL_Rect*,SDL_Color*> m_vpTextBoxes;

	std::fstream m_pTxtFile;
public:
	MainMenuUI(TTF_Font* pFont,SDL_Color color, SDL_Renderer* pRenderer);
	~MainMenuUI();

	void InitUI() override;

	// Inherited via UIInterface
	void UpdateUI() override;
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

	void SaveTextFile();

	void UpdateTextbox();

	void TextBoxSettings();

	void Destory();

};