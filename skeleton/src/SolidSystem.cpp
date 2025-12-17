#include "SolidSystem.h"

SolidSystem::~SolidSystem() {
	for (SolidGen* sg : solidGenerators) {
		delete sg;
		sg = nullptr;
	}
	solidGenerators.clear();
}

void SolidSystem::update(double t) {
	for (SolidGen* sg : solidGenerators) {
		if (sg->isActive()) {
			sg->generateS();
		}
	}
}
