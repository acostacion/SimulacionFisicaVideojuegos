#include "SolidSphereGen.h"

SolidSphereGen::SolidSphereGen(physx::PxPhysics* physics, physx::PxScene* scene, physx::PxTransform spawnPos)
	: SolidGen(physics, scene, spawnPos){
}

void SolidSphereGen::generateS() {
	// mientras este activo y haya menos de 10 solidos...
	if (_isActive && _solids.size() < 10) {
		physx::PxRigidDynamic* sphere = _physics->createRigidDynamic(_spawnPos);
		physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(1));
		sphere->attachShape(*sphereShape);

		physx::PxRigidBodyExt::updateMassAndInertia(*sphere, 0.15);

		_scene->addActor(*sphere);
		_solids.push_back(sphere);

		RenderItem* item = new RenderItem(sphereShape, sphere, { 1, 0, 0, 1 });
		RegisterRenderItem(item);
	}
}
