#pragma once
#include "GameObject.h"
#include "Vector2.h"
class ImageObject : public GameObject
{
	// Name Of the Object
	const char* m_pName;
	// Transform of the object
	SDL_Rect m_transform;

	// Position
	Vector2 m_position;

public:
	ImageObject(Vector2 position, int width, int height, const char* directory);
	~ImageObject();
	// Inherited via GameObject
	void Update(double deltatime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;
	SDL_Rect GetTransform() override { return m_transform; }
	const char* GetName() override { return m_pName; }

	// return current position of object
	Vector2 GetPosition() { return m_position; }

};

