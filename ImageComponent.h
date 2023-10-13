#pragma once
#include "SDL.h"
#include <string>
#include <map>
#include "Vector2.h"
class ImageComponent
{
private:

	const char* m_pSpriteName;

	SDL_Rect* m_transform;	// object location on screen

	SDL_Rect* m_frameTransform;	// area of sprite to render

	std::map<std::string, SDL_Rect*> m_allImages;
	
public:
	ImageComponent(const char* directory, SDL_Rect* transform);
	~ImageComponent();

	void Update(double deltaTime);
	void Render(SDL_Renderer* pRenderer, SDL_Texture* ptexture);

	void AddImageFrame(std::string name, int frameX, int frameY, int frameWidth, int frameHeight);
	void SetImageFrame(std::string name);

private:
	void Destroy();

};

