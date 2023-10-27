#pragma once
#include <SDL.h>

#include "GameObject.h"
#include "ImageComponent.h"
#include "Status.h"
#include "ButtonType.h"

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

	// Not Needed in this game object (considering of other ways to handle this)
	Status m_status;

	// Check if its on hover
	bool m_isOnHover;

	bool m_isAble;

	bool m_isClicked;
public:
	ButtonObject(SDL_Rect transform, const char* directory, const int index, Button_State type, const char* name = "UnNamed");
	~ButtonObject();
	
	void Update(double deltaTime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture);

	// Inherited via GameObject
	Status GetStatus() override { return m_status; }
	SDL_Rect GetTransform() override { return m_transform; }

	virtual const char* GetTextureName() { return m_pSpriteName; }

	bool GetAble() { return m_isAble; }

	bool GetClicked() { return m_isClicked; }

	void SetHover(bool isHover) { m_isOnHover = isHover; }

	void SetClick(bool isClick) { m_isClicked = isClick; }

private:
	void ButtonState();

	void SetButtonState(Button_State state);

	void SetImage();
};
