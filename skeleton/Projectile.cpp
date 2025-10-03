#include "Projectile.h"

Projectile::Projectile(physx::PxVec3 pos, projectileType p, integrateMode i, double size, Vector4 color)
	:Particle(pos, physx::PxVec3(0.0f), i, size, color) {
	// inicialmente pone gravedad de la tierra
	setGravity(EARTH_GRAVITY); 

	float auxVel;
	switch (p){
	case Projectile::CANNONBULLET:
		auxVel = 250.0f;
		break;
	case Projectile::TANKBULLET:
		auxVel = 1800.0f;
		break;
	case Projectile::GUN:
		auxVel = 330.0f;
		break;
	case Projectile::LASERBLASTER:
		auxVel = 300000000.0f;
		break;
	default:
		break;
	}

	// velocidad inicial
	setVel(GetCamera()->getDir() * auxVel);
}

void Projectile::setGravity(float g){
	setAccel(physx::PxVec3(0.0f, -g, 0.0f));
}
