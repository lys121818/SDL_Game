#pragma once
#include "GameObject.h"
#include "Defines.h"
#include "Vector2.h"
class CubeColider : public GameObject
{
private:
    // Width
    static constexpr int s_kWidth = 50;
    // Height
    static constexpr int s_kHeight = 50;
    // Speed
    static constexpr int s_kMaxSpeed = 500;
    static constexpr int s_kSpeed = 300;
    static constexpr int s_kMixSpeed = 100;

    // Name Of the Object
    const char* m_pName;

    double m_Speed = 300;

    Vector2 m_position;

    // Current direction movement. -1 for left, 1for right.
    int m_directionX;
    int m_directionY;

    // Transform of the object
    SDL_Rect m_transform;

    SDL_Texture* m_pTexture;

public:
    CubeColider(Vector2 position, const char* directory);
    ~CubeColider();
    

    // Inherited via GameObject
    void Update(double deltatime) override;

    void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) override;

    // return position of object
    Vector2 GetPosition() { return m_position; }
    // return the transform of object
    SDL_Rect GetTransform() override { return m_transform; }
    
    // Return Name of the object
    virtual const char* GetName() override { return m_pName; }

    // Move object
    void SetPosition(Vector2 position);

    // Sprint
    void SprintSpeed() { m_Speed = s_kMaxSpeed; }
    void NormalSpeed() { m_Speed = s_kSpeed; }
    void SlowSpeed() { m_Speed = s_kMixSpeed; }

    void MoveLeft() { --m_directionX; }
    void MoveRight() { ++m_directionX; }
    void MoveUp() { --m_directionY; }
    void MoveDown() { ++m_directionY; }

    void StopLeft() { ++m_directionX; }
    void StopRight() { --m_directionX; }
    void StopUp() { ++m_directionY; }
    void StopDown() { --m_directionY; }

};

