#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
private:
	static constexpr int s_kSpeed = 800;
	static constexpr int s_kHeight = 10;
	static constexpr int s_kWidth = 10;

	const char* m_pSpriteName;
	// Transform of the object
	SDL_Rect m_transform;

	// Position
	Vector2 m_position;
public:
	Bullet(Vector2 position, const char* directory);
	~Bullet();
	// Inherited via GameObject
	void Update(double deltatime) override;
	void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;
	virtual const char* GetTextureName() override { return m_pSpriteName; }

	SDL_Rect GetTransform() override { return m_transform; }
};

