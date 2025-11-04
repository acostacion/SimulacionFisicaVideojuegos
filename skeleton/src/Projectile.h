#pragma once
#include "Particle.h"
class Projectile : public Particle{
public:
	enum projectileType {
		CANNONBULLET,
		TANKBULLET,
		GUN,
		LASERBLASTER
	};

	Projectile(
		physx::PxVec3 pos,
		physx::PxVec3 dir,
		projectileType p,
		Vector4 color = { 1.0, 0.0, 0.0, 1.0 },
		integrateMode i = SEMIEULER,
		double size = 5.0
	);

	void integrate(double t) override;

private:
	// TIEMPO DE VIDA maximo que puede vivir una particula.
	const int MAX_LIFE_TIME = 200; // cada x llamadas al update...MAX_LIFE_TIME)
};

