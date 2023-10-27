#pragma once
#include <vector>
#include "GameSetting.h"
#include "GameObject.h"
#include "CollisionReferee.h"
#include "Textures.h"
#include <fstream>
#include <iostream>
class TiledMap
{
private:
	struct MaxTiles
	{
		int m_x;
		int m_y;
	}m_maxTiles;

	// Background information on start
	static constexpr int s_kBackgroundWidth = BACKGROUNDTILESIZE;
	static constexpr int s_kBackgroundHeight = BACKGROUNDTILESIZE;



	// Tiles
	std::vector<GameObject*> m_pTiles;

	const char* m_fileName;
	std::ifstream m_txtFile;



public:
	TiledMap(const char* txtFile);
	~TiledMap();

	// Tile Settings
	void Init(CollisionReferee* pReferee);

	// Render Tiles
	void Render(SDL_Renderer* pRenderer, Textures* pTexture);

	// Remove pointers
	void Delete();


private:
	void SetTiledMapToTxt();

	void LoadTiledMapFromTxt(size_t* map);

	void TileSettings(CollisionReferee* pReferee);
};

