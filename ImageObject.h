#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "ImageComponent.h"
class ImageObject : public GameObject
{
	// Name Of the Object
	const char* m_pSpriteName;
	// Transform of the object
	SDL_Rect m_transform;

	// Position
	Vector2 m_position;

	// Image Component
	ImageComponent m_imageComponent;

public:
	ImageObject(Vector2 position, int width, int height, const char* directory);
	~ImageObject();
	// Inherited via GameObject
	void Update(double deltatime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;
	SDL_Rect GetTransform() override { return m_transform; }
	const char* GetTextureName() override { return m_pSpriteName; }

	// Return Name of the object
	virtual const char* GetName() { return "UnNamed"; }

	// return current position of object
	Vector2 GetPosition() { return m_position; }

};

