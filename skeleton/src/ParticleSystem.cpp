#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem() {
	for (ParticleGen* pg : particleGenerators) {
		for (Particle* p : pg->particles) {
			deleteParticle(p);
		}
	}

	for (ParticleGen* pg : particleGenerators){
		delete pg;
		pg = nullptr;
	}
	particleGenerators.clear();
}

void ParticleSystem::update(double t) {

	// GENERACION DE NUEVAS PARTICULAS
	for (ParticleGen* pg : particleGenerators) {
		if (pg != nullptr) {
			pg->generateP();
		}
	}

	// MANTENIMIENTO DE PARTICULAS EXISTENTES
	for (ParticleGen* pg : particleGenerators) {
		if (pg != nullptr && pg->isActive()) {
			for (Particle* p : pg->particles) {
				if (p != nullptr) { // daba problemas de que llamaba a integrates de particulas muertas
					p->integrate(t); // updatea particula.

					// si ha superado su lifetime o se ha salido del espacio de accion TODO (modificar espacio de accion)
					if (p->isDead() || (p->getPos().y >= ACTION_ZONE.y)) {
						// eliminamos del vector, deregistereamos, lo ponemos a nullptr y lo eliminamos.
						deleteParticle(p);
						pg->particles.erase(std::find(pg->particles.begin(), pg->particles.end(), p));
					}
				}
			}
		}
	}
}

void ParticleSystem::deleteParticle(Particle* p){
	DeregisterRenderItem(p->getRenderItem());
	delete p;
	p = nullptr;
}
