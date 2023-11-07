#include "Textures.h"
#include "SDL_image.h" 
#include "ImageDirectory.h"
#include <iostream>
Textures::Textures(SDL_Renderer* pRenderer)
    : m_pRenderer(pRenderer)
{
}

Textures::~Textures()
{
    DestroyTextures();
}

void Textures::PreloadTextures(size_t sceneNumber)
{
    // Destory the previous textures before Preload new Textures
    DestroyTextures();

    // PlatFormer
    switch ((int)sceneNumber)
    {
        // Main Menu
        case 0: 
        {
            AddImagesToTexture(BACKGROUND);
            AddImagesToTexture(BUTTONS);
            break;
        }

        // Game Play
        case 1:
        {
            // Simple adding by using directory of the image
            // IMAGES
            AddImagesToTexture(PLAYER);
            AddImagesToTexture(BACKGROUND);

            // IMAGE SPRITES
            AddImagesToTexture(TILES);      
            AddImagesToTexture(OBJECTS);       

            // ANIMATION SPRITES
            AddImagesToTexture(PUMPKIN);
            AddImagesToTexture(ZOMBIEMALE);
            AddImagesToTexture(ZOMBIEFEMALE);

            // UI SPRITES
            AddImagesToTexture(HEALTHUI);
            break;
        }

        // Win Screen
        case 2:
        {
            AddImagesToTexture(BACKGROUND);
            AddImagesToTexture(BUTTONS);
            AddImagesToTexture(WIN_STATE);
            break;
        }
        // Loss Screen
        case 3:
        {
            AddImagesToTexture(BACKGROUND);
            AddImagesToTexture(LOSS_STATE);
            AddImagesToTexture(BUTTONS);
            break;
        }
        // Credit Scene
        case 4:
        {
            AddImagesToTexture(BACKGROUND);

            break;
        }
    default:
        break;
    }
}

SDL_Texture* Textures::GetTexture(const char* name)
{
    if (m_mpTextures[name] == nullptr)
        std::cout << "[Textures] There are no Texture with name: " << name << std::endl;

    return m_mpTextures[name];
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
        std::cout << "[Textures] Image loading failed Error: " << SDL_GetError() << std::endl;
    }

    // SDL_Surface -> SDL_Texture
    // Create texture from surface and save in pair
    imageTexture.second = SDL_CreateTextureFromSurface(m_pRenderer, pImageSurface);

    // Error when it fails to load the texture
    if (imageTexture.second == nullptr)
    {
        std::cout << "[Textures] Texture loading failed Error: " << SDL_GetError();
    }
    // add to mpTextures when image and texture loading is successfully done
    m_mpTextures.insert(imageTexture);
    // Free surface from memory as it's no longer needed.
    SDL_FreeSurface(pImageSurface);
}

void Textures::DestroyTextures()
{
    for (auto iter = m_mpTextures.begin(); iter != m_mpTextures.end(); ++iter)
    {
        SDL_DestroyTexture(iter->second);
    }
    m_mpTextures.clear();
}
