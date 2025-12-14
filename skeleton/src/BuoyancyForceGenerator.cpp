#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float V, float d)
	: _height(h), _volume(V), _liquid_density(d) {
	// particula q representa la superficie del agua
	_liquid_particle = new Particle(
		physx::PxVec3(0.0f, 0.0f, 0.0f),
		physx::PxVec3(0.0f),
		0.0,
		50.0,
		Vector4(0.0, 0.3, 1.0, 0.25),
		Particle::SEMIEULER,
		Particle::CUBE
	);
}

void BuoyancyForceGenerator::updateForce(Particle* p, double t) {
	float h = p->getPos().y;
	float h0 = _liquid_particle->getPos().y;

	physx::PxVec3 f = physx::PxVec3(0.0f);
	float immersed = 0.0;
	if (h - h0 > _height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > _height * 0.5) {
		// Totally immersed
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / _height + 0.5;
	}

	f.y = _liquid_density * _volume * immersed * 9.8;

	// esto es por lo de que haya varias fuerzas a la vez.
	p->setForce(p->getForce() + f);
}

BuoyancyForceGenerator::~BuoyancyForceGenerator() {
	delete _liquid_particle;
	_liquid_particle = nullptr;
}
