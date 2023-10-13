#include "ImageComponent.h"
#include <iostream>

ImageComponent::ImageComponent(const char* directory, SDL_Rect* transform)
	:m_pSpriteName(directory),
	 m_transform(transform),
	 m_frameTransform(nullptr)
{

}

ImageComponent::~ImageComponent()
{
	Destroy();
}

void ImageComponent::Update(double deltaTime)
{
}

void ImageComponent::Render(SDL_Renderer* pRenderer, SDL_Texture* ptexture)
{
	// error call when the image hasn't been set up
	if (m_frameTransform == nullptr)
	{
		std::cout << "CurrentImageFrame has not been set up! \n";
		return;
	}
	SDL_RenderCopy(pRenderer, ptexture, m_frameTransform, m_transform);
}

void ImageComponent::AddImageFrame(std::string name, int frameX, int frameY, int frameWidth, int frameHeight)
{
	// return when the frame is already created
	if (m_allImages.find(name) != m_allImages.end())
		return;
	int positionX = frameX * frameWidth;
	int positionY = frameY * frameHeight;
	std::pair<std::string, SDL_Rect*> newImageFrame;
	newImageFrame.first = name;
	newImageFrame.second = new SDL_Rect{ positionX, positionY, frameWidth, frameHeight };

	m_allImages.insert(newImageFrame);
}

void ImageComponent::SetImageFrame(std::string name)
{
	// if named image is exist -> set current frame to named image
	if(m_allImages.find(name) != m_allImages.end())
		m_frameTransform = m_allImages[name];
	// error call when the image is not found
	else
		std::cout << "The name: " << name << " does not exist\n";

}

void ImageComponent::Destroy()
{
	for (auto& element : m_allImages)
	{
		delete element.second;
	}
}
