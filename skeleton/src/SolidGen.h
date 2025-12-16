#pragma once
#include <vector>
#include <PxPhysicsAPI.h>

// nos basamos en la clase particlegen para crear esta.
// Clase padre ABSTRACTA para los Solid Generators hijos:
// - ...
class SolidGen {
public:
	SolidGen(physx::PxPhysics* physics, physx::PxScene* scene, bool active = true)
		: _physics(physics), _scene(scene), _isActive(active) { }

	virtual ~SolidGen();

	virtual void generateS() = 0;

	// getters/setters
	bool isActive() const { return _isActive; }
	void setActive(bool active) { _isActive = active; }


protected:
	physx::PxPhysics* _physics;
	physx::PxScene* _scene;

	bool _isActive;
};