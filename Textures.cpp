#include "Textures.h"
#include "SDL_image.h" 
#include "Defines.h"
#include <iostream>
Textures::Textures(SDL_Renderer* pRenderer)
    : m_pRenderer(pRenderer)
{
}

Textures::~Textures()
{
    DestoryTextures();
}

void Textures::PreloadTextures(size_t sceneNumber)
{
    // Destory the previous textures before Preload new Textures
    DestoryTextures();
    switch ((int)sceneNumber)
    {
    case 1:
    {
        // Simple adding by using directory of the image
        // IMAGES
        AddImagesToTexture(BACKGROUND);
        AddImagesToTexture(PLAYER);
        AddImagesToTexture(BULLET);
        AddImagesToTexture(STATIONARY1);
        AddImagesToTexture(STATIONARY2);

        // IMAGE SPRITES
        AddImagesToTexture(TILES);      
        AddImagesToTexture(OBJECTS);       

        // ANIMATION SPRITES
        AddImagesToTexture(PUMPKIN);
        AddImagesToTexture(ZOMBIEMALE);
        AddImagesToTexture(ZOMBIEFEMALE);
        break;
    }
    default:
        break;
    }
}

void Textures::AddImagesToTexture(const char* name)
{
    std::pair<const char*, SDL_Texture*> imageTexture;  //Pair to pass inform to m_mpTextures
    // Add directory of image as key of texture
    imageTexture.first = name;

    // Load image
    SDL_Surface* pImageSurface = IMG_Load(imageTexture.first);

    // Error when it fails to load the image
    if (pImageSurface == nullptr)
    {
        std::cout << "Image loading failed Error: " << SDL_GetError() << std::endl;
    }
    // SDL_Surface -> SDL_Texture
    // Create texture from surface and save in pair
    imageTexture.second = SDL_CreateTextureFromSurface(m_pRenderer, pImageSurface);

    // Error when it fails to load the texture
    if (imageTexture.second == nullptr)
    {
        std::cout << "Texture loading failed Error: " << SDL_GetError();
    }
    // add to mpTextures when image and texture loading is successfully done
    m_mpTextures.insert(imageTexture);
    // Free surface from memory as it's no longer needed.
    SDL_FreeSurface(pImageSurface);
}

void Textures::DestoryTextures()
{
    for (auto iter = m_mpTextures.begin(); iter != m_mpTextures.end(); ++iter)
    {
        SDL_DestroyTexture(iter->second);
    }
}
