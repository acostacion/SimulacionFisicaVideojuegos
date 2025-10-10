#pragma once
#include <random>
class ParticleGen
{
	virtual void generateP() = 0;

	// TODO: setters y getters pos, vel, dir, probGen
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _u{ 0,1 };	
};

