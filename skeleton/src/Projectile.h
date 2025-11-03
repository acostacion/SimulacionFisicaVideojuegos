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
		projectileType p,
		Vector4 color = { 1.0, 0.0, 0.0, 1.0 },
		integrateMode i = EULER,
		double size = 5.0
	);
};

