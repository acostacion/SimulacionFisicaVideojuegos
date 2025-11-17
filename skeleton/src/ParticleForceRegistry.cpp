#include "ParticleForceRegistry.h"

ParticleForceRegistry::~ParticleForceRegistry() {
	
	for (ForceGenerator* fg : forceGenerators) {
		delete fg;
		fg = nullptr;
	}
	forceGenerators.clear();
}

void ParticleForceRegistry::update(double t) {
	for (ForceGenerator* fg: forceGenerators){
		if (fg->isActive()){
			for (Particle* p : fg->particles) {
				fg->updateForce(p, t);
			}
		}
	}
}
