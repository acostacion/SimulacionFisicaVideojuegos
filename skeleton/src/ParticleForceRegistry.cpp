#include "ParticleForceRegistry.h"

ParticleForceRegistry::~ParticleForceRegistry() {
	
	for (ForceGenerator* fg : forceGenerators) {
		delete fg;
		fg = nullptr;
	}
	forceGenerators.clear();
}

void ParticleForceRegistry::update() {
	for (ForceGenerator* fg: forceGenerators){
		for (Particle* p : fg->particles) {
			fg->updateForce(p);
		}
	}
}
