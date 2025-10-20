#pragma once
#include "ParticleGen.h"
class GaussianGen : public ParticleGen
{
public:
	GaussianGen(physx::PxVec3 p, physx::PxVec3 v, physx::PxVec3 d);

	void generateP(std::vector<Particle*>& particles) override;
private:

	/* _d genera numeros aleatorios que siguen una distribución normal,
	 * sirve para crear pequenias variaciones centradas en un valor promedio (pos, vel...) */
	std::normal_distribution<double> _d{ 0, 1 };
};

