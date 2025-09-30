#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel, float size, Vector4 color)
: _pos(pos), _vel(vel), _size(size), _color(color)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(_size));
	const physx::PxTransform* tf = new physx::PxTransform(physx::PxVec3(_pos.getX(), _pos.getY(), _pos.getZ()));
	const Vector4 c = { _color.x, _color.y, _color.z, _color.w };

	_renderItem = new RenderItem(shape, tf, c);

	RegisterRenderItem(_renderItem);
}

Particle::~Particle() {
	DeregisterRenderItem(_renderItem);
}

void Particle::integrate(double t, integrateMode i){
	switch (i)
	{
	case EULER:
		integrateEuler(t);
		break;
	case SEMIEULER:
		break;
	case VERLET:
		break;
	default:
		break;
	}
}

void Particle::integrateEuler(double t){
	// POS_n+1 = POS_n + VEL_n * t
	_pos = _pos + _vel * t;

	// VEL_n+1 = VEL_n + a * t, a: acceleration
	_vel = _vel + _a * t;

	// damping
}
