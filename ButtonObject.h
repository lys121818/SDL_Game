#pragma once
#include <SDL.h>
#include <functional>

#include "GameObject.h"
#include "ImageComponent.h"
#include "Status.h"
#include "ButtonType.h"
#include "TextComponent.h"

class ButtonObject : public GameObject
{
private:
	Button_State m_currentState;
	// Name Of the Object
	const char* m_pSpriteName;

	// Transform of the object
	SDL_Rect m_transform;
	
	// Image componenet of the object
	ImageComponent m_imageComponent;

	// Text on button image
	TextComponent m_textComponent;

	// Not Needed in this game object (considering of other ways to handle this)
	Status m_status;

	// Mouse state Check
	bool m_isOnHover;

	bool m_isAble;

	bool m_isClicked;

	std::function<void()> m_callback;

public:
	ButtonObject(SDL_Rect transform, const char* directory, Button_State type, const char* name = "UnNamed");
	~ButtonObject();
	
	void Update(double deltaTime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture);

	// Inherited via GameObject
	Status GetStatus() override { return m_status; }
	SDL_Rect GetTransform() override { return m_transform; }

	virtual const char* GetTextureName() { return m_pSpriteName; }

	virtual void HandleEvent(SDL_Event* pEvent);

	bool GetAble() { return m_isAble; }

	bool GetClicked() { return m_isClicked; }

	void SetHover(bool isHover) { m_isOnHover = isHover; }

	void SetClick(bool isClick) { m_isClicked = isClick; }

	void SetTextInButton(TTF_Font* pFont, const char* pText, SDL_Color color, SDL_Renderer* pRenderer);

	void SetCallback(std::function<void()> callback) { m_callback = callback; }
private:
	void ButtonState();

	// set the button current state
	void SetButtonState(Button_State state);

	// Set the right image according to the state
	void SetImage();

	// Executes the callback
	void Trigger();

	// Returns whether (x,y) is within the bounds of the button.
	bool HitTest(int x, int y);
};
