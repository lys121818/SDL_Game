#pragma once
#include "GameObject.h"
#include "ColorDefine.h"
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

    double m_Speed = 300;

    Vector2 m_position;

    // Current direction movement. -1 for left, 1for right.
    int m_directionX;
    int m_directionY;

    // Transform of the object
    SDL_Rect m_transform;

    // Texture representing the appearance of this object
    SDL_Texture* m_pTexture;

public:
    CubeColider(SDL_Renderer* pRenderer, Vector2 position);
    ~CubeColider();
    

    // Inherited via GameObject
    void Update(double deltaTime) override;

    void Render(SDL_Renderer* pRenderer) override;

    // Move object
    void SetPosition(Vector2 position);
    Vector2 GetPosition() { return m_position; }

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

