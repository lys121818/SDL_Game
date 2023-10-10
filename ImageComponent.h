#pragma once
#include "SDL.h"
class ImageComponent
{
private:
	const char* m_pName;
	SDL_Rect* m_transform;
public:
	ImageComponent(const char* directory, SDL_Rect* transform);
	~ImageComponent();

	void Update(double deltatime);
	void Render(SDL_Renderer* pRenderer, SDL_Texture* ptexture);



};

