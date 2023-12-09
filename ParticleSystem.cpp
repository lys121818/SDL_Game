#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Vector2 centerPoint, int particleCount, float maxSpeed, float radious, bool isLoop)
	:
	m_kCenterPoint(centerPoint),
	m_kParticleCount(particleCount),
	m_kRadiusSqr(radious * radious),
	m_color(SDL_Color{BLACK}),
	m_isActive(true),
	m_isLoop(isLoop),
	m_size(1),
	m_remainingTime(0.0),
	m_pSpriteName(nullptr)
{

	m_vpParticles.reserve(m_kParticleCount);
	for (size_t i = 0; i < m_kParticleCount; ++i)
	{
		m_vpParticles.push_back(new Particle);
	}

	for (auto& particle : m_vpParticles)
	{
		// set poision to center
		particle->m_positionOffset = Vector2{ 0,0 };

		float rand_1 = m_rng.GetRandf(-1, 0);
		float rand_2 = m_rng.GetRandf(-1, 0);

		if (rand_1 < rand_2)
		{
			float temp = rand_1;
			rand_1 = rand_2;
			rand_2 = temp;

		}
		// Randomize velocities
		particle->m_velocity = Vector2{ rand_1,rand_2 } * maxSpeed;

	}
	
}

ParticleSystem::~ParticleSystem()
{
	for(auto& element : m_vpParticles)
		delete element;
}

void ParticleSystem::Update(double deltaTime)
{
	m_remainingTime += deltaTime;
	if (m_isActive)
	{
		std::vector<Particle*>::iterator iter;

		iter = m_vpParticles.begin();

		for (iter; iter < m_vpParticles.end(); ++iter)
		{
			(*iter)->m_positionOffset.m_x += (*iter)->m_velocity.m_x * (float)deltaTime;
			(*iter)->m_positionOffset.m_y += (*iter)->m_velocity.m_y * (float)deltaTime;

			if ((*iter)->m_positionOffset.SquareLength() >= m_kRadiusSqr)
			{
				if (m_isLoop)
				{
					(*iter)->m_positionOffset = Vector2{ 0,0 };
				}
				else
				{
					delete *iter;
					iter = m_vpParticles.erase(iter);
					break;
				}
			}
		}

		if (m_vpParticles.empty() )//|| m_remainingTime > s_kMaxParticleExistTime)
			m_isActive = false;
	}
}

void ParticleSystem::Render(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	if (m_isActive)
	{
		SDL_SetRenderDrawColor(pRenderer, m_color.r, m_color.g, m_color.b, m_color.a);

		std::vector<Particle*>::iterator iter;

		iter = m_vpParticles.begin();

		for (iter; iter < m_vpParticles.end(); ++iter)
		{
			// Get the particle position.
			Vector2& particlePosition = (*iter)->m_positionOffset;

			// Allocate an SDL_Rect with the transformations.
			SDL_Rect particleTransform
			{
				(int)m_kCenterPoint.m_x + particlePosition.m_x,
				(int)m_kCenterPoint.m_y + particlePosition.m_y,
				m_size,
				m_size
			};

			// Render as a rectangle.
			if (m_pSpriteName == nullptr)
			{
				SDL_RenderFillRect(pRenderer, &particleTransform);
			}
			else
			{
				SDL_RenderCopy(pRenderer, pTexture, nullptr, &particleTransform);
			}
		}

	}

}
