#pragma once
#include <SDL.h>
#include <unordered_map>
class Textures
{
private:
	std::unordered_map<const char*, SDL_Texture*> m_mpTextures;
	SDL_Renderer* m_pRenderer;
public:
	Textures(SDL_Renderer* pRenderer);
	~Textures();

public:
	void PreloadTextures(size_t sceneNumber);

	SDL_Texture* GetTexture(const char* name);

private:
	void AddImagesToTexture(const char* name);
	void DestoryTextures();
};

