#include "TiledMap.h"
#include "ImageObject.h"
#include "ObjectType.h"
#include "ImageDirectory.h"

TiledMap::TiledMap(const char* txtFile)
    :m_fileName(txtFile)
{
    // count of tiles needed in width
    m_maxTiles.m_x = (WINDOWWIDTH / s_kBackgroundWidth);

    // count of tiles needed in height
    m_maxTiles.m_y = (WINDOWHEIGHT / s_kBackgroundHeight);
}

TiledMap::~TiledMap()
{
}

void TiledMap::Init(CollisionReferee* pReferee)
{
	TileSettings(pReferee);
}

void TiledMap::Render(SDL_Renderer* pRenderer, Textures* pTextures)
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
            element->Render(pRenderer, pTextures->GetTexture(element->GetTextureName()));
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

void TiledMap::SetTiledMapToTxt()
{
}

void TiledMap::LoadTiledMapFromTxt(size_t* map)
{
    m_txtFile.open(m_fileName);
    if (m_txtFile.is_open())
    {
        for (size_t y = 0; y < m_maxTiles.m_y; y++)
        {
            for (size_t x = 0; x < m_maxTiles.m_x; x++)
            {
                m_txtFile >> map[(y * m_maxTiles.m_x) + x];
            }
        }
    }
    else
    {
        std::cout << "The .txt file doen't exist.\nFile Name: " << m_fileName << std::endl;
    }

    m_txtFile.close();
}

void TiledMap::TileSettings(CollisionReferee* pReferee)
{
    // Set Background tiles
    Vector2 tilePosition{0.0,0.0};

    if constexpr (WINDOWWIDTH % s_kBackgroundWidth != 0)
        ++m_maxTiles.m_x;   // add extra if it's short

    if constexpr (WINDOWHEIGHT % s_kBackgroundHeight != 0)
        ++m_maxTiles.m_y;   // add extra if it's short

    size_t* map = new size_t[m_maxTiles.m_x * m_maxTiles.m_y] {0};

    // Load tiled map
    LoadTiledMapFromTxt(map);
    // x[27] y[20]

    for (size_t y = 0; y < m_maxTiles.m_y; y++)
    {
        for (size_t x = 0; x < m_maxTiles.m_x; x++)
        {
            std::cout << map[(y * m_maxTiles.m_x) + x] << " ";
        }
        std::cout << '\n';
    }

    //int tiles[m_maxTiles.m_x]
    // runs loop size of tiles needed for height
    for (int y = 0; y < m_maxTiles.m_y; ++y)
    {
        // runs loop size of tiles needed for width
        for (int x = 0; x < m_maxTiles.m_x; ++x)
        {
            size_t currentLocation = (static_cast<size_t>(y) * m_maxTiles.m_x) + x;
            /// TRANSFORM
            Vector2 position;
            Vector2 size;

            // Position
            position.m_x = x * s_kBackgroundWidth;
            position.m_y = y * s_kBackgroundHeight;

            // Size
            size.m_x = s_kBackgroundWidth;
            size.m_y = s_kBackgroundHeight;

            switch (map[currentLocation])
            {
                case 0 :
                {
                    break;
                }

                case (size_t)ObjectType::kWall:
                {
                    m_pTiles.push_back(new ImageObject(position,size, pReferee, OBJECTS , 8, (size_t)ObjectType::kWall, "Wall")); // tile index goes in here
                    break;
                }

                case (size_t)ObjectType::kGround:
                {
                    // at the very left or left is empty
                    if (x == 0 || (map[currentLocation - 1] == 0))
                    {
                        m_pTiles.push_back(new ImageObject(position,size, pReferee, TILES, 0, (size_t)ObjectType::kGround, "Ground")); // tile index goes in here

                    }
                    // at the very right or right is empty
                    else if (x == m_maxTiles.m_x - 1 || (map[currentLocation + 1] == 0))
                    {
                        m_pTiles.push_back(new ImageObject(position, size, pReferee, TILES, 2, (size_t)ObjectType::kGround, "Ground")); // tile index goes in here

                    }
                    else
                    {
                        m_pTiles.push_back(new ImageObject(position, size, pReferee, TILES, 1, (size_t)ObjectType::kGround, "Ground")); // tile index goes in here
                    }
                    break;
                }

                case (size_t)ObjectType::kWinZone:
                {
                    m_pTiles.push_back(new ImageObject(position, size, pReferee, OBJECTS, 9, (size_t)ObjectType::kWinZone, "Win Zone"));
                    break;
                }

                case (size_t)ObjectType::kHealingZone:
                {
                    m_pTiles.push_back(new ImageObject(position, size, pReferee, OBJECTS, 7, (size_t)ObjectType::kHealingZone, "Healing Zone"));
                    break;
                }

                case (size_t)ObjectType::kDamageZone:
                {

                    m_pTiles.push_back(new ImageObject(position, size, pReferee, OBJECTS, 6, (size_t)ObjectType::kDamageZone, "Damage Zone"));
                    break;
                }

            default:
                break;
            }

        }
    }
    delete[] map;
}
