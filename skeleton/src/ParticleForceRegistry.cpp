#include "ParticleForceRegistry.h"

ParticleForceRegistry::~ParticleForceRegistry() {
	for (Particle* p : particles) delete p;
	particles.clear();
	for (ForceGenerator* fg : forceGenerators) delete fg;
	forceGenerators.clear();
}

void ParticleForceRegistry::update(double t) {
	for (ForceGenerator* fg: forceGenerators){
		for (Particle* p : particles) {
			fg->updateForce(p, t);
		}
	}
}
