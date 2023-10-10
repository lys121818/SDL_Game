#include "ImageComponent.h"

ImageComponent::ImageComponent(const char* directory, SDL_Rect* transform)
	:m_pName(directory),
	 m_transform(transform)
{
}

ImageComponent::~ImageComponent()
{
}

void ImageComponent::Update(double deltatime)
{
}

void ImageComponent::Render(SDL_Renderer* pRenderer, SDL_Texture* ptexture)
{
	SDL_RenderCopy(pRenderer, ptexture, nullptr, m_transform);
}
