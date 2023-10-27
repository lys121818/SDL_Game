#pragma once
#include "SDL.h"
#include <string>
#include <map>
#include "Vector2.h"

//==================================================================================================//
/// IMAGE COMPONENT
/// This is the Component for GameObject to render image from the sprite image
//==================================================================================================//


class ImageComponent
{
private:

	const char* m_pSpriteName;	// Image Location

	SDL_Rect* m_transform;	// Object location

	SDL_Rect* m_frameTransform;	// Area of sprite to render

	std::map<std::string, SDL_Rect*> m_allImages;	// Image Container
	
public:
	ImageComponent(const char* directory, SDL_Rect* transform);
	~ImageComponent();

	void Render(SDL_Renderer* pRenderer, SDL_Texture* ptexture);

	/// IMAGE FRAME
	// Store image to Image Container
	void AddImageFrame
	(
		std::string name,	// Name of the image
		int frameX, int frameY, // Position On Image Sprite
		int frameWidth, int frameHeight	// Size On Image Sprite
	);

	// Set image to render
	void SetImageFrame(std::string name);

private:
	// Image Sprite Settings
	void ImageSpriteSettings();

	void Destroy();

};

