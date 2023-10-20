#include "TiledMap.h"
#include "ImageObject.h"

TiledMap::TiledMap()
{
}

TiledMap::~TiledMap()
{
}

void TiledMap::Init(CollisionReferee* pReferee)
{
	TileSettings(pReferee);
}

void TiledMap::Render(SDL_Renderer* pRenderer, Textures* pTexture)
{

    //Render Background
    for (auto& element : m_pTiles)
    {
        // Only render inside the window size (on visible)
        if (element->GetTransform().x >= (0 - element->GetTransform().w) &&
            element->GetTransform().x < WINDOWWIDTH - 10 &&   // Window width
            element->GetTransform().y >= (0 - element->GetTransform().h) &&
            element->GetTransform().y < WINDOWHEIGHT - 10)    // Window height
        {
            element->Render(pRenderer, pTexture->GetTexture(element->GetTextureName()));
        }
    }

}

void TiledMap::Delete()
{
    for (auto& element : m_pTiles)
    {
        delete element;
    }
}

void TiledMap::TileSettings(CollisionReferee* pReferee)
{
    // Set Background tiles
    Vector2 tilePosition;

    // count of tiles needed in width
    int maxTilesX = (WINDOWWIDTH / s_kBackgroundWidth);

    // count of tiles needed in height
    int maxTilesY = (WINDOWHEIGHT / s_kBackgroundHeight);


    if (WINDOWWIDTH % s_kBackgroundWidth != 0)
        ++maxTilesX;   // add extra if it's short

    if (WINDOWHEIGHT % s_kBackgroundHeight != 0)
        ++maxTilesY;   // add extra if it's short

    // runs loop size of tiles needed for height
    for (int y = 0; y < maxTilesY; ++y)
    {
        // runs loop size of tiles needed for width
        for (int x = 0; x < maxTilesX; ++x)
        {
            int currentIndex = (y * maxTilesX) + x;

            /// TRANSFORM
            SDL_Rect tileTransform;

            // Position
            tileTransform.x = x * s_kBackgroundWidth;
            tileTransform.y = y * s_kBackgroundHeight;

            // Size
            tileTransform.w = s_kBackgroundWidth;
            tileTransform.h = s_kBackgroundHeight;


            // TODO: use fstream to Read From .txt file to set tilemap
            //       this is hard coding for testing out

            // Add tiles to vector
            // Background Tile Setting
            if (y % (maxTilesY - 1) == 0 || x % (maxTilesX - 1) == 0)
            {
                // bottom
                if (y == maxTilesY - 1)
                {
                    // left corner
                    if(x == 0)
                        m_pTiles.push_back(new ImageObject(tileTransform, pReferee, TILES, 0, Type::m_Ground)); // tile index goes in here
                    // right corner
                    else if(x == maxTilesX - 1)
                        m_pTiles.push_back(new ImageObject(tileTransform, pReferee, TILES, 2, Type::m_Ground)); // tile index goes in here

                    // bottom
                    m_pTiles.push_back(new ImageObject(tileTransform, pReferee, TILES, 1, Type::m_Ground)); // tile index goes in here

                }
                else
                    m_pTiles.push_back(new ImageObject(tileTransform, pReferee, OBJECTS, 8, Type::m_Wall)); // tile index goes in here


            }
            else if (y == 6 && (x <= 10 || x >= 15 ))
            {
                // left corner
                if (x == 0)
                    m_pTiles.push_back(new ImageObject(tileTransform, pReferee, TILES, 0, Type::m_Ground)); // tile index goes in here
                // right corner
                else if (x == maxTilesX - 1)
                    m_pTiles.push_back(new ImageObject(tileTransform, pReferee, TILES, 2, Type::m_Ground)); // tile index goes in here

                // bottom
                m_pTiles.push_back(new ImageObject(tileTransform, pReferee, TILES, 1, Type::m_Ground)); // tile index goes in here

            }
            else if (y == 13 && (x >= 25))
            {
                m_pTiles.push_back(new ImageObject(tileTransform, pReferee, TILES, 1, Type::m_Ground)); // tile index goes in here

            }
            else if (y == 5 && (x == 10 || x == 15))
            {
                m_pTiles.push_back(new ImageObject(tileTransform, pReferee, OBJECTS, 8, Type::m_Wall)); // tile index goes in here

            }
            else
                m_pTiles.push_back(new ImageObject(tileTransform, pReferee, TILES, 3, Type::m_BackGround)); // tile index goes in here
        }
    }

}
