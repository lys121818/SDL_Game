#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "RNG.h"
#include "ImageComponent.h"
#include <vector>

class ParticleSystem : public GameObject
{
	using Vector2 = Vector2<float>;
private:
	struct Particle
	{
		Vector2 m_positionOffset;
		Vector2 m_velocity;
	};

private:
	static constexpr double s_kMaxParticleExistTime = 5.0;

	// Particle cource center point.
	const Vector2 m_kCenterPoint;

	// Number of particles in this instance.
	const int m_kParticleCount;

	// Square of the maximum distance particles can travel before resetting.
	const float m_kRadiusSqr;

	const char* m_pSpriteName;

	//Array of particles.
	std::vector<Particle*> m_vpParticles;

	double m_remainingTime;

	int m_size;

	RNG m_rng;

	SDL_Color m_color;

	bool m_isActive;

	bool m_isLoop;
public:
	ParticleSystem(Vector2 centerPoint, int particleCount, float maxSpeed, float radious, bool isLoop);
	~ParticleSystem();

	// Gets called by the main loop each frame to update this object's state.
	virtual void Update(double deltaTime) override;

	// Gets called by the main loop each frame to render this object.
	virtual void Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture = nullptr) override;


	// [SETTERS]
	void SetColor(SDL_Color color) { m_color = color; }

	void SetSize(int size) { m_size = size; }

	virtual void SetActive(bool active) override { m_isActive = active; }

	void SetTextureName(const char* name) { m_pSpriteName = name; }

	// [GETTERS]
	virtual bool GetActive() override { return m_isActive; }

	virtual const char* GetTextureName() { if(m_pSpriteName) return m_pSpriteName; else return "No Name"; }

};

