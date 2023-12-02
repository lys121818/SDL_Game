#include "RNG.h"
#include <iostream>
#include <string>

// Path of RNG text file
#define RNGTXT "assets/TxtFile/RNG.txt"

RNG::RNG(unsigned int seed)
{

	// random generate
	if (seed == -1)		// last digit in seed = do random seed
		m_seed = m_randomDevice();
	// insert specific seed
	else
		m_seed = seed;


	m_engine.seed(m_seed);

	std::cout << "Current Seed" << m_seed << std::endl;
}

RNG::~RNG()
{
}

float RNG::GetRandf(float min, float max)
{
    std::uniform_real_distribution<float> distributionf(1.0, 6.0);

	float randf = distributionf(m_engine);

	return randf;
}

int RNG::GetRand(int min, int max)
{
	std::uniform_int_distribution<int> distributionf(min, max);

	int rand = distributionf(m_engine);

	return rand;
}
