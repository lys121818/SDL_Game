#include "Fonts.h"
#include "ImageDirectory.h"
#include "Defines.h"
#include <iostream>

Fonts::Fonts()
{
}

Fonts::~Fonts()
{
}

void Fonts::PreloadFonts(size_t sceneNumber)
{
    // Destory the previous textures before Preload new Textures
    DestroyFonts();

    // PlatFormer
    switch ((int)sceneNumber)
    {
        // Main Menu
        case 0:
        {
            AddTTFToFonts(FONT1, 50);
            AddTTFToFonts(FONT2, 40);
            AddTTFToFonts(FONT3, 40);
            AddTTFToFonts(SANS, 40);
            break;
        }

        // Game Play
        case 1:
        {
            AddTTFToFonts(FONT2, 35);
            break;
        }

        // Win Screen
        case 2:
        {
            AddTTFToFonts(FONT2, 35);
            break;
        }
        // Loss Screen
        case 3:
        {
            AddTTFToFonts(FONT2, 35);
            break;
        }
        // CreditScene
        case 4:
        {
            AddTTFToFonts(FONT2, 20);
            AddTTFToFonts(FONT3, 40);
            AddTTFToFonts(SANS, 20);
            break;
        }
    default:
        break;
    }
}

TTF_Font* Fonts::GetFont(const char* name)
{
	if(m_mpFonts[name] == nullptr)
		std::cout << "[Fonts] There are no Font with name: " << name << std::endl;

	return m_mpFonts[name];
}

void Fonts::AddTTFToFonts(const char* name, size_t size)
{
	std::pair<const char*, TTF_Font*> fontFile;

	fontFile.first = name;

    fontFile.second = TTF_OpenFont(name, size);

    // Error when it fails to load the texture
    if (fontFile.second == nullptr)
    {
        std::cout << "[Fonts] Fonts loading failed Error: " << SDL_GetError();
    }
    m_mpFonts.insert(fontFile);
}

void Fonts::DestroyFonts()
{
	for (auto iter = m_mpFonts.begin(); iter != m_mpFonts.end(); ++iter)
	{
		TTF_CloseFont(iter->second);
	}
    m_mpFonts.clear();
}
