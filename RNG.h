#pragma once
#include <random>
#include <SDL.h>

class RNG
{
	/*
		Seed does not create used same seed in game
		but creates new seed every new start
	*/
public:
	// able to insert the seed on create
	RNG();
	RNG(unsigned int seed);
	~RNG();
	

public:
	float GetRandf(float min, float max);

	int GetRand(int min, int max);

	unsigned int GetSeed() { return m_seed; }

	void SetSeed(unsigned int seed) { m_seed = seed; }
private:
	std::mt19937 m_engine;
	std::random_device m_randomDevice;

	bool isNewSeed = true;

	unsigned int m_seed;


};