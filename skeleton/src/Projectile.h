#pragma once
#include "Particle.h"
class Projectile : public Particle{
public:
	enum projectileType {
		ANGRYBIRD,
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
};

