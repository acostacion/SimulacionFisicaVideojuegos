#pragma once
#include "ParticleGen.h"
class GaussianGen : public ParticleGen
{
public:
	std::normal_distribution<double> _d{ 0, 1 };
	void generateP() override;
};

