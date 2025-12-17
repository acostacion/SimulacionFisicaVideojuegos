#include "SolidBoxGen.h"

SolidBoxGen::SolidBoxGen(physx::PxPhysics* physics, physx::PxScene* scene, physx::PxTransform spawnPos)
	: SolidGen(physics, scene, spawnPos) {
}

void SolidBoxGen::generateS() {
	// mientras este activo y haya menos de 10 solidos...
	if (_isActive && _solids.size() < 10) {
		physx::PxRigidDynamic* box = _physics->createRigidDynamic(_spawnPos);
		physx::PxShape* boxShape = CreateShape(physx::PxBoxGeometry(1, 1, 1));
		box->attachShape(*boxShape);

		physx::PxRigidBodyExt::updateMassAndInertia(*box, 0.15);

		_scene->addActor(*box);
		_solids.push_back(box);

		RenderItem* item = new RenderItem(boxShape, box, { 1, 0, 0, 1 });
		RegisterRenderItem(item);
	}
}
