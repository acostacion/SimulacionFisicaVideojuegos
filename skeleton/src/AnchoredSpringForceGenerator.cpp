#include "AnchoredSpringForceGenerator.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting, const physx::PxVec3& anchor_pos)
	: SpringForceGenerator(k, resting, (Particle*)nullptr),
	_pxphysics(nullptr), _pxscene(nullptr) {

	_otherParticle = new Particle(
		anchor_pos,
		physx::PxVec3(0.0f),
		1.0,
		1.0,
		Vector4(0.5, 0.5, 0.5, 1.0),
		Particle::SEMIEULER,
		Particle::CUBE
	);
}

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting, const physx::PxVec3& anchor_pos, physx::PxPhysics* physics, physx::PxScene* scene)
	: SpringForceGenerator(k, resting, (physx::PxRigidStatic*)nullptr),
	_pxphysics(physics), _pxscene(scene) {

	// anclaje solido rigido TODO hacer con solidos rigidos
	_otherSolid = _pxphysics->createRigidStatic(physx::PxTransform(anchor_pos));
	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(1.0, 1.0, 1.0));
	_otherSolid->attachShape(*shape);

	_pxscene->addActor(*_otherSolid);

	RenderItem* item = new RenderItem(shape, _otherSolid, Vector4(0.5, 0.5, 0.5, 1.0));
	RegisterRenderItem(item);
}
