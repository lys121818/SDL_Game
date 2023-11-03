#pragma once
#include "GameObject.h"
#include "ImageComponent.h"
#include <SDL.h>

class UIObject : public GameObject
{
private:

	// position of the object
	SDL_Rect m_transform;

	// Image of the object
	ImageComponent m_image;

	// Name of the UI Image
	const char* m_pSpriteName;

	Status m_status;

public:
	UIObject(SDL_Rect transform, const char* spriteName, size_t index = 0);
	~UIObject();

	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture);

	// all the UI Image Setup here
	void SetUIImage(const int index);

	// Set transform
	void SetTransform(SDL_Rect transform) { m_transform = transform; }

	const char* GetTextureName() override { return m_pSpriteName; }

	// Inherited via GameObject
	Status GetStatus() override;

	SDL_Rect GetTransform() override;

};

