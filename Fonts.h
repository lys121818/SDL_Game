#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
class Fonts
{
private:
	std::unordered_map<const char*, TTF_Font*> m_mpFonts;

	
public:
	Fonts();
	~Fonts();

	void PreloadFonts(size_t sceneNumber);

	TTF_Font* GetFont(const char* name);

private:
	void AddTTFToFonts(const char* name, size_t size);
	void DestroyFonts();

};

