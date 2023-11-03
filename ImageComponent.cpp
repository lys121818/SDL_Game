#include "ImageComponent.h"
#include "ImageDirectory.h"
#include <iostream>

ImageComponent::ImageComponent(const char* directory, SDL_Rect* transform)
	:
	m_pSpriteName(directory),
	m_transform(transform),
	m_frameTransform(nullptr)
{
	if(m_pSpriteName != nullptr)
		ImageSpriteSettings();
}

ImageComponent::~ImageComponent()
{
	Destroy();
}


void ImageComponent::Render(SDL_Renderer* pRenderer, SDL_Texture* ptexture)
{
	// error call when the image hasn't been set up
	if (m_frameTransform == nullptr)
	{
		std::cout << "[ImageComponent] CurrentImageFrame has not been set up! \n";
		return;
	}

	SDL_RenderCopy(pRenderer, ptexture, m_frameTransform, m_transform);
}

void ImageComponent::AddImageFrame(std::string name, int frameX, int frameY, int frameWidth, int frameHeight)
{

	// return when the frame is already created
	if (m_allImages.find(name) != m_allImages.end())
		return;
	// Pair to insert on map
	std::pair<std::string, SDL_Rect*> newImageFrame;

	/// SOURCE TRANSFORM
	SDL_Rect* imageTransform;

	// Source Position
	int positionX = frameX * frameWidth;
	int positionY = frameY * frameHeight;

	imageTransform = new SDL_Rect{ positionX, positionY, frameWidth, frameHeight };

	newImageFrame.first = name;
	newImageFrame.second = imageTransform;

	// Add to vector container
	m_allImages.insert(newImageFrame);

}

void ImageComponent::AddImageFrameByTransform(std::string name, int positionX, int positionY, int frameWidth, int frameHeight)
{

	// return when the frame is already created
	if (m_allImages.find(name) != m_allImages.end())
		return;
	// Pair to insert on map
	std::pair<std::string, SDL_Rect*> newImageFrame;

	/// SOURCE TRANSFORM
	SDL_Rect* imageTransform;

	imageTransform = new SDL_Rect{ positionX, positionY, frameWidth, frameHeight };

	newImageFrame.first = name;
	newImageFrame.second = imageTransform;

	// Add to vector container
	m_allImages.insert(newImageFrame);

}

void ImageComponent::SetImageFrame(std::string name)
{
	// if named image is exist -> set current frame to named image
	if (m_allImages.find(name) != m_allImages.end())
		m_frameTransform = m_allImages[name];

	// error call when the image is not found
	else
		std::cout << "The name: " << name << " does not exist\n";

}

// All the Sprite Image that are being used
void ImageComponent::ImageSpriteSettings()
{
	if (strcmp(m_pSpriteName, BACKGROUND) == 0)
	{
		AddImageFrame("BackGround",0,0,1000,750);
	}
	else if (strcmp(m_pSpriteName, TILES) == 0)
	{

		AddImageFrame("Ground1", 0, 0, 128, 128);
		AddImageFrame("Ground2", 1, 0, 128, 128);
		AddImageFrame("Ground3", 2, 0, 128, 128);

		AddImageFrame("FloatingGround1", 3, 0, 128, 128);
		AddImageFrame("FloatingGround2", 4, 0, 128, 128);
		AddImageFrame("FloatingGround3", 5, 0, 128, 128);

		AddImageFrame("MiddleUnderGround1", 0, 1, 128, 128);
		AddImageFrame("MiddleUnderGround2", 1, 1, 128, 128);
		AddImageFrame("MiddleUnderGround3", 2, 1, 128, 128);

		AddImageFrame("BottomUnderGround1", 0, 2, 128, 128);
		AddImageFrame("BottomUnderGround2", 1, 2, 128, 128);
		AddImageFrame("BottomUnderGround3", 2, 2, 128, 128);

		AddImageFrame("Ground1", 0, 0, 128, 128);
		AddImageFrame("Ground2", 1, 0, 128, 128);
		AddImageFrame("Ground3", 2, 0, 128, 128);

		AddImageFrame("Sky", 5, 2, 128, 128);
	}
	else if (strcmp(m_pSpriteName, OBJECTS) == 0)
	{
		AddImageFrame("SmallBush1", 0, 0, 64, 64);
		AddImageFrame("SmallBush2", 1, 0, 64, 64);

		AddImageFrame("Mushroom1", 2, 0, 64, 64);
		AddImageFrame("Mushroom2", 3, 0, 64, 64);

		AddImageFrame("BigBush1", 0, 1, 64, 128);
		AddImageFrame("BigBush2", 1, 1, 64, 128);

		AddImageFrame("Tree1", 2, 0, 128, 128);
		AddImageFrame("Tree2", 2, 1, 128, 128);



		AddImageFrame("Box", 0, 2, 64, 64);

		AddImageFrame("Sign1", 1, 2, 64, 64);
		AddImageFrame("Sign2", 2, 2, 64, 64);

		AddImageFrame("Rock", 3, 2, 64, 64);
	}
	else if (strcmp(m_pSpriteName, BUTTONS) == 0)
	{
		AddImageFrame("Normal", 0, 0, 100, 40);
		AddImageFrame("Hover", 1, 0, 100, 40);
		AddImageFrame("Disable", 0, 1, 100, 40);
		AddImageFrame("Click", 1, 1, 100, 40);
	}
	else if (strcmp(m_pSpriteName, WIN_STATE) == 0)
	{
		AddImageFrame("Win",0,0,750,1000);
	}
	else if (strcmp(m_pSpriteName, LOSS_STATE) == 0)
	{
		AddImageFrame("Loss", 0, 0, 750, 1000);
	}
	// UI
	else if (strcmp(m_pSpriteName, HEALTHUI) == 0)
	{
		AddImageFrameByTransform("Bar", 0, 0, 540, 121);
		AddImageFrameByTransform("Health_Long", 0, 150, 370, 53);
		AddImageFrameByTransform("BlankHealth", 0, 210, 366, 53);
		AddImageFrameByTransform("HealthSymbol", 400, 150, 115, 115);
		AddImageFrameByTransform("Health_Short", 0, 280, 51, 53);

	}
}

void ImageComponent::Destroy()
{
	for (auto& element : m_allImages)
	{
		delete element.second;
	}
}
