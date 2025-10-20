#pragma once
#include "ParticleGen.h"
class GaussianGen : public ParticleGen
{
public:
	void generateP() override;

private:
	std::normal_distribution<double> _d{ 0, 1 };
};

