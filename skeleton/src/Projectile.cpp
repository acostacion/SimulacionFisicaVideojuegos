#include "Projectile.h"

Projectile::Projectile(physx::PxVec3 pos, physx::PxVec3 dir, projectileType p, Vector4 color, integrateMode i, double size)
	:Particle(pos, physx::PxVec3(0.0), 1.0, size, color, i) {

	float auxVel;
	switch (p){
	case CANNONBULLET:
		auxVel = 250.0f;
		break;
	case TANKBULLET:
		auxVel = 1800.0f;
		break;
	case GUN:
		auxVel = 330.0f;
		break;
	case LASERBLASTER:
		auxVel = 300000000.0f;
		break;
	default:
		break;
	}

	// velocidad inicial
	setVel(dir * auxVel);
}

void Projectile::integrate(double t)
{
	Particle::integrate(t);

	// si ha superado su lifetime
	if (getLifeTime() > MAX_LIFE_TIME) {
		delete this;
	}
}

