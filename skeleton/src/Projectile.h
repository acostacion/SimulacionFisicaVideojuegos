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

private:
	const float EARTH_GRAVITY = 9.8f; // 9.8 m/(s^2) la gravedad es una aceleracion

	void setGravity(float g);
};

