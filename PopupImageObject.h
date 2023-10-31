#pragma once
#include "GameObject.h"
#include "ImageComponent.h"

class PopupImageObject : public GameObject
{
private:
	Status m_status;

	// Speed of object poping out
	static constexpr int s_kSpeed = 50;

	// Max size of image
	static constexpr int s_kMaxWidth = 400;
	static constexpr int s_kMaxHeight = 300;


	// Name Of the Object
	const char* m_pSpriteName;

	// Transform of the object
	SDL_Rect m_transform;

	// Image position
	Vector2 m_position;


	// Image Component
	ImageComponent m_imageComponent;

	bool m_isPoping;
public:
	PopupImageObject(Vector2 position, const char* directory, const int index, size_t type, const char* name = "UnNamed");
	~PopupImageObject();



	// Inherited via GameObject
	// Update

	void Update(double deltaTime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

	// Move to the direction
	void TryMove(Vector2 direction);

	// GETTERS
	SDL_Rect GetTransform() override { return m_transform; }

	const char* GetTextureName() override { return m_pSpriteName; }

	// Return Name of the object
	virtual const char* GetName() { return "UnNamed"; }

	virtual Status GetStatus() override { return m_status; }


	// SETTERS
	virtual void SetPosition(Vector2 position) override;


private:
	void SetImage(const int index);

	void PopingImage(double deltaTime);
};

