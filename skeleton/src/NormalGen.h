#pragma once
#include "ParticleGen.h"
class NormalGen : public ParticleGen
{
public:
	NormalGen(Particle* modelP, physx::PxVec3 p);

	void generateP() override;

private:
	/* _u genera numeros aleatorios uniformemente distribuidos entre 0 y 1,
	 * sirve para generar variaciones en las propiedades de las particulas (pos, vel, dir...) */
	std::uniform_real_distribution<double> _u{ 0,1 };
};

