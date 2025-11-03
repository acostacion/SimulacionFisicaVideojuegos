#include "Projectile.h"

Projectile::Projectile(physx::PxVec3 pos, projectileType p, Vector4 color, integrateMode i, double size)
	:Particle(pos, physx::PxVec3(0.0f), 1.0, size, color, i) {

	// TODO: que se elimine el proyectil al cabo de un rato.

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
	setVel(GetCamera()->getDir() * auxVel);
}

