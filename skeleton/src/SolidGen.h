#pragma once
#include <vector>
#include <PxPhysicsAPI.h>

// nos basamos en la clase particlegen para crear esta.
// Clase padre ABSTRACTA para los Solid Generators hijos:
// - Box
// - Sphere
// - ...
class SolidGen {
public:
	SolidGen(physx::PxPhysics* physics, physx::PxScene* scene,physx::PxTransform spawnPos, bool active = true)
		: _physics(physics), _scene(scene), _spawnPos(spawnPos), _isActive(active) { }

	virtual ~SolidGen() {
		for (physx::PxRigidDynamic* s : _solids) {
			_scene->removeActor(*s);
			s->release();
		}
	}

	virtual void generateS() = 0;

	// getters/setters
	bool isActive() const { return _isActive; }
	void setActive(bool active) { _isActive = active; }


protected:
	physx::PxPhysics* _physics;
	physx::PxScene* _scene;

	physx::PxTransform _spawnPos;
	bool _isActive;

	std::vector<physx::PxRigidDynamic*> _solids;
};