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
			// particulas
			for (Particle* p : fg->particles) {
				fg->updateForce(p, t);
			}

			// solidos rigidos
			for (physx::PxRigidDynamic* s : fg->solids) {
				fg->updateForce(s, t);
			}
		}
	}
}
