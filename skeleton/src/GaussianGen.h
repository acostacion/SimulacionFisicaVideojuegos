#pragma once
#include "ParticleGen.h"
class GaussianGen : public ParticleGen
{
public:
	GaussianGen(Particle* modelP, physx::PxVec3 p);

	void generateP() override;
private:
	/* _d genera numeros aleatorios que siguen una distribución normal,
	 * sirve para crear pequenias variaciones centradas en un valor promedio (pos, vel...) */
	std::normal_distribution<double> _d{ 0, 1 };
};

