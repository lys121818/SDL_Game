#include "RNG.h"
#include <iostream>
#include <string>

// Path of RNG text file
#define RNGTXT "assets/TxtFile/RNG.txt"
RNG::RNG()
{
	m_seed = m_randomDevice();
	m_engine.seed(m_seed);
}
RNG::RNG(unsigned int seed)
{
	m_seed = seed;
	m_engine.seed(m_seed);
}

RNG::~RNG()
{
}

float RNG::GetRandf(float min, float max)
{
    std::uniform_real_distribution<float> distributionf(min,max);

	float randf = distributionf(m_engine);

	return randf;
}

int RNG::GetRand(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);

	int rand = distribution(m_engine);

	return rand;
}
