#pragma once
#include <vector>
#include "GameSetting.h"
#include "GameObject.h"
#include "CollisionReferee.h"
#include "Textures.h"
class TiledMap
{
private:
	// Background information on start
	static constexpr int s_kBackgroundWidth = BACKGROUNDTILESIZE;
	static constexpr int s_kBackgroundHeight = BACKGROUNDTILESIZE;

	// Tiles
	std::vector<GameObject*> m_pTiles;

public:
	TiledMap();
	~TiledMap();

	// Tile Settings
	void Init(CollisionReferee* pReferee);

	// Render Tiles
	void Render(SDL_Renderer* pRenderer, Textures* pTexture);

	// Remove pointers
	void Delete();

private:
	void TileSettings(CollisionReferee* pReferee);
};

