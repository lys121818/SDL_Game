#pragma once
#include "GameObject.h"
#include "Vector2.h"
class ImageObject : public GameObject
{
	// Transform of the object
	SDL_Rect m_transform;

	// Position
	Vector2 m_position;

	// Texture representing the appearance of this object
	SDL_Texture* m_pTexture;
public:
	ImageObject(SDL_Renderer* pRenderer, Vector2 position, const char* directory);
	~ImageObject();
	// Inherited via GameObject
	void Update(double deltatime) override;
	void Render(SDL_Renderer* pRenderer) override;
};

